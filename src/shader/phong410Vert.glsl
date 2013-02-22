#version 410 core

layout(location = 0)in vec4 vertex;
layout(location = 1)in vec4 normal;
layout(location = 2)in vec4 color;


uniform mat4 modelMatrix;
uniform mat4 MVP;
uniform mat3 normalMat;
uniform float ka;
uniform float kd;
uniform float ks;
uniform float shininess;
uniform vec3 eye;
uniform int hasVertexColor;

out vec4 vPos;
out vec4 vNormal;
out vec4 vColor;

void main(){
    vPos = modelMatrix * vertex;      //Vertex Position in Worldspace

    vNormal = normalize(normal);
    vec3 vnormal3 =  vNormal.xyz;
    vnormal3 = normalMat*vnormal3;
    vNormal = vec4(vnormal3,1.0f);  //Normal in Worldspace;
    gl_Position = MVP * vertex;
    vColor = color;	
    
}
