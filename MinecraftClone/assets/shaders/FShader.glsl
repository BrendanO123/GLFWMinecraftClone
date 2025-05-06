#version 330

in vec2 TexCord;
in vec3 Normal;
in float invert;

out vec4 fragment;

uniform sampler2D Texture;
uniform float alphaH;

const float ambient = 0.5f;
const vec3 lightDirection = normalize(vec3(0.8, 1, 0.7));

const float highlightSaturation = 0.3f;


float SCurve(float t){ return t * t * (3 - 2 * t); }

float Lerp(float a, float b, float t) { return a + t * (b - a); }

void main(){
    vec4 color = texture(Texture, TexCord);
    if(color.a<alphaH){discard;}

    if(invert > 0){
        color = vec4(SCurve(1 - color.x), SCurve(1 - color.y), SCurve(1 - color.z), 1);
        float grayScale = SCurve((color.x + color.y + color.z) / 3);
        color = vec4(
            Lerp(grayScale, 1 - color.x, highlightSaturation), 
            Lerp(grayScale, 1 - color.y, highlightSaturation),
            Lerp(grayScale, 1 - color.z, highlightSaturation), 1
        );
    }
    color=color * vec4(  vec3(   (max(dot(Normal, lightDirection), 0.0) /*diffuse light*/) + ambient /*ambient light*/),  1.0) /*light*/;
    if(invert > 0){fragment = vec4(color.xyz, 0.6);}
    else{fragment = color;}
}