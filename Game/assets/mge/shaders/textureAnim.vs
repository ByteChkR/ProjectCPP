//DIFFUSE TEXTURE VERTEX SHADER
#version 130 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	mvpMatrix;
uniform int frame;
uniform int frames;

in vec3 vertex;
in vec3 normal;
in vec2 uv;


out vec2 texCoord; //make sure the texture coord is interpolated

void main( void ){
	vec2 uv2 = uv;
	uv2.x = (uv.x/frames) + float(frame)/float(frames) ;
	gl_Position = mvpMatrix * vec4(vertex, 1.f);
	texCoord = uv2;
}
