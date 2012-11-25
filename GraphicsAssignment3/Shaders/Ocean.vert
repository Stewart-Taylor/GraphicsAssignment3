uniform float time;

varying vec3 lightDir,normal;


void main()
{

	normal = normalize(gl_NormalMatrix * gl_Normal);
	lightDir = normalize(vec3(gl_LightSource[0].position));
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	
	float timer = time * 0.001;
	
	vec4 position = gl_Vertex;
	vec2 point = vec2(position.x,position.y);
    float val1 = 0.1 * sin(position.y+ timer)  ;
	float val2 = 0.3 * sin(position.x+ (timer*2.0))  ;
	//float val3 = 0.5f *sin(rand(point) + timer ) ;
    position.z = val1 + val2  + 0.4;

   
   
   
	//Scale It Up
	//position.x *= 2.0;
	//position.y *= 2.0;
	//position.z *= 2.0;

   gl_Position = gl_ModelViewProjectionMatrix * position;
   
 //  gl_Position = ftransform();
} 

