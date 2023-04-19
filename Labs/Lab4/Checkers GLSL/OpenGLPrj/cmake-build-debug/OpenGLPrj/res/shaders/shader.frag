#version 330

out vec4 fragColor;

void main()
{
    int x = int(mod(gl_FragCoord.x, 8.0));
    int y = int(mod(gl_FragCoord.y, 8.0));
    int i = int(x / 4);
    int j = int(y / 4);
    int check = int(mod(i + j, 2));
    fragColor = vec4(vec3(check), 1.0);
}
