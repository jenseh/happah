#version 330 compatibility

in vec4 vertex;	
in vec4 normal;				    
in vec4 pointSelectionColor; 

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
out vec4 vColor;
out vec4 vPointSelectionColor;

void main(){
	gl_TexCoord[0] = vec4(0.0f);
	
	gl_Position = modelViewMatrix * vertex;
	vColor = vec4(1.0f,0.0f,0.0f,1.0f);
	vPointSelectionColor = pointSelectionColor;
}