#version 330

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec3 instance_position;

uniform mat4 u_camera_matrix;

out vec3 i_position;
out vec3 i_normal;

void main() {
  vec4 world_position = vec4(vertex_position, 1.0);
  world_position.xyz += instance_position;
  
  i_position = world_position.xyz;
  i_normal = vertex_normal;

  gl_Position = u_camera_matrix * world_position;
}