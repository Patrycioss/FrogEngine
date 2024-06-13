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
uniform bool flipHorizontal;
uniform bool flipVertical;

void main() 
{
    int choice = int(time * animationSpeed) % frameCount;
    int spriteID = choice + cycleStartFrame;
    vec2 pos = vec2(spriteID % columns, int (spriteID/columns));

    float factorX = (TexCoords.x / float(columns));
    
    if (flipHorizontal){
        factorX *= -1; 
        factorX += (1 / float(columns));
    }
    
    float factorY = (TexCoords.y / rows);
    
    if (flipVertical){
        factorY *= -1;
        factorY += (1 / float(rows));
    }
    
    float colorX = factorX + pos.x * (1.0 / columns);
    float colorY =  factorY + pos.y * (1.0 / rows);
    
    // + 0.001f for floating point rounding errors to ensure there's nothing coming through from other frames.
    color = spriteColor * texture(image, vec2(colorX, colorY + 0.001f));
}  