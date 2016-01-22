#ifdef GL_ES
precision mediump float;
#endif

attribute   vec4    custom_a_position;
attribute   vec4    custom_a_color;

varying     vec4    v_color;

void main()
{
    vec4 pos    = vec4(custom_a_position, 0, 1);
    gl_Position = CC_MVPMatrix * pos;
    v_color     = custom_a_color;
}


