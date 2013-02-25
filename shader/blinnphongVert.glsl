#version 330 compatibility

// TransformationsMatrizen vom Programm gesetzt
uniform mat4 MVP, modelMatrix;
uniform mat3 normalMat;

// Camera position
uniform vec3 eye;

// Material uniforms
uniform float ka, kd, ks;
uniform float shininess;

// Indicates whether a fixed vertex color is used
uniform int hasVertexColor;
in vec4 color;
out vec4 vColor;

// Position and normal of the current vertex
in vec4 vertex, normal;
out vec3 vNormal, vWorldPosition;


void main(void)
{
        gl_Position = MVP * vertex;
        vNormal = normalize(normalMat * normal.xyz);
        vWorldPosition = vec4(modelMatrix * vertex).xyz;
        vColor = color;
}
