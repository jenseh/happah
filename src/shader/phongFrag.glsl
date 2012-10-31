#version 330 compatibility


in vec4 normal;
uniform vec4 vertexOut;
uniform vec4 eye;
layout(location = 0, index = 0) out vec4 fragColor;



void main( void)
{
	vec4 lightPosition[2];
	vec4 ambient[2];
	
		
	lightPosition[0] = vec4(3.0f,5.0f,5.0f,1.0f);
	ambient[0] = vec4(1.0f,0.0f,1.0f,1.0f);
	
	lightPosition[1] = vec4(-4.0f,-4.0f,-3.0f,1.0f);
	ambient[1] = vec4(0.0f,1.0f,1.0f,1.0f);
	
	for (int i=0; i <2 ; i++){
	
	vec4 lightWS = normalize(lightPosition[i]-vertexOut);
	vec4 viewWS =  normalize(eye - vertexOut);
	vec4 halfwayWS = normalize(lightWS + viewWS);
	float phong = 10.0f;
	
	float diffuse = max(0.0f, dot(lightWS,normal));
	float specular = max(0.0f, pow(dot(halfwayWS,normal),phong));

	
	gl_FragColor+= (diffuse + specular)*ambient[i];
	
	}
	
	
}
