#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec4 aColor;

uniform mat4 view;
uniform mat4 projection;

out vec4 color_frag;
out vec2 uv;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);
    color_frag = aColor;
    uv = aUV;
}