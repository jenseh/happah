#version 410 compatibility

in vec4 vertex;
uniform mat4 MVP;
uniform vec4 eye;


out vec4 normal;
out vec4 vertexWP;


void main(void)
{
	vec4 center = vec4(0.0f,0.0f,0.0f,0.0f);
	normal = normalize(vertex-center);
	gl_Position = MVP*vertex;
	vertexWP = MVP*vertex;

}