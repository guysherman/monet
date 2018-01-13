#version 410
in vec2 texture_coordinates;
uniform sampler2DRect basic_texture;

out vec4 frag_colour;

void main () {
	vec4 texel = texture(basic_texture, texture_coordinates);
	frag_colour = vec4(texel.r, texel.g, texel.b, 1.0);
    //frag_colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
