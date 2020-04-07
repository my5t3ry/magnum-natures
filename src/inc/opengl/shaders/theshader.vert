#version 320 es

in vec2 pos;
in vec3 color;
in float sides;
uniform mat4 MVP;

out vec3 fColor;
out float vSides;

void main()
{
    gl_Position = MVP * vec4(pos, 0.0,0.9);
    gl_PointSize = 4.0;
    fColor = color;
    vSides = sides;
}
