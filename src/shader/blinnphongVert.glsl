#version 330 compatibility

// TransformationsMatrizen vom Programm gesetzt
uniform mat4 MVP, MV;
uniform mat3 normalMat;

// Kameraposition
uniform vec3 eye;

//input aus VBO
in vec4 vertex;
in vec4 normal;
in vec4 color;

// An FragmentShader weitergereichte Variablen
out vec3 vNormal, vWorldPosition;
out vec4 vColor;




void main(void)
{
        gl_Position = MVP * vertex;
        vNormal = normalize(normalMat * normal.xyz);
        vWorldPosition = vec4(MV * vertex).xyz;	
        vColor = color;
}
