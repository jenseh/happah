#version 330 compatibility

// TransformationsMatritzen
uniform mat4 MVP, MV;


// KameraPosition
uniform vec3 eye;

// Material
uniform float ka,kd,ks;
uniform float shininess;

// Output des VertexShaders
in vec3 vNormal, vWorldPosition;
in vec4 vColor;



void main( void)
{
    // Lichtposition und Farbe sind hier FIX im Worldspace angegeben

    vec3 lightPosition[2];
    vec4 lightColor[2];
    lightPosition[0] = vec3(5.0f, 5.0f, 5.0f);
    lightPosition[1] = vec3(-5.0f, 5.0f, -5.0f);
    lightColor[0] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    lightColor[1] = vec4(1.0f, 0.0f, 1.0f, 1.0f);

    // Change as soon as every vertex has its own coloer
    // Ambient background lighting
   gl_FragColor =ka* vColor;
  		 

    // Blinn Phong lighting for each light source
    for(int i = 0; i < 2; i ++){
        vec3 lightWS  = normalize(lightPosition[i] - vWorldPosition);
        vec3 viewWS   = normalize(eye - vWorldPosition);
        vec3 halfwayWS = normalize(lightWS + viewWS);

        float diffuse = max(0.0f, dot(lightWS, normalize(vNormal)));
        float specular = pow(max(0.0f, dot(halfwayWS, vNormal)), shininess);




         gl_FragColor += (diffuse * kd + specular * ks) * lightColor[i];

    }

}
