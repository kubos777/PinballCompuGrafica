/*-----------------------------------------------------------------
----Proyecto final de Computación Gráfica, grupo 2, semestre 2018-1
----MESA DE PINBALL CON TEMÁTICA DE RICK Y MORTY
----hecha por Chávez Delgado Jorge Luis y Vargas Castro Daniel.
-----------------------------------------------------------------*/
#include "texture.h"
#include "figuras.h"
#include "Camera.h"

//Variables para la cámara.
CCamera objCamera;
GLfloat g_lookupdown = 0.0f;
//Para la iluminación
GLfloat luz_ambiente[] = { 0.0f, 0.0f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat luz_difuso[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat luz_especular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat luz_posicion[] = { 0.0f, 100.0f, 0.0f, 0.0f };			// Light Position
GLfloat luz_direccion[] = { 0.0f, 100.0f, 0.0f, 0.0f };			// Light Position
//Texturas.
CTexture text_skybox;
CTexture text_mueble;
CTexture text_vidrio;
CTexture text_tablero;
//Objeto para dibujar.
CFiguras figura;


void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difuso);
	glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, luz_direccion);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Se cargan texturas
	//Textura del ambiente.
	text_skybox.LoadTGA("Texturas/skyBox.tga");
	text_skybox.BuildGLTexture();
	text_skybox.ReleaseImage();
	//Textura de la mesa.
	text_mueble.LoadTGA("Texturas/mueble.tga");
	text_mueble.BuildGLTexture();
	text_mueble.ReleaseImage();
	//Textura del vidrio de la mesa.
	text_vidrio.LoadTGA("Texturas/vidrio.tga");
	text_vidrio.BuildGLTexture();
	text_vidrio.ReleaseImage();
	//Textura del tablero (bajo el vidrio)
	text_tablero.LoadTGA("Texturas/tableroAtras.tga");
	text_tablero.BuildGLTexture();
	text_tablero.ReleaseImage();

	objCamera.Position_Camera(95.0f, 50.0f, 95.0f, 0.0f, 0.0f, 0.0f, 0, 1, 0);
	return;
}

void reshape(int w, int h) {
	if (h == 0) h = 1; 

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 400.0);
	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

// Aqui ponemos lo que queremos dibujar.
void display(void) { 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix(); //Para la cámara.
		glRotatef(g_lookupdown, 1.0f, 0, 0);
		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
			objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
			objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);

		glPushMatrix(); //Para todo el dibujo.

			glPushMatrix(); //Para el ambiente.
				glDisable(GL_LIGHTING);				
				figura.skybox(200.0, 200.0, 200.0, text_skybox.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix(); //Terminamos ambiente.

			glPushMatrix(); //Para la mesa
				glTranslatef(0.0, -25.0, 10.0);
				glPushMatrix(); //Bloque A
					glScalef(60.0, 30.0, 130.0);
					glDisable(GL_LIGHTING);
					figura.prisma_rect(text_mueble.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();
				glPushMatrix(); //Bloque B
					glTranslatef(0.0, 25.0, 10.0);
					glScalef(60.0, 20.0, 110.0);
					glDisable(GL_LIGHTING);
					figura.prisma_tria(text_mueble.GLindex, text_vidrio.GLindex, text_tablero.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();
				glPushMatrix(); //Bloque C
					glTranslatef(0.0, 25.0, -55.0);
					glScalef(60.0, 20.0, 20.0);
					glDisable(GL_LIGHTING);
					figura.prisma_rect(text_mueble.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();
				glPushMatrix(); //Bloque D
					glTranslatef(0.0, 70.0, -55.0);
					glScalef(70.0, 70.0, 20.0);
					glDisable(GL_LIGHTING);
					figura.prisma_rect(text_mueble.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();
				glPushMatrix(); //PATA E
					glTranslatef(25.0, -45.0, -60.0);
					glScalef(10.0, 60.0, 10.0);
					glDisable(GL_LIGHTING);
					figura.prisma_rect(text_mueble.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();
				glPushMatrix(); //PATA F
					glTranslatef(25.0, -45.0, 60.0);
					glScalef(10.0, 60.0, 10.0);
					glDisable(GL_LIGHTING);
					figura.prisma_rect(text_mueble.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();
				glPushMatrix(); //PATA G
					glTranslatef(-25.0, -45.0, 60.0);
					glScalef(10.0, 60.0, 10.0);
					glDisable(GL_LIGHTING);
					figura.prisma_rect(text_mueble.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();
				glPushMatrix(); //PATA G
					glTranslatef(-25.0, -45.0, -60.0);
					glScalef(10.0, 60.0, 10.0);
					glDisable(GL_LIGHTING);
					figura.prisma_rect(text_mueble.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();
			glPopMatrix();	//Terminamos mesa.

		glPopMatrix();	//Terminamos dibujo.
	glPopMatrix(); //Terminamos cámara.

	glutSwapBuffers();
} 

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera(CAMERASPEED + 0.01);
			break;
		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED + 0.01));
			break;
		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED + 0.02));
			break;
		case 'd':
		case 'D':
			objCamera.Strafe_Camera(CAMERASPEED + 0.02);
			break;
		case 27:
			exit(0); 
			break;
		default:
			break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y) {
	switch (a_keys) {
		case GLUT_KEY_PAGE_UP:
			objCamera.UpDown_Camera(CAMERASPEED);
			break;
		case GLUT_KEY_PAGE_DOWN:
			objCamera.UpDown_Camera(-CAMERASPEED);
			break;
		case GLUT_KEY_UP:
			g_lookupdown -= 1.0f;
			break;
		case GLUT_KEY_DOWN:
			g_lookupdown += 1.0f;
			break;
		case GLUT_KEY_LEFT:
			objCamera.Rotate_View(-CAMERASPEED);
			break;
		case GLUT_KEY_RIGHT:
			objCamera.Rotate_View(CAMERASPEED);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) { 
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize (650, 650);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Proyecto Final");
	init();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutMainLoop();
	 
	return 0;
}



