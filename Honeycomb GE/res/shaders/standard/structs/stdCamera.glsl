#ifndef STD_CAMERA_GLSL
#define STD_CAMERA_GLSL

///
/// The Standard Camera Structure.
///
struct Camera {
	float width; // The width of the projection
	float height; // The height of the projection

    mat4 projection; // The projection of the Camera
    mat4 view; // The view of the camera (Projection / Orien. & Trans.)
    vec3 translation; // The position of the Camera
};

#endif