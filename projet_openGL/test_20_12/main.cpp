/*============================================================================
Nom du projet :
Auteurs :
============================================================================*/

#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <time.h>

#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CArc.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CData2i.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CDonneesGraphe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPoint3f.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPointAnnexe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CSegment.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CSommet.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/consts.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CGraphe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CEnvironnement.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CCamera.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CTrain.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CWagon.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CTexture.h"

GLuint herbe;
GLuint ciel;
GLuint bois;
GLuint feuille;
GLuint sun;
GLuint eau;
GLuint roche;
GLuint texture_wagon;
#define mSPF 30

using namespace std;

// Construction des tables du graphe
CDonneesGraphe gdata("/Users/Sylvain/Documents/ENSG/opengl/test_20_12/data/SXYZ.TXT",
                     "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/data/SIF.TXT",
                     "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/data/PAXYZ.TXT",
                     "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/data/AXYZ.TXT");
// Construction de la base de données orientée objet du graphe
CGraphe graphe(gdata);

//Initialisation wagons
CWagon wagon_a;
CWagon wagon_b;
CWagon wagon_c;

//Initialisation trains
CTrain A(wagon_a, wagon_b,wagon_c);

//Paramètres de la caméra
    int type_cam = 0;      //permet de changer le mode de vue

    //"Oeil de la caméra"
    float xcam = 17;
    float ycam = -10;
    double distcam = 10;

    //Point visé par la caméra
    double xcentre=15;
    double ycentre=15;
    double zcentre=0;

    //Ciel
    double xciel=2;
    double yciel=1;
    double zciel=40;

    int nbr_types_cam=7;

GLvoid defineWindow(char * titre)
{
    GLsizei screenWidth, screenHeight ;
    screenWidth= glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition(screenWidth/10, screenHeight/10);
    glutInitWindowSize(screenWidth/1.2, screenHeight /1.2);
    glutCreateWindow(titre);
    // Définition de la couleur du fond de la fenêtre
    glClearColor(1.,1.,1.,1.);
}

