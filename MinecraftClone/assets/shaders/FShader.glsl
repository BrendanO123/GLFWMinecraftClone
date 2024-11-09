#version 330

in vec2 TexCoord;
out vec4 fragment;

uniform sampler2D Texture;

uniform float alphaH;

void main(){
    vec4 color = texture(Texture, TexCoord);
    if(color.a<alphaH){discard;}
    fragment=color;
}