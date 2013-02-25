#version 330 compatibility


// === INPUT VERTEX ATTRIBUTES  === //
in vec4 vertex;					    // vertex position model space
in vec4 normal;					    // vertex normal modelSpace
in vec4 color;					    // vertex color

// ===           UNIFORMS      ===  //
uniform mat4 MMatrix;				// model  			 Matrix
uniform mat4 MVPMatrix;				// model - view - projection Matrix
uniform mat3 NMatrix;					// normal 					 Matrix



// ===   VERTEX SHADER OUTPUT   === //
out vec4 vVertex;				// vertex position world space				
out vec4 vNormal;					// vertex normal world space
out vec4 vColor;					// vertex color

void main(){
		
    vVertex = MMatrix * vertex;      

    vNormal = normalize(normal);
    vec3 vNormal3 =  vNormal.xyz;
    vNormal3 = NMatrix*vNormal3;
    vNormal = vec4(vNormal3,1.0f);  
   
	vColor = color;	   
   
    gl_Position = MVPMatrix * vertex;
       
}
