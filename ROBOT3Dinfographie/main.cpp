


/************************************************************/
/*     PROJET Robot et scène graphique OpenGL sous glut     */
/************************************************************/
/*													        */
/*        ESGI: algorithmique pour l'infographie	        */
/*													        */
/************************************************************/
/*													        */
/*                      Objectif:                           */
/*  Mise en place des parties 1),2),3),4),5) du projet      */
/*													        */
/************************************************************/

#include <windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

float alpha = 0.0;
float teta = 0.0;
float R = 5.0;
int debout=0;

float xo, yo, zo;
/*float xo = R*cos(teta)*sin(alpha);
float yo = R*sin(teta);
float zo = R*cos(teta)*cos(alpha);*/
float xi = 0.0;
float yi = 0.0;
float zi= 0.0;
float u = 0.0;
float v = 1;
float w = 0.0;
GLUquadricObj *obj;

int f = 0;

float left_arm = 0.0;
int left_arm_check = 0;
float angleL2 = 0.0;
float left_shoulder = 0;
int left_shoulder_check = 0;
float torso = 0.0;
int bodyCheck = 0;
float leg = 0.0;


/* prototypes de fonctions */
void initRendering();
void display(void);
void reshape(int w,int h);
void update(int value);
void keyboard(unsigned char key, int x, int y);


