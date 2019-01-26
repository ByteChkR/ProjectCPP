#version 330

const int MAX_LIGHTS = 8;

//Structs
struct Material
{
	//Texture Data
	sampler2D diffuseTexture;
	sampler2D normalTexture;
	sampler2D specularTexture;
	float shinyness;
};

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
out vec4 fragColor;

//Lighting
uniform int lightCount;
uniform Light lights[MAX_LIGHTS];
uniform Material material;

//UV
in vec2 texCoord;

//Lighting
in vec3 fragmentWorldPosition;
in vec3 lightPoss[MAX_LIGHTS];
in vec3 lightFwds[MAX_LIGHTS];

vec4 AnalyzeLight(int index, vec3 fragWorldPos)
{	
	float dist = distance(lightPoss[i] - fragWorldPos); //measure distance
	vec4 ret = light.type == 0 ? //0 = Directional Light. Other = pointlight
		vec4(normalize(lightFwds[i]), dist):
		vec4(normalize(lightPoss[i]), dist);
	return ret;
}

vec4 CalculateLight(Light source, vec3 wNormal)
{
	//Uses W to tell distance between light and fragment
	vec4 ldir = AnalyzeLight(source, fragmentWorldPosition);



	float falloff = 1 + (ldir.w * source.attenuation.x) +
					(ldir.w * ldir.w * source.attenuation.y);

	float diffuseIntensity = max(dot(wNormal, vec3(ldir)), 0.0) / falloff;
	
	//Specular
	vec3 reflectDir = reflect(-vec3(ldir), wNormal);
	float spec = pow(max(dot(vec3(ldir), reflectDir), 0.0), material.shinyness);
	vec3 specular = texture(material.specularTexture, texCoord) * spec * diffuseIntensity;

	//Ambient
	vec3 ambient = source.ambientColor / falloff;

	//Diffuse
	vec3 diffuse = texture(material.diffuseTexture, texCoord) + (source.intensity * source.color) * diffuseIntensity;

	return ambient + diffuse + specular;
}

void main( void )
{
	vec3 ret = vec3(0);

	for(int i = 0; i < lightCount; i++)
	{
		ret += CalculateLight(lights[i], texture(material.normalTexture, texCoord));
	}

	fragColor = vec4(ret, 1);
}