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
uniform vec3 cameraPosition;
uniform float textureXOffset;

out vec2 texCoord;
out vec3 worldNormal;
out vec3 fragmentWorldPosition;
out vec3 fragmentCameraPosition;
out vec3 fPlayerPosition;
out mat3 TBN;

void main( void ){

		//Constructing TBN matrix for Normals
		vec3 T = normalize(vec3(viewMatrix * modelMatrix * vec4(tangent, 0.0)));
		vec3 B = normalize(vec3(viewMatrix * modelMatrix * vec4(bitangent, 0.0)));
		vec3 N = normalize(vec3(viewMatrix * modelMatrix * vec4(normal, 0.0)));
		TBN = mat3(T,B,N);


		//Calculating the offset for the shadow(where the shadow would be)
		vec4 playerCameraPosition = viewMatrix*vec4(playerPosition, 1);

		float playerHeightX = max((-playerPosition.z) / genOffset, 0.0);
		float playerHeightY = playerPosition.x / hwm;

		vec2 playerHeightUV = vec2(playerHeightX, playerHeightY)+vec2(time*heightMapSpeed,0.0);

		playerHeightUV/=heightMapTiling;

		float playerT = pow(clamp(-playerCameraPosition.z/xMoveTiling, 0, 1), xOffsetSmoothness);

		float playertexoffx = playerT*maxXOffset;
		float playertexoff = texture(yOffTexture, clamp(playerHeightUV, 0, 1)).y*maxHeight;

		vec2 playerOffset= vec2(playertexoffx, playertexoff);

		vec3 finalPlayerPosition = playerPosition + vec3(playerOffset, 0);
		playerCameraPosition = viewMatrix * vec4(finalPlayerPosition,1);

		//Calculating the Offset

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
		fragmentCameraPosition = vec3(cameraPosition);

		vertexWorldPosition = (vertexWorldPosition + vec4(offset, 0, 0)); //Applying the offset
		vertexCameraPosition = viewMatrix * vertexWorldPosition; //Updating the Camera position(now with offset)

    	texCoord = uv+ vec2(textureXOffset, time*movingspeed);
    	worldNormal = vec3(viewMatrix * modelMatrix * vec4(normal, 0));
    	fragmentWorldPosition = vec3(vertexWorldPosition);
    	fPlayerPosition = vec3(finalPlayerPosition);
    	gl_Position = projectionMatrix * vertexCameraPosition;
}