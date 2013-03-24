#version 330

in vec4 vertex;					    
in vec4 normal;					    
in vec4 color;					    

uniform mat4 modelMatrix;				
uniform mat4 modelViewProjectionMatrix;				
uniform mat3 normalMatrix;
uniform vec4 colorComponent;	
uniform int  isColorPerVertex;		 					

out vec4 vVertex;	// vertex position world space				
out vec4 vNormal;	// vertex normal world space
out vec4 vColor;	// vertex color

void main() {
	vVertex = modelMatrix * vertex;      

	vec4 normalizedNormal = normalize(normal);
	vec3 normalizedNormal3D =  normalizedNormal.xyz;
	vec3 transformedNormal3D = normalMatrix * normalizedNormal3D;
	vNormal = vec4(transformedNormal3D, 1.0f);  
   	
   	
   	// TODO: check if color attribute is disabled , if so, set vColor to a color given by a uniform
   	if (isColorPerVertex == 1){
		vColor = color;
	}
	else {
		vColor = colorComponent;
	}   
   
	gl_Position = modelViewProjectionMatrix * vertex;
}
