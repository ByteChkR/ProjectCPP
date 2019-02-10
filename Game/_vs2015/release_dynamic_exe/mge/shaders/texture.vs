//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;
uniform float maxHeight;
uniform float genOffset;
uniform float hwm;
uniform float maxXOffset;
uniform float xOffsetSmoothness;

uniform sampler2D yOffTexture;

out vec2 texCoord;
out vec3 worldNormal;
out vec3 fragmentWorldPosition;

void main( void ){
		vec4 vertexWorldPosition = viewMatrix * modelMatrix * vec4(vertex, 1);
		
		vec2 heightUV = vec2((-vertexWorldPosition.z) / genOffset,(vec4(vertex,1)*modelMatrix).x/hwm);

		float t = pow(clamp(-vertexWorldPosition.z/genOffset, 0 , 1), xOffsetSmoothness);

		float texoffx = t*maxXOffset;

		float texoff = texture(yOffTexture, heightUV).y*maxHeight;
		//float offset = max(sin(-(vertexWorldPosition.z/15))*maxHeight,0.0);

		vertexWorldPosition = (vertexWorldPosition + vec4(texoffx,texoff,0,0));
    	gl_Position = projectionMatrix * vertexWorldPosition;
    	texCoord = uv;
    	worldNormal = vec3(viewMatrix * modelMatrix * vec4(normal, 0));
    	fragmentWorldPosition = vec3(vertexWorldPosition);
}
