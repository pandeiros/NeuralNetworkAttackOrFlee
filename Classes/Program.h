#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Program : public cocos2d::Scene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Program);

    void update (float dt);

private:
    /// Layers
    cocos2d::LayerColor * gameLayer;
    cocos2d::LayerColor * networkLayer;
    cocos2d::LayerColor * infoLayer;

    /// Entities
    Player * player;
    std::vector<Enemy *> vecEnemies;
};

#endif // __PROGRAM_H__
