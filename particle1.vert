//particle.vert

uniform float time;            //value provided by application program
attribute vec3 vel;            //value provided by application program

void main(void)
{
  float s = 1000.0;            //scale factor
  float g = -10.0;
  float t;
  t =  time / s;             //time in ms


  vec4 object_pos = gl_Vertex; 
  object_pos.x = object_pos.x + vel.x*t;
  object_pos.y = object_pos.y + vel.y*t  + g/(2.0)*t*t;
  object_pos.z = object_pos.z + vel.z*t;
  
  gl_Position = gl_ModelViewProjectionMatrix * object_pos;

}
