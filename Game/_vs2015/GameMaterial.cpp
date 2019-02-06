#include "GameMaterial.hpp"


#include "glm.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* GameMaterial::_shader = NULL;
GLint GameMaterial::_aVertex = 0;
GLint GameMaterial::_aNormal = 0;
GLint GameMaterial::_aUV = 0;
GLint GameMaterial::_diffuseTex = 0;
GLint GameMaterial::_heightTex = 0;
GLint GameMaterial::_lightCount = 0;
GLint GameMaterial::_maxHeight = 0;
GLint GameMaterial::_normalTex = 0;
GLint GameMaterial::_shinyness = 0;
GLint GameMaterial::_specularTex = 0;
GLint GameMaterial::_uMMatrix = 0;
GLint GameMaterial::_uPMatrix = 0;
GLint GameMaterial::_uVMatrix = 0;
GLuint GameMaterial::_uniformBlockIndex = 0;
GLLight GameMaterial::_lightLocations[8];

GameMaterial::GameMaterial(Material material)
{
	this->material = material;
	_lazyInitializeShader();
}

GameMaterial::~GameMaterial() {}

void GameMaterial::_lazyInitializeShader() {
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "GameShaderStatic.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "GameShaderStatic.fs");
		_shader->finalize();

		//for (size_t i = 0; i < 8; i++)
		//{
		//	_lightLocations[i] = GLLight(
		//		_shader->getUniformLocation("lights[" + std::to_string(i) + "].type"),
		//		_shader->getUniformLocation("lights[" + std::to_string(i) + "].intensity"),
		//		_shader->getUniformLocation("lights[" + std::to_string(i) + "].attenuation"),
		//		_shader->getUniformLocation("lights[" + std::to_string(i) + "].position"),
		//		_shader->getUniformLocation("lights[" + std::to_string(i) + "].color"),
		//		_shader->getUniformLocation("lights[" + std::to_string(i) + "].ambientColor"),
		//		_shader->getUniformLocation("lights[" + std::to_string(i) + "].forward")
		//	);
		//}

		//cache all the uniform and attribute indexes
		_uMMatrix = _shader->getUniformLocation("modelMatrix");
		_uVMatrix = _shader->getUniformLocation("viewMatrix");
		_uPMatrix = _shader->getUniformLocation("perspectiveMatrix");
		//_lightCount = _shader->getUniformLocation("lightCount");

		_diffuseTex = _shader->getUniformLocation("diffuseTexture");
		//_normalTex = _shader->getUniformLocation("material.normalTexture");
		//_specularTex = _shader->getUniformLocation("material.specularTexture");
		//_heightTex = _shader->getUniformLocation("heightMap");
		//_maxHeight = _shader->getUniformLocation("maxHeight");
		//_shinyness = _shader->getUniformLocation("material.shinyness");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");

		
	}
}

void GameMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	if (!_diffuseTex)return;

	_shader->use();

	
	for (int i = 0; i < pWorld->getLightCount(); i++)
	{
		//_lightLocations[i].SetLight(&pWorld->getLightAt(i)->GetParams());
	}
	

	//glUniform1f(_shinyness, material.shininess);
	//glUniform1f(_maxHeight, material.maxHeight);
	//glUniform1i(_lightCount, pWorld->getLightCount());
	
	//glBindBuffer(GL_UNIFORM_BUFFER, _lightUBO);
	//glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightParams) * 8, &params);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, material.diffuse->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(_diffuseTex, 0);

	//if (material.normal != nullptr)
	//{

	//	//setup texture slot 0
	//	glActiveTexture(GL_TEXTURE1);
	//	//bind the texture to the current active slot
	//	glBindTexture(GL_TEXTURE_2D, material.normal->getId());
	//	//tell the shader the texture slot for the diffuse texture is slot 0
	//	glUniform1i(_normalTex, 1);

	//}
	//else 
	//{

	//}

	//if (material.specular != nullptr)
	//{

	//	//setup texture slot 0
	//	glActiveTexture(GL_TEXTURE2);
	//	//bind the texture to the current active slot
	//	glBindTexture(GL_TEXTURE_2D, material.specular->getId());
	//	//tell the shader the texture slot for the diffuse texture is slot 0
	//	glUniform1i(_normalTex, 2);

	//}
	//if (material.height != nullptr)
	//{

	//	//setup texture slot 0
	//	glActiveTexture(GL_TEXTURE3);
	//	//bind the texture to the current active slot
	//	glBindTexture(GL_TEXTURE_2D, material.height->getId());
	//	//tell the shader the texture slot for the diffuse texture is slot 0
	//	glUniform1i(_heightTex, 3);

	//}
	//pass in a precalculate mvp matrix (see texture material for the opposite)

	glUniformMatrix4fv(_uMMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	glUniformMatrix4fv(_uVMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_uPMatrix, 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}


void GameMaterial::setMaterial(Material material)
{
	this->material = material;
}
