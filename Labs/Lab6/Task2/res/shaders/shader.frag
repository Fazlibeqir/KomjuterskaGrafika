#version 330 core
out vec4 FragColor;

uniform vec3 ChangeColor;
void main()
{
        FragColor = vec4(ChangeColor, 1.0);
}
