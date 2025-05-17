#version 400

in vec2 TexCord;
in vec3 Normal;

out vec4 fragment;

uniform sampler2D Texture;
uniform float alphaH;
uniform float invert;

const float ambient = 0.5f;
const vec3 lightDirection = normalize(vec3(0.8, 1, 0.7));

const float highlightSaturation = 0.3f;


float SCurve(float t){ return t * t * (3 - 2 * t); }
float Lerp(float a, float b, float t) { return a + t * (b - a); }

void main(){

    //manually sample nearest mipmap levels and interpolate color linearly between the two
    //set alpha to max of two levels
    float mipmap = textureQueryLod(Texture, TexCord).x;
    vec4 colorL = textureLod(Texture, TexCord, floor(mipmap));
    vec4 colorH = textureLod(Texture, TexCord, ceil(mipmap));

    vec4 color = vec4(0.0f); float n = 0;
    if(colorL.a>=alphaH){
        if((floor(mipmap)+1-mipmap)>=alphaH){color.w = colorL.w;}
        color += vec4(colorL.xyz * (floor(mipmap)+1-mipmap), 0.0f);
        n += (floor(mipmap)+1-mipmap);
    }
    if(colorH.a>=alphaH){
        if((mipmap - floor(mipmap))>=alphaH){color.w = max(color.w, colorH.w);}
        color += vec4(colorH.xyz * (mipmap - floor(mipmap)), 0.0f);
        n += (mipmap - floor(mipmap));
    }

    //discared empty texels
    if(n ==0 || color.w<alphaH){discard;}

    //normalize
    color = vec4(color.xyz / n, color.w);

    //---
    //run the rest of the code like normal
    //---


    //code for inverted colors on cursor/selected block overlay
    if(invert > 0.5f){
        color = vec4(SCurve(1 - color.x), SCurve(1 - color.y), SCurve(1 - color.z), 1);
        float grayScale = SCurve((color.x + color.y + color.z) / 3);
        color = vec4(
            Lerp(grayScale, 1 - color.x, highlightSaturation), 
            Lerp(grayScale, 1 - color.y, highlightSaturation),
            Lerp(grayScale, 1 - color.z, highlightSaturation), 1
        );
    }

    //lighting
    color=color * vec4(  vec3(   (max(dot(Normal, lightDirection), 0.0) /*diffuse light*/) + ambient /*ambient light*/),  1.0) /*light*/;
    
    //I am pretty sure this is deprecated
    if(invert > 0.5f){fragment = vec4(color.xyz, 0.6);}
    else{fragment = color;}
}