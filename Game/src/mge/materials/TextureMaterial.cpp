

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
#include "mge/core/AbstractGame.hpp"
#include "../_vs2015/Level.h"
#include "../_vs2015/TextureMovingMaterial.h"
ShaderProgram* TextureMaterial::_shader = NULL;

float TextureMaterial::heightmapTiling = 1.6;
float TextureMaterial::heightmapSpeed = 0.2;
float TextureMaterial::maxXOff = 50;
float TextureMaterial::xOffsetSmootness = 2;
Texture* TextureMaterial::_heightMap = nullptr;

GLint TextureMaterial::_heightMapTiling = 0;

GLint TextureMaterial::_uMMatrix = 0;
GLint TextureMaterial::_uVMatrix = 0;
GLint TextureMaterial::_uPMatrix = 0;
GLint TextureMaterial::_uDiffuseTexture = 0;
GLint TextureMaterial::_uEmmissiveTexture = 0;
GLint TextureMaterial::_uSpecularTexture = 0;

GLint TextureMaterial::_aVertex = 0;
GLint TextureMaterial::_aNormal = 0;
GLint TextureMaterial::_aUV = 0;
GLLight TextureMaterial::_lightLocations[8];
GLint TextureMaterial::_lightCount = 0;
GLint TextureMaterial::_shininess = 0;
GLint TextureMaterial::_steps = 0;
GLint TextureMaterial::_time = 0;
GLint TextureMaterial::_heightTexID = 0;
GLint TextureMaterial::_maxHeight = 0;
GLint TextureMaterial::_width = 0;
GLint TextureMaterial::_genOffset = 0;
GLint TextureMaterial::_maxXOff = 0;
GLint TextureMaterial::_xOffsetSmootness = 0;
GLint TextureMaterial::_movingspeed = 0;
GLint TextureMaterial::_heightMapSpeed = 0;

GLint TextureMaterial::_blend = 0;
GLint TextureMaterial::_blendingSoftness = 0;
GLint TextureMaterial::_colorCount = 0;
GLint TextureMaterial::_colorTiling = 0;

TextureMaterial::TextureMaterial(Texture * pDiffuseTexture, Texture* emmissiveTexture, Texture* specularTexture, float shininess, int steps, float colorTextureBlending, float blendSmoothing, float colorTilin, Texture* heightMap) :_diffuseTexture(pDiffuseTexture) {
	maxHeight = 5;
	_emmissiveTexture = emmissiveTexture;
	_specularTexture = specularTexture;
	if (heightMap != nullptr)_heightMap = heightMap;
	width = 8;
	genOffset = 150;
	maxXOff = 50;
	this->shininess = shininess;
	this->steps = steps;
	blend = colorTextureBlending;
	blendingSoftness = blendSmoothing;
	colorTiling = colorTilin;
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

		_heightMapSpeed = _shader->getUniformLocation("heightMapSpeed");


		_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
		_uSpecularTexture = _shader->getUniformLocation("specularTexture");

		_uEmmissiveTexture = _shader->getUniformLocation("emissiveTexture");
		_heightTexID = _shader->getUniformLocation("yOffTexture");
		_maxHeight = _shader->getUniformLocation("maxHeight");



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
		_movingspeed = _shader->getUniformLocation("movingspeed");
		_heightMapTiling = _shader->getUniformLocation("heightMapTiling");

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
	glm::vec3(0,1,0),
	glm::vec3(0,0,1),
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

	glUniform1f(_genOffset, genOffset);
	glUniform1f(_width, width);

	if (_heightMap != nullptr)
	{
		//setup texture slot 0
		glActiveTexture(GL_TEXTURE1);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, _heightMap->getId());
		//tell the shader the texture slot for the diffuse texture is slot 0
		glUniform1i(_heightTexID, 1);

		glUniform1f(_maxHeight, maxHeight);
	}

	if (_emmissiveTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _emmissiveTexture->getId());
		glUniform1i(_uEmmissiveTexture, 2);
	}	

	if (_specularTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _specularTexture->getId());
		glUniform1i(_uSpecularTexture, 3);
	}

	glUniform1f(_movingspeed, TextureMovingMaterial::Movingspeed);

	glUniform1f(_heightMapSpeed, TextureMaterial::heightmapSpeed);
	glUniform1f(_heightMapTiling, TextureMaterial::heightmapTiling);

	glUniform1f(_xOffsetSmootness, xOffsetSmootness);
	glUniform1f(_maxXOff, glm::sin(AbstractGame::instance->GetTimeSinceStartup()/5)*maxXOff);

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
