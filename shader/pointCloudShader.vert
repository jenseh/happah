#version 330 compatibility

in vec4 vertex;	
in vec4 normal;				    
in vec4 color; 

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
out vec4 vColor;

void main(){
	gl_TexCoord[0] = vec4(0.0f);
	
	gl_Position = modelViewMatrix * vertex;
	vColor = vec4(1.0f,0.0f,0.0f,1.0f);
}