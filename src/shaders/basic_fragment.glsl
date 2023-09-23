#version 330 core
in vec4 position;
in float depth;
in vec3 normal;
in vec3 eye;
out vec4 screenColor;

uniform vec4 Color;

uniform float shininess = 50.0;

void main()
{
    vec3 lightDir = -normalize(vec3(0.5, 1.0, 0.5)); // Direction to the light source
    vec3 viewDir = normalize(eye - position.xyz);   // Direction to the camera
    vec3 normalDir = normalize(normal);              // Surface normal

    // Calculate the ambient, diffuse, and specular reflection components
    vec3 ambient = vec3(0.1, 0.1, 0.1) * vec3(Color.x, Color.y, Color.z);
    float diffuseStrength = max(dot(normalDir, -lightDir), 0.0);
    vec3 diffuse = Color.xyz * diffuseStrength;

    vec3 halfwayDir = normalize(-lightDir + viewDir); // Halfway vector
    float specularStrength = pow(max(dot(normalDir, halfwayDir), 0.0), shininess);
    vec3 specular = vec3(1.0, 1.0, 1.0) * specularStrength;

    // Combine ambient, diffuse, and specular components
    vec3 finalColor = ambient + diffuse + specular;

    screenColor = vec4(finalColor, Color.w);
}
