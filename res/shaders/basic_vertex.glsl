#version 330 core

mat4 perspective(float fov, float aspectRatio, float near, float far) {
    float f = 1.0 / tan(fov * 0.5);
    float rangeInv = 1.0 / (near - far);

    return mat4(
        vec4(f / aspectRatio, 0.0, 0.0, 0.0),
        vec4(0.0, f, 0.0, 0.0),
        vec4(0.0, 0.0, (near + far) * rangeInv, -1.0),
        vec4(0.0, 0.0, 2.0 * near * far * rangeInv, 0.0)
    );
}

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform vec3 CameraPosition;  // Camera position in world space

out vec4 position;
out float depth;
out vec3 normal;
out vec3 eye;  // Eye vector in view space

void main()
{
    // Transform the position from model space to world space
    vec4 worldPosition = Model * vec4(aPos, 1.0);
    
    // Transform the position from world space to camera/view space
    vec4 viewPosition = View * worldPosition;
    
    // Calculate the eye vector in view space
    eye = normalize(vec3(-viewPosition));  // Assuming the camera looks along the negative z-axis
    
    // Transform the position from camera/view space to clip space
    gl_Position = Projection * viewPosition;
    
    position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    
    vec4 nor = Model * vec4(aNor, 0.0);
    normal = vec3(nor.x, nor.y, nor.z);
    
    depth = distance(viewPosition, vec4(0, 0, 0, 1.0));
}
