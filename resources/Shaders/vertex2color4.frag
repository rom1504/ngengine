// GLSL version
#version 150 core

// input
in vec4 color;
in float alpha;

// output
out vec4 out_Color;

// main function
void main()
{
  // pixel final color
  out_Color = color * vec4(1.0, 1.0, 1.0, alpha);
}