GLvoid initialize(char * titre)
{
    GLvoid defineWindow(char *);
    glutInitDisplayMode(GLUT_RGB);
    defineWindow(titre);

    int largeur = glutGet(GLUT_WINDOW_WIDTH) ;
    int hauteur = glutGet(GLUT_WINDOW_HEIGHT) ;
    int aspect = (GLfloat) largeur/hauteur;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,aspect,1,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void display()
{
    //GLfloat Yellow[]={1.,1.,0.,1.};
    //glClear( GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH);
    glEnable(GL_DOUBLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

//    herbe = loadTexture("/Users/Sylvain/Documents/ENSG/opengl/test_20_12/bin/textures/grass.jpg");
//    ciel  = loadTexture("/Users/Sylvain/Documents/ENSG/opengl/test_20_12/bin/textures/ciel.jpg");
//    bois  = loadTexture("/Users/Sylvain/Documents/ENSG/opengl/test_20_12/bin/textures/bois.jpg");
//    feuille = loadTexture("/Users/Sylvain/Documents/ENSG/opengl/test_20_12/bin/textures/feuille.jpg");
//    sun = loadTexture("/Users/Sylvain/Documents/ENSG/opengl/test_20_12/bin/textures/sun.jpeg");
//    eau = loadTexture("/Users/Sylvain/Documents/ENSG/opengl/test_20_12/bin/textures/eau.jpg");
//    roche = loadTexture("/Users/Sylvain/Documents/ENSG/opengl/test_20_12/bin/textures/roche.jpg");
    texture_wagon = loadTexture("/Users/Sylvain/Documents/ENSG/opengl/test_20_12/bin/textures/wagon.jpg");

    CCamera camera;
    camera.Position(type_cam,xcam,ycam,distcam,xcentre,ycentre,zcentre,xciel,yciel,zciel);

    CEnvironnement environnement;
    environnement.Ground();
    // Affichage du graphe, des sommets et des points annexes
    environnement.AffichageGraphe(graphe);

    //environnement.Soleil(sun,1,20,13);
    //environnement.Arbre(bois, feuille, -5,10);
    //environnement.Lac(eau,12,17,3);
    environnement.Sapin(25,0);
    //environnement.Ciel(ciel);
    environnement.Maison(30,18);
    environnement.Tunnel(graphe);
    environnement.Poteau(graphe);
    //environnement.Montagne(roche,20,-3);

    environnement.Pont();

     //---------------------Affichage des trains------------------------------//
    A.Train_dessiner(1,texture_wagon);

    glFlush() ;
}

void keyboard_ascii(int key, int i, int j)
{
    //mouvement de la caméra avec les flèches directionnelles
    switch(key){
        case GLUT_KEY_DOWN:
                ycam = ycam-0.5;
                ycentre=ycentre-0.5;
                glutPostRedisplay();
                break;
        case GLUT_KEY_LEFT:
                xcam = xcam-0.5;
                xcentre=xcentre-0.5;
                glutPostRedisplay();
                break;
        case GLUT_KEY_UP:
                ycam = ycam+0.5;
                ycentre=ycentre+0.5;
                glutPostRedisplay();
                break;
        case GLUT_KEY_RIGHT:
                xcam = xcam+0.5;
                xcentre=xcentre+0.5;
                glutPostRedisplay();
                break;
    }
}

void keyboard_ordinary(unsigned char key, int i, int j)
{
    //mouvement de la caméra avec les flèches directionnelles
    switch(key){
        case '-':
            distcam = distcam+0.5;
            break;
        case '+':
            distcam = distcam-0.5;
            break;

        case 'i':
            if (type_cam==0){
                type_cam=7;
            }else {
                type_cam=0;
            }
            break;

        case 'a':
            xcam = xcam-1;
            ycam = ycam-1;
            break;
        case 'z':
            xcam = xcam+1;
            ycam = ycam+1;
            break;

        case 'e':
            xcentre = xcentre+5;
            ycentre = ycentre+5;
            break;
        case 'r':
            xcentre = xcentre-5;
            ycentre = ycentre-5;
            break;

//        case 'c':
//            if (type_cam==6){
//                type_cam=0;
//            }else if (type_cam==7) {
//                type_cam=0;
//            }else {
//                type_cam++;
//            }
//            break;
//        case 'p':
//            if (type_cam==0){
//                type_cam= nbr_types_cam-1;
//            }else if (type_cam==7) {
//                type_cam=0;
//            }else {
//                type_cam--;
//            }
//            break;

        case 27: //touche echap : quitter
            if (type_cam == 0){
                exit(0);
            }else {
                type_cam=0;
            }
            break;
    }
}


static float new_x = 0 , new_y = 0 ;
static bool action = false ;

void clic_souris(int bouton, int etat, int x, int y){
    action = bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN;
    if(!action) return;
    new_x = x;
    new_y = y;
}

void deplacement(int x, int y){

    float deplacement_x, deplacement_y;
    float facteur=0.01;
    if(!action){
        return;
    }
    deplacement_x = facteur*(new_x - x);
    deplacement_y = facteur*(new_y - y);
    xcam = xcam + deplacement_x;
    ycam = ycam + deplacement_y;
    glutPostRedisplay();
}

int main(int argc , char **argv)
{
    //on va créer les trains, en les plaçant à des sommets aléatoires
    srand((unsigned)time(NULL)); // initialisation de rand

    //tirage de nombres aléatoires differents
    int alea=rand()%gdata.NS;

    //on initialise les trains et les wagons
    A.Train_initialiser(alea, graphe);

    glutInit(&argc,argv); /* Négociation des sessions avec le window system */
    initialize(argv[0]); /* Fonction pour initialiser la machine OpenGL */

    glutDisplayFunc(display); /* callback de rendu à écrire */
    glutIdleFunc(display); /* rappelle la fonction passée en parametre à chaque fois que le cpu est inoccupé */

    glutSpecialFunc(keyboard_ascii); /* callback de fonction permettant l'utilisation des touches du clavier (format ASCII) */
    glutKeyboardFunc(keyboard_ordinary); /* callback de fonction permettant l'utilisation des autres touches du clavier */

    glutMouseFunc(clic_souris); /* callback de fonction permettant de récupérer l'action faite avec la souris (ici clic gauche) */
    glutMotionFunc(deplacement); /* callback de fonction permettant de déplacer la scène lors de l'action de la souris (clic gauche) */

    glutMainLoop(); /* Fonction de boucle infinie */

    return EXIT_SUCCESS;
}
