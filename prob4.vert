//prob5.vert

uniform float time;            //value provided by application program

attribute float p1x;            //value provided by application program
attribute float p1y;            //value provided by application program
attribute float p1z;            //value provided by application program

varying float color;

void main(void)
{
  float s = 10000.0;            //scale factor
  float t;
  t =  time / s;             //time in ms

  color = t;

  vec4 point1;
  point1.x = p1x;
  point1.y = p1y;
  point1.z = p1z;
  point1.w = 1.0;

  vec4 object_pos = mix(gl_Vertex, point1, t); 
  //vec4 object_pos = point1; 
  //vec4 object_pos = gl_Vertex; 
  
  gl_Position = gl_ModelViewProjectionMatrix * object_pos;

}
