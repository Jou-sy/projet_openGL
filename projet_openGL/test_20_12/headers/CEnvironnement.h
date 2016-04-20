#ifndef CENVIRONNEMENT_H
#define CENVIRONNEMENT_H
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CGraphe.h"

class CEnvironnement
{
    public:
        CEnvironnement(){};
        ~CEnvironnement(){};

void AffichageGraphe(CGraphe graphe);
void Ground();
void Maison(float x, float y);
void Tunnel(CGraphe graphe);
void Lac(int eau, float x, float y, float r);
void Soleil(int sun, float x, float y, float z);
void Sapin(float x, float y);
void Arbre(int bois, int feuille, float x, float y);
void Pont();
void Poteau(CGraphe graphe);
void Montagne(int roche, float x, float y);
void Ciel(int ciel);
};


#endif // CENVIRONNEMENT_H
