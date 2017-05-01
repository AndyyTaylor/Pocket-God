#version 410

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_UV;

out vec2 UV;

void main() {
    vec2 vertex_position = in_Position.xy - vec2(640, 360);
    vec2 vert = vec2(0, 0) - vertex_position / vec2(640, 360);

    gl_Position = vec4(-vert.x, vert.y, in_Position.z, 1);

    UV = in_UV;
}
