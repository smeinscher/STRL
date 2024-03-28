#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 camera_position;

in VS_OUT {
    vec4 color_geom;
} gs_in[];

out vec4 color_frag;

out vec2 uv;

void main()
{
    vec4 position = gl_in[0].gl_Position;

    vec2 va = position.xy + vec2(-0.5, -0.5) * 0.025;
    gl_Position = projection * view * vec4(va, position.zw);
    uv = vec2(0.0, 0.0);
    color_frag = gs_in[0].color_geom;
    EmitVertex();

    vec2 vb = position.xy + vec2(-0.5, 0.5) * 0.025;
    gl_Position = projection * view * vec4(vb, position.zw);
    uv = vec2(0.0, 1.0);
    color_frag = gs_in[0].color_geom;
    EmitVertex();

    vec2 vc = position.xy + vec2(0.5, -0.5) * 0.025;
    gl_Position = projection * view * vec4(vc, position.zw);
    uv = vec2(1.0, 0.0);
    color_frag = gs_in[0].color_geom;
    EmitVertex();

    vec2 vd = position.xy + vec2(0.5, 0.5) * 0.025;
    gl_Position = projection * view * vec4(vd, position.zw);
    uv = vec2(1.0, 1.0);
    color_frag = gs_in[0].color_geom;
    EmitVertex();
    /**vec3 camera_to_point = normalize(camera_position - position);
    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(up, camera_to_point);

    position -= right * 0.25 * 0.5;
    gl_Position = vec4(position, 1.0);
    uv = vec2(0.0, 0.0);
    color_frag = gs_in[0].color_geom;
    EmitVertex();

    position.y += 0.25;
    gl_Position = vec4(position, 1.0);
    uv = vec2(0.0, 1.0);
    color_frag = gs_in[0].color_geom;
    EmitVertex();

    position.y -= 0.25;
    position += right * 0.25;
    gl_Position = vec4(position, 1.0);
    uv = vec2(1.0, 0.0);
    color_frag = gs_in[0].color_geom;
    EmitVertex();

    position.y += 0.25;
    gl_Position = vec4(position, 1.0);
    uv = vec2(1.0, 1.0);
    color_frag = gs_in[0].color_geom;
    EmitVertex();*/

    EndPrimitive();
}