// Based on Algorithms found @: http://stackoverflow.com/questions/6893302/

/// Packs the specified Vector3 color into a floating point value.
/// vec3 color : The color to be packed.
/// return : The packed floating point value.
float packColor(vec3 color) {
	vec3 col = clamp(round(color * 255.0F), 0.0F, 255.0F);

	return col.r + col.g * 256.0F + col.b * 256.0F * 256.0F;
}

/// Unpacks the specified float into a Vector3 color.
/// float pack : The float to be unpacked.
/// return : The unpacked Vector3 color.
vec3 unpackColor(float pack) {
	vec3 color;

	color.b = floor(pack / (256.0F * 256.0F));
	color.g = floor((pack - color.b * 256.0F * 256.0F) / 256.0F);
	color.r = floor(pack - color.b * 256.0F * 256.0F - color.g * 256.0F);
	
	return color / 255.0F;
}

/*
float packColor(vec4 col) {
    vec4 col2 = clamp(col, 0.0F, 1.0F);

	return dot(col2, vec4(
		1.0F, 1.0F / 255.0F, 1.0F / 65025.0F, 1.0F / 16581375.0F));
}

vec4 unpackColor(float f) {
	vec4 color = vec4(1.0F, 255.0F, 65025.0F, 16581375.0F) * f;

	color = fract(color);
	color -= color.yzww * vec4(
		1.0F / 255.0F, 1.0F / 255.0F, 1.0F / 255.0F, 0.0F);

	return clamp(color, 0,1);
}
*/