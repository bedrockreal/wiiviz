#version 330 core

in vec2 vNdc;
out vec4 FragColor;

uniform mat4 uInvViewProj;
uniform vec3 uCameraPos;

uniform float uMinorScale;
uniform float uMajorScale;
uniform vec4 uMinorColor;
uniform vec4 uMajorColor;
uniform vec4 uAxisXColor;
uniform vec4 uAxisZColor;
uniform float uFadeStart;
uniform float uFadeEnd;

vec3 unprojectPoint(vec2 ndc, float z) {
    vec4 p = uInvViewProj * vec4(ndc, z, 1.0);
    return p.xyz / p.w;
}

float gridLine(vec2 coord) {
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    return 1.0 - min(line, 1.0);
}

void main() {
    vec3 nearPoint = unprojectPoint(vNdc, -1.0);
    vec3 farPoint  = unprojectPoint(vNdc,  1.0);

    vec3 rayOrigin = nearPoint;
    vec3 rayDir = normalize(farPoint - nearPoint);

    if (abs(rayDir.z) < 1e-5) {
        discard;
    }

    float t = -rayOrigin.z / rayDir.z;
    if (t <= 0.0) {
        discard;
    }

    vec3 worldPos = rayOrigin + t * rayDir;
    vec2 gridPos = worldPos.xy;

    float minor = gridLine(gridPos / uMinorScale);
    float major = gridLine(gridPos / uMajorScale);

    vec4 color = vec4(0.0);
    color += uMinorColor * minor;
    color = mix(color, uMajorColor, major);

    float axisX = 1.0 - min(abs(worldPos.y) / fwidth(worldPos.y), 1.0);
    float axisZ = 1.0 - min(abs(worldPos.x) / fwidth(worldPos.x), 1.0);

    color = mix(color, uAxisXColor, axisX);
    color = mix(color, uAxisZColor, axisZ);

    float dist = distance(uCameraPos, worldPos);
    float fade = 1.0 - smoothstep(uFadeStart, uFadeEnd, dist);

    color.a *= fade;

    if (color.a <= 0.001) {
        discard;
    }

    FragColor = color;
}

