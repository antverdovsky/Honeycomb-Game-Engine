#ifndef STD_AMBIENT_LIGHT_GLSL
#define STD_AMBIENT_LIGHT_GLSL

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
/// return : The ambient light color.
vec3 calculateAmbientLight(AmbientLight aL) {
    // Calculate the ambient light but do NOT apply the intensity to the W
    // component, so that the surface does not become transparent if the
    // intensity is less than 1.0F.
    return aL.base.intensity * aL.base.color.xyz;
}

#endif