#version 410
layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 tc;
uniform mat4 matrix;

out vec2 texture_coordinates;
out vec4 tc_ne_nw;
out vec4 tc_se_sw;
out vec4 tc_n_s;
out vec4 tc_e_w;

void main () {
	texture_coordinates = tc;

	tc_ne_nw.xy = tc + vec2( 1, -1);
	tc_ne_nw.zw = tc + vec2(-1, -1);

	tc_se_sw.xy = tc + vec2( 1, 1);
	tc_se_sw.zw = tc + vec2(-1, 1);

	tc_n_s.xy = tc + vec2( 0, -1);
	tc_n_s.zw = tc + vec2( 0,  1);

	tc_e_w.xy = tc + vec2( 1,  0);
	tc_e_w.zw = tc + vec2(-1,  0);

	gl_Position = matrix * vec4 (vp, 0.0, 1.0);
}
