#version 410

in vec2 UV;

out vec4 frag_Color;

uniform sampler2D tex;

void main() {
    if (UV.x == -2) {
        frag_Color = vec4(1.0, 1.0, 1.0, 1.0);
    } else {
        frag_Color = texture(tex, UV).rgba;
    }
}
