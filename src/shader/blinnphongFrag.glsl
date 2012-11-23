#version 330 compatibility

// TransformationsMatritzen
uniform mat4 MVP,MV;


// KameraPosition
uniform vec3 eye;


// Output des VertexShaders
in vec3 vNormal,vWorldPosition;




void main( void)
{
    gl_FragColor = vec4(0.3f,0.1f,0.4f,1.0f);

    // Lichtposition und Farbe sind hier FIX im Worldspace angegeben

    vec3 lightPosition[2];
    vec4 lightColor[2];
    lightPosition[0] = vec3(5.0f,5.0f,5.0f);
    lightPosition[1] = vec3(-5.0f,-5.0f,-5.0f);
    lightColor[0] = vec4(0.4f,0.0f,0.4f,1.0f);  // Rotes Licht
    lightColor[1] = vec4(0.0f,0.4f,0.4f,1.0f);	// Blaues Licht


    // Blinn Phong Beleuchtung für jedes der Lichter
    for(int i = 0; i < 2; i ++){
        vec3 lightWS  = normalize(lightPosition[i] - vWorldPosition);
        vec3 viewWS   = normalize(eye - vWorldPosition);
        vec3 halfwayWS = normalize(lightWS + viewWS);
        float phong = 5.0f;

        float diffuse = max(0.0f, dot(lightWS,vNormal));
        float specular = max(0.0f, pow(dot(halfwayWS,vNormal),phong));


    	 gl_FragColor += (specular+diffuse)*lightColor[i];
		
    }
    

}
