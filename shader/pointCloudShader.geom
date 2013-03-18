#version 330 compatibility

layout (points) in;
layout(triangle_strip, max_vertices=4) out;

in vec4 vColor[];

uniform mat4 modelViewMatrix;	
uniform mat4 projectionMatrix;
uniform float pointRadius;

out vec4 gVertex;
out vec4 gColor;
out vec3 vertexLightPosition;
out vec4 camPosition;

void main(){
		
		float size = pointRadius*0.5f;
		gl_TexCoord[0]= gl_in[0].gl_TexCoord[0];
		gColor = vColor[0];
		
		vertexLightPosition = normalize(vec3(3.0f,0.0f,5.0f));
		camPosition = gl_in[0].gl_Position;
		
		gl_TexCoord[0].st = vec2(-1.0f,-1.0f);
		vec4 pos = gl_in[0].gl_Position;
		pos.xy += vec2(-size,-size);
		gl_Position = projectionMatrix * pos;
		EmitVertex();
	
		gl_TexCoord[0].st = vec2(-1.0f,1.0f);
		pos = gl_in[0].gl_Position;
		pos.xy += vec2(-size,size);
		gl_Position = projectionMatrix * pos;
		EmitVertex();
		
		gl_TexCoord[0].st = vec2(1.0f,-1.0f);
		pos = gl_in[0].gl_Position;
		pos.xy += vec2(size,-size);
		gl_Position = projectionMatrix * pos;
		EmitVertex();
		
		gl_TexCoord[0].st = vec2(1.0f,1.0f);
		pos = gl_in[0].gl_Position;
		pos.xy += vec2(size,size);
		gl_Position = projectionMatrix * pos;
		EmitVertex();
		
		EndPrimitive();
}