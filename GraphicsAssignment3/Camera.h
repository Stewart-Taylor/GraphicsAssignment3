#pragma once
class Camera
{
public:
	Camera(void);
	~Camera(void);
	void update();
	void mouseControl(int x , int y);
	void keyboardControl(unsigned char key, int x, int y);
};