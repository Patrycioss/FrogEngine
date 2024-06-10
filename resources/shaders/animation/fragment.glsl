#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D image;
uniform vec4 spriteColor;

uniform int columns;
uniform int rows;
uniform float time;
uniform float animationSpeed;
uniform int cycleStartFrame;
uniform int frameCount;

void main() 
{
    int choice = int(time * animationSpeed) % frameCount;
    int spriteID = choice + cycleStartFrame;
    vec2 pos = vec2(spriteID % columns, int (spriteID/columns));
    
    color = spriteColor * texture(image, 
            vec2(
            (TexCoords.x / columns) + pos.x * (1.0 / columns), 
            (TexCoords.y / rows) + pos.y * (1.0 / rows)
            )
    );
}  