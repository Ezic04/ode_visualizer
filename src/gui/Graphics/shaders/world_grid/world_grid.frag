#version 330

uniform vec3 camera_position;

in vec2 uv;

const float k_cell_size = 1.0; // in world units
const float k_fade_start = 10.0;
const float k_fade_end = 30.0;

vec3 k_grid_color = vec3(0.29, 0.29, 0.29);
vec3 k_z_axis_color = vec3(0.0, 0.0, 1.0);
vec3 k_x_axis_color = vec3(1.0, 0.0, 0.0);

float getLineAlpha(float uv_dir) {
  float half_cell_size = k_cell_size / 2.0;
  float dist_to_grid = abs(mod(uv_dir - half_cell_size, k_cell_size) - half_cell_size);
  float line_thickness = max(abs(dFdx(uv_dir)), abs(dFdy(uv_dir)));
  return dist_to_grid < line_thickness ? 
    (line_thickness - dist_to_grid) / line_thickness 
    : 0.0;
}

float getFadeAlpha(void) {
  float dist_to_camera = distance(vec3(uv.x, 0.0, uv.y), camera_position);
  float alpha = 1.0;
  if (dist_to_camera > k_fade_start) {
    alpha -= ((dist_to_camera - k_fade_start) / (k_fade_end - k_fade_start));
  }
  return alpha < 0.0 ? 0.0 : alpha;
}

vec3 getGridColor(void) {
  if (abs(uv.x) < k_cell_size / 2.0) {
    return k_z_axis_color;       
  } else if (abs(uv.y) < k_cell_size / 2.0) {
    return k_x_axis_color;
  } else {
    return k_grid_color;
  }
}

void main(void) {
  float x_alpha = getLineAlpha(uv.x);
  float y_alpha = getLineAlpha(uv.y);

  vec4 color = vec4(k_grid_color, 0.0);
  if (x_alpha > y_alpha) {
    
    color = abs(uv.x) < k_cell_size / 2.0 ? 
      vec4(k_z_axis_color, x_alpha) 
      : vec4(color.xyz, x_alpha);

  } else {

    color = abs(uv.y) < k_cell_size / 2.0 ? 
      vec4(k_x_axis_color, y_alpha) 
      : vec4(color.xyz, y_alpha);

  }

  color.a *= getFadeAlpha();
  gl_FragColor = color;
}