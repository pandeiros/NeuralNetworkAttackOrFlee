#ifndef __ENEMY_H__
#define __ENEMY_H__

#define ENEMY_IMG "enemy.png"

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite {
public:
    // implement the "static create()" method manually
    static Enemy * create () {
        Enemy *pRet = new Enemy ();
        if (pRet && pRet->initWithFile (std::string (ENEMY_IMG))) {
            pRet->autorelease ();
            pRet->setAnchorPoint (cocos2d::Vec2 (0.5, 0.5));
            return pRet;
        }
        else {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }

private:

};

#endif // __ENEMY_H__
