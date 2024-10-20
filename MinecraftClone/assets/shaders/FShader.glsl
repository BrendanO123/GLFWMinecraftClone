#version 330

in vec2 TexCoord;
out vec4 fragment;

uniform sampler2D Texture;

void main(){
    vec4 color = texture(Texture, TexCoord);
    if(color.a==0){discard;}
    fragment=color;
    //fragment = vec4(TexCoord, 0.f, 1.f);
}