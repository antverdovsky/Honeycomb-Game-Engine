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
    vec4 color; // The color of the light
    float intensity; // The intensity of the light
};

///
/// The attenuation structure.
///
struct Attenuation {
	float constant; // The constant coefficient in the attenuation equation
	float linear; // The linear coefficient in the attenuation equation
	float quadratic; // The quadratic coefficient in the attenuation equation
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
	Attenuation attenuation; // The attenuation of the light
	
	vec3 position; // The 3D position of the light in the world
    float range; // The sphere-like radius of the light (the higher this value
                 // the more accurate the attenuation of the light).
};

///
/// The spot light structure
///
struct SpotLight {
    BaseLight base; // The base component of the light
    Attenuation attenuation; // The attenuation of the light

    vec3 position; // The 3D position of the light in the world
    vec3 direction; // The direction of the light in the world
    
    float range; // The range of the light (height of the cone formed by the 
                 // light point and light ray).
    float cosAngle; // The cosine of the spot angle of the light (angle of 
                        // the 1 / 2 cone formed by the light point and the 
                        // light ray).
};

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS
in vec3 out_vs_norm; // Take in the normal outputted by VS
in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform AmbientLight ambientLight; // The ambient light
uniform DirectionalLight directionalLight; // The directional light (TODO: ARRAY of many lights)
uniform PointLight pointLight; // The point light (TODO: ARRAY...)
uniform SpotLight spotLight; // The spot light (TODO: ARRAY)
uniform Material material; // The material

uniform vec3 cameraPos; // TEMP TEMP TEMP TODO!

/// Forward Declarations
vec4 calculateAmbientLight(AmbientLight aL, Material mat);
float calculateAttenuation(Attenuation atten);
vec4 calculateDiffuseLight(BaseLight bL, Material mat, vec3 dir, vec3 norm);
vec4 calculateDirectionalLight(DirectionalLight dL, Material mat, vec3 cP,
    vec3 wP, vec3 norm);
vec4 calculatePointLight(PointLight pL, Material mat, vec3 cP, vec3 wP, 
    vec3 norm);
vec4 calculateSpecularReflection(BaseLight bL, Material mat, vec3 cP, vec3 wP,
    vec3 dir, vec3 norm);
vec4 calculateSpotLight(SpotLight sL, Material mat, vec3 cP, vec3 wP, 
    vec3 norm);

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

/// Calculates the attenuation of the specified attenuation component at the
/// specified distance.
/// Attenuation atten : The attenuation component.
/// float d : The distance of the fragment from the light.
/// return : The value of the attenuation at the fragment distance given.
float calculateAttenuation(Attenuation atten, float d) {
	return (atten.constant + atten.linear * d + atten.quadratic * d * d);
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
    // Calculate the displacement vector between the world position of the
    // fragment and the point light position.
    vec3 displacement = wP - pL.position;
    
    // Calculate the distance between the fragment and the point light. If the
    // distance exceeds the range of the point light, return a zero vector 
    // since the point light can't affect this fragment.
    float dispMag = length(displacement);
    if (dispMag > pL.range) return vec4(0.0F, 0.0F, 0.0F, 0.0F);
        
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

/// Calculates the light which should be applied to this fragment given the
/// spot light which shines upon it, the material of the surface, the camera
/// position, the world position of the fragment and the normal of the surface
/// normal.
/// SpotLight sL : The spot light which shines on this fragment.
/// Material mat : The material of the surface on this fragment.
/// vec3 cP : The world position of the camera.
/// vec3 wP : The world position of this fragment.
/// vec3 norm : The normalized normal of the surface.
vec4 calculateSpotLight(SpotLight sL, Material mat, vec3 cP, vec3 wP, 
        vec3 norm) {
    // Calculate the displacement vector between the world position of the
    // fragment and the spot light position.
    vec3 displacement = wP - sL.position;
    
    // Calculate the distance between the fragment and the point light. If the
    // distance exceeds the range of the point light, return a zero vector 
    // since the point light can't affect this fragment.
    float dispMag = length(displacement);
    if (dispMag > sL.range) return vec4(0.0F, 0.0F, 0.0F, 0.0F);
    
    // Calculate the angle between the fragment and the spot light. If the 
    // angle exceeds the angle of the spot light, return a zero vector since
    // the spot light can't affect this fragment.
    vec3 direction = normalize(displacement);
    float cosAngle = dot(direction, normalize(sL.direction));
    if (cosAngle < sL.cosAngle) return vec4(0.0F, 0.0F, 0.0F, 0.0F);
    
    // Calculate the Attenuation of the Point Light, and the adjusted
    // attenuation which will make the attenuation zero at the range of the
    // spot light and zero at the edge of the angle of the spot light to allow 
    // for a smoother light transition.
    float atten = calculateAttenuation(sL.attenuation, dispMag);
    float intensity = (1.0F / atten) * sL.base.intensity * 
        (1.0F - (1.0F - cosAngle) / (1.0F - sL.cosAngle)) * 
        ((sL.range - dispMag) / sL.range);
    
    // Calculate the Diffuse and Specular Light components of the Spot Light 
    // and scale by the attenuation to adjust the light with distance.
    vec4 diffuse = calculateDiffuseLight(sL.base, mat, direction, norm);
    vec4 specular = calculateSpecularReflection(sL.base, mat, cP, wP, 
        direction, norm);
    diffuse = vec4(diffuse.xyz * intensity, diffuse.w);
    specular = vec4(specular.xyz * intensity, specular.w);
    
    // Return the blend of the Diffuse and Specular lighting
    return diffuse + specular;
}

void main() {
    // Calculate the contributions of the Light sources
    vec4 ambientComponent = calculateAmbientLight(ambientLight, material);
    vec4 directionalComponent = calculateDirectionalLight(directionalLight,
        material, cameraPos, out_vs_pos, out_vs_norm);
    vec4 pointComponent = calculatePointLight(pointLight, material, cameraPos,
        out_vs_pos, out_vs_norm);
    vec4 spotComponent  = calculateSpotLight(spotLight, material, cameraPos,
        out_vs_pos, out_vs_norm);
        
    // Sum up the contributions of the Light sources
    vec4 totalLight = ambientComponent + directionalComponent + 
        pointComponent + spotComponent;
    
	// Set the color to the color provided by the Texture, mixed with the
    // lighting for this fragment.
	gl_FragColor = vec4(totalLight.xyz, 1.0F);// * texture2D(textureSampler, out_vs_texCoord);
}