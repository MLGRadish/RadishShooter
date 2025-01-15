#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 uv;

uniform mat4 model, view, proj;

out vec2 uv_frag;

void main() {
	gl_Position = proj * view * model * vec4 (vertex, 1.0);
	uv_frag = uv;
}
