#version 330

uniform mat4 u_model_matrix;
uniform mat4 u_camera_matrix;

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec3 instance_position;

out vec3 i_position;
out vec3 i_normal;

void main() {
  vec4 world_position = u_model_matrix * vec4(vertex_position, 1.0);

  // transform normals correctly here
  
  world_position.xyz += instance_position;
  
  i_position = world_position.xyz;
  i_normal = vertex_normal;

  gl_Position = u_camera_matrix * world_position;
}