/* Programme principal */
int main(int argc,  char **argv)
{
    int open=0;

    /* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition (glutGet(GLUT_SCREEN_HEIGHT)/3, glutGet(GLUT_SCREEN_HEIGHT)/2);


    /*MESSAGE DE BIENVENUE AVEC LES CONTROLES POSSIBLES */

    printf("---------------BIENVENUE DANS LE LABORATOIRE DU GROUPE 14----------- \n ");
    printf("\nMembres du groupes : \n --Professeur Luis Miguel \n --Professeur Ousmane Salamatao \n --Professeur Hemono arthur");

    while(open!=1)
    {
        printf("\n\n#Pour entrer dans notre laboratoire taper [1] et confirmer :");
        scanf("%d",&open);

    }
    if(open==1)
    {
        printf("\n ---Porte ouverte avec succes--- !");
        glutCreateWindow("ROBOT 3D OPTIMUS-PRIME");
    }


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
void initRendering()
{

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
void display(void)
{

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


    /*INITIALISATION DE LA POSITION DU CAMERA */

    glLoadIdentity();


    xo = R * cos(teta) * sin(alpha);
    yo = R * sin(teta);
    zo = R * cos(teta) * cos(alpha);

    glTranslatef(0.0, 0.0, -6.5);
    gluLookAt(xo, yo, zo, xi, yi, zi, u, v, w);
    /*glTranslatef(0.0f, 0.0f, -5.0f);   */                   // déplacement caméra
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
    if(debout == 1){
        glTranslatef(0.0f, 3.9f, 0.0f);
    }else{
        glTranslatef(0.0f, 2.9f, 0.0f);
    }

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
//corps
    glPushMatrix();
if(debout == 1)
        glTranslatef(0, 1, 0);
//torso
    glPushMatrix();

    glTranslatef(0, 1.5, 0);
    if(bodyCheck == 1)
    {
    }
    else
    {
        glRotatef(torso, 1,0,0);
    }
    glPushMatrix();
    obj = gluNewQuadric();
    gluCylinder(obj, 1.5, 1.01, 1.3, 30, 30);
    /*glutSolidCube(1.7);*/

    /* EPAULE*/
    glPushMatrix();
    glColor3f(0.0f, 0.4f, 0.4f);
    obj = gluNewQuadric();
    glTranslatef(0, 0.0, -0.55);
    gluCylinder(obj, 0.2, 1.3, 1.0, 30, 30);
    glPopMatrix();
    /* ********* */
    /* ABDOMEN*/
    glPushMatrix();
    glColor3f(0.0f, 0.4f, 0.4f);
    obj = gluNewQuadric();
    glTranslatef(0, 0.0, 1.0);
    gluCylinder(obj, 1.0, 1.0, 1.3, 30, 30);
    glPopMatrix();
    /*FIN ABDOMEN*/
    /* Bas de l'ABDOMEN*/
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.4f);
    obj = gluNewQuadric();
    glTranslatef(0, 0.0, 2.1);
    glutSolidSphere(0.95,10,10);

    glPopMatrix();
    /*FIN BAS DE L'ABDOMEN*/
    glPopMatrix();
    /*Fin ABDOMEN*/

    /*DEBUT REIN*/
    glPushMatrix();
    glColor3f(0.3f, 1.0f, 0.4f);
    obj = gluNewQuadric();
    glTranslatef(0, 0.0, 2.7);
    gluCylinder(obj, 0.75, 0.1, 1.0, 30, 30);
    glPopMatrix();
    /*fIN REIN*/
    glPopMatrix();


//left part of Body

    glPushMatrix();
    glTranslatef(1.4,1,0);
    glColor3f(1.0f, 0.5f, 0.0f);
    glutSolidSphere(0.5,10,10);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(left_shoulder, 0, 0, 1);
    glTranslatef(1,0,0);
    glPushMatrix();
    glScalef(2,0.6,0.7);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(1,0,0);
    glColor3f(1.0f, 0.5f, 0.0f);
    glutSolidSphere(0.5,10,10);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(left_arm, 0, 0, 1);
    glTranslatef(1,0,0);
    glPushMatrix();
    glScalef(2,1,1);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(1,0,0);
    glutSolidSphere(0.5,10,10);
    glRotatef(left_shoulder, 0, 0, 1);//left hand
    glTranslatef(0.8,0,0);
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glScalef(1,0.5,0.5);
    glutSolidCube(0.4);
    glPopMatrix();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 1.0f);
//Right Part of Body
    glPushMatrix();
    glTranslatef(-1.4,1,0);
    glColor3f(1.0f, 0.5f, 0.0f);
    glutSolidSphere(0.5,10,10);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(left_shoulder, 0, 0, -1);
    glTranslatef(-1,0,0);
    glPushMatrix();
    glScalef(2,0.6,0.7);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(-1,0,0);
    glColor3f(1.0f, 0.5f, 0.0f);
    glutSolidSphere(0.5,10,10);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(left_arm, 0, 0, -1);
    glTranslatef(-1,0,0);
    glPushMatrix();
    glScalef(2,1,1);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(-1, 0,0);
    glutSolidSphere(0.5,10,10);
    glRotatef(left_shoulder, 0, 0, -1);//left hand
    glTranslatef(-0.8,0,0);
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glScalef(1,0.5,0.5);
    glutSolidCube(0.4);
    glPopMatrix();
    glPopMatrix();

    glColor3f(0.0f, 1.0f, 1.0f);
//Lower Left Leg
    glPushMatrix();
    if(bodyCheck == 1)
    {
        glTranslatef(-0.5, 1.5, 2.9);
    }
    else
    {
        glTranslatef(-0.9, -1.7, 0.2);
    }

    glutSolidSphere(0.65,10,10);
    if(bodyCheck == 1)
    {
        glRotatef(leg, 1,0,0);
    }
    else
    {
        glRotatef(torso, 1, 0, 0);
        glTranslatef(0.0, 0, 0);
    }
    glPushMatrix();
    obj = gluNewQuadric();

    gluCylinder(obj, 0.4, 0.4, 1.7, 30, 30);
    glPopMatrix();
    glTranslatef(0, 0, 2.0);
    glutSolidSphere(0.55,10,10);
    if(bodyCheck == 1 || debout == 1)
    {
    }
    else
    {

        glRotatef(torso, 1, 0, 0);
        glTranslatef(0.0, 0.0, 0.3);

    }
    glPushMatrix();
    obj = gluNewQuadric();
    gluCylinder(obj, 0.5, 0.2, 1.7, 30, 30);
    glPopMatrix();
    glTranslatef(0, 0, 1.4);
    glutSolidSphere(0.55,10,10);
    glPopMatrix();

//Lower Right Leg
    glColor3f(0.0f, 1.0f, 1.0f);
    glPushMatrix();
    if(bodyCheck == 1)
    {
        glTranslatef(0.5, 1.5, 2.9);
    }
    else
    {
        glTranslatef(0.9, -1.7, 0.2);
    }
    glutSolidSphere(0.65,10,10);
    if(bodyCheck == 1)
    {

    }
    else
    {

        glRotatef(torso, 1, 0, 0);
        glTranslatef(0.0, 0, 0);
    }
    glPushMatrix();
    obj = gluNewQuadric();
    gluCylinder(obj, 0.4, 0.4, 1.7, 30, 30);
    glPopMatrix();
    glTranslatef(0, 0, 2.0);
    glutSolidSphere(0.55,10,10);
    if(bodyCheck == 1 || debout == 1 )
    {

    }
    else
    {
        glTranslatef(0.0, -0.35, 0);
        glRotatef(torso, 1, 0, 0);
    }
    glPushMatrix();
    obj = gluNewQuadric();
    gluCylinder(obj, 0.5, 0.2, 1.5, 30, 30);
    glPopMatrix();
    glTranslatef(0, 0, 1.4);
    glutSolidSphere(0.55,10,10);
    glPopMatrix();

//neck LE COU DU ROBOT
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glRotatef(torso, 1, 0, 0);
    glPushMatrix();
    /*glScalef(2,1,1);*/
    obj = gluNewQuadric();
    gluCylinder(obj, 0.4, 0.4, 1.7, 30, 30);
    glPopMatrix();
    glPopMatrix();
//right eye
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.3, 3, 0.7);
    glPushMatrix();
    /*glScalef(2,1,1);*/
    obj = gluNewQuadric();
    glutSolidSphere(0.35,10,10);
    glPopMatrix();
    glPopMatrix();

    /*PUPILLE DE L'OEIL RIGHT*/
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.35, 3, 0.9);
    glPushMatrix();
    /*glScalef(2,1,1);*/
    obj = gluNewQuadric();
    glutSolidSphere(0.20,10,10);
    glPopMatrix();
    glPopMatrix();
    /*end pupille*/


