#version 330 compatibility

// TransformationsMatrizen vom Programm gesetzt
uniform mat4 MVP,MV,normalMat;

// Kameraposition
uniform vec3 eye;

//input aus VBO
in vec4 vertex;
in vec4 normal;

// An FragmentShader weitergereichte Variablen
out vec3 vNormal,vWorldPosition;




void main(void)
{
	
	gl_Position = MVP*vertex;
	vNormal = (normalize(normalMat *normal)).xyz;
	vWorldPosition = (MV*vertex).xyz;
	
}
