/*		Ocean Vertex Shader
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This vertex shader is applied to the Ocean Body
 * It simulates the movement of the ocean by adjusting the height values
 * The shader also adjust normals to eye coords
 * and position to eye coords
 *
 * Last Updated: 30/11/2012
*/

uniform float time;
varying vec3 lightDir,normal;

const vec3 lighPos = vec3(10,300,300);

void main()
{
	normal = normalize(gl_NormalMatrix * gl_Normal);
	lightDir = normalize(lighPos);
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	float timer = time * 0.01;
	
	vec4 position = gl_Vertex;
	vec2 point = vec2(position.x,position.y);
    float val1 = 3.4 * sin(position.y+ timer);
	float val2 = 4.6 * sin(position.x+ (timer));
	float val3 = 2.9 * sin(position.z+ (timer/2.0));
    position.z = (val1 + val2  + val3) * 0.2;

   gl_Position = gl_ModelViewProjectionMatrix * position;
} 

