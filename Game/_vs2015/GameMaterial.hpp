#ifndef GAMEMATERIAL_HPP
#define GAMEMATERIAL_HPP

#include "Material.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"


class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class GameMaterial : public AbstractMaterial
{
public:
	GameMaterial(Material material);
	virtual ~GameMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setMaterial(Material material);

protected:
private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//in this example we cache all identifiers for uniforms & attributes
	static GLint _uMMatrix;
	static GLint _uVMatrix;
	static GLint _uPMatrix;
	static GLint _diffuseTex;
	static GLint _normalTex;
	static GLint _specularTex;
	static GLint _heightTex;
	static GLint _maxHeight;
	static GLint _shinyness;
	static GLint _lightCount;
	static GLuint _lightUBO;
	Material material;

	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;


	GameMaterial(const GameMaterial&);
	GameMaterial& operator=(const GameMaterial&);

};


#endif