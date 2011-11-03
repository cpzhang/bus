precision mediump float;

varying vec4 vDestinationColor;
varying vec2 vTexCoord;

uniform sampler2D uTex;

void main()
{
    gl_FragColor = vDestinationColor;
    gl_FragColor = texture2D(uTex, vTexCoord);
}
