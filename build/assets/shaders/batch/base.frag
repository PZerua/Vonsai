#version 410 core

in vec2 v_texCoord;
flat in uint v_idx;

out vec4 f_color;

uniform sampler2D u_texture[3];

///////////////////////////////////////////////////////////////////////////////

void main() {
    f_color = texture(u_texture[v_idx-1], v_texCoord);
}
