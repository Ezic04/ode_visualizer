#version 330

in vec3 i_position;
in vec3 i_normal;

const float ambient_strength = 0.5;
const vec3 ambient_color = vec3(1.0, 1.0, 0.0);

const vec3 diffuse_position = vec3(0.0, 0.0, 0.0);

const vec3 object_color = vec3(1.0, 1.0, 1.0);

void main() {
    vec3 normal = normalize(i_normal);

    vec3 ambient_light = ambient_strength * ambient_color;

    vec3 diffuse_direction = normalize(diffuse_position - i_position);
    vec3 diffuse_light = max(dot(normal, diffuse_direction), 0.0) * ambient_color;

    gl_FragColor = vec4((ambient_light + diffuse_light) * object_color, 1.0);
}