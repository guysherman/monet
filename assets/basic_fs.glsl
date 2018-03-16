#version 410
in vec2 texture_coordinates;
in vec4 tc_ne_nw;
in vec4 tc_se_sw;
in vec4 tc_n_s;
in vec4 tc_e_w;
uniform sampler2DRect basic_texture;
uniform sampler2D mask_texture;

layout (location=0) out vec4 frag_colour;
void main () {
	// vec4 texel = texture(basic_texture, texture_coordinates);
	// frag_colour = vec4(texel.r, texel.r, texel.r, 1.0);

	float n = texture(basic_texture, tc_n_s.xy).r;
	float ne = texture(basic_texture, tc_ne_nw.xy).r;
	float e = texture(basic_texture, tc_e_w.xy).r;
	float se = texture(basic_texture, tc_se_sw.xy).r;
	float s = texture(basic_texture, tc_n_s.zw).r;
	float sw = texture(basic_texture, tc_se_sw.zw).r;
	float w = texture(basic_texture, tc_e_w.zw).r;
	float nw = texture(basic_texture, tc_ne_nw.zw).r;
	float c = texture(basic_texture, texture_coordinates).r;

	float horizontal = 0.5 * (w + e);
	float vertical = 0.5 * (n + s);
	float diagonal = 0.25 * (nw + ne + se + sw);
	float adjacent = 0.25 * (n + s + e + w);

	vec4 mask_value = texture(mask_texture, 0.5 * texture_coordinates);

	float r = 	mask_value.r * c +
				mask_value.g * horizontal +
				mask_value.b * diagonal +
				mask_value.a * vertical;

	float g =  	mask_value.r * adjacent +
				mask_value.g * c +
				mask_value.b * adjacent +
				mask_value.a * c;

	float b = 	mask_value.r * diagonal +
				mask_value.g * vertical +
				mask_value.b * c +
				mask_value.a * horizontal;


	frag_colour = vec4(r * 1.819, g, b * 1.484, 1.0) * 2;
	//frag_colour = mask_value;
}
