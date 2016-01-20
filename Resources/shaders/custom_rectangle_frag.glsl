#ifdef GL_ES
precision mediump float;
#endif

varying     vec4    custom_v_color;

void main()
{
    gl_FragColor = custom_v_color;
}
