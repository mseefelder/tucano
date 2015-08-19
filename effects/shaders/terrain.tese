
#version 430 core


//layout (triangles, equal_spacing, cw) in;
layout (triangles, fractional_odd_spacing, cw) in;



in TC_OUT
{
    vec3 position;
	vec3 normal;
	vec2 uv;
	float depth;
} te_in[]; 


out TE_OUT
{
    vec3 position;
	vec3 normal;
	vec2 uv;
	float depth;
} te_out; 


uniform sampler2D in_HeightMap;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform float depthLevel;


void main()
{
	
	vec4 tePos =(gl_TessCoord.x * gl_in[0].gl_Position) +
				(gl_TessCoord.y * gl_in[1].gl_Position) +
				(gl_TessCoord.z * gl_in[2].gl_Position);
	te_out.position = (modelViewMatrix * tePos).xyz;
	

	vec3 teNormal =	(gl_TessCoord.x * te_in[0].normal) +
					(gl_TessCoord.y * te_in[1].normal) +
					(gl_TessCoord.z * te_in[2].normal);
	te_out.normal = teNormal;
	te_out.normal = vec3(modelViewMatrix * vec4(teNormal,0.0)).xyz;


	vec2 teUV =	(gl_TessCoord.x * te_in[0].uv) +
				(gl_TessCoord.y * te_in[1].uv) +
				(gl_TessCoord.z * te_in[2].uv);
	te_out.uv = teUV;

	te_out.depth =	(gl_TessCoord.x * te_in[0].depth) +
					(gl_TessCoord.y * te_in[1].depth) +
					(gl_TessCoord.z * te_in[2].depth);


	float height = texture(in_HeightMap, te_out.uv).r;
	tePos.y += height * depthLevel - (depthLevel * 0.5f);


	gl_Position = projectionMatrix * modelViewMatrix * tePos;
	te_out.position = (modelViewMatrix * tePos).xyz;
}

