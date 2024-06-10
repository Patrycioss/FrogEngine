#version 330 core
layout (location = 0) in vec4 vertex;// <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform bool flipHorizontal;
uniform bool flipVertical;

void main()
{
    float texX = vertex.z;
    
    if (flipHorizontal){
        texX *= -1;
    }
    
    float texY = vertex.w;
    
    if (flipVertical){
        texY *= -1;
    }
    
    TexCoords = vec2(texX, texY);
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}