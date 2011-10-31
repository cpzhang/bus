attribute vec4 Position;
attribute vec4 Color;

varying vec4 DestinationColor;

uniform mat4 Projection;
uniform mat4 ModelView;

void main()
{
    //DestinationColor = Color;
    //gl_Position = Projection * ModelView * Position;
    DestinationColor = vec4(1.0, 0.0, 0.0, 1.0);
    gl_Position = Position;
}