#version 330 core
out vec4 FragColor;

in vec2 uv_frag;

uniform sampler2D tex;

void main(){
    FragColor = texture(tex, uv_frag);
}
