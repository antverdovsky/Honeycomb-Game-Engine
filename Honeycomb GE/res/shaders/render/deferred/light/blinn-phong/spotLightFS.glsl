#version 330 core

#include <../../../../util/packing.glsl>
#include <../../../../standard/structs/stdMaterial.glsl>
#include <../../../../standard/light/blinn-phong/blinnPhongSpot.glsl>

in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform SpotLight spotLight; // The spot light
uniform Camera camera;

uniform sampler2D gBufferPosition;
uniform sampler2D gBufferMaterial;
uniform sampler2D gBufferNormal;

uniform sampler2D shadowMap;

out vec4 fragColor;

void main() {
    vec2 screenCoord = vec2(gl_FragCoord.x / camera.width,
							gl_FragCoord.y / camera.height);
    
    vec3 pos = texture2D(gBufferPosition, screenCoord).xyz;
    vec3 norm = normalize(texture2D(gBufferNormal, screenCoord).xyz);
	
	vec4 mat = texture2D(gBufferMaterial, screenCoord);
	vec4 specShine = unpackRGBA(mat.a);
	
	vec3 diffuse = unpackRGB(mat.b);
	vec3 spec = specShine.rgb;
	float shine = specShine.a * 255.0F;

	vec4 shadowCoords = spotLight.shadow.projection * vec4(pos, 1.0F);

	fragColor = vec4(calculateSpotLight(spotLight, camera, pos, norm, shine, 
		spec, diffuse, shadowMap, shadowCoords), 1.0F);
}