attribute vec4 vPosition;
attribute vec2 vUV;
uniform mat4 ModelLocal;
uniform mat4 ViewProj;
varying vec2 uv;
void main()
{
   gl_Position = ViewProj * (ModelLocal * vPosition);
   uv.x = vUV.x;
   uv.y = vUV.y;
}       
