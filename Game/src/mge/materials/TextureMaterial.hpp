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
        TextureMaterial (Texture* pDiffuseTexture, float shininess, int steps, float colorTextureBlending, float blendSmoothing, float colorTilin, Texture* heightMap = nullptr);
        virtual ~TextureMaterial ();

        virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        void setDiffuseTexture (Texture* pDiffuseTexture);

		static Texture* _heightMap;
    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
		static GLint _uMMatrix;
		static GLint _uVMatrix;
		static GLint _uPMatrix;
        static GLint _uDiffuseTexture;
		static GLLight _lightLocations[8];
		static GLint _lightCount;
		static GLint _shininess;
		static GLint _steps;
		static int offset;
		int _offset;
        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

		static GLint _colorCount;
		static GLint _blendingSoftness;
		static GLint _blend;
		static GLint _colorTiling;
		static GLint _time;
		static GLint _heightTexID;
		static GLint _maxHeight;
		static GLint _genOffset;
		static GLint _width;

        Texture* _diffuseTexture;
		float shininess;
		int steps;


		float blendingSoftness;
		float blend;
		float colorTiling;
		float maxHeight;
		float genOffset;
		float width;



        TextureMaterial(const TextureMaterial&);
        TextureMaterial& operator=(const TextureMaterial&);

};

#endif // TEXTUREMATERIAL_HPP
