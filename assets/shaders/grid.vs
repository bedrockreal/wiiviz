#version 330 core

// use one oversized triangle in clip space

out vec2 vNdc;

const vec2 kTriangle[3] = vec2[](
    vec2(-1.0, -1.0),
    vec2( 3.0, -1.0),
    vec2(-1.0,  3.0)
);

void main() {
    vec2 pos = kTriangle[gl_VertexID];
    vNdc = pos;
    gl_Position = vec4(pos, 0.0, 1.0);
}
