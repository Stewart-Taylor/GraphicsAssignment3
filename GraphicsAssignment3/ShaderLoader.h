#pragma once
class ShaderLoader
{
public:
	ShaderLoader(void);
	~ShaderLoader(void);
	static int textFileWrite(char *fn, char *s);
	static char *textFileRead(char *fn);
};

