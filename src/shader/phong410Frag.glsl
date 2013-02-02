#version 410 compatibility

in vec4 vPosWS;
in vec4 vNormalWS;
in vec4 vColor;

//uniform float ka;
//uniform float kd;
//uniform float ks;
//uniform float shininess;


layout (location = 0) out vec4 fragmentColor;


void main() {

	vec4 lightPosWS = vec4(2.0f, 2.0f, 2.0f,1.0f);
	vec4 lightColor = vec4(0.4f, 0.0f, 0.8f,1.0f);
	//vec4 ka = vec4(1.0f,1.0f,1.0f,1.0f);
	//vec4 kd = vec4(0.5f,0.5f,0.5f,0.0f);
	//vec4 ks = vec4(1.6f,1.6f,1.6f,1.0f);	
	float ka= 1.0f;
	float kd = 0.5f;
 	float ks = 1.0f;
	float shininess = 20.0f;
	
	vec4 normalWS = normalize(vNormalWS);
	vec4 lightWS = normalize(lightPosWS - vPosWS);
	vec4 viewWS = normalize(vPosWS);
	vec4 halfWS = normalize(viewWS + lightWS);


	// Ambient Part
	vec4 Iambient = vec4(0.3f,0.3f,0.3f,1.0f) * ka;			
	// Diffuse Part
	vec4 Idiff    = lightColor * kd * max(dot(lightWS,normalWS),0.0f) ;
	
	//Specular Part
	vec4 Ispec    = lightColor * ks * pow(max(dot(halfWS,normalWS),0.0f),shininess) ;	

	fragmentColor = Iambient+Idiff+Ispec;	
	
}