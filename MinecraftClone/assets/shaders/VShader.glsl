#version 330

uniform mat4 MVP;

in vec3 vPos;
in vec2 vtexPos;

out vec2 TexCoord;

void main(){
    gl_Position = MVP * vec4(vPos, 1.0);
    TexCoord = vtexPos;
}