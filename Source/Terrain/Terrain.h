#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include "../Model.h"

class Terrain
{
public:
    static const int SIZE = 800;
    static const int VERTEX_COUNT = 100;

    Terrain();

    // At some point I need to modify my code to allow me pass around 'references'
    //const Model& getModel(){ return m_model; }
    Model model;  // m_ for privates?
private:


    void generateTerrain();

};




#endif
