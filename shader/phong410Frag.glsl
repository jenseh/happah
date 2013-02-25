#version 410 core

in vec4 vPos;           //World Space
in vec4 vNormal;        //World Space
in vec4 vColor;

uniform mat4 modelMatrix;
uniform mat4 MVP;
uniform mat3 normalMat;
uniform float ka;
uniform float kd;
uniform float ks;
uniform float shininess;
uniform vec3 eye;
uniform float phong;
uniform int hasVertexColor;

layout (location = 0) out vec4 fragmentColor;


void main() {

        vec4 lightPos = vec4(8.0f, 8.0f, 0.0f,1.0f); // CameraSpace
        vec4 lightColor = vec4(0.6f, 0.6f, 0.6f,1.0f);

        vec4 eyeWS   = vec4(eye,1.0f);
        vec4 normalWS = normalize(vNormal);
        vec4 lightWS = normalize(lightPos - vPos);
        vec4 viewWS = normalize(eyeWS-vPos);
        vec4 halfWS = normalize(viewWS + lightWS);


	// Ambient Part
        vec4 Iambient = ka* vColor;
	// Diffuse Part
        float NdotL = dot(normalWS,lightWS);
        vec4 Idiffuse =lightColor* kd * max(NdotL,0.0f) ;

	//Specular Part
        float HdotN = dot(halfWS,normalWS);

        vec4 Ispecular  = lightColor * ks* pow(max(HdotN,0.0f),phong);

       fragmentColor = clamp(Iambient+Idiffuse+Ispecular,0.0f,1.0f);
      //  fragmentColor = vec4(phong,ks,0.0f,1.0f);
	
}
