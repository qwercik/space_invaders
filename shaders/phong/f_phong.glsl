#version 330

uniform sampler2D tex;

out vec4 pixelColor;

in vec4 l1;
in vec4 l2;
in vec4 n;
in vec4 v;
in vec4 r1;
in vec4 r2;
in vec2 iTexCoord;

void main(void)
{
    float nl1 = clamp(dot(normalize(l1), normalize(n)), 0.4, 1);
    float vr1 = pow(clamp(dot(normalize(v), normalize(r1)), 0, 1), 25);

    float nl2 = clamp(dot(normalize(l2), normalize(n)), 0, 0.5);
    float vr2 = pow(clamp(dot(normalize(v), normalize(r2)), 0, 0.5), 25);

    vec4 color = texture(tex, iTexCoord);
    // We don't use any specular texture
    vec4 specular = color;

    pixelColor = vec4(color.rgb * (nl1 + nl2), color.a) + vec4(specular.rgb * (vr1 + vr2), specular.a);
}
