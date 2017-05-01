#version 410

in vec2 UV;

out vec4 frag_Color;

uniform vec4 Colour;

void main() {
    frag_Color = Colour;
}
