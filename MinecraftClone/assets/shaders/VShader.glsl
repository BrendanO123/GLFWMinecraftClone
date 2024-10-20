#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float blockMapW_blocks;
uniform float blockMapH_blocks;

in vec3 vPos;
in vec2 vtexPos;

out vec2 TexCoord;

void main(){
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    TexCoord = vec2(vtexPos.x / blockMapW_blocks, vtexPos.y / blockMapH_blocks);
}