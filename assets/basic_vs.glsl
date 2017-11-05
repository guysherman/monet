#version 410
layout (location = 0) in vec2 vp;
layout (location = 1) in vec4 col;
layout (location = 2) in vec2 tc;
uniform mat4 matrix;

out vec4 vertex_colors;
out vec2 texture_coordinates;

void main () {
	texture_coordinates = tc;
	vertex_colors = col;
	gl_Position = matrix * vec4 (vp, 0.0, 1.0);
}
