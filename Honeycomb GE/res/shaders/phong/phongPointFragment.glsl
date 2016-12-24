///
/// Phong Fragment Shader.
///
/// Calculates the lighting on a fragment, and shades it to emulate lighting.
///

#version 330 core

uniform sampler2D textureSampler; // Texture Sampler

#include <standard\stdPhongLight.glsl>

///
/// The point light structure.
///
struct PointLight {
    BaseLight base; // The base component of the light
	Attenuation attenuation; // The attenuation of the light
	
	vec3 position; // The 3D position of the light in the world
    float range; // The sphere-like radius of the light (the higher this value
                 // the more accurate the attenuation of the light).
};

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS
in vec3 out_vs_norm; // Take in the normal outputted by VS
in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform PointLight pointLight; // The point light
uniform Material material; // The material

uniform vec3 cameraPos; // TEMP TEMP TEMP TODO!

/// Calculates the light which should be applied to this fragment, given the
/// point light which shines on it, the material of the surface, the coordinate
/// of the fragment position and the surface normal.
/// PointLight pL : The point light which shines on the surface.
/// Material mat : The material of the surface.
/// vec3 cP : The "position" of the camera in the world.
/// vec3 wP : The world position of the fragment.
/// vec3 norm : The normal of the surface.
/// return : The vector which can be used to add or detract lighting from the
///          fragment.
vec4 calculatePointLight(PointLight pL, Material mat, vec3 cP, vec3 wP, 
        vec3 norm) {
    // Calculate the displacement vector between the world position of the
    // fragment and the point light position.
    vec3 displacement = wP - pL.position;
    
    // Calculate the distance between the fragment and the point light. If the
    // distance exceeds the range of the point light, return a zero vector 
    // since the point light can't affect this fragment.
    float dispMag = length(displacement);
//    if (dispMag > pL.range) return vec4(0.0F, 0.0F, 0.0F, 0.0F); // todo: no significant frame change... redundant?
        
	// Get the unit vector pointing in the direction of the displacement
    vec3 direction  = normalize(displacement);
    
    // Calculate the Attenuation of the Point Light, and the adjusted
    // attenuation which will make the attenuation zero at the range of the
    // point light to allow for a smoother light transition.
	float atten = calculateAttenuation(pL.attenuation, dispMag);
	float intensity = (1.0F / atten) * pL.base.intensity * 
		((pL.range - dispMag) / pL.range);
    
    // Calculate the Diffuse and Specular Light components of the Point Light 
    // and scale by the attenuation to adjust the light with distance.
    vec4 diffuse = calculateDiffuseLight(pL.base, mat, direction, norm);
    vec4 specular = calculateSpecularReflection(pL.base, mat, cP, wP, 
        direction, norm);
    diffuse = vec4(diffuse.xyz * intensity, diffuse.w);
    specular = vec4(specular.xyz * intensity, specular.w);
    
    // Return the blend of the Diffuse and Specular lighting
    return vec4(vec3(diffuse.xyz + specular.xyz), diffuse.w + specular.w);
}

void main() {
    // Calculate the contributions of the Light sources
    vec4 pointComponent = calculatePointLight(pointLight, material, cameraPos,
        out_vs_pos, out_vs_norm);
        
    // Sum up the contributions of the Light sources
    vec4 totalLight = pointComponent;
    
	// Set the color to the color provided by the Texture, mixed with the
    // lighting for this fragment.
	gl_FragColor = vec4(totalLight.xyz, 1.0F) * 
		texture2D(textureSampler, out_vs_texCoord);
}