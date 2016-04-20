#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CTrain.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CGraphe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPoint3f.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPointAnnexe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CSommet.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CWagon.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

CTrain::CTrain(CWagon wagon_A, CWagon wagon_B, CWagon wagon_C){
    //Initialisations
    stop = 0;

    Deplacement_initial = 0.08;

    init_ang_train = 0;
    init_ang_train_Z = 0;

    nbr_wagons = 3;

    CWagon wagon_a = wagon_A;
    CWagon wagon_b = wagon_B;
    CWagon wagon_c = wagon_C;

    pa_suiv_id = 0;

}

CTrain::~CTrain(){
}

void CTrain::Train_initialiser(int sommet, CGraphe graphe){
    //Position initiale du train (aléatoire sur un sommet)
    CSommet sommet_dep = graphe.list_sommet.at(sommet);
    //Tirage au hasard de l'arc à suivre
    int arc_choisi_id = rand()%graphe.getListArcSortantDuSommet(sommet_dep).size();
    arc_choisi = graphe.getListArcSortantDuSommet(sommet_dep).at(arc_choisi_id);
    int sommet_dep_id = arc_choisi.id_sommet_ini;
    //Initialisation de ses coordonnées comme les coordonnées du sommet de départ
    train_coord = (CPoint3f)graphe.list_sommet.at(sommet_dep_id);
    train_coord.Z = train_coord.Z + 0.33;
    //Calcul du prochain point annexe que va suivre le train
    CPoint3f pa_proch = graphe.getListPointAnnexeArc(arc_choisi).at(pa_suiv_id);

    //Distance entre le train et le point annexe suivant
    double dist_train_pa_proch = sqrt(pow(pa_proch.X-train_coord.X,2)+pow(pa_proch.Y-train_coord.Y,2)+pow(pa_proch.Z-train_coord.Z,2));

    //calcul de la distance séparant le train de son wagon
    wagon_a.dX = -(pa_proch.X-train_coord.X)/dist_train_pa_proch;
    wagon_a.dY = -(pa_proch.Y-train_coord.Y)/dist_train_pa_proch;
    wagon_a.dZ = -(pa_proch.Z-train_coord.Z)/dist_train_pa_proch;


    //Initialisation des coordonnées du wagon comme celles du train auxquelles on ajoute la distance fixée
    wagon_a.wagon_coord.X = train_coord.X+1*wagon_a.dX/1.3;
    wagon_a.wagon_coord.Y = train_coord.Y+1*wagon_a.dY/1.3;
    wagon_a.wagon_coord.Z = train_coord.Z+1*wagon_a.dZ/1.3;
    wagon_b.wagon_coord.X = train_coord.X+2*wagon_a.dX/1.3;
    wagon_b.wagon_coord.Y = train_coord.Y+2*wagon_a.dY/1.3;
    wagon_b.wagon_coord.Z = train_coord.Z+2*wagon_a.dZ/1.3;
    wagon_c.wagon_coord.X = train_coord.X+3*wagon_a.dX/1.3;
    wagon_c.wagon_coord.Y = train_coord.Y+3*wagon_a.dY/1.3;
    wagon_c.wagon_coord.Z = train_coord.Z+3*wagon_a.dZ/1.3;

    // Définition de son arc suivi, comme celui du train
    wagon_a.arc_choisi = arc_choisi;
    wagon_b.arc_choisi = arc_choisi;
    wagon_c.arc_choisi = arc_choisi;
}

