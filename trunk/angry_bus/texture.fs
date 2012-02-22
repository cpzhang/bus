precision mediump float;

varying vec2 vTexCoord;

uniform sampler2D uSampler;
uniform vec4 uBlendColor;
void main()
{
    gl_FragColor = texture2D(uSampler, vTexCoord) * uBlendColor;
}
