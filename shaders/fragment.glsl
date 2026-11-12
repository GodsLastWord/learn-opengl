#version 330 core

in vec3 ourColor;
in vec2 textureCoordinates;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main() {
    FragColor = texture(ourTexture, textureCoordinates);
}

