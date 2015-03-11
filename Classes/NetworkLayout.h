#ifndef __NETWORK_LAYOUT_H__
#define __NETWORK_LAYOUT_H__

#define ENEMY_IMG "enemy.png"

#include "cocos2d.h"

class NetworkLayout {
public:
    void init ();
    void draw ();

private:
    void drawInputNeurons ();
    void drawOutputNeurons ();
    void drawHiddenNeurons ();

    unsigned int layersCoords[3];
    unsigned int inputCoords[3];
};

#endif // __NETWORK_LAYOUT_H__
