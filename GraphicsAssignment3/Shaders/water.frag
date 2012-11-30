/*		Water Fragment Shader
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This fragment shader is applied to the Ship reflection
 * It genereates a moving watery like effect
 * Requires adjustment to fit with camera movement
 *
 * Last Updated: 28/11/2012
*/
uniform float timer;
uniform sampler2D tex;
const float PI = 3.141;
const float speed = 0.2;
const float speed_x = 0.3;
const float speed_y = 0.3;
const float intensity = 3.;
const int steps = 8;
const float frequency = 4.0;
const int angle = 7; 
const float delta = 20.;
const float intence = 400.;
const float emboss = 0.3;

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

void main(void)
{
	vec2 p = (gl_FragCoord.xy) , c1 = p, c2 = p;
	float cc1 = col(c1);

	float dx = emboss*(cc1-col(c2))/delta;

	c2.x = p.x;
	float dy = emboss*(cc1-col(c2))/delta;

	c1.x += dx;
	c1.y = -(c1.y+dy);

	float alpha = 1.+dot(dx,dy)*intence;

	vec4 col  = texture2D(tex,c1)*(alpha);
	col[3] = 0.1;
	gl_FragColor = col;
}