void CTrain::Train_dessiner(int couleur, int texture_wagon) {
    //glEnable(GL_LIGHTING);
        if (couleur == 1){
            glColor3d(1,0,0);
        }
        else if (couleur == 2){
            glColor3d(0,1,0);
        }
        else if (couleur == 3){
            glColor3d(0,0,1);
        }

    //Locomotive
    glPushMatrix();
        glTranslated(train_coord.X,train_coord.Y,train_coord.Z+0.2);
        glRotatef(init_ang_train,0,0,1);
        glRotatef(init_ang_train_Z,1,1,0);
        glutSolidCube(0.7);
        glTranslated(0,0,0.35);
        GLUquadric* quad = gluNewQuadric();
        gluCylinder(quad, 0.35, 0, 1, 10, 10);
        gluDeleteQuadric(quad);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
        glTranslated(wagon_a.wagon_coord.X,wagon_a.wagon_coord.Y,wagon_a.wagon_coord.Z+0.33);
        glRotatef(wagon_a.init_ang_wagon,0,0,1);
        glRotatef(wagon_a.init_ang_wagon_Z,1,1,0);
        GLUquadric* quad3 = gluNewQuadric();
        gluQuadricTexture(quad3,GL_TRUE);
        glBindTexture(GL_TEXTURE_2D,texture_wagon);
        gluSphere (quad3, 0.4, 10, 10);
        gluDeleteQuadric(quad3);
    glPopMatrix();

    glPushMatrix();
        glTranslated(wagon_b.wagon_coord.X,wagon_b.wagon_coord.Y,wagon_b.wagon_coord.Z+0.33);
        glRotatef(wagon_b.init_ang_wagon,0,0,1);
        glRotatef(wagon_b.init_ang_wagon_Z,1,1,0);
        GLUquadric* quad4 = gluNewQuadric();
        gluQuadricTexture(quad4,GL_TRUE);
        glBindTexture(GL_TEXTURE_2D,texture_wagon);
        gluSphere (quad4, 0.4, 10, 10);
        gluDeleteQuadric(quad4);
    glPopMatrix();

    glPushMatrix();
        glTranslated(wagon_c.wagon_coord.X,wagon_c.wagon_coord.Y,wagon_c.wagon_coord.Z+0.33);
        glRotatef(wagon_c.init_ang_wagon,0,0,1);
        glRotatef(wagon_c.init_ang_wagon_Z,1,1,0);
        GLUquadric* quad5 = gluNewQuadric();
        gluQuadricTexture(quad5,GL_TRUE);
        glBindTexture(GL_TEXTURE_2D,texture_wagon);
        gluSphere (quad5, 0.4, 10, 10);
        gluDeleteQuadric(quad5);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //glDisable(GL_LIGHTING) ;
}

void CTrain::Train_deplacement(CPoint3f pt_suivant){
        double distance = sqrt(pow(pt_suivant.X-train_coord.X,2)+pow(pt_suivant.Y-train_coord.Y,2)+pow(pt_suivant.Z-train_coord.Z,2));
        dX = (pt_suivant.X-train_coord.X)/distance*Deplacement_initial;
        dY = (pt_suivant.Y-train_coord.Y)/distance*Deplacement_initial;
        dZ = (pt_suivant.Z-train_coord.Z)/distance*Deplacement_initial;
        init_ang_train = atan(dY/dX)*180/3.14;
        init_ang_train_Z = atan(dZ/sqrt(pow(dX,2)+pow(dY,2)))*180/3.14;
        //Déplacement train
        train_coord.X=train_coord.X+dX;
        train_coord.Y=train_coord.Y+dY;
        train_coord.Z=train_coord.Z+dZ;
        stop = 0;
}

