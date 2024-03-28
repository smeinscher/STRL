#version 460 core

out vec4 FragColor;

in vec4 color_frag;
in vec2 uv;

uniform sampler2D texture1;

void main()
{
    FragColor = color_frag * texture(texture1, uv);
    if (FragColor.a < 0.1)
    {
        discard;
    }
}