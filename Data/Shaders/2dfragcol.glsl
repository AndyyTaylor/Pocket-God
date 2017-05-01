#version 410

// in vec2 UV;

out vec4 frag_Color;

uniform vec4 Colour;

void main() {
    // frag_Color = vec4(1.0, 1.0, 1.0, 1.0);
    frag_Color = Colour;
}
