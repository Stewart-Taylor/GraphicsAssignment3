/*		Shadow Helper
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * Used to provide a matrix manipulation to render shadows
 * 
 * Reference: topic_7/shadow.c
 *
 * Last Updated: 24/10/2012
*/

#include <freeglut.h>
#include "ShadowHelper.h"


ShadowHelper::ShadowHelper(void)
{
}

ShadowHelper::~ShadowHelper(void)
{
}

void ShadowHelper::shadow_matrix(GLfloat lt[4],GLfloat pl[4],GLfloat shadow_proj[16])
{
	//First define values for usual notation  
	//for plane and light position/direction.

	GLfloat lx, ly, lz, lw; // light coordinates
	GLfloat a, b, c, d; // for equation of plane
	GLfloat rdotl; //dot product of normal and light position/direction

	// Light position is (lx, ly, lz, lw). The plane on which to draw the 
	// shadows has equation a*x + b*y + c*z + d = 0

	lx = lt[0]; ly = lt[1]; lz = lt[2]; lw = lt[3];
	a = pl[0]; b = pl[1]; c = pl[2]; d = pl[3];
    rdotl = a*lx + b*ly + c*lz + d*lw;

   shadow_proj[0]  = -a*lx + rdotl;
   shadow_proj[1]  = -a*ly;
   shadow_proj[2]  = -a*lz;
   shadow_proj[3]  = -a*lw;
   shadow_proj[4]  = -b*lx;
   shadow_proj[5]  = -b*ly + rdotl;
   shadow_proj[6]  = -b*lz;
   shadow_proj[7]  = -b*lw;
   shadow_proj[8]  = -c*lx;
   shadow_proj[9]  = -c*ly;
   shadow_proj[10] = -c*lz + rdotl;
   shadow_proj[11] = -c*lw;
   shadow_proj[12] = -d*lx;
   shadow_proj[13] = -d*ly;
   shadow_proj[14] = -d*lz;
   shadow_proj[15] = -d*lw + rdotl;
}