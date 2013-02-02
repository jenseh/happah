#version 410 compatibility

layout(location = 0)in vec4 vertex;
layout(location = 1)in vec4 normal;
layout(location = 2)in vec4 color;


uniform mat4 MV;
uniform mat4 MVP;
uniform mat4 normalMat;


out vec4 vPosWS;
out vec4 vNormalWS;
out vec4 vColor;


void main(){
    vPosWS = MV * vertex;
    vNormalWS = normalMat*normal;		
    gl_Position = MVP * vertex;	
    vColor = color;	
    
}