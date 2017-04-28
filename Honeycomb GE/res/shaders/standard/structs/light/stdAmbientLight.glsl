#ifndef STD_AMBIENT_LIGHT_GLSL
#define STD_AMBIENT_LIGHT_GLSL

#include <stdBaseLight.glsl>

///
/// The ambient light strcture.
///
struct AmbientLight {
    BaseLight base; // The base component of the light
};

#endif