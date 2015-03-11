#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#define FONT_PATH "fonts/neural.ttf"
#define FONT_BORDER_PATH "fonts/neuralol.ttf"

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
    void initParamLabels ();
    void initInfoLabels ();
    void initMsgLabels ();

    /// Events
    void keyPressedEvent (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void generateScene ();
    void updateParam (bool increase);
    void updateLabelColors ();

    /// Simulation
    void simulateOne (float dt);
    void simulateMany ();
    void predict ();
    bool activeSimulationOne = false;
    unsigned int targetIndex = 0;
    int status = 0; // 0 - unresolved, 1 - victory, -1 - defeat.
    unsigned int victories = 0;
    unsigned int defeats = 0;
    float step = 0.1;

    /// Layers
    cocos2d::LayerColor * gameLayer;
    cocos2d::LayerColor * networkLayer;
    cocos2d::LayerColor * infoLayer;

    /// Entities
    Player * player;
    std::vector<Enemy *> vecEnemies;

    /// Parameters
    unsigned int iterations = 1;
    unsigned int minHp = 100;
    unsigned int maxDistance = 500;
    unsigned int maxEnemies = 3;

    /// Game status
    unsigned int hp = 100;
    unsigned int distance = 0;
    unsigned int enemies = 3;
   
    /// Parameter Labels
    cocos2d::Label * lblIterations;
    cocos2d::Label * lblMaxDistance;
    cocos2d::Label * lblMinHp;
    cocos2d::Label * lblMaxEnemies;
    cocos2d::Label * lblEnemies;
    cocos2d::Label * lblDistance;
    cocos2d::Label * lblHP;

    /// Info labels
    cocos2d::Label * lblIterationsInfo;
    cocos2d::Label * lblMaxDistanceInfo;
    cocos2d::Label * lblMinHpInfo;
    cocos2d::Label * lblMaxEnemiesinfo;
    cocos2d::Label * lblEnemiesInfo;
    cocos2d::Label * lblDistanceInfo;
    cocos2d::Label * lblHPInfo;

    /// Changing parameters control
    int activeParam = 0;

    /// Control labels

    /// Message labels
    cocos2d::Label * lblVictories;
    cocos2d::Label * lblDefeats;

    /// Other
    cocos2d::Size visibleSize;
};

#endif // __PROGRAM_H__
