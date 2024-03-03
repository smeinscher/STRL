#version 460 core

out vec4 FragColor;

in vec4 color;
in vec2 uv;
in float time;

uniform sampler2D texture1;

/* This animation is the material of my first youtube tutorial about creative
   coding, which is a video in which I try to introduce programmers to GLSL
   and to the wonderful world of shaders, while also trying to share my recent
   passion for this community.
                                       Video URL: https://youtu.be/f4s1h2YETNY
*/

//https://iquilezles.org/articles/palettes/
vec3 palette(float t
)
{
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);

    return a + b * cos(6.28318 * (c * t + d));
}

//https://www.shadertoy.com/view/mtyGWy
void main()
{
    vec2 fc0 = (gl_FragCoord.xy * 2.0 - vec2(800, 600)) / 600;
    vec2 fc1 = fc0;
    vec3 finalColor = vec3(0.0);

    for (float i = 0.0; i < 4.0; i++)
    {
        fc0 = fract(fc0 * 1.5) - 0.5;

        float d = length(fc0) * exp(-length(fc1));

        vec3 col = palette(length(fc1) + i * 0.4 + time * 0.4);

        d = sin(d * 8.0 + time) / 8.0;
        d = abs(d);

        d = pow(0.01 / d, 1.2);

        finalColor += col * d;
    }

    FragColor = vec4(finalColor, 1.0) * texture(texture1, uv);
}