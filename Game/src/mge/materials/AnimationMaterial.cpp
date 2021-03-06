#include "glm.hpp"

#include "mge/materials/AnimationMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"
#include "../_vs2015/Debug.h"
ShaderProgram* AnimationMaterial::_shader = NULL;

GLint AnimationMaterial::_uMVPMatrix = 0;
GLint AnimationMaterial::_uDiffuseTexture = 0;

GLint AnimationMaterial::_uFrame = 0;
GLint AnimationMaterial::_uNumberFrames = 0;
GLint AnimationMaterial::_aVertex = 0;
GLint AnimationMaterial::_aNormal = 0;
GLint AnimationMaterial::_aUV = 0;

AnimationMaterial::AnimationMaterial(Texture* pDiffuseTexture, int pNumberOfFrames) {
	_diffuseTexture = pDiffuseTexture;
	_framesCount = pNumberOfFrames;
	_currentFrame = 0;
	_lazyInitializeShader();
	//_uNumberFrames = pNumberOfFrames;
}

AnimationMaterial::~AnimationMaterial() {}

void AnimationMaterial::_lazyInitializeShader() {
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "textureAnim.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "textureAnim.fs");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");

		_uFrame = _shader->getUniformLocation("frame");
		_uNumberFrames = _shader->getUniformLocation("frames");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
	}
}

void AnimationMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
	_diffuseTexture = pDiffuseTexture;
}

void AnimationMaterial::render(int pass, World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (pass != 1 || !_diffuseTexture) return;
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

	glUniform1i(_uFrame, _currentFrame);

	glUniform1i(_uNumberFrames, _framesCount);

	//pass in a precalculate mvp matrix (see texture material for the opposite)
	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV, -1, -1);
}

void AnimationMaterial::SetFrame(int pFrame)
{
	if (pFrame < 0)
	{
		Debug::LogError("ERROR: Tried to set frame smaller than 0");
		return;
	}

	if (pFrame > _framesCount - 1)
	{
		Debug::LogError("ERROR: Tried to set frame bigger than the frame count");
		return;
	}

	_currentFrame = pFrame;
}

void  AnimationMaterial::NextFrame()
{
	if (_currentFrame == _framesCount - 1)
	{
		_currentFrame = 0;
		return;
	}

	_currentFrame++;

}

int AnimationMaterial::GetCurrentFrameNum()
{
	return _currentFrame;
}