//DIFFUSE TEXTURE FRAGMENT SHADER
#version 130 // for glsl version (12 is for older versions , say opengl 2.1

struct Light
{
	int type;
	float intensity;
	vec2 attenuation;
	vec3 position;
	vec3 color;
	vec3 ambientColor;
};

uniform Light lights[8];
uniform int lightCount;
uniform sampler2D diffuseTexture;
uniform float shininess;
uniform int steps;
in vec2 texCoord;
in vec3 worldNormal;
in vec3 fragmentWorldPosition;
out vec4 fragment_color;

vec3 Calculate(int index, vec3 wNormal)
{
	vec3 dir = lights[index].position-fragmentWorldPosition;
	vec3 dirN = normalize(dir);
	float distance = length(dir);
	float diffIntensity = max(dot(normalize(dir), normalize(wNormal)), 0.0);

	float falloff = 1 + (lights[index].attenuation.x * distance) + (lights[index].attenuation.y * distance * distance);

	diffIntensity /= falloff;

	float stepSize = 1.0/steps;
	float i = floor(diffIntensity / stepSize);

	vec3 diffuse = vec3(texture(diffuseTexture, texCoord)) * stepSize * i;


	vec3 refDir = reflect(-dirN, wNormal);
	float specIntensity = pow(max(dot(dirN, refDir), 0.0), shininess);
	vec3 specular = lights[index].color * specIntensity * diffIntensity;

	vec3 ambient = lights[index].ambientColor * (1- diffIntensity);

	return specular + diffuse + ambient;
}



void main( void ) {

	vec3 ret = vec3(0);
	vec3 wn = normalize(worldNormal);
	for(int i = 0; i < lightCount; i++)
	{
		ret += Calculate(i, wn);
	}

	fragment_color = vec4(ret, 1);
}
