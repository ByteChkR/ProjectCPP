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
uniform float xMoveTiling;
uniform float xOffsetSmoothness;
uniform float maxXOffset;
uniform vec3 offset;

out vec2 fUV;

void main( void ){
	
		vec4 vertexWorldPosition = modelMatrix * vec4(vertex, 1);
		vec4 vertexCameraPosition = viewMatrix * vertexWorldPosition;
		float heightX = abs(vertexWorldPosition.z) / genOffset;
		float heightY = vertexWorldPosition.x / hwm;

		vec2 heightUV = vec2(heightX, heightY) + vec2(time * heightMapSpeed, 0);

		heightUV /= heightMapTiling;

		float t = pow(clamp(-vertexCameraPosition.z / xMoveTiling, 0 , 1), xOffsetSmoothness);

		float texoffx = t * maxXOffset; //X offset based on min and max offset

		float texoff = texture(heightMap, heightUV).y * maxHeight; //Y Offset based on heightmap


		vec2 offsetHM = vec2(texoffx, texoff);

		vertexWorldPosition = (vertexWorldPosition + vec4(offset, 0) + vec4(offsetHM, 0, 0)); //Applying the offset
		
		vertexWorldPosition.y -= clamp(vertexWorldPosition.z, 0, vertexWorldPosition.z)/hwm;
		
		vertexCameraPosition = viewMatrix * vertexWorldPosition; //Updating the Camera position(now with offset)

		
		
    	fUV = uv;
    	gl_Position = projectionMatrix * vertexCameraPosition;


}
