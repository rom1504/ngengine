// GLSL version
#version 150 core

in float alpha;

// Shader's output
out vec4 out_Color;

// main function
void main()
{
  // pixel final color
  out_Color = vec4(1.0, 1.0, 1.0, alpha);
}

