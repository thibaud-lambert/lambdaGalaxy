#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 gPosition[3];

uniform mat4 matView;
uniform mat4 matObj;
uniform mat4 matProj;

out vec3 vNormal;
out vec3 triDistance;

void main()
{
    vec3 A = gPosition[2] - gPosition[0];
    vec3 B = gPosition[1] - gPosition[0];
    vNormal = normalize(cross(A, B));

    triDistance = vec3(1, 0, 0);
    gl_Position = matProj * matView *  matObj * vec4(gPosition[0],1);
    EmitVertex();

    triDistance = vec3(0, 1, 0);
    gl_Position = matProj * matView *  matObj * vec4(gPosition[1],1);
    EmitVertex();

    triDistance = vec3(0, 0, 1);
    gl_Position = matProj * matView *  matObj * vec4(gPosition[2],1);
    EmitVertex();

    EndPrimitive();
}
