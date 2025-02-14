#version 330

uniform ivec3 modelPos;
uniform ivec3 cameraPosI;

uniform mat4 viewAndProjectionMatrix;

uniform float blockMapW_blocks;
uniform float blockMapH_blocks;

in vec2 vPos;
in int height;
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
	gl_Position = viewAndProjectionMatrix * vec4(vPos.x + modelPos.x, height + modelPos.y, vPos.y + modelPos.z, 1.0);
    TexCoord = vec2(vtexPos.x / blockMapW_blocks, vtexPos.y / blockMapH_blocks);
    
    Normal = normals[normal];
}