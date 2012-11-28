
uniform float timer;
uniform float resX;
uniform float resY;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{
	vec2 res = vec2(resX,resY);
    vec2 point = vec2(gl_FragCoord.x  ,gl_FragCoord.y );

    float dist = distance(point,res);
    float maxDist = resX  + 200.0; 
    float perc = dist/maxDist;

	vec4 col = vec4(0.4,0.3,0.14,1.0);
	
    col[0] = col[0] * (perc);
    col[1] = col[1] * (perc);
    col[2] = col[2] * (perc);
    col[3] = col[3] * (perc);

   float val = rand(point);
  
   gl_FragColor = col ;
}