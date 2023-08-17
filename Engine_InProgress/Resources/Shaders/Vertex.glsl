attribute vec4 al_pos;
attribute vec4 al_color;
attribute vec2 al_texcoord;
uniform mat4 al_projview_matrix;
varying vec4 varying_color;
varying vec2 uv;

void main()
{
   varying_color = al_color;
   uv = al_texcoord;
   gl_Position = al_projview_matrix * al_pos;
}