#version 330

layout (location = 0) in vec3 vertex_position;

uniform vec3 camera_position;
uniform mat4 camera_matrix;

out vec2 uv;

void main() {
  vec4 world_position = vec4(vertex_position, 1.0);
  world_position.xz += camera_position.xz;

  uv = world_position.xz;
  gl_Position = camera_matrix * world_position;
}