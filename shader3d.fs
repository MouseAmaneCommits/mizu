#version 330 core

out vec4 FragColor;
in vec2 in_txPos;
uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, in_txPos);
} 
