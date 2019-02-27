//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

const int COLORCOUNT = 8;

struct Light
{
	int type;
	float intensity;
	vec2 attenuation;
	vec3 position;
	vec3 color;
	vec3 ambientColor;
};

uniform float time;

uniform vec3 colors[COLORCOUNT];
uniform int colorCount;
uniform float colorTiling;
uniform float textureBlend;
uniform float blendSmoothing;

uniform Light lights[8];
uniform int lightCount;

uniform sampler2D emissiveTexture;
uniform sampler2D specularTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform float shininess;
in vec2 texCoord;
in vec3 worldNormal;
in mat3 TBN;
in vec3 fragmentWorldPosition;
in vec3 fragmentCameraPosition;
out vec4 fragment_color;

vec3 GetToonColor(float intens)
{
	float sint = time + colorCount*intens * colorTiling;
	float rem = mod(sint,1);
	int col = int(sint);
	rem = pow(rem, blendSmoothing);
	return colors[col%colorCount]*(1-rem) + colors[(col+1)%colorCount] * (rem);
}

vec4 Calculate(int index, vec3 wNormal)
{
	vec3 dir = lights[index].position-fragmentWorldPosition;
	vec3 dirN = normalize(dir);
	float distance = length(dir);
	
	float diffIntensity = max(dot(wNormal, dirN),0.0);

	float falloff = 1 + (lights[index].attenuation.x * distance) + (lights[index].attenuation.y * distance * distance);


	vec3 refDir = reflect(-dirN, wNormal);
	float spec = pow(max(dot(wNormal, refDir),0.0),shininess)/falloff;

	diffIntensity/=falloff;
	vec3 ambient  = lights[index].ambientColor*lights[index].intensity;
	vec3 specular = lights[index].intensity*spec * diffIntensity * texture(specularTexture, texCoord).rgb;
	vec4 difftexcolor = texture(diffuseTexture, texCoord);
	if(difftexcolor.a < 0.1)discard;
	vec3 finalDiffuse = GetToonColor(diffIntensity)*(1-textureBlend) + vec3(difftexcolor)*textureBlend;
	
	vec3 diffuse = (finalDiffuse * lights[index].intensity) * diffIntensity;


	vec3 emmissive = texture(emissiveTexture, texCoord).rgb;
	//emmissive/=falloff;
	vec4 result = vec4(0);
	result.rgb = specular + diffuse + ambient + emmissive;
	result.a = difftexcolor.a;
	return result;
}



void main( void ) {

	vec4 ret = vec4(0);
	vec3 wn = normalize(worldNormal);//texture(normalTexture, texCoord).rgb;
	//wn=normalize(wn*2.0-1.0);
	//wn=normalize(TBN*wn);
	for(int i = 0; i < lightCount; i++)
	{
		ret += Calculate(i, wn);
	}

	fragment_color = ret;
}
