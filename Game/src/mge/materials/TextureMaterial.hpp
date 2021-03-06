#ifndef TEXTUREMATERIAL_HPP
#define TEXTUREMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"
#include "../_vs2015/GLLight.hpp"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class TextureMaterial : public AbstractMaterial
{
public:
	TextureMaterial(Texture* pDiffuseTexture, Texture* emmissiveTexture, Texture* specularTexture, float shininess, float colorTextureBlending, float blendSmoothing, float colorTilin, Texture* heightMap = nullptr);
	virtual ~TextureMaterial();

	virtual void render(int pass, World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setDiffuseTexture(Texture* pDiffuseTexture);

	static Texture* _heightMap;
	static float maxXOff;
	static float currentXOff;
	static float xOffsetSmootness;
	static float heightmapTiling;
	static float heightmapSpeed;
	static float maxHeight;
	static float genOffset;
	static float width;
	static float xMoveTiling;
	static glm::vec3 fogColor;
	static float fogEnd;
	static float fogBegin;
	static float fogBlendSmoothness;
protected:
private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	static GLint _fogColor;
	static GLint _fogBegin;
	static GLint _fogEnd;
	static GLint _fogBlendSmoothness;

	//in this example we cache all identifiers for uniforms & attributes
	static GLint _uMMatrix;
	static GLint _uVMatrix;
	static GLint _uPMatrix;
	static GLint _uDiffuseTexture;
	static GLLight _lightLocations[8];
	static GLint _lightCount;
	static GLint _shininess;
	static int offset;
	int _offset;
	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV; 
	static GLint _aTangents;
	static GLint _aBitangents;

	static GLint _time;
	static GLint _heightTexID;
	static GLint _maxHeight;
	static GLint _genOffset;
	static GLint _width;
	static GLint _xOffsetSmootness;
	static GLint _maxXOff;
	static GLint _movingspeed;
	static GLint _heightMapTiling;
	static GLint _heightMapSpeed;
	static GLint _uEmmissiveTexture;
	static GLint _xMoveTiling;
	static GLint _camPos;
	

	Texture* _emmissiveTexture;
	static GLint _uSpecularTexture;
	Texture* _specularTexture;


	Texture* _diffuseTexture;
	float shininess;



	float blendingSoftness;
	float blend;
	float colorTiling;



	TextureMaterial(const TextureMaterial&);
	TextureMaterial& operator=(const TextureMaterial&);

};

#endif // TEXTUREMATERIAL_HPP
