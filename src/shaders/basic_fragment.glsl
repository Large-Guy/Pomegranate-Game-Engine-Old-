#version 330 core
in vec4 position;
in float depth;
in vec3 normal;
in vec3 eye;
out vec4 screenColor;

uniform vec4 Color;



void main()
{
    vec3 l = normalize(vec3(0.0,1.0,0.0));
    vec3 nor = normalize(normal);
    vec3 col = vec3(Color.x,Color.y,Color.z);
    float cosTheta = clamp(dot(nor,l),0.0,1.0)+0.75;
    col = col*cosTheta;
    screenColor = vec4(col.x,col.y,col.z,1.0f);  
}