#ifndef CTRAIN_H
#define CTRAIN_H

#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CGraphe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPoint3f.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPointAnnexe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CSommet.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CWagon.h"

#include <string>
#include <vector>

class CTrain{

    public:

        bool stop;

        double Deplacement_initial;
        double dX;
        double dY;
        double dZ;

        float init_ang_train;
        float init_ang_train_Z;

        CArc arc_choisi;
        CPoint3f train_coord;
        CArc arc_suivant;
        CPoint3f pt_suivant;

        int arc_aleatoire_id;
        int pa_suiv_id;
        int nbr_wagons;

//        CWagon wagon_a;
//        CWagon wagon_b;
//        CWagon wagon_c;
//
//        CTrain(CWagon wagon_A, CWagon wagon_B, CWagon wagon_C);
        ~CTrain();

    void Train_initialiser(int sommet, CGraphe graphe);
    void Train_dessiner(int couleur, int texture_wagon);
    void Train_deplacement(CPoint3f pt_suivant);
    //void Train_avancer(CGraphe graphe, CTrain train_bis, CTrain train_ter);

};

#endif // CTRAIN_H
