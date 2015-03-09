#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PLAYER_IMG "player.png"

#include "cocos2d.h"

class Player : public cocos2d::Sprite {
public:
    // implement the "static create()" method manually
    static Player * create () {
        Player *pRet = new Player ();
        if (pRet && pRet->initWithFile (std::string (PLAYER_IMG))) {
            pRet->autorelease ();
            pRet->setAnchorPoint (cocos2d::Vec2(0.5, 0.5));
            return pRet;
        }
        else {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }

    /*virtual bool init () override {
        this->setTexture (std::string (PLAYER_IMG));

        return true;
    }*/

private:

};

#endif // __PLAYER_H__
