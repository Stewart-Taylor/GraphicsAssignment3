/*		Shader Loader CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * Helper class aids with loading in text files for use in shaders
 *
 * Refrence : Share Drive Graphics Week 11 Example
 * 
 * Last Updated: 29/11/2012
*/

#include "ShaderLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ShaderLoader::ShaderLoader(void)
{
}

ShaderLoader::~ShaderLoader(void)
{
}

char* ShaderLoader::textFileRead(char *fn)
{
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {
      
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

int ShaderLoader::textFileWrite(char *fn, char *s) 
{
	FILE *fp;
	int status = 0;

	if (fn != NULL) {
		fp = fopen(fn,"w");

		if (fp != NULL) {
			
			if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
				status = 1;
			fclose(fp);
		}
	}
	return(status);
}