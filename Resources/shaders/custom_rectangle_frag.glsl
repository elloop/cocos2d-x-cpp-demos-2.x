#ifdef GL_ES
precision mediump float;
#endif

uniform     vec4    custom_u_color;

void main()
{
    gl_FragColor = custom_u_color; 
}
