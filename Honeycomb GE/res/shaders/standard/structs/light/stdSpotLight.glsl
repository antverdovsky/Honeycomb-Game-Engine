#ifndef STD_SPOT_LIGHT_GLSL
#define STD_SPOT_LIGHT_GLSL

#include <stdBaseLight.glsl>

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
    float angle; // The spot angle of the light.
};

#endif