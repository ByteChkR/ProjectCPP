

#include "TextureMovingMaterial.h"
#include "mge/materials/TextureMaterial.hpp"
#include "glm.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"
#include "../_vs2015/GLLight.hpp"
#include "mge/core/AbstractGame.hpp"
#include "../_vs2015/Level.h"
ShaderProgram* TextureMovingMaterial::_shader = NULL;

float TextureMovingMaterial::Movingspeed = 0.3f;
GLint TextureMovingMaterial::_uMMatrix = 0;
GLint TextureMovingMaterial::_uVMatrix = 0;
GLint TextureMovingMaterial::_uPMatrix = 0;
GLint TextureMovingMaterial::_uDiffuseTexture = 0;

GLint TextureMovingMaterial::_aVertex = 0;
GLint TextureMovingMaterial::_aNormal = 0;
GLint TextureMovingMaterial::_aUV = 0;
GLLight TextureMovingMaterial::_lightLocations[8];
GLint TextureMovingMaterial::_lightCount = 0;
GLint TextureMovingMaterial::_shininess = 0;
GLint TextureMovingMaterial::_steps = 0;
GLint TextureMovingMaterial::_time = 0;
GLint TextureMovingMaterial::_heightTexID = 0;
GLint TextureMovingMaterial::_maxHeight = 0;
GLint TextureMovingMaterial::_width = 0;
GLint TextureMovingMaterial::_genOffset = 0;
GLint TextureMovingMaterial::_maxXOff = 0;
GLint TextureMovingMaterial::_xOffsetSmootness = 0;

GLint TextureMovingMaterial::_blend = 0;
GLint TextureMovingMaterial::_blendingSoftness = 0;
GLint TextureMovingMaterial::_colorCount = 0;
GLint TextureMovingMaterial::_colorTiling = 0;
GLint TextureMovingMaterial::_movingspeed = 0;

TextureMovingMaterial::TextureMovingMaterial(Texture * pDiffuseTexture, float shininess, int steps, float colorTextureBlending, float blendSmoothing, float colorTilin) :_diffuseTexture(pDiffuseTexture) {
	maxHeight = 8;
	width = 8;
	genOffset = 150;
	this->shininess = shininess;
	this->steps = steps;
	blend = colorTextureBlending;
	blendingSoftness = blendSmoothing;
	colorTiling = colorTilin;
	_offset = offset;
	offset += 4;
	_lazyInitializeShader();

}

TextureMovingMaterial::~TextureMovingMaterial() {}

void TextureMovingMaterial::_lazyInitializeShader() {
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "texture.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "texturemoving.fs");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		_uMMatrix = _shader->getUniformLocation("modelMatrix");
		_uVMatrix = _shader->getUniformLocation("viewMatrix");
		_uPMatrix = _shader->getUniformLocation("projectionMatrix");


		_heightTexID = _shader->getUniformLocation("yOffTexture");
		_maxHeight = _shader->getUniformLocation("maxHeight");

		_movingspeed = _shader->getUniformLocation("movingspeed");

		_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
		_lightCount = _shader->getUniformLocation("lightCount");
		_shininess = _shader->getUniformLocation("shininess");
		_steps = _shader->getUniformLocation("steps");
		_maxXOff = _shader->getUniformLocation("maxXOffset");
		_xOffsetSmootness = _shader->getUniformLocation("xOffsetSmoothness");

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

		//Color;
		_colorCount = _shader->getUniformLocation("colorCount");
		_colorTiling = _shader->getUniformLocation("colorTiling");
		_blend = _shader->getUniformLocation("textureBlend");
		_blendingSoftness = _shader->getUniformLocation("blendSmoothing");
		_time = _shader->getUniformLocation("time");

		_width = _shader->getUniformLocation("hwm");
		_genOffset = _shader->getUniformLocation("genOffset");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
	}
}

void TextureMovingMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
	_diffuseTexture = pDiffuseTexture;
}

static glm::vec3 colors[8] =
{
	glm::vec3(1,0,0),
	glm::vec3(0,1,0),
	glm::vec3(0,0,1),
	glm::vec3(0.25,0.75,0),
	glm::vec3(0,1,0),
	glm::vec3(0,0.75,0.25),
	glm::vec3(0,0.5,0.5),
	glm::vec3(0,0,1),

};

int TextureMovingMaterial::offset = 0;

void TextureMovingMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (!_diffuseTexture) return;

	_shader->use();

	//Print the number of lights in the scene and the position of the first light.
	//It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
	//if (pWorld->getLightCount() > 0) {
	//    std::cout << "TextureMovingMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
	//}

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(_uDiffuseTexture, 0);

	glUniform1f(_genOffset, genOffset);
	glUniform1f(_width, width);
	glUniform1f(_movingspeed, Movingspeed);

	if (TextureMaterial::_heightMap != nullptr)
	{
		//setup texture slot 0
		glActiveTexture(GL_TEXTURE1);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, TextureMaterial::_heightMap->getId());
		//tell the shader the texture slot for the diffuse texture is slot 0
		glUniform1i(_heightTexID, 1);

		glUniform1f(_maxHeight, maxHeight);
	}

	glUniform1f(_xOffsetSmootness, TextureMaterial::xOffsetSmootness);
	glUniform1f(_maxXOff, glm::sin(AbstractGame::instance->GetTimeSinceStartup() / 5)*TextureMaterial::maxXOff);

	glUniform1f(_shininess, shininess);
	glUniform1i(_steps, steps);

	glUniform1f(_time, AbstractGame::instance->GetTimeSinceStartup());

	glUniform1i(_lightCount, pWorld->getLightCount());
	for (int i = 0; i < pWorld->getLightCount(); i++)
	{

		_lightLocations[i].SetLight(&pWorld->getLightAt(i)->GetParams());
	}

	glUniform1i(_colorCount, 3);
	glUniform1f(_colorTiling, colorTiling);
	glUniform1f(_blend, blend);
	glUniform1f(_blendingSoftness, blendingSoftness);

	for (size_t i = 0; i < colors->length(); i++)
	{
		int index = (i + _offset) % colors->length();
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
