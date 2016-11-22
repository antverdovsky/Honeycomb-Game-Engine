///
/// Phong Fragment Shader.
///
/// Calculates the lighting on a fragment, and shades it to emulate lighting.
///

#version 330 core

uniform sampler2D textureSampler; // Texture Sampler

///
/// The material structure.
///
struct Material {
    vec4 ambientColor; // Color under ambient light
    vec4 diffuseColor; // Color under diffuse light.
    vec4 specularColor; // Color under specular light
    float shininess; // Shininess for the Specular Spread
};

///
/// The basic structure for all lights.
/// 
struct BaseLight {
    float intensity; // The intensity of the light
    vec4 color; // The color of the light
};

///
/// The ambient light strcture.
///
struct AmbientLight {
    BaseLight base; // The base component of the light
};

///
/// The directional light structure.
///
struct DirectionalLight {
    BaseLight base; // The base component of the light
    vec3 direction; // The direction of the light
};

///
/// The point light structure.
///
struct PointLight {
    BaseLight base; // The base component of the light

	float constant; // The constant term in the Attenuation
	float linear; // The linear term in the Attenuation
	float quadratic; // The quadratic term in the Attenuation
	
	vec3 position; // The 3D position of the light in the world
};

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS
in vec3 out_vs_norm; // Take in the normal outputted by VS
in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform AmbientLight ambientLight; // The ambient light
uniform DirectionalLight directionalLight; // The directional light (TODO: ARRAY of many lights)
uniform PointLight pointLight; // The point light (TODO: ARRAY...)
uniform Material material; // The material

uniform vec3 cameraPos; // TEMP TEMP TEMP TODO!

/// Forward Declarations
vec4 calculateAmbientLight(AmbientLight aL, Material mat);
vec4 calculateDiffuseLight(BaseLight bL, Material mat, vec3 dir, vec3 norm);
vec4 calculateDirectionalLight(DirectionalLight dL, Material mat, vec3 norm);
vec4 calculatePointLight(PointLight pL, Material mat, vec3 norm);
vec4 calculateSpecularReflection(BaseLight bL, Material mat, vec3 cP, vec3 wP,
        vec3 dir, vec3 norm);

/// Calculates the light which should be applied to this fragment, given the
/// ambient light which shines on it.
/// AmbientLight aL : The ambient light which should be calculated.
/// Material mat : The material for which the light should be calculated.
/// return : The vector which can be used to add or detract lighting from the 
///          fragment.
vec4 calculateAmbientLight(AmbientLight aL, Material mat) {
    // Calculate the ambient light but do NOT apply the intensity to the W
    // component, so that the surface does not become transparent if the
    // intensity is less than 1.0F.
    return vec4(
        vec3(aL.base.intensity * aL.base.color.xyz * mat.ambientColor.xyz *
            aL.base.color.w * mat.ambientColor.w),
        aL.base.color.w * mat.ambientColor.w);             
}

/// Calculates the diffuse light which should be applied to this fragment, 
/// given some base light which shines on it.
/// BaseLight bL : The base light which should be calculated.
/// Material mat : The material for which the light should be calculated.
/// vec3 dir : The direction with which the BaseLight shines upon the surface.
/// vec3 norm : The normal of the surface on which the BaseLight shines upon.
///             This should be normalized, prior to being passed in.
/// return : The vector which can be used to add or detract lighting from the
///          fragment.
vec4 calculateDiffuseLight(BaseLight bL, Material mat, vec3 dir, vec3 norm) {
    float diff = max(dot(-dir, norm), 0.0F);
    
    // Calculate the diffuse light but do NOT apply the intensity to the W
    // component, so that the surface does not become transparent if the
    // intensity is less than 1.0F.
    return vec4(
        vec3(diff * bL.intensity * bL.color.xyz * mat.diffuseColor.xyz * 
            bL.color.w * mat.diffuseColor.w),
        bL.color.w * mat.diffuseColor.w);
}

