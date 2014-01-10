// Version du GLSL

#version 150 core

uniform mat4 projection;
uniform mat4 modelview;

// Entrée Shader

in vec2 in_Vertex;


// Fonction main

void main()
{
    // Position finale du vertex

    gl_Position = projection * modelview * vec4(in_Vertex, 0., 1.0);
}
