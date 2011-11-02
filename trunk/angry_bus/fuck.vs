attribute vec4 aPosition;
attribute vec4 aColor;

// varying variables, input to the fragment shader
varying vec4 vDestinationColor;

uniform mat4 uProjection;
uniform mat4 uModelView;

void main()
{
    //DestinationColor = Color;
    //gl_Position = Projection * ModelView * Position;
    vDestinationColor = vec4(1.0, 0.0, 0.0, 1.0);
    gl_Position = uModelView * aPosition;
}
