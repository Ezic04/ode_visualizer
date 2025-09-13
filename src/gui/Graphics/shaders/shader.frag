#version 330

in vec4 vColour;

void main() {
    gl_FragColor = vec4(vColour.xyz, 1.0);
}