#include "CCamera.h"
#include <GL/glu.h>

void CCamera::Position(int type_cam, float xcam, float ycam, double distcam, double xcentre,
                       double ycentre, double zcentre, double xciel, double yciel, double zciel)
{
    //---------------------Position de la caméra---------------------//
    switch(type_cam) {
        case 0:
            gluLookAt(xcam,ycam,distcam,xcentre,ycentre,zcentre,xciel,yciel,zciel);
            break;
//        case 1:
//            gluLookAt(A.Coord.X,A.Coord.Y-5,5,A.Coord.X,A.Coord.Y,A.Coord.Z,0,1,0);
//            break;
//        case 2:
//            gluLookAt(B.Coord.X,B.Coord.Y-5,5,B.Coord.X,B.Coord.Y,B.Coord.Z,0,1,0);
//            break;
//        case 3:
//            gluLookAt(C.Coord.X,C.Coord.Y-5,5,C.Coord.X,C.Coord.Y,C.Coord.Z,0,1,0);
//            break;
//        case 4:
//            gluLookAt(A.Coord.X,A.Coord.Y,A.Coord.Z+1,A.prochain_point.X,A.prochain_point.Y,A.prochain_point.Z+1,0,0,1);
//            break;
//        case 5:
//            gluLookAt(B.Coord.X,B.Coord.Y,B.Coord.Z+1,B.prochain_point.X,B.prochain_point.Y,B.prochain_point.Z+1,0,0,1);
//            break;
//        case 6:
//            gluLookAt(C.Coord.X,C.Coord.Y,C.Coord.Z+1,C.prochain_point.X,C.prochain_point.Y,C.prochain_point.Z+1,0,0,1);
        case 7:
            gluLookAt(xcam,ycam+40,distcam,10,10,zcentre,2,1,40);
    }
}
