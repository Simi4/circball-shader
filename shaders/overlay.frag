#version 330 core
out vec4 FragColor;

in float dotprod;

void main()
{
    if (dotprod > 0.25)
        discard;
    FragColor = vec4(1.);
}
