

#include "TextureMaterial.hpp"
#include "glm.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"
#include "../_vs2015/GLLight.hpp"

ShaderProgram* TextureMaterial::_shader = NULL;

GLint TextureMaterial::_uMMatrix = 0;
GLint TextureMaterial::_uVMatrix = 0;
GLint TextureMaterial::_uPMatrix = 0;
GLint TextureMaterial::_uDiffuseTexture = 0;

GLint TextureMaterial::_aVertex = 0;
GLint TextureMaterial::_aNormal = 0;
GLint TextureMaterial::_aUV = 0;
GLLight TextureMaterial::_lightLocations[8];
GLint TextureMaterial::_lightCount = 0;
GLint TextureMaterial::_shininess = 0;
GLint TextureMaterial::_steps = 0;

TextureMaterial::TextureMaterial(Texture * pDiffuseTexture, float shininess, int steps) :_diffuseTexture(pDiffuseTexture) {
	this->shininess = shininess;
	this->steps = steps;
	_offset = offset;
	offset += 4;
	_lazyInitializeShader();
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::_lazyInitializeShader() {
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "texture.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "texture.fs");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		_uMMatrix = _shader->getUniformLocation("modelMatrix");
		_uVMatrix = _shader->getUniformLocation("viewMatrix");
		_uPMatrix = _shader->getUniformLocation("projectionMatrix");
		_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
		_lightCount = _shader->getUniformLocation("lightCount");
		_shininess = _shader->getUniformLocation("shininess");
		_steps = _shader->getUniformLocation("steps");
		//Light Locations
		for (size_t i = 0; i < 8; i++)
		{
			_lightLocations[i] = GLLight(
				_shader->getUniformLocation("lights[" + std::to_string(i) + "].type"),
				_shader->getUniformLocation("lights[" + std::to_string(i) + "].intensity"),
				_shader->getUniformLocation("lights[" + std::to_string(i) + "].attenuation"),
				_shader->getUniformLocation("lights[" + std::to_string(i) + "].position"),
				_shader->getUniformLocation("lights[" + std::to_string(i) + "].color"),
				_shader->getUniformLocation("lights[" + std::to_string(i) + "].ambientColor")
			);
		}

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
	}
}

void TextureMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
	_diffuseTexture = pDiffuseTexture;
}

static glm::vec3 colors[8] =
{
	glm::vec3(1,0,0),
	glm::vec3(0.75,0.25,0),
	glm::vec3(0.5,0.5,0),
	glm::vec3(0.25,0.75,0),
	glm::vec3(0,1,0),
	glm::vec3(0,0.75,0.25),
	glm::vec3(0,0.5,0.5),
	glm::vec3(0,0,1),

};

int TextureMaterial::offset = 0;

void TextureMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (!_diffuseTexture) return;

	_shader->use();

	//Print the number of lights in the scene and the position of the first light.
	//It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
	//if (pWorld->getLightCount() > 0) {
	//    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
	//}

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(_uDiffuseTexture, 0);

	glUniform1f(_shininess, shininess);
	glUniform1i(_steps, steps);

	glUniform1i(_lightCount, pWorld->getLightCount());
	for (int i = 0; i < pWorld->getLightCount(); i++)
	{
		
		_lightLocations[i].SetLight(&pWorld->getLightAt(i)->GetParams());
	}

	for (size_t i = 0; i < 8; i++)
	{
		int index = (i + _offset) % 8;
		glUniform3f(_shader->getUniformLocation("colors[" + std::to_string(i) + "]"), colors[index].x, colors[index].y, colors[index].z);
	}

	//pass in a precalculate mvp matrix (see texture material for the opposite)
	//glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_uPMatrix, 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_uVMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_uMMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
