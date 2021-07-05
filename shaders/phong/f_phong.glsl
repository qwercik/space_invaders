#version 330

uniform sampler2D tex;

out vec4 pixelColor;

in vec4 l1;
in vec4 l2;
in vec4 n;
in vec4 v;
in vec4 r;
in vec2 iTexCoord;

void main(void)
{
    vec4 color = texture(tex, iTexCoord);
    float nl1 = clamp(dot(n, l1), 0, 1);
    float rv = clamp(dot(r, v), 0, 1);

    pixelColor = vec4(color.rgb * nl1, color.a) + vec4(color.rgb * pow(rv, 15), color.a);
}
