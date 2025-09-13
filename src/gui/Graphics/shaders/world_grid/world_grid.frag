#version 330

in vec2 uv;

const float line_thickness = 0.01;

void main() {
    float x_dist = distance(uv.x, floor(uv.x));
    float y_dist = distance(uv.y, floor(uv.y));

    if (x_dist < line_thickness / 2.0 || x_dist > 1.0 - (line_thickness / 2.0)
        || y_dist < line_thickness / 2.0 || y_dist > 1.0 - (line_thickness / 2.0)
    ) { gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); } 
    else { gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0); }
}