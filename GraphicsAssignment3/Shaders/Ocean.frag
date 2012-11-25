varying vec3 lightDir,normal;
uniform sampler2D tex;
uniform float time;


float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


void main()
{

	float timer = time * 0.00001;
	
	
   float x = gl_FragCoord.x;
   float y = gl_FragCoord.y;
   float z = gl_FragCoord.z;
  
  
  
   vec4 vCol = vec4( 0.04,0.85,0.75,1.0);
	
	vCol = vCol;


	vec3 ct,cf;
	vec4 texel;
	float intensity,at,af;
	
	intensity = max(dot(lightDir,normalize(normal)),0.0);
	
	cf = intensity * (gl_FrontMaterial.diffuse).rgb + 
					  gl_FrontMaterial.ambient.rgb;
	af = gl_FrontMaterial.diffuse.a;
	
	texel = texture2D(tex,gl_TexCoord[0].st);
	ct = texel.rgb;
	ct = ct * vCol;
	at = texel.a;

	
vec4 col =  vec4(ct * cf , at * af );
	//vec2 point = vec2(x+ sin(timer),y + sin(timer));


	//float randV = rand(point);
	float alphaV =  0.6; //clamp(randV ,0.6 , 0.7);
	

	gl_FragColor = vec4(col.x , col.y , col.z, alphaV);
	//gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}
