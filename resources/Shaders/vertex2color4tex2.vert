// GLSL version
#version 150 core

// matrixs
uniform mat4 projection;
uniform mat4 modelview;

// shader's entries
in vec2 in_Vertex;
in vec4 in_Color;
in vec2 in_TexCoord0;

// output
out vec4 color;
out vec2 tex_coord;

// main function
void main()
{
  // vertex final position
  gl_Position = projection * modelview * vec4(in_Vertex, 1., 1.0);

  color = in_Color;
  tex_coord = in_TexCoord0;
}

