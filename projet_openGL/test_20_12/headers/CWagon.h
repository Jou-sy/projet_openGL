#ifndef CWAGON_H
#define CWAGON_H

#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CGraphe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPoint3f.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPointAnnexe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CSommet.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CTrain.h"

#include <string>
#include <vector>

class CWagon
{
    public:

        double Dep_initial;
        double dX;
        double dY;
        double dZ;

        float init_ang_wagon;
        float init_ang_wagon_Z;

    	CPoint3f wagon_coord;
        CArc arc_choisi;

        int pa_suiv_id;

    	CWagon();
        ~CWagon();

    void Wagon_deplacement(CPoint3f pt_suivant);

};

#endif // CWAGON_H
