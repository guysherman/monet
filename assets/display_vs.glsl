#version 410
layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 tc;
uniform mat4 matrix;

out vec2 texture_coordinates;

void main () {
	texture_coordinates = tc;

	gl_Position = matrix * vec4 (vp, 0.0, 1.0);
}
