#version 330 compatibility

in vec4 vertex;					    
in vec4 normal;					    
in vec4 color;					    

uniform mat4 modelMatrix;				
uniform mat4 modelViewProjectionMatrix;				
uniform mat3 normalMatrix;					 					

out vec4 vVertex; // vertex position world space				
out vec4 vNormal; // vertex normal world space
out vec4 vColor; // vertex color

void main() {
	vVertex = modelMatrix * vertex;      

	vec4 normalizedNormal = normalize(normal);
	vec3 normalizedNormal3D =  normalizedNormal.xyz;
	vec3 transformedNormal3D = normalMatrix * normalizedNormal3D;
	vNormal = vec4(transformedNormal3D, 1.0f);  
   
	vColor = color;	   
   
	gl_Position = modelViewProjectionMatrix * vertex;
}
