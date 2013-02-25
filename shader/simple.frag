#version 330 compatibility

in vec4 vVertex; // interpolated position in world space           
in vec4 vNormal; // interpolated normal in world space
in vec4 vColor; // interpolated color

uniform vec3 cameraPosition;    
uniform float ambientFactor; 				
uniform float diffuseFactor;				
uniform float specularFactor;				
uniform float phongExponent;			

out vec4 fragmentColor; // color of each pixel	

//SIMPLE BLINN-PHONG SHADING
void main() {
        vec4 lightPosition = vec4(8.0f, 8.0f, 0.0f, 1.0f);    
        vec4 lightColor = vec4(0.6f, 0.6f, 0.6f, 1.0f);

	// calculate lighting in worldspace 
        vec4 cameraPosition4D = vec4(cameraPosition, 1.0f);
        vec4 normal = normalize(vNormal);
        vec4 lightDirection = normalize(lightPosition - vVertex);
        vec4 viewVector = normalize(cameraPosition4D - vVertex);
        vec4 halfwayVector = normalize(viewVector + lightDirection);

	// ambient contribution 
        vec4 ambientIntensity = ambientFactor * vColor;
        
	// diffuse contribution
        float normalDotLightDirection = dot(normal, lightDirection);
        vec4 diffuseIntensity = lightColor * diffuseFactor * max(normalDotLightDirection, 0.0f) ;

	// specular contribution
        float halfwayVectorDotNormal = dot(halfwayVector, normal);
        vec4 specularIntensity  = lightColor * specularFactor * pow(max(halfwayVectorDotNormal, 0.0f), phongExponent);

	// add all Contributions
	fragmentColor = clamp(ambientIntensity + diffuseIntensity + specularIntensity, 0.0f, 1.0f);
     
	
}
