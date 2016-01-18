#ifdef GL_ES							
precision lowp float;					
#endif									
										
varying vec2 v_texCoord;				
uniform sampler2D CC_Texture0;			
										
void main()								
{										
    vec4 redColor = vec4(1, 0, 0, 1);
    gl_FragColor = redColor * texture2D(CC_Texture0, v_texCoord);			
}											
