#version 330

uniform vec3 u_camera_position;

uniform float u_cell_size;
uniform float u_fade_start;
uniform float u_fade_end;

uniform vec3 u_grid_color;
uniform vec3 u_x_axis_color;
uniform vec3 u_z_axis_color;

in vec2 uv;

float getLineAlpha(float uv_dir) {
  float half_cell_size = u_cell_size / 2.0;
  float dist_to_grid = abs(mod(uv_dir - half_cell_size, u_cell_size) - half_cell_size);
  float line_thickness = max(abs(dFdx(uv_dir)), abs(dFdy(uv_dir)));
  return dist_to_grid < line_thickness ? 
    (line_thickness - dist_to_grid) / line_thickness 
    : 0.0;
}

float getFadeAlpha(void) {
  float dist_to_camera = distance(vec3(uv.x, 0.0, uv.y), u_camera_position);
  float alpha = 1.0;
  if (dist_to_camera > u_fade_start) {
    alpha -= ((dist_to_camera - u_fade_start) / (u_fade_end - u_fade_start));
  }
  return alpha < 0.0 ? 0.0 : alpha;
}

vec3 getGridColor(void) {
  if (abs(uv.x) < u_cell_size / 2.0) {
    return u_z_axis_color;       
  } else if (abs(uv.y) < u_cell_size / 2.0) {
    return u_x_axis_color;
  } else {
    return u_grid_color;
  }
}

void main(void) {
  float x_alpha = getLineAlpha(uv.x);
  float y_alpha = getLineAlpha(uv.y);

  vec4 color = vec4(u_grid_color, 0.0);
  if (x_alpha > y_alpha) {
    
    color = abs(uv.x) < u_cell_size / 2.0 ? 
      vec4(u_z_axis_color, x_alpha) 
      : vec4(color.xyz, x_alpha);

  } else {

    color = abs(uv.y) < u_cell_size / 2.0 ? 
      vec4(u_x_axis_color, y_alpha) 
      : vec4(color.xyz, y_alpha);

  }

  color.a *= getFadeAlpha();
  gl_FragColor = color;
}