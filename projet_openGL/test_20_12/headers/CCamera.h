#ifndef CCAMERA_H
#define CCAMERA_H


class CCamera
{
    public:
        CCamera(){};
        ~CCamera(){};

void Position(int type_cam, float xcam, float ycam, double distcam, double xcentre,
              double ycentre, double zcentre, double xciel, double yciel, double zciel);

};

#endif // CCAMERA_H
