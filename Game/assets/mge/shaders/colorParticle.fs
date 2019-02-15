//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1


uniform vec4 ParticleColor;

out vec4 fragment_color;

void main( void ) {
	fragment_color = ParticleColor;
}
