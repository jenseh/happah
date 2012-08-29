#version 420

in vec4 vertex;
uniform mat4 MVP;



void main(void)
{
	gl_Position = MVP*vertex;
}