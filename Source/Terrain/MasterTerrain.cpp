// Copyright 2017 Andy Taylor
#include "MasterTerrain.h"

#include <cstdlib>
#include <ctime>

#include "Passage.h"
#include "Starting.h"
#include "Chamber.h"
#include "../Camera.h"
#include "../Math/Matrix.h"
#include "../Shaders/Shader_Program.h"

MasterTerrain::MasterTerrain() {
    generateDungeon();
}

void MasterTerrain::generateDungeon() {
    srand((int) time(0));
    for (int i = 0; i < 10; i++){
        std::cout << rand() << std::endl;
    }
    genStartingArea();
    std::cout << terrains.size() << " terrain elements generated" << std::endl;
    //Starting s = Starting(0, 0, 200, 200, 200);
}

void MasterTerrain::genStartingArea() {
    // std::vector<float> bounds;
    int r = rand() % 2;
    if (r > 1){ r = 0; } // Changed depending on how many possibilities I've created

    Starting s;
    float width, height, length;
    int exits[4];
    switch(r) {
        case 0:
        {
            // bounds = {-1, -1, 0, 50, 0, 50};
            width = 200;
            height = 200;
            length = 200;
            
            for (int i = 0; i < 4; i++) {
                exits[i] = 1;
            }
            
            break;
        }
        case 1:
        {
            width = 200;
            height = 200;
            length = 200;
            
            exits[1] = 1;
            exits[0] = 2;
            exits[2] = 2;
        }
        default:
            // terrains.push_back(Starting(0, 0, 200, 200, 200));
            break;
    }
    s = Starting(0, 0, 0, width, height, length);
    
    if (exits[0] == 1) s.addAdjTerrain(genPassage(0, -height/2, length/2, 0, 0));
    if (exits[1] == 1) s.addAdjTerrain(genPassage(0, -height/2, -length/2, 180, 0));
    if (exits[2] == 1) s.addAdjTerrain(genPassage(width/2, -height/2, 0, 90, 0));
    if (exits[3] == 1) s.addAdjTerrain(genPassage(-width/2, -height/2, 0, 270, 0));
    
    s.generateTerrain();
    terrains.push_back(s);
}

Terrain MasterTerrain::genChamber(float worldX, float worldY, float worldZ, float rot, int depth) {
    // std::vector<float> bounds;
    depth += 1;
    int r = rand() % 4;
    if (r > 3){ r = 0; } // Changed depending on how many possibilities I've created

    Chamber s;
    int index = 0;
    float width, height, length;
    switch(r) {
        case 0:
        {
            width = 200;
            height = 200;
            length = 300;
            break;
        }
        case 1:
        {
            width = 100;
            height = 200;
            length = 100;
            break;
        }
        case 2:
        {
            width = 300;
            height = 200;
            length = 300;
            break;
        }
        case 3:
        {
            width = 600;
            height = 200;
            length = 200;
            break;
        }
        default:
            // terrains.push_back(Starting(0, 0, 200, 200, 200));
            break;
    }
    
    double xoff, yoff, zoff;
    int xmod, ymod, zmod;
    getModifiers(&xmod, &ymod, &zmod, rot);
    
    if (rot == 0 || rot == 180) {
        xoff = xmod*width/2;
        yoff = height/2*ymod;
        zoff = zmod*length/2;
    } else if (rot == 90 || rot == 270) {
        xoff = xmod*length/2;
        yoff = height/2*ymod;
        zoff = zmod*width/2;
    }
    
    s = Chamber(worldX+xoff, worldY+height, worldZ+zoff, width, height, length);
    s.model.entity.rotation.y = rot;

    if (depth < MAXDEPTH) {
        s.addAdjTerrain(genPassage(worldX+xoff*2, worldY+yoff, worldZ+zoff*2, rot, depth));
        
        int xmod2, ymod2, zmod2;
        int xmod3, ymod3, zmod3;
        float width2 = width, height2 = height, length2 = length;
        getDimensions(&width2, &height2, &length2, normang(rot));
        
        getModifiers2(&xmod3, &ymod3, &zmod3, normang(rot));
        getModifiers2(&xmod2, &ymod2, &zmod2, normang(rot+90));
        s.addAdjTerrain(genPassage(worldX+width2/2*xmod2*xmod3, worldY+height2/2*ymod2*ymod3, worldZ+length2/2*zmod2*zmod3, normang(rot+90), depth));
        
        getModifiers2(&xmod3, &ymod3, &zmod3, normang(rot));
        getModifiers2(&xmod2, &ymod2, &zmod2, normang(rot-90));
        s.addAdjTerrain(genPassage(worldX+width2/2*xmod2*xmod3, worldY+height2/2*ymod2*ymod3, worldZ+length2/2*zmod2*zmod3, normang(rot-90), depth));
    }
    
    s.generateTerrain();

    index = terrains.size();
    terrains.push_back(s);

    return terrains[index];
}

