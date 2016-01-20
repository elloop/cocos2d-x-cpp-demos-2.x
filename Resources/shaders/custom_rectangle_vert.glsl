#ifdef GL_ES
precision mediump float;
#endif

attribute   vec4    custom_a_position;
uniform     vec4    custom_u_color;

varying     vec4    custom_v_color;

void main()
{
    gl_Position = CC_MVPMatrix * custom_a_position;
    custom_v_color = custom_u_color;
}


