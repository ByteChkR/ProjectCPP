#version 330

const int MAX_LIGHTS = 8;

struct Light
{
	int type;
	float intensity;
	vec2 attenuation;
	vec3 position;
	vec3 color;
	vec3 ambientColor;
	vec3 forward;
};


//Heightmap
uniform sampler2D heightMap;
uniform float maxHeight;

//Matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;

//Mesh Data
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normTangent;
layout (location = 4) in vec3 normBitangent;

//UV
out vec2 texCoord;

//Lighting
uniform Light lights[MAX_LIGHTS];
uniform int lightCount;
//transformed positions and directions(in TBN space)
out vec3 fragmentWorldPosition;
out vec3 lightPoss[MAX_LIGHTS]; 
out vec3 lightFwds[MAX_LIGHTS];

void main( void )
{
	vec4 v = vec4(vertex, 1);
	//Heightmap
	v.y = v.y + texture(heightMap, uv).x * maxHeight;


	mat4 mvpMat = modelMatrix * viewMatrix * perspectiveMatrix;
	gl_Position = mvpMat * v;


	texCoord = uv;

	vec3 T = normalize(vec3(modelMatrix * vec4(normTangent, 0)));
	vec3 B = normalize(vec3(modelMatrix * vec4(normBitangent, 0)));
	vec3 N = normalize(vec3(modelMatrix * vec4(normal, 0)));
	mat3 TBNMatrix = mat3(T, B, N);

	for(int i = 0; i < lightCount; i++)
	{
		lightPoss[i] = TBNMatrix * lights[i].position;
		lightFwds[i] = TBNMatrix * lights[i].forward;
	}
	fragmentWorldPosition = TBNMatrix * vec3(modelMatrix * vec4(vec3(v),0));
}