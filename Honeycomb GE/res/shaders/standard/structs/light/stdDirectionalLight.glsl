#ifndef STD_DIRECTIONAL_LIGHT_GLSL
#define STD_DIRECTIONAL_LIGHT_GLSL

#include <stdBaseLight.glsl>

///
/// The directional light structure.
///
struct DirectionalLight {
    BaseLight base; // The base component of the light
	Shadow shadow;	// The shadow component of the light
    
    vec3 direction; // The direction of the light
};

#endif