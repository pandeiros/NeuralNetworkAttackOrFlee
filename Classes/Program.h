#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#define FONT_PATH "fonts/neural.ttf"

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
    /// Init methods.
    void initLayers ();
    void initPlayer ();
    void initKeyListener ();
    void initLabels ();

    /// Events
    void keyPressedEvent (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void spawnEnemies ();

    /// Layers
    cocos2d::LayerColor * gameLayer;
    cocos2d::LayerColor * networkLayer;
    cocos2d::LayerColor * infoLayer;

    /// Entities
    Player * player;
    std::vector<Enemy *> vecEnemies;

    /// Parameters
    unsigned int iterations = 1;
    unsigned int spawnCount = 3;
    unsigned int hp = 100;
    unsigned int distance = 0;
    unsigned int maxDistance = 500;

    /// Parameter Labels
    cocos2d::Label * lblIterations;
    cocos2d::Label * lblMaxDistance;
    cocos2d::Label * lblSpawns;
    cocos2d::Label * lblDistance;
    cocos2d::Label * lblHP;

    /// Other
    cocos2d::Size visibleSize;
};

#endif // __PROGRAM_H__
