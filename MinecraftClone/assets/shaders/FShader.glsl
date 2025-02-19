#version 330

in vec2 TexCoord;
in vec3 Normal;
in float invert;

out vec4 fragment;

uniform sampler2D Texture;
uniform float alphaH;

const float ambient = .5;
const vec3 lightDirection = normalize(vec3(0.8, 1, 0.7));

float SCurve(float t){ return t * t * (3 - 2 * t); }
void main(){
    vec4 color = texture(Texture, TexCoord);
    if(color.a<alphaH){discard;}

    if(invert > 0){
        color = vec4(1 - color.x, 1 - color.y, 1 - color.z, 1);
    }
    fragment=color * vec4(  vec3(   (max(dot(Normal, lightDirection), 0.0) /*diffuse light*/) + ambient /*ambient light*/),  1.0) /*light*/;
}