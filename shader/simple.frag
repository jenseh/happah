#version 330 compatibility

// === VERTEX SHADER OUTPUT === //
in vec4 vVertex;				// interpolated position in world space           
in vec4 vNormal;        		// interpolated normal in world space
in vec4 vColor;					// interpolated color

// === 		UNIFORMS		=== //
uniform vec3 cameraPosition;    // camera position in world space

//		shading materials		//
uniform float ka; 				// ambient  factor
uniform float kd;				// diffuse  factor
uniform float ks;				// specular factor	
uniform float phong;			// phong exponent for specular lighting


// === FRAGMENT SHADER OUTPUT === //
out vec4 fragmentColor;			  // color of each pixel	


void main() {
		// SIMPLE BLINN-PHONG SHADING //
		
        vec4 lightPos 	= vec4(8.0f, 8.0f, 0.0f,1.0f);    
        vec4 lightColor = vec4(0.6f, 0.6f, 0.6f,1.0f);

		// calculate vectors needed  
        vec4 camPosWS   = vec4(cameraPosition,1.0f);
        vec4 normalWS 	= normalize(vNormal);
        vec4 lightWS 	= normalize(lightPos - vVertex);
        vec4 viewWS 	= normalize(camPosWS-vVertex);
        vec4 halfWS 	= normalize(viewWS + lightWS);


		// ambient contribution 
        vec4 Iambient 	= ka* vColor;
        
		// diffuse contribution
        float NdotL 	= dot(normalWS,lightWS);
        vec4 Idiffuse 	=lightColor* kd * max(NdotL,0.0f) ;

		// specular contribution
        float HdotN 	= dot(halfWS,normalWS);
        vec4 Ispecular  = lightColor * ks* pow(max(HdotN,0.0f),phong);

       // add all Contributions
       fragmentColor 	= clamp(Iambient+Idiffuse+Ispecular,0.0f,1.0f);
     
	
}