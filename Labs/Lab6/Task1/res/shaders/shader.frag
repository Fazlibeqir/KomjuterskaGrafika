#version 330 core
out vec4 FragColor;
in vec3 VerPos;


void main()
{
        FragColor = vec4(VerPos.x + 0.5, VerPos.y + 0.5, VerPos.z + 0.5,1);
}
