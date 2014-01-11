// GLSL version
#version 150 core

// input
in vec4 color;
in vec2 tex_coord;

// Uniform
uniform sampler2D texture;

// output
out vec4 out_color;

// main function
void main()
{
  // pixel final color
  out_color = color * texture2D(texture, tex_coord);
}

