precision mediump float;                     
uniform sampler2D BaseMap;
varying vec2 uv;
void main()
{
  gl_FragColor = texture2D(BaseMap, uv);
  gl_FragColor = vec4(uv.x, uv.y, 1.0, 1.0);
}

