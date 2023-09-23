#version 330 core
in vec4 position;
in vec4 view_position;
in float depth;
out vec4 screenColor;

uniform vec4 Color;

void main()
{
    float d = distance(view_position.xyz,vec3(0,0,0));
    screenColor = vec4(Color.x,Color.y,Color.z,1-d/50.0);
}