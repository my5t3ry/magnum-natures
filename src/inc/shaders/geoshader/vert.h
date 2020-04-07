// header file generated by txt2h, 2003-2006 by ScottManDeath
#ifndef  TXT_HEADER_vert
#define  TXT_HEADER_vert

const std::string  vertShader  =
"\n"
"in highp vec2 pos;"
"\n"
"in highp vec3 color;"
"\n"
"in highp float sides;"
"\n"
"uniform mat4 MVP;"
"\n"
"\n"
"out highp vec3 vColor;"
"\n"
"out highp float vSides;"
"\n"
"\n"
"void main()"
"\n"
"{"
"\n"
"    gl_Position = MVP * vec4(pos, 0.0,0.9);"
"\n"
"    gl_PointSize = 4.0;"
"\n"
"    vColor= color;"
"\n"
"    vSides= sides;"
"\n"
"}"
"\n"
;


#endif  // #ifdef TXT_HEADER_vert