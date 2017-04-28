#ifndef PACKING_GLSL
#define PACKING_GLSL

/// Packs the specified Vector3 color into a floating point value.
/// vec3 color : The color to be packed.
/// return : The packed floating point value.
float packRGB(vec3 color) {
	vec3 col = clamp(color * 255.0F, 0.0F, 255.0F);

	uint r = uint(col.r) << 24;
	uint g = uint(col.g) << 16;
	uint b = uint(col.b) <<  8;

	uint rgb = r + g + b;
	float ieeeRGB = uintBitsToFloat(rgb);

	return ieeeRGB;
}

/// Packs the specified Vector4 color into a floating point value.
/// vec4 color : The color to be packed.
/// return : The packed floating point value.
float packRGBA(vec4 color) {
	vec4 col = clamp(color * 255.0F, 0.0F, 255.0F);

	uint r = uint(col.r) << 24;
	uint g = uint(col.g) << 16;
	uint b = uint(col.b) <<  8;
	uint a = uint(col.a) <<  0;

	uint rgba = r + g + b + a;
	float ieeeRGBA = uintBitsToFloat(rgba);

	return ieeeRGBA;
}

/// Unpacks the specified float into a Vector3 color.
/// float pack : The float to be unpacked.
/// return : The unpacked Vector3 color.
vec3 unpackRGB(float pack) {
	uint rgb = floatBitsToUint(pack);

	float r = float((rgb & 0xFF000000U) >> 24) / 255.0F;
	float g = float((rgb & 0x00FF0000U) >> 16) / 255.0F;
	float b = float((rgb & 0x0000FF00U) >>  8) / 255.0F;

	return vec3(r, g, b);
}

/// Unpacks the specified float into a Vector4 color.
/// float pack : The float to be unpacked.
/// return : The unpacked Vector3 color.
vec4 unpackRGBA(float pack) {
	uint rgba = floatBitsToUint(pack);

	float r = float((rgba & 0xFF000000U) >> 24) / 255.0F;
	float g = float((rgba & 0x00FF0000U) >> 16) / 255.0F;
	float b = float((rgba & 0x0000FF00U) >>  8) / 255.0F;
	float a = float((rgba & 0x000000FFU) >>  0) / 255.0F;

	return vec4(r, g, b, a);
}

#endif