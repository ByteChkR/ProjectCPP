//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

uniform vec3 offset;

out vec2 fUV;

void main( void ){
	
	fUV = uv;

	vec4 v = projectionMatrix * modelMatrix * vec4(vertex, 1.f);
	
    gl_Position = v+vec4(offset,0);


}
