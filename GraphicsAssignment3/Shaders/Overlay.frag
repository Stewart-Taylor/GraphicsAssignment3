void main(void)
{
    vec2 res = vec2(150,150);
    vec2 point = vec2(gl_FragCoord.x ,gl_FragCoord.y );
    
    float dist = distance(point,res);
    float maxDist = 150.0;
    
    float perc = dist/maxDist;
      
	vec4 col = texture2D(tex,uv)*vec4(vColor, 1.0);
    
    col[0] = col[0] * (1.0-perc);
    col[1] = col[1] * (1.0-perc);
    col[2] = col[2] * (1.0-perc);
    col[3] = col[3] * (1.0-perc);

    gl_FragColor = col; 
}