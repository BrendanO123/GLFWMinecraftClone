#version 330

in vec2 TexCoord;
in vec3 Normal;

out vec4 fragment;

uniform sampler2D Texture;
uniform float alphaH;

const float ambient = .5;
const vec3 lightDirection = normalize(vec3(0.8, 1, 0.7));

void main(){
    vec4 color = texture(Texture, TexCoord);
    if(color.a<alphaH){discard;}

    fragment=color * vec4(  vec3(   (max(dot(Normal, lightDirection), 0.0) /*diffuse light*/) + ambient /*ambient light*/),  1.0) /*light*/;
}