/// Calculates the light which should be applied to this fragment, given the
/// directional light which shines on it and the normal of the surface.
/// DirectionLight dL : The directional light which will be used to calculate
///                     the effect of the light.
/// Material mat : The material for which the light should be calculated.
/// vec3 cP : The "position" of the camera in the world.
/// vec3 wP : The world position of the fragment.
/// vec3 norm : The normal vector of the surface. This should be normalized,
///             prior to being passed in.
/// return : The vector which can be used to add or detract lighting from the
///          fragment.
vec4 calculateDirectionalLight(DirectionalLight dL, Material mat, vec3 cP,
        vec3 wP, vec3 norm) {
    // Calculate the Diffuse and Specular Light components of the Directional
    // Light.
    vec4 diffuse = calculateDiffuseLight(dL.base, mat, dL.direction, norm);
    vec4 specular = calculateSpecularReflection(dL.base, mat, cameraPos, wP, 
        dL.direction, norm);
    
    // Return the blend of the Diffuse and Specular lighting
    return diffuse + specular;
}

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
	// Both variables refer to the quantity between the Point Light position
    // and the Fragment position.
    vec3 direction  = normalize(wP - pL.position); // Direction
	float displacement  = length(wP - pL.position); // Distance
    
    // Calculate the Attenuation of the Point Light
    float atten = pL.base.intensity / (pL.constant + pL.linear * displacement +
        pL.quadratic * displacement * displacement);
    
    // Calculate the Diffuse and Specular Light components of the Point Light 
    // and scale by the attenuation to adjust the light with distance.
    vec4 diffuse = calculateDiffuseLight(pL.base, mat, direction, norm);
    vec4 specular = calculateSpecularReflection(pL.base, mat, cP, wP, 
        direction, norm);
    diffuse = vec4(diffuse.xyz * atten, diffuse.w);
    specular = vec4(specular.xyz * atten, specular.w);
        
    // Return the blend of the Diffuse and Specular lighting
    return diffuse + specular;
}

/// Calculates the specular reflection for this fragment given the light for
/// which the reflection is being computed, the material of the surface and the
/// coordinates of the camera and the fragment.
/// BaseLight bL : The light for which the reflection is being computed.
/// Material mat : The material of the surface.
/// vec3 cP : The "position" of the camera in the world.
/// vec3 wP : The position of the fragment in the world.
/// vec3 dir : The direction with which the light hits the surface.
/// vec3 norm : The normal to the surface.
vec4 calculateSpecularReflection(BaseLight bL, Material mat, vec3 cP, vec3 wP,
        vec3 dir, vec3 norm) {
    vec3 direction = normalize(cP - wP); // Direction from Cam to Frag
    vec3 reflection = normalize(reflect(dir, norm)); // Get the reflection
    
    // Calculate the specular reflection factor
    float spec = pow(max(dot(direction, reflection), 0.0F), mat.shininess);
    
    // Calculate the specular light but do NOT apply the intensity to the W
    // component, so that the surface does not become transparent if the
    // intensity is less than 1.0F.
    return vec4(
        vec3(spec * bL.intensity * bL.color.xyz * mat.specularColor.xyz *
            bL.color.w * mat.specularColor.w),
        bL.color.w * mat.specularColor.w);
}

void main() {
    // Calculate the contributions of the Light sources
    vec4 ambientComponent = calculateAmbientLight(ambientLight, material);
    vec4 directionalComponent = calculateDirectionalLight(directionalLight,
        material, cameraPos, out_vs_pos, out_vs_norm);
    vec4 pointComponent = calculatePointLight(pointLight, material, cameraPos,
        out_vs_pos, out_vs_norm);
        
    // Sum up the contributions of the Light sources
    vec4 totalLight = ambientComponent + directionalComponent + pointComponent;
    
	// Set the color to the color provided by the Texture, mixed with the
    // lighting for this fragment.
	gl_FragColor = vec4(totalLight.xyz, 1.0F) * texture2D(textureSampler, out_vs_texCoord);
}