//left eye
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.3, 3, 0.7);
    glPushMatrix();
    /*glScalef(2,1,1);*/
    obj = gluNewQuadric();
    glutSolidSphere(0.35,10,10);
    glPopMatrix();
    glPopMatrix();

    /*PUPILLE DE L'OEIL LEFT*/
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.35, 3, 0.9);
    glPushMatrix();
    /*glScalef(2,1,1);*/
    obj = gluNewQuadric();
    glutSolidSphere(0.20,10,10);
    glPopMatrix();
    glPopMatrix();
    /*end pupille*/

//Hat -CHAPEAU DU ROBOT
    glTranslatef(0.0f, 4.5f, 0.0f);
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
    // Front
    glNormal3f(0.0f,0.0f,1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right
    glNormal3f(1.0f,0.0f,0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back
    glNormal3f(0.0f,0.0f,-1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left
    glNormal3f(-1.0f,0.0f,0.0f);
    glColor3f(1.0f,0.0f,0.0f);       // Red
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f,1.0f,0.0f);       // Blue
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glColor3f(0.0f,0.0f,1.0f);       // Green
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glEnd();   // Done drawing the pyramid
    glPopMatrix();

    /*CARTONN A COTER DU ROBOT */
    if(f == 1)
    {
        glTranslatef(0.0f, -4.7f, 0.0f);
        glColor3f(1.0f, 0.5f, 0.0f);
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
    }


    glutSwapBuffers();

    /* On force l'affichage */
    glFlush();
}


/* Fonction de mise à jour: mouvements des objets*/
void update(int value)
{
    angleL2 += 1;
    //torso
    if(torso <90)
    {
        torso += 90;
        keyboard('a', 0, 0);
    }

    //left arm
    if (left_arm < 90 && left_arm_check == 0)
    {
        left_arm += 0.51;
    }
    if(left_arm > 90)
    {
        left_arm_check = 1;
    }
    if(left_arm > 0 && left_arm_check == 1)
    {
        left_arm -= 0.51;
    }
    if(left_arm < 0)
    {
        left_arm_check = 0;
    }

    //left shoulder
    if (left_shoulder < 20 && left_shoulder_check == 0 && left_arm_check == 0)
    {
        left_shoulder += 0.11;
        /*printf("%f\n", left_shoulder);*/
    }
    if(left_shoulder > 20)
    {
        left_shoulder_check = 1;
    }
    if(left_shoulder > 0 && left_shoulder_check == 1 && left_arm_check == 1)
    {
        left_shoulder -= 0.11;
    }
    if(left_shoulder < 0)
    {
        left_shoulder_check = 0;
    }

    if (angleL2 > 360)
    {
        angleL2 -= 360;
    }

    /* *********** */


    glutPostRedisplay();
    glutTimerFunc(10,update, 0);
}


/*  Mise en forme de la scène pour l'affichage */
void reshape(int w, int h)
{
    glViewport(0, 0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0,	200.0);



}



/* Fonction de gestion au clavier */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {

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
        xo = 0;
        yo = 0;
        zo = 5;
        break;

    case 'w':   /* Quitter le programme */
        exit(0);

    case 'z': //monter caméra en regardant le centre
        if(teta < 89)
        {
            teta+=0.08;

        }
        break;

    case 's': //descendre caméra en regardant le centre
        teta -= 0.08;

        break;
    case '4': //tourner à gauche la caméra en regardant le centre
        if(R<10)
        {
            R += 0.08;
        }


        break;

    case '6': //tourner à droite la caméra en regardant le centre
        R -= 0.09;

        break;
    case 'q': //tourner à gauche la caméra en regardant le centre
        alpha += 0.09;
        break;

    case 'd': //tourner à droite la caméra en regardant le centre
        alpha -= 0.08;
        break;
    case 'f': //activer/décativer donut
        if(f == 0)
        {

            f = 1;
            break;
        }
        else
        {
            f = 0;
            break;
        }
        case 'h': //lever le robot
        if(debout == 0)
        {
            debout = 1;
            break;
        }
        else
        {
            debout = 0;
            break;
        }


    case 'u': //lever le robot
        if(bodyCheck == 0)
        {
            bodyCheck = 1;
            break;
        }
        else
        {
            bodyCheck = 0;
            break;
        }
    }
}





/*
    //COOL TRIANGLE
         glBegin(GL_TRIANGLES);
        //FRONT
    glRotatef(torso, 0, 0, 1);
    glColor3f( 1, 0, 0 ); // red
    glVertex3f( -0.8, -0.8 , 0);
    glColor3f( 0, 1, 0 ); // green
    glVertex3f( 0.8, -0.8, 0 );
    glColor3f( 0, 0, 1 ); // blue
    glVertex3f( 0, 0.9, 0 );

    //SIDE

    glColor3f( 1, 0, 0 ); // red
    glVertex3f( -0.8, -0.8, 1.6 );
    glColor3f( 0, 1, 0 ); // green
    glVertex3f( 0.8, -0.8, 1.6 );
    glColor3f( 0, 0, 1 ); // blue
    glVertex3f( 0, 0.9, 0 );

    //BASE
     glColor3f( 1, 0, 0 ); // red
    glVertex3f( -0.8, -0.8, 1.6 );
    glColor3f( 0, 1, 0 ); // green
    glVertex3f( 0.8, -0.8, 1.6 );
    glColor3f( 0, 0, 1 ); // blue
    glVertex3f( -0.8, -0.8, 0 );
    glVertex3f( 0.8, -0.8, 0 );

    glEnd();
*/
