

#include "TextureMaterial.hpp"
#include "glm.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"
#include "../_vs2015/GLLight.hpp"
#include "mge/core/AbstractGame.hpp"
#include "../_vs2015/Level.h"
#include "../_vs2015/TextureMovingMaterial.h"
#include "../_vs2015/PlayerController.hpp"
#include "mge/core/Camera.hpp"
ShaderProgram* TextureMaterial::_shader = NULL;

float TextureMaterial::heightmapTiling = 1;
float TextureMaterial::heightmapSpeed = 0.0;
float TextureMaterial::maxXOff = 50;
float TextureMaterial::xOffsetSmootness = 3;
float TextureMaterial::maxHeight = 10;
float TextureMaterial::genOffset = 100;
float TextureMaterial::width = 8;

float TextureMaterial::xMoveTiling = 100;
Texture* TextureMaterial::_heightMap = nullptr;

glm::vec3 TextureMaterial::fogColor = glm::vec3(0.5);
float TextureMaterial::fogBegin = 50;
float TextureMaterial::fogEnd = 75;
float TextureMaterial::fogBlendSmoothness = 2;

GLint TextureMaterial::_fogColor = 0;
GLint TextureMaterial::_fogBegin = 0;
GLint TextureMaterial::_fogEnd = 0;
GLint TextureMaterial::_fogBlendSmoothness = 0;

GLint TextureMaterial::_xMoveTiling = 0;
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
GLint TextureMaterial::_aBitangents = 0;
GLint TextureMaterial::_aTangents = 0;
GLLight TextureMaterial::_lightLocations[8];
GLint TextureMaterial::_lightCount = 0;
GLint TextureMaterial::_shininess = 0;
GLint TextureMaterial::_time = 0;
GLint TextureMaterial::_heightTexID = 0;
GLint TextureMaterial::_maxHeight = 0;
GLint TextureMaterial::_width = 0;
GLint TextureMaterial::_genOffset = 0;
GLint TextureMaterial::_maxXOff = 0;
GLint TextureMaterial::_xOffsetSmootness = 0;
GLint TextureMaterial::_heightMapSpeed = 0;
GLint TextureMaterial::_camPos = 0;


TextureMaterial::TextureMaterial(Texture * pDiffuseTexture, Texture* emmissiveTexture, Texture* specularTexture, float shininess, float colorTextureBlending, float blendSmoothing, float colorTilin, Texture* heightMap) :_diffuseTexture(pDiffuseTexture) {
	_emmissiveTexture = emmissiveTexture;
	_specularTexture = specularTexture;
	if (heightMap != nullptr)_heightMap = heightMap;
	this->shininess = shininess;
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

		_fogColor = _shader->getUniformLocation("fogColor");
		_fogBegin = _shader->getUniformLocation("fogBegin");
		_fogEnd = _shader->getUniformLocation("fogEnd");
		_fogBlendSmoothness = _shader->getUniformLocation("fogBlendSmoothness");




		_lightCount = _shader->getUniformLocation("lightCount");
		_shininess = _shader->getUniformLocation("shininess");
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

		_xMoveTiling = _shader->getUniformLocation("xMoveTiling");

		
		_time = _shader->getUniformLocation("time");
		
		_width = _shader->getUniformLocation("hwm");
		_genOffset = _shader->getUniformLocation("genOffset");
		
		_heightMapTiling = _shader->getUniformLocation("heightMapTiling");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
		_aTangents = _shader->getAttribLocation("tangents");
		_aBitangents = _shader->getAttribLocation("bitangent");
		_camPos = _shader->getUniformLocation("cameraPosition");
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

void TextureMaterial::render(int pass, World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (pass != 0 || !_diffuseTexture) return;

	_shader->use();

	//Print the number of lights in the scene and the position of the first light.
	//It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
	//if (pWorld->getLightCount() > 0) {
	//    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
	//}

	glm::vec3 camPos = (AbstractGame::instance->_world->getMainCamera())->getWorldPosition();
	glUniform3f(_camPos, camPos.x, camPos.y, camPos.z);



	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(_uDiffuseTexture, 0);

	glUniform1f(_genOffset, TextureMaterial::genOffset);
	glUniform1f(_width, TextureMaterial::width);
	glUniform1f(_xMoveTiling, TextureMaterial::xMoveTiling);
	if (_heightMap != nullptr)
	{
		//setup texture slot 0
		glActiveTexture(GL_TEXTURE1);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, _heightMap->getId());
		//tell the shader the texture slot for the diffuse texture is slot 0
		glUniform1i(_heightTexID, 1);

		glUniform1f(_maxHeight, TextureMaterial::maxHeight);
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


	glUniform1f(_heightMapSpeed, TextureMaterial::heightmapSpeed);
	glUniform1f(_heightMapTiling, TextureMaterial::heightmapTiling);

	glUniform1f(_xOffsetSmootness, TextureMaterial::xOffsetSmootness);
	glUniform1f(_maxXOff, TextureMaterial::maxXOff);

	glUniform3f(_fogColor, fogColor.x, fogColor.y, fogColor.z);
	glUniform1f(_fogBegin, fogBegin);
	glUniform1f(_fogEnd, fogEnd);
	glUniform1f(_fogBlendSmoothness, fogBlendSmoothness);


	glUniform1f(_shininess, shininess);

	glUniform1f(_time, AbstractGame::instance->GetTimeSinceStartup());

	glUniform1i(_lightCount, pWorld->getLightCount());
	for (int i = 0; i < pWorld->getLightCount(); i++)
	{
		
		_lightLocations[i].SetLight(&pWorld->getLightAt(i)->GetParams());
	}


	for (int i = 0; i < colors->length(); i++)
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
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV,_aTangents, _aBitangents);
}
