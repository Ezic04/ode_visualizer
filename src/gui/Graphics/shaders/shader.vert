#version 330

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 instance_position;

uniform mat4 model_matrix;
uniform mat4 camera_matrix;

out vec4 vColour;

void main() {
  vec4 world_position = model_matrix * vec4(vertex_position, 1.0);
  world_position.xyz += instance_position;
  gl_Position = camera_matrix * world_position;

  vColour = vec4(clamp(vertex_position, 0.0f, 1.0f), 1.0f);
}