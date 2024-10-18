#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 vPos;
in vec2 vtexPos;

out vec2 TexCoord;

void main(){
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    TexCoord = vtexPos;
}