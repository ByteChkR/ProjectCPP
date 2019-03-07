#ifndef ANIMATERIAL_HPP
#define ANIMMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"
#include<iostream>

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class AnimationMaterial : public AbstractMaterial
{
public:
	AnimationMaterial(Texture* pDiffuseTexture, int pNumberOfFrames);
	virtual ~AnimationMaterial();

	virtual void render(int pass, World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setDiffuseTexture(Texture* pDiffuseTexture);

	void SetFrame(int pFrame);
	void NextFrame();
	int GetCurrentFrameNum();
protected:
private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//in this example we cache all identifiers for uniforms & attributes
	static GLint _uMVPMatrix;
	static GLint _uDiffuseTexture;

	static GLint _uFrame;
	static GLint _uNumberFrames;

	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;

	Texture* _diffuseTexture;
	int _framesCount;
	int _currentFrame;
	AnimationMaterial(const AnimationMaterial&);
	AnimationMaterial& operator=(const AnimationMaterial&);

};

#endif // TEXTUREMATERIAL_HPP
