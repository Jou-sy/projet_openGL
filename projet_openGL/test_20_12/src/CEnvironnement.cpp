#include "CEnvironnement.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPoint3f.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CGraphe.h"

void CEnvironnement::AffichageGraphe(CGraphe graphe)
{
    //Affichage des sommets
    for (int s=0; s<graphe.nb_sommet; s++)
    {
        //On récupère chaque sommet
        CSommet ptSommet = graphe.list_sommet.at(s);

        //Création de sphères représentant les sommets
        glPushMatrix();
            // Choix de la couleur d'affichage des sommets
            glColor3d(0,0,0);
            glTranslated(ptSommet.X,ptSommet.Y,ptSommet.Z+0.1);
            // Choix de la forme d'affichage des sommets
//            GLUquadric* qobj = gluNewQuadric();
//            gluQuadricNormals(qobj, GLU_SMOOTH);
//            gluCylinder(qobj, 0.4, 0.1, 0.15, 105, 1);
        glPopMatrix();
    }

    //Affichage des points annexes
    for (int pa=0; pa<graphe.nb_point_annex; pa++)
    {
        //On récupère chaque sommet
        CPointAnnexe ptAnnexe = graphe.list_point_annexe.at(pa);

        //Création de sphères représentant les sommets
        glPushMatrix();
            // Choix de la couleur d'affichage des pts annexes
            glColor3d(0,0,0);
            glTranslated(ptAnnexe.X,ptAnnexe.Y,ptAnnexe.Z+0.1);
            // Choix de la forme d'affichage des pts annexes
//            glutSolidSphere(0.15,16,16);
        glPopMatrix();
    }


    //Affichage des arcs
    for (int a=0; a<graphe.nb_arc ;a++)
    {
        //On récupère chaque arc
        CArc ligneArc = graphe.list_arc.at(a);
        //On récupère les sommets initial et final de chaque arc
        CSommet sommetInit  = graphe.list_sommet.at(ligneArc.id_sommet_ini);
        CSommet sommetFin  = graphe.list_sommet.at(ligneArc.id_sommet_fin);

        //On récupère le nombre de points annexes associés à chaque arc
        int nbr = ligneArc.list_point_annexe.size();

        glBegin(GL_LINE_STRIP);
        // Choix de la couleur d'affichage des arcs
        glColor3d(0,0,0);
        // Choix de la forme d'affichage des arcs
        glVertex3f(sommetInit.X,sommetInit.Y,sommetInit.Z+0.1);

        //On trace chaque arc allant d'un point annexe à un autre
        for (int i=0; i<nbr; i++)
        {
                CPointAnnexe ptannexe  = graphe.list_point_annexe.at(ligneArc.list_point_annexe.at(i));
                // Choix de la forme d'affichage des arcs
                glVertex3f(ptannexe.X,ptannexe.Y,ptannexe.Z+0.1);
        }

        // Choix de la forme d'affichage des arcs
        glVertex3f(sommetFin.X,sommetFin.Y,sommetFin.Z+0.1);
        glEnd();

    }
}

void CEnvironnement::Ground()
{
    glPushMatrix();
    glTranslated(0, 0, -0.01);
    GLboolean fonce = GL_TRUE;
    GLfloat i,j;
    for(j=-6;j<39;j+=1)
    {
        for (i=-6;i<39;i+=1)
        {
        //glPushMatrix();
        if(fonce == GL_TRUE)
        {
            glColor3ub(0,220,50);
            glRectf(i,j,i+1,j+1);
            fonce =! fonce;
        }
        else
        {
            glColor3ub(0,255,20);
            glRectf(i,j,i+1,j+1);
            fonce =! fonce;
        }
        //glPopMatrix();
        }
//    glPushMatrix();
//    glColor3ub(0,156,0);
//    glRectf(i,j,i+0.5,j+0.5);
//    fonce =! fonce;
//    glPopMatrix();
    }
    glPopMatrix();
}

void CEnvironnement::Maison(float x, float y){
//glEnable(GL_LIGHTING);
    glPushMatrix();
        //GLUquadric* quad = gluNewQuadric();
        glColor3d(0.9,0.,0.);
        glTranslated(x, y, 1.5);
        glRotatef(0, 1, 1, 0);
        glutSolidCube(3);
        glColor3d(0.9,0.,0.4);
        glTranslated(0,0,0.75);
        glutSolidCone(3.2, 2, 100, 100);
    glPopMatrix();
    //glDisable(GL_LIGHTING);
}

void CEnvironnement::Tunnel(CGraphe graphe){
    CPointAnnexe ptAnnexe1  = graphe.list_point_annexe.at(26);
    CPointAnnexe ptAnnexe2  = graphe.list_point_annexe.at(27);
    //glEnable(GL_LIGHTING);
    glPushMatrix();
        GLUquadric *quad = gluNewQuadric();
        glColor3d(0.2,0.4,0.9);
        glTranslated(ptAnnexe1.X, ptAnnexe1.Y, 0);
        glRotatef(-90, 0, 1, 0);
        glRotatef(63.435, 1, 0, 0);
        glTranslated(0, 0, -1);
        gluCylinder(quad, 2, 2, sqrt(45), 100, 100);
    glPopMatrix();
    //glDisable(GL_LIGHTING);

}

