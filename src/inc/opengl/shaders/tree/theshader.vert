#version 320 es
in highp vec4 rec;
in highp vec3 color;
in highp float sides;
uniform mat4 MVP;

out highp vec4 rectangle;
out highp vec3 fColor;
out highp float vSides;

void main()
{
    gl_Position = MVP * vec4(rec[0], rec[1], 0.0, 0.9);
    gl_PointSize = 2.0;
    fColor = color;
    rectangle = rec;
    vSides = sides;
}
