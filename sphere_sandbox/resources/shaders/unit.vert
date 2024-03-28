#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec4 aColor;

uniform mat4 view;
uniform mat4 projection;

out VS_OUT {
    vec4 color_geom;
} vs_out;
out vec4 color_frag;
out vec2 uv;

void main()
{
    vs_out.color_geom = aColor;
    color_frag = aColor;
    uv = aUV;

    vec3 camera_right_world_space = vec3(view[0][0], view[1][0], view[2][0]);
    vec3 camera_up_world_space = vec3(view[0][1], view[1][1], view[2][1]);

    vec3 vertex_position_world_space = aPos + camera_right_world_space + camera_up_world_space;

    gl_Position = projection * view * vec4(aPos, 1.0);

}