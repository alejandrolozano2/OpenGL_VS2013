#version 330 core
in vec4 outcolor;
out vec4 color;

void main()
{
  color = vec4(outcolor.x, 0.0f, 1.0f, 1.0f);
}