#version 410 core

in vec3 vPosition;

uniform mat4 matView;
uniform mat4 matObj;
uniform mat4 matProj;

out vec3 gPosition;

void main()
{
    gl_Position = matProj * matView *  matObj * vec4(vPosition,1);
}


