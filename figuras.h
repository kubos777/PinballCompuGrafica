//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text);
	void prisma_tria (GLuint text, GLuint text2, GLuint text3);
	void prisma_rect (GLuint text);
	void skybox(float altura, float largo, float profundidad, GLuint text);
};
