#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float blockMapW_blocks;
uniform float blockMapH_blocks;

in vec3 vPos;
in vec2 vtexPos;

in int normal;

out vec2 TexCoord;
out vec3 Normal;

const vec3 normals[] = vec3[](
	vec3( 0,  0,  1), // Forward
	vec3( 0,  0, -1), // Back
	vec3( 1,  0,  0), // Right
	vec3(-1,  0,  0), // Left
	vec3( 0,  1,  0), // Up
	vec3( 0, -1,  0) // Down
);


void main(){
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    TexCoord = vec2(vtexPos.x / blockMapW_blocks, vtexPos.y / blockMapH_blocks);
    
    Normal = normals[normal];
}