#version 330

layout (location = 0) in vec3 vertex_position;

uniform mat4 u_camera_matrix;
uniform vec3 u_camera_position;

out vec2 uv;

void main() {
  vec4 world_position = vec4(vertex_position, 1.0);
  world_position.xz += u_camera_position.xz;

  uv = world_position.xz;
  gl_Position = u_camera_matrix * world_position;
}