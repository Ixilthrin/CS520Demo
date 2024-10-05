//prob5.vert

uniform float time;            //value provided by application program
attribute vec3 vel;            //value provided by application program
attribute vec3 position;            //value provided by application program

// current velocity
vec3 velocity;

void main(void)
{
  float s = 5000.0;            //scale factor
  float g = -9.8;
  float t;
  t =  time / s;             //time in ms

  velocity.y = vel.y + g/(2.0)*t;
  if (t > .5)
  {
    velocity = reflect(velocity, vec3(0.0, 1.0, 0.0));
  }

  vec4 object_pos = gl_Vertex; 
  object_pos.x = position.x + object_pos.x + vel.x*t;
  object_pos.y = position.y + object_pos.y + velocity.y*t;
  object_pos.z = position.z + object_pos.z + vel.z*t;
  
  gl_Position = gl_ModelViewProjectionMatrix * object_pos;

}
