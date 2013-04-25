#version 330 compatibility

in vec4 vertex;	
in vec4 normal;				    
in vec4 pointSelectionColor; 

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec4 colorComponent;
out vec4 vColor;
out vec4 vPointSelectionColor;

void main(){
	gl_TexCoord[0] = vec4(0.0f);
	
	gl_Position = modelViewMatrix * vertex;
	vColor = colorComponent;
	vPointSelectionColor = pointSelectionColor;
}