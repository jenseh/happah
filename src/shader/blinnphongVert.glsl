#version 330 compatibility

// TransformationsMatrizen vom Programm gesetzt
uniform mat4 MVP,MV;
uniform mat4 normalMat;

// Kameraposition
uniform vec3 eye;

//input aus VBO
in vec4 vertex;
in vec4 normal;

// An FragmentShader weitergereichte Variablen
out vec3 vNormal,vWorldPosition;




void main(void)
{
	
        gl_Position = MVP * vertex;
        vec4 tNormal = normalize(normalMat * normal);
        vNormal = tNormal.xyz;
        vWorldPosition = vec4(MV * vertex).xyz;
	
}
