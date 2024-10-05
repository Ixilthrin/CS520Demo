//tests.frag
//a minimal fragment shader

varying float color;

void main(void)
{
    gl_FragColor = mix(vec4(1.0, 0.0, 0.0, 0.0), vec4( 1, 1, 0, 0), color);    
}
