


/************************************************************/
/*            TP2: Primitives 3D et couleur                 */
/************************************************************/
/*													        */
/*        ESGI: algorithmique pour l'infographie	        */
/*													        */
/************************************************************/
/*													        */
/*  Objectif: afficher des formes 3D et illuminer la scène  */
/*													        */
/************************************************************/




#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdlib.h>
#include<stdio.h>




float left_arm = 0.0;
int left_arm_check = 0;
float angleL2 = 0.0;
float left_shoulder = 0;
int left_shoulder_check = 0;
float torso = 0.0;


/* prototypes de fonctions */
void initRendering();
void display(void);
void reshape(int w,int h);
void update(int value);
void keyboard(unsigned char key, int x, int y);


/* Programme principal */
int main(int argc,  char **argv){

	/* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("TP2: primitives 3D et illumination");

	/* Initialisation d'OpenGL */
	initRendering();

	/* Enregistrement des fonctions de rappel */
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc (20,update, 0);
	glutKeyboardFunc(keyboard);

	/* Entrée dans la boucle principale de glut, traitement des évènements */
    glutMainLoop();
    return 0;
}


/* Initialisation d'OpenGL pour le rendu de la scène */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

	/* Activation des couleurs */
	glEnable(GL_COLOR_MATERIAL);

	/* définit la couleur d'effacement et la couleur de fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* Activation des lumières */
	//glEnable(GL_LIGHTING);          // Activation du mode
	//glEnable(GL_LIGHT0);            // Activation lumière n°0
	//glEnable(GL_LIGHT1);            // Activation lumière n°1
	//glEnable(GL_LIGHT2);            // Activation lumière n°2

	/* Les normales (crées par glNormal(*)) sont automatiquement unitaires */
	glEnable(GL_NORMALIZE);


	/* Activation du mode ombrage (shading) et lissage (smooth) des couleur */
	glShadeModel(GL_SMOOTH);

	/*  définit la taille d'un pixel*/
	glPointSize(2.0);

}

/* Création de la scène avec lampes */
void display(void){

	/* Déclaration des couleurs et positions des lampes */
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};   // Color (0.2, 0.2, 0.2)

	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};    // Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};      // Positioned at (4, 0, 8)

	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f};    // Color (0.5, 0.2, 0.2)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};// Coming from the direction (-1, 0.5, 0.5)

	    /*glRotatef(angleL2, 0.0f, 1.0f, 0.0f);*/
	GLfloat lightColor2[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat lightPos2[] = {-3.0f, 0.0f, 0.0f, 1.0f};
	    /*glRotatef(angleL2, 0.0f, 1.0f, 0.0f);*/




	/* Déclaration des différents types de matière des sphères */
	GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
	GLfloat mat_diffuse[] = {0.1, 0.5, 0.8, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat no_shininess[] = {0.0};
	GLfloat low_shininess[] = {5.0};
	GLfloat high_shininess[] = {100.0};
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};



	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();




	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, -5.0f);                      // déplacement caméra
	glColor3f(1.0f, 1.0f, 1.0f);


	// Ajout lumière ambiante
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);





    	// Ajout lumière positionnelle L0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);        // lumière diffuse
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);         // position

	// Ajout lumière positionnelle L1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor1);       // lumiére spéculaire
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	//Ajout lumière positionnelle L2
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);



	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
    glRotatef(angleL2, 0.0f, 1.0f, 0.0f);
	glTranslatef(-3.0f, 0.0f, 0.0f);
	/*glutWireCube(0.1);*/
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
	/*glNormal3f(0.0f, 0.0f, 1.0f);
	glNormal3b(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);*/
	glPopMatrix();

	/* Dessine la sphère haut gauche, réflexion diffuse, pas d'ambiante, ni spéculaire*/