Terrain MasterTerrain::genPassage(float worldX, float worldY, float worldZ, float rot, int depth) {
    depth += 1;
    int r = rand() % 20;
    if (r > 0){ r = 0; } // Changed depending on how many possibilities I've created

    Passage p;

    int index = 0;
    float width, height, length;
    switch(r) {
        case 0:
        {
            width = 100; height = 100; length = 500;
            double xoff, yoff, zoff;
            int xmod, ymod, zmod;
            getModifiers(&xmod, &ymod, &zmod, rot);
            if (rot == 0 || rot == 180) {
                xoff = xmod*width/2;
                yoff = height/2*ymod;
                zoff = zmod*length/2;
            } else if (rot == 90 || rot == 270) {
                xoff = xmod*length/2;
                yoff = height/2*ymod;
                zoff = zmod*width/2;
            }

            p = Passage(worldX+xoff, worldY+yoff, worldZ+zoff, width, height, length);
            p.model.entity.rotation.y = rot;
            p.generateTerrain();

            if (depth < MAXDEPTH) p.addAdjTerrain(genChamber(worldX+xoff*2, worldY-yoff*2, worldZ+zoff*2, rot, depth));

            index = terrains.size();
            terrains.push_back(p);
            break;
        }
        default:
            break;
    }

    return terrains[index];
}

void MasterTerrain::getModifiers(int* xmod, int* ymod, int* zmod, float rot) {
    if (rot == 0){
        *xmod = 0;
        *ymod = 1;
        *zmod = 1;
    } else if (rot == 90) {
        *xmod = 1;
        *ymod = 1;
        *zmod = 0;
    } else if (rot == 180) {
        *xmod = 0;
        *ymod = 1;
        *zmod = -1;
    } else if (rot == 270) {
        *xmod = -1;
        *ymod = 1;
        *zmod = 0;
    }
}

void MasterTerrain::getModifiers2(int* xmod, int* ymod, int* zmod, float rot) {
    if (rot == 0){
        *xmod = 1;
        *ymod = 1;
        *zmod = 1;
    } else if (rot == 90) {
        *xmod = 1;
        *ymod = 1;
        *zmod = 1;
    } else if (rot == 180) {
        *xmod = 1;
        *ymod = 1;
        *zmod = -1;
    } else if (rot == 270) {
        *xmod = -1;
        *ymod = 1;
        *zmod = 1;
    }
}

void MasterTerrain::getDimensions(float* width, float* height, float* length, float rot) {
    float width2 = *width, height2 = *height, length2 = *length;
    if (rot == 90 || rot == 270) {
        *width = length2;
        *height = height2;
        *length = width2;
    }
}

float MasterTerrain::normang(float ang) {
    while (ang >= 360){ ang -= 360; }
    while (ang < 0){ ang += 360; }
    return ang;
}

void MasterTerrain::render(Shader::Shader_Program* simpleShader, Camera* camera) {
    for (int i = 0; i < terrains.size(); i++) {
        glm::mat4 m = Maths::createModelMatrix(terrains[i].model.entity);
        glm::mat4 v = Maths::createViewMatrix(*camera);
        glm::mat4 mvp = Maths::createProjMatrix() * v * m;
        simpleShader->loadMVP(mvp, m, v);

        terrains[i].model.draw();
    }
}
