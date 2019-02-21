#version 130

//Heightmap
//uniform sampler2D heightMap;
//uniform float maxHeight;

//Matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;

//Mesh Data
in vec3 normal;
in vec3 vertex;

in vec2 uv;
//in vec3 normTangent;
//in vec3 normBitangent;

//UV
out vec2 texCoord;
//out vec3 fragmentWorldPosition;
//out vec3 worldNormal;


void main( void )
{
	//vec4 v = vec4(vertex, 1);
	//Heightmap
	//v.y = v.y + texture(heightMap, uv).x * maxHeight;


	mat4 mvpMat = modelMatrix * viewMatrix * perspectiveMatrix;
	gl_Position = mvpMat * vec4(vertex,1);


	texCoord = uv;

	//fragmentWorldPosition = vec3(modelMatrix * vec4(vertex, 1));
	//worldNormal = vec3(modelMatrix * vec4(vertex, 0));
}