/*	glPushMatrix();
		glTranslatef(-3.0f, 3.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glutSolidSphere(1.0, 18.0, 18.0);
	glPopMatrix();*/

	/* Dessine la sphère haut droit, réflexion diffuse, spéculaire, brillance faible pas d'ambiante*/
	/*glPushMatrix();
		glTranslatef(3.0f, 3.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glutSolidSphere(1.0, 18.0, 18.0);
	glPopMatrix();*/

	/* Dessine la sphère bas droit, réflexion diffuse, spéculaire, brillance élevée pas d'ambiante*/
	/*glPushMatrix();
		glTranslatef(3.0f, -3.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glutSolidSphere(1.0, 18.0, 18.0);
	glPopMatrix();


	/* Dessine la sphère bas gauche, réflexion diffuse, émission, pas de réflexion ambiante ou spéculaire*/
	glPushMatrix();
		glTranslatef(-2.0f, 2.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		glutSolidSphere(1.0, 18.0, 18.0);
	glPopMatrix();



    /* Dessine un cube scalé en mvt */
/*	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);*/




	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    //left shoulder
 /*   glPushMatrix();
        glTranslatef(-3,0,0);
        /*glRotatef(angle2, 1, 0, -1);*/
    /*    glScalef(2,1,1);
        glutWireCube(1.0);
    glPopMatrix();
    //left arm
      glPushMatrix();
        /*glRotatef(angle2, 0, 0, 1);*/
  /*      glTranslatef(-5,0,0);
        glScalef(4,1,1);
        glutWireCube(1.0);
    glPopMatrix();
   //torso
   glPushMatrix();
        glTranslatef(-1,0,0);
        /*glRotatef(angle2, 1, 0, -1);*/
 /*       glScalef(2,1,1);
        glutWireCube(2.0);
   glPopMatrix();
   //right shoulder
   glPushMatrix();
        glTranslatef(1,0,0);
      /*  glRotatef(angle2, 1, 0, -1);*/
    /*    glScalef(2,1,1);
        glutWireCube(1.0);
    glPopMatrix();
    //right arm
    glPushMatrix();
        glRotatef(angle, 0, 0, 1);
        glTranslatef(3,0,0);
        glScalef(4,1,1);
        glutWireCube(1.0);
    glPopMatrix();
    //right hand
    glPushMatrix();
        glRotatef(angle, 0, 0, 1);
        glTranslatef(5,0,0);
        glScalef(4,1,1);
        glutWireCube(0.1);
    glPopMatrix();*/

 //torso
 glPushMatrix();
    glTranslatef(-2, -1, 0);
    glRotatef(torso, 0,0,-1);
    glPushMatrix();
        glScalef(2,1,1);
        glutWireCube(1.5);
        /*glutSolidCube(1.7);*/
    glPopMatrix();
 glPopMatrix();

 // Upper Left Leg

  /*glPushMatrix();
 glTranslatef(-1.7, -2.5, -0.5);
    glRotatef(torso, 0,-1,0);
    glPushMatrix();
        glScalef(2,1,1);
        glutWireCube(0.8);
    glPopMatrix();
glPopMatrix();
*/
 //Upper Right Leg
 /*  glPushMatrix();
 glTranslatef(-2.2, -2.5, -0.5);
    glRotatef(torso, 0,-1,0);
    glPushMatrix();
        glScalef(2,1,1);
        glutWireCube(0.8);
    glPopMatrix();
glPopMatrix();*/

 //Lower Left Leg
 glPushMatrix();
 glTranslatef(-1.5, -3.2, 0.5);
    glRotatef(torso, 0,0,-1);
    glPushMatrix();
        glScalef(2,1,1);
        glutWireCube(0.8);
    glPopMatrix();
glPopMatrix();

//Lower Right Leg
glPushMatrix();
 glTranslatef(-2.3, -3.2, 0.5);
    glRotatef(torso, 0,0,-1);
    glPushMatrix();
        glScalef(2,1,1);
        glutWireCube(0.8);
    glPopMatrix();
glPopMatrix();

//Right Part of Body
 glPushMatrix();
        glTranslatef(-3,0,0);
        glutSolidSphere(0.5,10,10);
        glRotatef(left_shoulder, 0, 0, -1);
        glTranslatef(-1,0,0);
    glPushMatrix();
        glScalef(2,1,1);
        glutWireCube(1.0);
    glPopMatrix();
        glTranslatef(-1,0,0);
        glutSolidSphere(0.5,10,10);
        glRotatef(left_arm, 0, 0, -1);
        glTranslatef(-1,0,0);
    glPushMatrix();
        glScalef(2,1,1);
        glutWireCube(1.0);
    glPopMatrix();
    glTranslatef(-1, 0,0);
     glutSolidSphere(0.5,10,10);
        glRotatef(left_shoulder, 0, 0, -1);//left hand
        glTranslatef(-0.8,0,0);
    glPushMatrix();
        glScalef(1,0.5,0.5);
        glutWireCube(0.4);
    glPopMatrix();
glPopMatrix();






//left part of Body
   glPushMatrix();
        glTranslatef(-1,0,0);
        glutSolidSphere(0.5,10,10);
        glRotatef(left_shoulder, 0, 0, 1);
        glTranslatef(1,0,0);
    glPushMatrix();
        glScalef(2,1,1);
        glutWireCube(1.0);
    glPopMatrix();
        glTranslatef(1,0,0);
        glutSolidSphere(0.5,10,10);
        glRotatef(left_arm, 0, 0, 1);
        glTranslatef(1,0,0);
    glPushMatrix();
        glScalef(2,1,1);
        glutWireCube(1.0);
    glPopMatrix();
    glTranslatef(1,0,0);
    glutSolidSphere(0.5,10,10);
        glRotatef(left_shoulder, 0, 0, 1);//left hand
        glTranslatef(0.8,0,0);
    glPushMatrix();
        glScalef(1,0.5,0.5);
        glutWireCube(0.4);
    glPopMatrix();
glPopMatrix();



/*
	glBegin(GL_QUADS);

	//Front
	glNormal3f(0,0,1);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	glVertex3f(1.5f, -1.0f, 1.5f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	glVertex3f(-1.5f, 1.0f, 1.5f);

	//Right
	glNormal3f(1,0,0);
	glVertex3f(1.5f, -1.0f, -1.5f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	glVertex3f(1.5f, -1.0f, 1.5f);

	//Back
    glNormal3f(0,0,-1);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	glVertex3f(-1.5f, 1.0f, -1.5f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	glVertex3f(1.5f, -1.0f, -1.5f);

	//Left
    glNormal3f(-1,0,0);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	glVertex3f(-1.5f, 1.0f, -1.5f);

	glEnd();
	glPopMatrix();

*/
	glutSwapBuffers();

	/* On force l'affichage */
	glFlush();
}


