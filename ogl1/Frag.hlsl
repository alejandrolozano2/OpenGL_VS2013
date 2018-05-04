#version 330 core
in vec4 outcolor;
out vec4 color;

void main()
{
  color = vec4(outcolor.x, outcolor.y, 0.2f, 1.0f);
}