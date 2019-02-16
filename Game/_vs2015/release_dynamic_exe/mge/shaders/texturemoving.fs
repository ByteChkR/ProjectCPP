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

uniform sampler2D diffuseTexture;
uniform sampler2D emissionMap;
uniform float shininess;
uniform float movingspeed;
uniform float ShadowSize;
uniform float ShadowLength;
in vec2 texCoord;
in vec3 worldNormal;
in vec3 fragmentWorldPosition;
in vec3 fPlayerPosition;
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
	float spec = pow(max(dot(dirN, refDir),0.0),shininess)/falloff;

	diffIntensity/=falloff;
	vec3 ambient  = lights[index].ambientColor;
	vec3 specular = spec * diffIntensity * vec3(1);
	vec4 difftexcolor = texture(diffuseTexture, texCoord);
	vec3 finalDiffuse = GetToonColor(diffIntensity)*(1-textureBlend) + vec3(difftexcolor)*textureBlend;
	
	vec3 emmissive = texture(emissionMap, texCoord).rgb;

	vec3 diffuse = (finalDiffuse * lights[index].intensity) * diffIntensity;
	vec4 result = vec4(0);
	result.rgb = specular + diffuse + ambient + emmissive;
	result.a = difftexcolor.a;
	return result;
}



void main( void ) {

	float d = distance(fPlayerPosition.xz , fragmentWorldPosition.xz);
	float yd = fPlayerPosition.y-fragmentWorldPosition.y;
	vec4 ret = vec4(0);
	vec3 wn = normalize(worldNormal);
	for(int i = 0; i < lightCount; i++)
	{
		ret += Calculate(i, wn);
	}

	fragment_color = d > ShadowSize * clamp( 1-( yd / ShadowLength) ,0,1) ? ret : vec4(0,0,0,1);
}
