#version 330 core
out vec4 FragColor;
in vec3 VertPos;


void main()
{
        FragColor = vec4(VertPos.x + 0.5, VertPos.y + 0.5, VertPos.z + 0.5,1);
}
