//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;
in vec3 tangent;
in vec3 bitangent;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;
uniform float maxHeight;
uniform float genOffset;
uniform float hwm;
uniform float time;
uniform float maxXOffset;
uniform float xMoveTiling;
uniform float xOffsetSmoothness;
uniform float movingspeed;
uniform float heightMapSpeed;
uniform float heightMapTiling;
uniform sampler2D yOffTexture;
uniform vec3 playerPosition;

out vec2 texCoord;
out vec3 worldNormal;
out vec3 fragmentWorldPosition;
out vec3 fPlayerPosition;
out mat3 TBN;

void main( void ){

		vec3 T = normalize(vec3(viewMatrix * modelMatrix * vec4(tangent, 0.0)));
		vec3 B = normalize(vec3(viewMatrix * modelMatrix * vec4(bitangent, 0.0)));
		vec3 N = normalize(vec3(viewMatrix * modelMatrix * vec4(normal, 0.0)));
		TBN = mat3(T,B,N);

		vec4 vertexWorldPosition = modelMatrix * vec4(vertex, 1);
		vec4 vertexCameraPosition = viewMatrix * vertexWorldPosition;

		float heightX = max((-vertexWorldPosition.z) / genOffset, 0.0);
		float heightY = vertexWorldPosition.x / hwm;

		vec2 heightUV = vec2(heightX, heightY) + vec2(time * heightMapSpeed, 0);

		heightUV /= heightMapTiling;

		float t = pow(clamp(-vertexCameraPosition.z / xMoveTiling, 0 , 1), xOffsetSmoothness);

		float texoffx = t * maxXOffset; //X offset based on min and max offset

		float texoff = texture(yOffTexture, clamp(heightUV, 0, 1)).y * maxHeight; //Y Offset based on heightmap

		vec2 offset = vec2(texoffx, texoff);

		vertexWorldPosition = (vertexWorldPosition + vec4(offset, 0, 0)); //Applying the offset
		vertexCameraPosition = viewMatrix * vertexWorldPosition; //Updating the Camera position(now with offset)

    	texCoord = uv+ vec2(0, time*movingspeed/3);
    	worldNormal = vec3(viewMatrix * modelMatrix * vec4(normal, 0));
    	fragmentWorldPosition = vec3(vertexWorldPosition);
    	gl_Position = projectionMatrix * vertexCameraPosition;
}