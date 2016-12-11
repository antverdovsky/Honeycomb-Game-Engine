#version 330

/// TODO... put the structures in some container, as they are being recopied...

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
/// The directional light structure.
///
struct DirectionalLight {
    BaseLight base; // The base component of the light
    
    vec3 direction; // The direction of the light
};

in vec2 ovs_TexturePosition; // Take in texture coordinate outputted by VS
in vec3 ovs_Normal; // Take in the normal outputted by VS
in vec3 ovs_Position; // Take in the world position outputted by VS

uniform Material ufs_Material; // The material for this Fragment
uniform sampler2D ufs_Texture; // Texture Sampler [todo]
uniform vec3 ufs_CameraPosition; // Camera Position
uniform DirectionalLight ufs_DirectionalLight; // Directional Light

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
    vec4 specular = calculateSpecularReflection(dL.base, mat, cP, wP, 
        dL.direction, norm);
    
    // Return the blend of the Diffuse and Specular lighting
    return diffuse + specular;
}

void main() {
    vec4 light = calculateDirectionalLight(ufs_DirectionalLight, 
        ufs_Material, ufs_CameraPosition, ovs_Position, ovs_Normal);
        
    gl_FragColor = texture2D(ufs_Texture, ovs_TexturePosition) * light;
}