//void CTrain::Train_avancer(CGraphe graphe, CTrain train_bis, CTrain train_ter){
//    //On regarde si le point suivant est un point annexe
//    if (iPASuiv<graphe.getListPointAnnexeArc(ArcSuivi).size()){
//        // Si oui, on détermine le prochain point à atteindre
//        CPoint3f prochPA=graphe.getListPointAnnexeArc(ArcSuivi).at(iPASuiv);
//        pt_suivant = prochPA;
//        // Le train se déplacer jusqu'au point annexe
//        calcul_mvt(prochPA);
//        //Si on est aux alentours d'un PA, on passe au suivant
//        if (fabs(train_coord.X-prochPA.X)<0.1){
//            iPASuiv+=1;
//        }
//    }
//    //Sinon, on arrive à un sommet
//    else {
//        // Le train se déplace jusqu'au sommet
//        CSommet prochSommet=graphe.list_sommet.at(ArcSuivi.id_sommet_fin);
//        pt_suivant = prochSommet;
//
//        //On détermine alors aléatoirement l'arc suivant
//        arc_aleatoire_id = rand()%graphe.getListArcSortantDuSommet(prochSommet).size();
//        arc_suivant = graphe.getListArcSortantDuSommet(prochSommet).at(arc_aleatoire_id);
//
//        //si on arrive à la distance de sécurité du sommet, ie 2, on teste si la voie est libre
//        if(pow(pow(prochSommet.X-train_coord.X,2)+pow(prochSommet.Y-train_coord.Y,2)+pow(prochSommet.Z-train_coord.Z,2),0.5)<2){
//            //on teste si qqun s'approche aussi du sommet
//            if (pt_suivant.X!=autretrain.pt_suivant.X && pt_suivant.X!=autretrain2.pt_suivant.X){
//               if(arc_suivant.id_arc!=autretrain.ArcSuivi.id_arc && arc_suivant.id_arc!=autretrain2.ArcSuivi.id_arc){
//                   //si l'arc suivant n'est pas occupé et que personne s'en approche
//                   //on avance encore jusqu'à la distance de 0.1
//                    if(!(pow(pow(prochSommet.X-train_coord.X,2)+pow(prochSommet.Y-train_coord.Y,2)+pow(prochSommet.Z-train_coord.Z,2),0.5)<0.1)){
//                        //on se déplace
//                      calcul_mvt(prochSommet);
//                    }
//                    else{
//                        //on s'engage dans le nouvel arc
//                        ArcSuivi = arc_suivant;
//                        int Id_sommet_depart = ArcSuivi.id_sommet_ini;
//                        train_coord = (CPoint3f)graphe.list_sommet.at(Id_sommet_depart);
//                        iPASuiv = 0;
//                        arret=0;
//                    }
//            }
//            else {
//                //Si l'arc est occupé on ne fait rien
//                arret = 1;
//            }
//        }else { //un autre train arrive sur le sommet
//                //si ce train est deja arrete au sommet
//                if ((autretrain.arret==1 && pt_suivant.X==autretrain.pt_suivant.X )|| (autretrain2.arret==1 && pt_suivant.X==autretrain2.prochain_point.X)){
//                    //on avance sur l'arc, sauf s'il est déjà occupé
//                     if(arc_suivant.id_arc!=autretrain.ArcSuivi.id_arc && arc_suivant.id_arc!=autretrain2.ArcSuivi.id_arc){
//                           //si l'arc suivant n'est pas occupé
//                           //on avance encore jusqu'à la distance de 0.1
//                            if(!(pow(pow(prochSommet.X-train_coord.X,2)+pow(prochSommet.Y-train_coord.Y,2)+pow(prochSommet.Z-train_coord.Z,2),0.5)<0.1)){
//                                //on se déplace
//                               calcul_mvt(prochSommet);
//                            }else{
//                                //on s'engage dans le nouvel arc
//                                ArcSuivi = arc_suivant;
//                                int Id_sommet_depart = ArcSuivi.id_sommet_ini;
//                                train_coord = (CPoint3f)graphe.list_sommet.at(Id_sommet_depart);
//                                iPASuiv = 0;
//                                arret=0;
//                            }
//                       }else {
//                            //Si l'arc est occupé on ne fait rien
//                            arret = 1;
//                       }
//                }else{ //si aucun train n'est arrete au sommet
//                        //on s'arrete
//                        arret = 1;
//                    }
//
//            }
//
//        }else{ //on est encore loin du sommet : le train peut se déplacer
//
//            //Déplacement
//                calcul_mvt(prochSommet);
//        }
//    }
//
// if(arret!=1){
//        if (W1.iPASuiv<graphe.getListPointAnnexeArc(W1.ArcSuivi).size()){
//            //si le point suivant est un point annexe
//            // position à atteindre
//            CPoint3f prochPA=graphe.getListPointAnnexeArc(W1.ArcSuivi).at(W1.iPASuiv);
//            //Déplacement
//            W1.calcul_mvt(prochPA);
//            if (fabs(W1.train_coord.X-prochPA.X)<0.1){
//                W1.iPASuiv+=1;
//            }
//        }
//        else {
//            // On arrive à un sommet
//            // position à atteindre
//            CSommet prochSommet=graphe.list_sommet.at(W1.ArcSuivi.id_sommet_fin);
//            if(pow(pow(prochSommet.X-W1.train_coord.X,2)+pow(prochSommet.Y-W1.train_coord.Y,2)+pow(prochSommet.Z-W1.train_coord.Z,2),0.5)<
//               2 + pow(pow(train_coord.X-W1.train_coord.X,2)+pow(train_coord.Y-W1.train_coord.Y,2)+pow(train_coord.Z-W1.train_coord.Z,2),0.5)){
//                //Si le wagon est proche du sommet (à la distance de sécurité + la distance entre lui et la loco tr1)
//                //il faut tester si l'arc sur lequel va s'engager le train est occupé, auquel cas il faut s'arrêter, ou libre
//                    if(prochainArc.id_arc!=autretrain.ArcSuivi.id_arc && prochainArc.id_arc!=autretrain2.ArcSuivi.id_arc){
//                    //si l'arc suivant n'est pas occupé
//                            //on avance encore jusqu'à la distance de 0.1
//                            if(!(pow(pow(prochSommet.X-W1.train_coord.X,2)+pow(prochSommet.Y-W1.train_coord.Y,2)+pow(prochSommet.Z-W1.train_coord.Z,2),0.5)<0.1)){
//                                //on se déplace
//                               W1.calcul_mvt(prochSommet);
//                            }
//                            else{
//                                //on s'engage dans le nouvel arc
//                                W1.ArcSuivi = prochainArc;
//                                int Id_sommet_depart = W1.ArcSuivi.id_sommet_ini;
//                                W1.train_coord = (CPoint3f)graphe.list_sommet.at(Id_sommet_depart);
//                                W1.iPASuiv = 0;
//                            }
//                    }
//                    else {
//                            //on ne fait rien
//                    }
//            }
//            else{ //le wagon peut se déplacer (on est encore loin du sommet)
//                //deplacement wagon
//                W1.calcul_mvt(prochSommet);
//            }
//        }
//
//        if (W2.iPASuiv<graphe.getListPointAnnexeArc(W2.ArcSuivi).size()){
//            //si le point suivant est un point annexe
//            // position à atteindre
//            CPoint3f prochPA=graphe.getListPointAnnexeArc(W2.ArcSuivi).at(W2.iPASuiv);
//            //Déplacement
//            W2.calcul_mvt(prochPA);
//            if (fabs(W2.train_coord.X-prochPA.X)<0.1){
//                W2.iPASuiv+=1;
//            }
//        }
//        else {
//            // On arrive à un sommet
//            // position à atteindre
//            CSommet prochSommet=graphe.list_sommet.at(W2.ArcSuivi.id_sommet_fin);
//            if(pow(pow(prochSommet.X-W2.train_coord.X,2)+pow(prochSommet.Y-W2.train_coord.Y,2)+pow(prochSommet.Z-W2.train_coord.Z,2),0.5)<
//               2 + pow(pow(train_coord.X-W2.train_coord.X,2)+pow(train_coord.Y-W2.train_coord.Y,2)+pow(train_coord.Z-W2.train_coord.Z,2),0.5)){
//                //Si le wagon est proche du sommet (à la distance de sécurité + la distance entre lui et la loco tr1)
//                //il faut tester si l'arc sur lequel va s'engager le train est occupé, auquel cas il faut s'arrêter, ou libre
//                    if(prochainArc.id_arc!=autretrain.ArcSuivi.id_arc && prochainArc.id_arc!=autretrain2.ArcSuivi.id_arc){
//                    //si l'arc suivant n'est pas occupé
//                            //on avance encore jusqu'à la distance de 0.1
//                            if(!(pow(pow(prochSommet.X-W2.train_coord.X,2)+pow(prochSommet.Y-W2.train_coord.Y,2)+pow(prochSommet.Z-W2.train_coord.Z,2),0.5)<0.1)){
//                                //on se déplace
//                               W2.calcul_mvt(prochSommet);
//                            }
//                            else{
//                                //on s'engage dans le nouvel arc
//                                W2.ArcSuivi = prochainArc;
//                                int Id_sommet_depart = W2.ArcSuivi.id_sommet_ini;
//                                W2.train_coord = (CPoint3f)graphe.list_sommet.at(Id_sommet_depart);
//                                W2.iPASuiv = 0;
//                            }
//                    }
//                    else {
//                            //on ne fait rien
//                    }
//
//            }
//            else{ //le wagon peut se déplacer (on est encore loin du sommet)
//                //deplacement wagon
//                W2.calcul_mvt(prochSommet);
//            }
//
//        }
//
//
//        if (W3.iPASuiv<graphe.getListPointAnnexeArc(W3.ArcSuivi).size()){
//            //si le point suivant est un point annexe
//            // position à atteindre
//            CPoint3f prochPA=graphe.getListPointAnnexeArc(W3.ArcSuivi).at(W3.iPASuiv);
//            //Déplacement
//            W3.calcul_mvt(prochPA);
//            if (fabs(W3.train_coord.X-prochPA.X)<0.1){
//                W3.iPASuiv+=1;
//            }
//        }
//        else {
//            // On arrive à un sommet
//            // position à atteindre
//            CSommet prochSommet=graphe.list_sommet.at(W3.ArcSuivi.id_sommet_fin);
//            if(pow(pow(prochSommet.X-W3.train_coord.X,2)+pow(prochSommet.Y-W3.train_coord.Y,2)+pow(prochSommet.Z-W3.train_coord.Z,2),0.5)<
//               2 + pow(pow(train_coord.X-W3.train_coord.X,2)+pow(train_coord.Y-W3.train_coord.Y,2)+pow(train_coord.Z-W3.train_coord.Z,2),0.5)){
//                //Si le wagon est proche du sommet (à la distance de sécurité + la distance entre lui et la loco tr1)
//                //il faut tester si l'arc sur lequel va s'engager le train est occupé, auquel cas il faut s'arrêter, ou libre
//                    if(prochainArc.id_arc!=autretrain.ArcSuivi.id_arc && prochainArc.id_arc!=autretrain2.ArcSuivi.id_arc){
//                    //si l'arc suivant n'est pas occupé
//                            //on avance encore jusqu'à la distance de 0.1
//                            if(!(pow(pow(prochSommet.X-W3.train_coord.X,2)+pow(prochSommet.Y-W3.train_coord.Y,2)+pow(prochSommet.Z-W3.train_coord.Z,2),0.5)<0.1)){
//                                //on se déplace
//                               W3.calcul_mvt(prochSommet);
//                            }
//                            else{
//                                //on s'engage dans le nouvel arc
//                                W3.ArcSuivi = prochainArc;
//                                int Id_sommet_depart = W3.ArcSuivi.id_sommet_ini;
//                                W3.train_coord = (CPoint3f)graphe.list_sommet.at(Id_sommet_depart);
//                                W3.iPASuiv = 0;
//                            }
//                    }
//                    else {
//                            //on ne fait rien
//                    }
//
//            }
//            else{ //le wagon peut se déplacer (on est encore loin du sommet)
//                //deplacement wagon
//                W3.calcul_mvt(prochSommet);
//            }
//
//        }
//    }
//  }
