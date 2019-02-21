#version 130

const int MAX_LIGHTS = 8;

//Structs
struct Material
{
	//Texture Data
	sampler2D diffuseTexture;
	//sampler2D normalTexture;
	//sampler2D specularTexture;
	float shinyness;
};
uniform sampler2D diffuseTexture;
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

//Out
//out vec4 fragColor;
out vec4 fragment_color;
//Lighting

//uniform Light lights[MAX_LIGHTS];
//uniform Material material;
//uniform int lightCount;

//UV
in vec2 texCoord;

//Lighting
//in vec3 fragmentWorldPosition;
//in vec3 worldNormal;
//in vec3 lightPoss[MAX_LIGHTS];
//in vec3 lightFwds[MAX_LIGHTS];



void main( void )
{
	

	fragment_color = texture(diffuseTexture, texCoord);
}