#version 430 core


layout(vertices = 3) out;
in vec3 vPosition[];
in vec3 vNormal[];
out vec3 tcPosition[];
out vec3 tcNormal[];
uniform float TessLevelInner;
uniform float TessLevelOuter;

#define ID gl_InvocationID

void main()
{
    tcPosition[ID] = vPosition[ID];
	tcNormal[ID] = vNormal[ID];
    if (ID == 0) {
        gl_TessLevelInner[0] = TessLevelInner;
        gl_TessLevelOuter[0] = TessLevelOuter;
        gl_TessLevelOuter[1] = TessLevelOuter;
        gl_TessLevelOuter[2] = TessLevelOuter;
    }
}
