#version 410
in vec4 vertex_colors;
in vec2 texture_coordinates;
uniform sampler2D basic_texture;

out vec4 frag_colour;
void main () {
	vec4 texel = texture(basic_texture, texture_coordinates);
	frag_colour = texel * vertex_colors;
	//frag_colour = vertex_colors;
}
