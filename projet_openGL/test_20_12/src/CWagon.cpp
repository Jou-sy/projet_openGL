#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CWagon.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CGraphe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPoint3f.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CPointAnnexe.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CSommet.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CTrain.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

CWagon::CWagon(){

    Dep_initial = 0.08;

    init_ang_wagon = 0;
    init_ang_wagon_Z = 0;

    pa_suiv_id = 0;

}

CWagon::~CWagon(){
}

void CWagon::Wagon_deplacement(CPoint3f pt_suivant){

    double distance_pt = sqrt(pow(pt_suivant.X-wagon_coord.X,2)+pow(pt_suivant.Y-wagon_coord.Y,2)+pow(pt_suivant.Z-wagon_coord.Z,2));

    dX = (pt_suivant.X-wagon_coord.X)/distance_pt*Dep_initial;
    dY = (pt_suivant.Y-wagon_coord.Y)/distance_pt*Dep_initial;
    dZ = (pt_suivant.Z-wagon_coord.Z)/distance_pt*Dep_initial;

    init_ang_wagon = atan(dY/dX)*180/3.14;
    init_ang_wagon_Z = atan(dZ/sqrt(pow(dX,2)+pow(dY,2)))*180/3.14;

    wagon_coord.X = wagon_coord.X+dX;
    wagon_coord.Y = wagon_coord.Y+dY;
    wagon_coord.Z = wagon_coord.Z+dZ;

}
