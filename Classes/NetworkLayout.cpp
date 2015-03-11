#include "NetworkLayout.h"

void NetworkLayout::init () {
    layersCoords[0] = 100;
    layersCoords[1] = 200;
    layersCoords[2] = 300;
    inputCoords[0] = 70;
    inputCoords[1] = 140;
    inputCoords[2] = 210;
}

void NetworkLayout::draw () {
    drawInputNeurons ();
    drawOutputNeurons ();
    drawHiddenNeurons ();
}

void NetworkLayout::drawInputNeurons () {
    cocos2d::ccDrawColor4B (0,255,0,150);

    for (unsigned int i = 0; i < 3; ++i) {
        cocos2d::ccDrawSolidCircle (cocos2d::Vec2 (layersCoords[0], inputCoords[i]), 25, 360, 50);
    }
}

void NetworkLayout::drawOutputNeurons () {
}

void NetworkLayout::drawHiddenNeurons () {
}
