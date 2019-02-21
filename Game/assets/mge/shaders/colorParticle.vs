//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

uniform sampler2D heightMap;
uniform float maxHeight;
uniform float genOffset;
uniform float hwm;
uniform float heightMapSpeed;
uniform float time;
uniform float heightMapTiling;

uniform vec3 offset;

out vec2 fUV;

void main( void ){
	
		vec4 vertexWorldPosition = viewMatrix * modelMatrix * vec4(vertex, 1);
		
		vec2 heightUV = vec2((-vertexWorldPosition.z) / genOffset,(vec4(vertex,1)*modelMatrix).x/hwm) + vec2(time*heightMapSpeed, 0);

		heightUV/=heightMapTiling;

		float texoff = texture(heightMap, heightUV).y*maxHeight;

	fUV = uv;

	vec4 v = projectionMatrix * modelMatrix * vec4(vertex, 1.f);
	
    gl_Position = v+vec4(offset + vec3(0,texoff,0),0);


}
