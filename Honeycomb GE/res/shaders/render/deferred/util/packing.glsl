/// Packs the specified Vector3 color into a unsigned integer value.
/// vec3 color : The color to be packed.
/// return : The packed unsigned integer value.
uint packRGB(vec3 color) {
	vec3 col = clamp(color * 255.0F, 0.0F, 255.0F);

	uint r = uint(col.r) << 24;
	uint g = uint(col.g) << 16;
	uint b = uint(col.b) <<  8;

	uint rgb = r + g + b;
	return rgb;
}

/// Packs the specified Vector4 color into a unsigned integer value.
/// vec4 color : The color to be packed.
/// return : The packed unsigned integer value.
uint packRGBA(vec4 color) {
	vec4 col = clamp(color * 255.0F, 0.0F, 255.0F);

	uint r = uint(col.r) << 24;
	uint g = uint(col.g) << 16;
	uint b = uint(col.b) <<  8;
	uint a = uint(col.a) <<  0;

	uint rgba = r + g + b + a;
	return rgba;
}

/// Unpacks the specified unsigned integer into a Vector3 color.
/// uint pack : The unsigned integer to be unpacked.
/// return : The unpacked Vector3 color.
vec3 unpackRGB(uint pack) {
	float r = float((pack & 0xFF000000U) >> 24) / 255.0F;
	float g = float((pack & 0x00FF0000U) >> 16) / 255.0F;
	float b = float((pack & 0x0000FF00U) >>  8) / 255.0F;

	return vec3(r, g, b);
}

/// Unpacks the specified unsigned integer into a Vector3 color.
/// uint pack : The unsigned integer to be unpacked.
/// return : The unpacked Vector3 color.
vec4 unpackRGBA(uint pack) {
	float r = float((pack & 0xFF000000U) >> 24) / 255.0F;
	float g = float((pack & 0x00FF0000U) >> 16) / 255.0F;
	float b = float((pack & 0x0000FF00U) >>  8) / 255.0F;
	float a = float((pack & 0x000000FFU) >>  0) / 255.0F;

	return vec4(r, g, b, a);
}