

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
#include "../_vs2015/PlayerController.hpp"
#include "mge/core/Camera.hpp"
ShaderProgram* TextureMovingMaterial::_shader = NULL;

float TextureMovingMaterial::Movingspeed = 0.13f;
GLint TextureMovingMaterial::_heightMapTiling = 0;
GLint TextureMovingMaterial::_uMMatrix = 0;
GLint TextureMovingMaterial::_uVMatrix = 0;
GLint TextureMovingMaterial::_uPMatrix = 0;
GLint TextureMovingMaterial::_uDiffuseTexture = 0;
GLint TextureMovingMaterial::_uEmmissiveTexture = 0;
GLint TextureMovingMaterial::_uSpecularTexture = 0;
GLint TextureMovingMaterial::_uNormalTexture = 0;

GLint TextureMovingMaterial::_aVertex = 0;
GLint TextureMovingMaterial::_aNormal = 0;
GLint TextureMovingMaterial::_aUV = 0;
GLint TextureMovingMaterial::_aBitangents = 0;
GLint TextureMovingMaterial::_aTangents = 0;
GLLight TextureMovingMaterial::_lightLocations[8];
GLint TextureMovingMaterial::_lightCount = 0;
GLint TextureMovingMaterial::_shininess = 0;
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
GLint TextureMovingMaterial::_xMoveTiling = 0;
GLint TextureMovingMaterial::_heightMapSpeed = 0;
GLint TextureMovingMaterial::_playerPos = 0;
float TextureMovingMaterial::ShadowSize = 1;
float TextureMovingMaterial::ShadowLength = 2;
GLint TextureMovingMaterial::_shadowLength = 0;
GLint TextureMovingMaterial::_shadowSize = 0;
GLint TextureMovingMaterial::_camPos = 0;


TextureMovingMaterial::TextureMovingMaterial(Texture* pDiffuseTexture, Texture* emmissiveTexture, Texture* specularTexture, Texture* normalTexture, float shininess, float colorTextureBlending, float blendSmoothing, float colorTilin) :_diffuseTexture(pDiffuseTexture) {
	_diffuseTexture = pDiffuseTexture;
	_emmissiveTexture = emmissiveTexture;
	_specularTexture = specularTexture;
	_normalTexture = normalTexture;
	this->shininess = shininess;
	blend = colorTextureBlending;
	blendingSoftness = blendSmoothing;
	colorTiling = colorTilin;
	_offset = offset;
	offset += 4;
	_lazyInitializeShader();

}

TextureMovingMaterial::~TextureMovingMaterial() {}

void TextureMovingMaterial::setNormalTexture(Texture* tex)
{
	_normalTexture = tex;
}

void TextureMovingMaterial::_lazyInitializeShader() {
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "texturemoving.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "texturemoving.fs");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		_shadowSize = _shader->getUniformLocation("ShadowSize");
		_shadowLength = _shader->getUniformLocation("ShadowLength");
		_uMMatrix = _shader->getUniformLocation("modelMatrix");
		_uVMatrix = _shader->getUniformLocation("viewMatrix");
		_uPMatrix = _shader->getUniformLocation("projectionMatrix");


		_heightTexID = _shader->getUniformLocation("yOffTexture");
		_maxHeight = _shader->getUniformLocation("maxHeight");

		_heightMapSpeed = _shader->getUniformLocation("heightMapSpeed");
		_movingspeed = _shader->getUniformLocation("movingspeed");

		_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
		_uNormalTexture = _shader->getUniformLocation("normalTexture");

		_uSpecularTexture = _shader->getUniformLocation("specularTexture");
		_uEmmissiveTexture = _shader->getUniformLocation("emissiveTexture");
		_lightCount = _shader->getUniformLocation("lightCount");
		_shininess = _shader->getUniformLocation("shininess");
		_maxXOff = _shader->getUniformLocation("maxXOffset");
		_xOffsetSmootness = _shader->getUniformLocation("xOffsetSmoothness");
		_xMoveTiling = _shader->getUniformLocation("xMoveTiling");

		_aTangents = _shader->getAttribLocation("tangents");
		_aBitangents = _shader->getAttribLocation("bitangent");
		_camPos = _shader->getUniformLocation("cameraPosition");
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
		_heightMapTiling = _shader->getUniformLocation("heightMapTiling");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
		_playerPos = _shader->getUniformLocation("playerPosition");
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

void TextureMovingMaterial::render(int pass, World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (pass != 0 || !_diffuseTexture) return;

	_shader->use();

	glm::vec3 camPos = (AbstractGame::instance->_world->getMainCamera())->getWorldPosition();
	glUniform3f(_camPos, camPos.x, camPos.y, camPos.z);
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

	glm::vec3 ppos = PlayerController::instance->getOwner()->getLocalPosition()*glm::vec3(0, 0, 1);
	ppos -= AbstractGame::instance->_world->getMainCamera()->getLocalPosition()*glm::vec3(0, 0, 1);//Camera has different y and x component. so we are discarding that


	glUniform3f(_playerPos, ppos.x, ppos.y, ppos.z);

	glUniform1f(_genOffset, TextureMaterial::genOffset);
	glUniform1f(_width, TextureMaterial::width);
	glUniform1f(_movingspeed, Movingspeed);
	glUniform1f(_heightMapTiling, TextureMaterial::heightmapTiling);
	glUniform1f(_heightMapSpeed, TextureMaterial::heightmapSpeed);
	glUniform1f(_xMoveTiling, TextureMaterial::xMoveTiling);
	glUniform1f(_shadowSize, ShadowSize);
	glUniform1f(_shadowLength, 2);

	if (TextureMaterial::_heightMap != nullptr)
	{
		//setup texture slot 0
		glActiveTexture(GL_TEXTURE1);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, TextureMaterial::_heightMap->getId());
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
	if (_normalTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, _normalTexture->getId());
		glUniform1i(_uNormalTexture, 4);
	}

	glUniform1f(_xOffsetSmootness, TextureMaterial::xOffsetSmootness);
	glUniform1f(_maxXOff, TextureMaterial::maxXOff);

	glUniform1f(_shininess, shininess);


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
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV, _aTangents, _aBitangents);
}
