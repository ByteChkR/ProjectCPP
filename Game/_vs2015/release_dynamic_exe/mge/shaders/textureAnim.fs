//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D diffuseTexture;
in vec2 texCoord;
out vec4 fragment_color;

void main( void ) {

	vec4 test = texture(diffuseTexture,texCoord);
	if(test.a <0.1)
	{
		discard;
	}

	fragment_color = test;
}
