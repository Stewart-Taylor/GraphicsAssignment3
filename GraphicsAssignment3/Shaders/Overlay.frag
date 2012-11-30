/*		Overlay Fragment Shader
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This fragment shader is applied to the Overlay Plane
 * It genereates a gradient circle effect to the center
 * Strong at the deges than the center
 * Provides a slight colour overlay to simulate a slght bloom effect, enhances brighter colours
 * Also produces a slight sepia tint which makes the scene look more vintage
 *
 * Last Updated: 30/11/2012
*/

uniform float timer;
uniform float resX;
uniform float resY;

void main(void)
{
	vec2 res = vec2(resX,resY);
    vec2 point = vec2(gl_FragCoord.x  ,gl_FragCoord.y );

    float dist = distance(point,res);
    float maxDist = resX  + 200.0; 
    float perc = dist/maxDist;

	vec4 col = vec4(0.4,0.3,0.14,1.0); // The colour tint max
	
    col[0] = col[0] * (perc);
    col[1] = col[1] * (perc);
    col[2] = col[2] * (perc);
    col[3] = col[3] * (perc);

   gl_FragColor = col ;
}