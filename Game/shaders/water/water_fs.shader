#version 330 core

in vec2 TexCoord; // Texture coordinates from the vertex shader

uniform sampler2D waterTexture; // The texture sampler

out vec4 FragColor;

void main() {
    vec4 sampledColor = texture(waterTexture, TexCoord); // Sample the texture
    float alpha = 0.5; // Set the desired transparency (0.5 means 50% transparent)
    FragColor = vec4(sampledColor.rgb, alpha); // Use the sampled color and the specified alpha value
}