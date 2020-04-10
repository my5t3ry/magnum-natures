#version 320 es
layout(points) in;
layout(triangle_strip, max_vertices = 64) out;

in highp vec4 rectangle[];
in highp vec3 vColor[];
in highp float vSides[];
out highp vec3 fColor;

const float PI = 3.1415926;

void main()
{
    fColor = vColor[0];
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = vec4(rectangle[0][2]+gl_in[0].gl_Position[0], rectangle[0][3]+gl_in[0].gl_Position[1], gl_in[0].gl_Position[2], gl_in[0].gl_Position[3]);
    EmitVertex();
    gl_Position = vec4(rectangle[0][2]+gl_in[0].gl_Position[0], gl_in[0].gl_Position[1], gl_in[0].gl_Position[2], gl_in[0].gl_Position[3]);
    EmitVertex();
    gl_Position = vec4(gl_in[0].gl_Position[0], rectangle[0][3]+gl_in[0].gl_Position[1], gl_in[0].gl_Position[2], gl_in[0].gl_Position[3]);
    EmitVertex();
    //
    //    for (float i = 0.0; i <= vSides[0]; i+=1.0) {	        // Angle between each side in radians
    //        float ang = PI * 2.0 / vSides[0] * i;
    //        // Offset from center of point (0.3 to accomodate for aspect ratio)
    //        vec4 offset = vec4(cos(ang) * 0.3, -sin(ang) * 0.4, 0.0, 0.0);
    //        gl_Position = gl_in[0].gl_Position - offset;
    //
    //        EmitVertex();
    //    }
    EndPrimitive();
}
