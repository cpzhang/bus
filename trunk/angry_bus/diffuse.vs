/* 
 attributes for values that may change per vertex
 uniforms for values that may change per draw call
 */
attribute vec4 aPosition;
attribute vec4 aColor;

// varying variables, input to the fragment shader
varying vec4 vDestinationColor;

uniform mat4 uModelViewProjection;

void main()
{
    vDestinationColor = aColor;

    /*
     gl_Position is used to output the vertex position in  clip coordinates. The gl_Position values are used by the clipping and viewport stages to perform appropriate clipping of primitives and convert the vertex position from clip coordinates to screen coordinates.
     The value of gl_Position is undefined if the vertex shader does not write to gl_Position. gl_Position is a floating-point variable declared using the highp precision qualifier.
     */
    gl_Position = uModelViewProjection * aPosition;
}
