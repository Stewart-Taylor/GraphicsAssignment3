uniform float timer;


uniform sampler2D tex;
 float PI = 3.1415926535897932;

//speed
 float speed = 0.2;
 float speed_x = 0.3;
 float speed_y = 0.3;

// geometry
 float intensity = 3.;
 int steps = 8;
 float frequency = 4.0;
 int angle = 7; // better when a prime

// reflection and emboss
 float delta = 20.;
 float intence = 400.;
 float emboss = 0.3;

//---------- crystals effect

  float col(vec2 coord)
  {
	float time = timer * 20.0;
  
  
    float delta_theta = 2.0 * PI / float(angle);
    float col = 0.0;
    float theta = 0.0;
    for (int i = 0; i < steps; i++)
    {
      vec2 adjc = coord;
      theta = delta_theta*float(i);
      adjc.x += cos(theta)*time*speed + time * speed_x;
      adjc.y -= sin(theta)*time*speed - time * speed_y;
      col = col + cos( (adjc.x*cos(theta) - adjc.y*sin(theta))*frequency)*intensity;
    }

    return cos(col);
  }

//---------- main

void main(void)
{
vec2 p = (gl_FragCoord.xy) , c1 = p, c2 = p;
float cc1 = col(c1);

//c2.x += 1/delta;
float dx = emboss*(cc1-col(c2))/delta;

c2.x = p.x;
//c2.y += 1/delta;
float dy = emboss*(cc1-col(c2))/delta;

c1.x += dx;
c1.y = -(c1.y+dy);

float alpha = 1.+dot(dx,dy)*intence;

vec4 col  = texture2D(tex,c1)*(alpha);
col[3] = 0.1;
gl_FragColor = col;
}