// GLSL version
#version 150 core

// matrixs
uniform mat4 projection;
uniform mat4 modelview;

// shader's entries
in vec2 in_Vertex;
in float in_Alpha;

out float alpha;

// main function
void main()
{
  // vertex final position
  gl_Position = projection * modelview * vec4(in_Vertex, 0., 1.0);

  alpha = in_Alpha;
}