void CEnvironnement::Lac(int eau, float x, float y, float r){
    //glEnable(GL_LIGHTING);
    //glColor3d(1,1,1);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad,GL_TRUE);
        glBindTexture(GL_TEXTURE_2D,eau);
        glColor3d(0.2,0.4,0.9);
        glTranslated(x, y, 0.01);
        glRotatef(0, 1, 1, 0);
        gluDisk(quad,0,r,100,100);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //glDisable(GL_LIGHTING);
}
void CEnvironnement::Soleil(int sun, float x, float y, float z){
    //glEnable(GL_LIGHTING);
    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad,GL_TRUE);
        glBindTexture(GL_TEXTURE_2D,sun);
        //glColor3d(0.9,0.7,0.);
        glTranslated(x, y, z);
        glRotatef(0, 1, 1, 0);
        gluSphere(quad,2,100,100);
        gluDeleteQuadric(quad);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_LIGHTING);
}

void CEnvironnement::Sapin(float x, float y){
    //glEnable(GL_LIGHTING);
    glPushMatrix();
        GLUquadric* quad = gluNewQuadric();
        glColor3d(0.5,0.5,0.5);
        glTranslated(x, y, 0);
        //glRotatef(0, 1, 1, 0);
        gluCylinder(quad, 0.1, 0.1, 2.2, 105, 1);
        glColor3d(0.1,0.1,0.1);
        glTranslated(0, 0, 2.6);
        //glRotatef(180,0, 1, 0);
        glutSolidCone(0.8,3,16,16);
    glPopMatrix();
    //glDisable(GL_LIGHTING);
}
void CEnvironnement::Arbre(int bois, int feuille, float x, float y){
//    //glEnable(GL_LIGHTING);
//    glPushMatrix();
//        GLUquadric* quad = gluNewQuadric();
//        glColor3d(0.5,0.5,0.5);
//        glTranslated(x, y, 0);
//        //glRotatef(0, 1, 1, 0);
//        gluCylinder(quad, 0.1, 0.1, 2.2, 105, 1);
//        glColor3d(0.1,0.1,0.1);
//        glTranslated(0, 0, 2.6);
//        //glRotatef(180,0, 1, 0);
//        gluSphere(quad,0.8,16,16);
//    glPopMatrix();
//    //glDisable(GL_LIGHTING);


    glPushMatrix();
    glTranslatef(x,y,0);

    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    GLUquadricObj *tronc;
    tronc = gluNewQuadric();
    gluQuadricTexture(tronc,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D,bois);
    gluCylinder(tronc,0.15,0.15,2.2,100,100);
    gluDeleteQuadric(tronc);

    glTranslatef(0,0,2.2);

    GLUquadricObj *sphere;
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D,feuille);
    gluSphere(sphere,0.7,10,10);
    gluDeleteQuadric(sphere);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void CEnvironnement::Pont(){

    glColor3d(0,0,0);
    glBegin(GL_QUADS);
    glVertex3d(11,2.5,2);
    glVertex3d(10,2.5,0);
    glVertex3d(10,3.5,0);
    glVertex3d(11,3.5,2);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3d(13,2.5,2);
    glVertex3d(11,2.5,2);
    glVertex3d(11,3.5,2);
    glVertex3d(13,3.5,2);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3d(14,2.5,0);
    glVertex3d(13,2.5,2);
    glVertex3d(13,3.5,2);
    glVertex3d(14,3.5,0);
    glEnd();

}

void CEnvironnement::Poteau(CGraphe graphe){
//glEnable(GL_LIGHTING);
    for (int pa=11;pa<13;pa++)
    {
        //On récupère chaque point annexe d'altitude !=0 et n'appartenant pas au pont
        CPointAnnexe ptAnnexe  = graphe.list_point_annexe.at(pa);
        //On affiche un pylône
        glPushMatrix();
            glColor3d(1,1,1);
            glTranslated(ptAnnexe.X, ptAnnexe.Y, ptAnnexe.Z/2);
            glutSolidCone(0.1,ptAnnexe.Z/2,100,100);
        glPopMatrix();
    }
//glDisable(GL_LIGHTING);
}

void CEnvironnement::Montagne(int roche, float x, float y){
    //glEnable(GL_LIGHTING);
    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad,GL_TRUE);
        glBindTexture(GL_TEXTURE_2D,roche);
        glColor3d(0.5,0.5,0.5);
        glTranslated(x, y, 0);
        //glRotatef(0, 1, 1, 0);
        gluCylinder(quad,4,0,7,16,16);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //glDisable(GL_LIGHTING);
}

void CEnvironnement::Ciel(int ciel){
    //glEnable(GL_LIGHTING);
    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad,GL_TRUE);
        glBindTexture(GL_TEXTURE_2D,ciel);
        glTranslatef(12.205,10.065,0.0);
        glRotatef(0, 1, 1, 0);
        gluSphere(quad,25,100,100);
        gluDeleteQuadric(quad);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_LIGHTING);
}
