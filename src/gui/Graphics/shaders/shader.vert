#version 330

layout (location = 0) in vec3 pos;
out vec4 vColour;
uniform mat4 MVP;

void main() {
  gl_Position = MVP * vec4(pos, 1.0);
  vColour = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}