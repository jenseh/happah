#version 330

in vec4 gVertex;
in vec4 gColor;
in vec3 vertexLightPosition;
in vec4 camPosition;

uniform mat4 projectionMatrix;
uniform float pointRadius;	
	
out vec4 fragmentColor; 

void main(){
	
	
	float x = gl_TexCoord[0].x;
	float y = gl_TexCoord[0].y;
	float z2 = 1.0f- x*x -y*y;
	
	if(z2 <= 0.0f)
		discard;
		
	float z = sqrt(z2);
	
	vec3 normal = vec3(x,y,z);
	
	float diffuseIntensity = max(dot(normal , vertexLightPosition),0.0f	);
	
	vec4 pos = camPosition;
	pos.z = z* pointRadius;
	pos = projectionMatrix * pos;
	
	//gl_FragDepth = (pos.z / pos.w+1.0f) / 2.0f;
	fragmentColor = gColor * diffuseIntensity;
	
	//fragmentColor = gl_TexCoord[0];
}