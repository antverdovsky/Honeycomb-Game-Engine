#include <stdBaseLight.glsl>

///
/// The ambient light strcture.
///
struct AmbientLight {
    BaseLight base; // The base component of the light
};

/// Calculates the light which should be applied to this fragment, given the
/// ambient light which shines on it.
/// AmbientLight aL : The ambient light which should be calculated.
/// return : The vector which can be used to add or detract lighting from the 
///          fragment.
vec4 calculateAmbientLight(AmbientLight aL) {
    // Calculate the ambient light but do NOT apply the intensity to the W
    // component, so that the surface does not become transparent if the
    // intensity is less than 1.0F.
    return vec4(vec3(aL.base.intensity * aL.base.color.xyz), aL.base.color.w);
}