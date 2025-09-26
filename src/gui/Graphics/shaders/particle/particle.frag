#version 330

uniform vec3 u_camera_position;
uniform vec3 u_object_color;

in vec3 i_position;
in vec3 i_normal;

const vec3 ambient_color = vec3(1.0, 1.0, 0.0);
const float ambient_strength = 0.5;

const vec3 diffuse_position = vec3(0.0, 0.0, 0.0);
const float diffuse_strength = 0.5;

const float specular_strength = 1.0;

void main() {
    vec3 normal = normalize(i_normal);

    vec3 ambient_light = ambient_strength * ambient_color;

    vec3 diffuse_direction = normalize(diffuse_position - i_position);
    vec3 diffuse_light = diffuse_strength * max(dot(normal, diffuse_direction), 0.0) * ambient_color;

    vec3 view_direction = normalize(u_camera_position - i_position);
    vec3 reflect_direction = reflect(-diffuse_direction, normal);
    vec3 specular = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), 32) * ambient_color;

    gl_FragColor = vec4((ambient_light + diffuse_light + specular) * u_object_color, 1.0);
}