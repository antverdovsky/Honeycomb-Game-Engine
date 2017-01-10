///
/// The Standard Camera Structure.
///
struct Camera {
	float width; // The width of the projection
	float height; // The height of the projection

    mat4 projection; // The projection of the Camera
    vec3 translation; // The position of the Camera
};