/* Fonction de mise à jour: mouvements des objets*/
void update(int value){
	angleL2 += 1;

	//torso
	if(torso <90){
        torso += 90;
	}

	//left arm
	if (left_arm < 90 && left_arm_check == 0){
		left_arm += 0.51;
	}
	if(left_arm > 90){
        left_arm_check = 1;
	}
	if(left_arm > 0 && left_arm_check == 1){
        left_arm -= 0.51;
	}
	if(left_arm < 0){
        left_arm_check = 0;
	}

		//left shoulder
	if (left_shoulder < 20 && left_shoulder_check == 0 && left_arm_check == 0){
		left_shoulder += 0.11;
		printf("%f\n", left_shoulder);
	}
	if(left_shoulder > 20){
        left_shoulder_check = 1;
	}
	if(left_shoulder > 0 && left_shoulder_check == 1 && left_arm_check == 1){
        left_shoulder -= 0.11;
	}
	if(left_shoulder < 0){
        left_shoulder_check = 0;
	}

	if (angleL2 > 360){
		angleL2 -= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(10,update, 0);
}


/*  Mise en forme de la scène pour l'affichage */
void reshape(int w, int h){
	glViewport(0, 0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0,	200.0);



}



/* Fonction de gestion au clavier des activations des lumières */
void keyboard(unsigned char key, int x, int y) {
		switch (key){

			case 'a':   /* activation lumière n°0 */
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHT2);
				glutPostRedisplay();
				break;

			case 'b':   /* activation lumière n°1*/
				glEnable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				glutPostRedisplay();
				break;
            case 'c':    /*activation lumière n°2*/
                glEnable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
                glDisable(GL_LIGHT1);
                glEnable(GL_LIGHT2);
                break;


			case 'l':   /* activation des lumières  */
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				glutPostRedisplay();
				break;

			case 'L':   /* désactivation des lumières  */
				glDisable(GL_LIGHTING);
				glutPostRedisplay();
				break;

			case 'q':   /* Quitter le programme */
				exit(0);
		}
}
