#include "Program.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Program::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Program::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // =====================================================================

    initLayers ();
    initPlayer ();
    initKeyListener ();
    initParamLabels ();
    initInfoLabels ();
    updateLabelColors ();

    scheduleUpdate ();

    return true;
}

void Program::update (float dt) {
    if (activeSimulationOne && status == 0 && vecEnemies.size() > 0)
        simulateOne (dt);
    else {
        // Update messages.

        activeSimulationOne = false; 
    }

    // Update labels
    lblIterations->setString (std::to_string (iterations));
    lblMaxDistance->setString (std::to_string (maxDistance));
    lblMaxEnemies->setString (std::to_string (maxEnemies));
    lblMinHp->setString (std::to_string (minHp));

    lblHP->setString (std::to_string (hp));
    lblDistance->setString (std::to_string (distance));
    lblEnemies->setString (std::to_string (enemies));

    lblMaxEnemies->setColor (Color3B (255, (10 - maxEnemies) * 255 / 9, (10 - maxEnemies) * 255 / 9));
}

void Program::initLayers () {
    // >>> GAME LAYER <<<
    gameLayer = cocos2d::LayerColor::create (cocos2d::Color4B (10, 103, 163, 150));
    gameLayer->setPosition (visibleSize.width * 2 / 7.f, visibleSize.height * 2 / 5.f);
    gameLayer->changeHeight (visibleSize.height * 3 / 5);
    gameLayer->changeWidth (visibleSize.width * 5 / 7);
    this->addChild (gameLayer);

    // >>> NETWORK LAYER <<<
    infoLayer = cocos2d::LayerColor::create (cocos2d::Color4B (255, 65, 0, 150));
    infoLayer->setPosition (0, visibleSize.height * 2 / 5.f);
    infoLayer->changeHeight (visibleSize.height * 3 / 5);
    infoLayer->changeWidth (visibleSize.width * 2 / 7);
    this->addChild (infoLayer);

    // >>> GAME LAYER <<<
    networkLayer = cocos2d::LayerColor::create (cocos2d::Color4B (255, 188, 0, 150));
    networkLayer->setPosition (0, 0);
    networkLayer->changeHeight (visibleSize.height * 2 / 5);
    this->addChild (networkLayer);
}

void Program::initPlayer () {
    // >>> PLAYER <<<
    player = Player::create ();
    player->setPosition (50, gameLayer->getBoundingBox ().size.height / 2.f);
    gameLayer->addChild (player, 15);
}

void Program::initKeyListener () {
    // >>> KEY LISTENER <<<
    EventListenerKeyboard * keyListener = EventListenerKeyboard::create ();
    keyListener->onKeyPressed = CC_CALLBACK_2 (Program::keyPressedEvent, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority (keyListener, this);
}

void Program::initParamLabels () {
    // >>> ITERATIONS <<<
    lblIterations = Label::createWithTTF (std::to_string (iterations), std::string (FONT_PATH), 60);
    lblIterations->setAnchorPoint (Vec2 (0, 0));
    lblIterations->setPosition (25, infoLayer->getBoundingBox ().size.height * 3 / 4 + 5);
    lblIterations->setColor (Color3B (255, 255, 255));
    infoLayer->addChild (lblIterations, 10);

    // >>> MAX DISTANCE <<<
    lblMaxDistance = Label::createWithTTF (std::to_string (maxDistance), std::string (FONT_PATH), 60);
    lblMaxDistance->setAnchorPoint (Vec2 (0, 0));
    lblMaxDistance->setPosition (25, infoLayer->getBoundingBox ().size.height * 2 / 4 + 5);
    lblMaxDistance->setColor (Color3B (255, 255, 255));
    infoLayer->addChild (lblMaxDistance, 10);

    // >>> MIN HP <<<
    lblMinHp = Label::createWithTTF (std::to_string (minHp), std::string (FONT_PATH), 60);
    lblMinHp->setAnchorPoint (Vec2 (0, 0));
    lblMinHp->setPosition (25, infoLayer->getBoundingBox ().size.height * 1 / 4 + 5);
    lblMinHp->setColor (Color3B (255, 255, 255));
    infoLayer->addChild (lblMinHp, 10);

    // >>> MAX ENEMIES <<<
    lblMaxEnemies = Label::createWithTTF (std::to_string (maxEnemies), std::string (FONT_PATH), 60);
    lblMaxEnemies->setAnchorPoint (Vec2 (0, 0));
    lblMaxEnemies->setPosition (25, infoLayer->getBoundingBox ().size.height * 0 / 4 + 5);
    lblMaxEnemies->setColor (Color3B (255, (10 - maxEnemies) * 255 / 9, (10 - maxEnemies) * 255 / 9));
    infoLayer->addChild (lblMaxEnemies, 10);

    // =====================================================================

    // >>> HP <<<
    lblHP = Label::createWithTTF (std::to_string (hp), std::string (FONT_PATH), 60);
    lblHP->setAnchorPoint (Vec2 (0, 0));
    lblHP->setPosition (gameLayer->getBoundingBox ().size.width * 0 / 3 + 20, 20);
    lblHP->setColor (Color3B (225, 225, 225));
    gameLayer->addChild (lblHP, 10);

    // >>> ENEMIES <<<
    lblEnemies = Label::createWithTTF (std::to_string (enemies), std::string (FONT_PATH), 60);
    lblEnemies->setAnchorPoint (Vec2 (0, 0));
    lblEnemies->setPosition (gameLayer->getBoundingBox ().size.width * 2 / 5, 20);
    lblEnemies->setColor (Color3B (225, 225, 225));
    gameLayer->addChild (lblEnemies, 10);

    // >>> DISTANCE <<<
    lblDistance = Label::createWithTTF (std::to_string (distance), std::string (FONT_PATH), 60);
    lblDistance->setAnchorPoint (Vec2 (0, 0));
    lblDistance->setPosition (gameLayer->getBoundingBox ().size.width * 4 / 5 + 20, 20);
    lblDistance->setColor (Color3B (225, 225, 225));
    gameLayer->addChild (lblDistance, 10);
}

void Program::initInfoLabels () {
    // >>> ITERATIONS INFO <<<
    lblIterationsInfo = Label::createWithTTF ("Iterations", std::string (FONT_PATH), 30);
    lblIterationsInfo->setAnchorPoint (Vec2 (0, 0));
    lblIterationsInfo->setPosition (10, infoLayer->getBoundingBox ().size.height * 3 / 4 + 65);
    lblIterationsInfo->setColor (Color3B (200, 200, 200));
    infoLayer->addChild (lblIterationsInfo, 10);

    // >>> MAX DISTANCE INFO <<<
    lblMaxDistanceInfo = Label::createWithTTF ("Max Distance", std::string (FONT_PATH), 30);
    lblMaxDistanceInfo->setAnchorPoint (Vec2 (0, 0));
    lblMaxDistanceInfo->setPosition (10, infoLayer->getBoundingBox ().size.height * 2 / 4 + 65);
    lblMaxDistanceInfo->setColor (Color3B (200, 200, 200));
    infoLayer->addChild (lblMaxDistanceInfo, 10);

    // >>> MIN HP INFO <<<
    lblMinHpInfo = Label::createWithTTF ("Min Hp", std::string (FONT_PATH), 30);
    lblMinHpInfo->setAnchorPoint (Vec2 (0, 0));
    lblMinHpInfo->setPosition (10, infoLayer->getBoundingBox ().size.height * 1 / 4 + 65);
    lblMinHpInfo->setColor (Color3B (200, 200, 200));
    infoLayer->addChild (lblMinHpInfo, 10);

    // >>> MAX ENEMIES INFO <<<
    lblMaxEnemiesinfo = Label::createWithTTF ("Enemies", std::string (FONT_PATH), 30);
    lblMaxEnemiesinfo->setAnchorPoint (Vec2 (0, 0));
    lblMaxEnemiesinfo->setPosition (10, infoLayer->getBoundingBox ().size.height * 0 / 4 + 65);
    lblMaxEnemiesinfo->setColor (Color3B (200, 200, 200));
    infoLayer->addChild (lblMaxEnemiesinfo, 10);

    // ===================================================================

    // >>> HP INFO <<<
    lblHPInfo = Label::createWithTTF ("HP", std::string (FONT_PATH), 30);
    lblHPInfo->setAnchorPoint (Vec2 (0, 0));
    lblHPInfo->setPosition (gameLayer->getBoundingBox ().size.width * 0 / 3 + 20, 80);
    lblHPInfo->setColor (Color3B (200, 200, 200));
    gameLayer->addChild (lblHPInfo, 10);

    // >>> ENEMIES INFO <<<
    lblEnemiesInfo = Label::createWithTTF ("Remaining Enemies", std::string (FONT_PATH), 30);
    lblEnemiesInfo->setAnchorPoint (Vec2 (0, 0));
    lblEnemiesInfo->setPosition (gameLayer->getBoundingBox ().size.width * 2 / 5 - 10, 80);
    lblEnemiesInfo->setColor (Color3B (200, 200, 200));
    gameLayer->addChild (lblEnemiesInfo, 10);

    // >>> DISTANCE INFO <<<
    lblDistanceInfo = Label::createWithTTF ("Distance", std::string (FONT_PATH), 30);
    lblDistanceInfo->setAnchorPoint (Vec2 (0, 0));
    lblDistanceInfo->setPosition (gameLayer->getBoundingBox ().size.width * 4 / 5 + 10, 80);
    lblDistanceInfo->setColor (Color3B (200, 200, 200));
    gameLayer->addChild (lblDistanceInfo, 10);
}

void Program::generateScene () {
    for (auto & e : vecEnemies) {
        if (e && e->getParent())
            e->removeFromParent ();
    }

    vecEnemies.clear ();

    for (unsigned int i = 0; i < maxEnemies; ++i) {
        Enemy * enemy = Enemy::create ();
        enemy->setPosition (rand () % maxDistance + 150, gameLayer->getBoundingBox ().size.height / 2.f);
        gameLayer->addChild (enemy, 10);
        vecEnemies.push_back (enemy);
    }
    enemies = maxEnemies;
    targetIndex = 0;

    minHp == 100 ? hp = 100 : hp = minHp + (rand () % (100 - minHp) + 1);

    // Sort
    std::sort (vecEnemies.begin (), vecEnemies.end (), [] (Enemy * a, Enemy * b) {
        return (a->getPosition ().x < b->getPosition ().x); });

    // Update distance
    distance = 9999;
    for (auto & e : vecEnemies) {
        distance = std::min (distance, (unsigned)e->getPosition ().x - (unsigned)player->getPosition ().x);
    }
}

void Program::keyPressedEvent (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    typedef cocos2d::EventKeyboard::KeyCode Key;

    switch (keyCode) {
        // EXIT
        case Key::KEY_ESCAPE:
            Director::getInstance ()->end ();
            break;

        // PARAM CHOICE UP
        case Key::KEY_UP_ARROW :
            activeParam == 0 ? activeParam = 3 : activeParam = (activeParam - 1) % 4;            
            updateLabelColors ();
            break;

        // PARAM CHOICE DOWN
        case Key::KEY_DOWN_ARROW:
            activeParam = (activeParam + 1) % 4;
            updateLabelColors ();
            break;

        // INCREASE PARAM
        case Key::KEY_RIGHT_ARROW:
            updateParam (true);
            break;

        // DECREASE PARAM
        case Key::KEY_LEFT_ARROW:
            updateParam (false);
            break;

        // SPAWN / SHUFFLE
        case Key::KEY_S :
            generateScene ();
            break;

        // ANIMATED SIMULATION (ONE)
        case Key::KEY_SPACE :
            if (status != 0) {
                generateScene ();
                status = 0;
            }
            activeSimulationOne = true;
            break;

        // MULTIPLE FAST SIMULATIONS
        case Key::KEY_ENTER :
        case Key::KEY_RETURN :
            simulateMany ();
            break;

        // PREDICT
        case Key::KEY_BACKSPACE :
            predict ();
            break;
    }

    // NUMBER OF SPAWNS
    /*if (keyCode >= Key::KEY_1 && keyCode <= Key::KEY_9) {
        maxEnemies = (unsigned int)(keyCode) - 76;
    }*/
}   

void Program::updateParam (bool increase) {
    switch (activeParam) {
        // ITERATIONS
        case 0:
            if (increase) {
                iterations *= 10;
                if (iterations > 1000)
                    iterations = 1000;
            }
            else {
                iterations /= 10;
                if (iterations == 0)
                    iterations = 1;
            }
            break;

            // MAX DISTANCE
        case 1:
            if (increase) {
                maxDistance += 100;
                if (maxDistance > 2000)
                    maxDistance = 2000;
            }
            else {
                maxDistance -= 100;
                if (maxDistance < 100)
                    maxDistance = 100;
            }
            break;
            
            // MIN HP
        case 2:
            if (increase) {
                minHp += 10;
                if (minHp > 100)
                    minHp = 100;
            }
            else {
                minHp -= 10;
                if (minHp == 0)
                    minHp = 10;
            }
            break;

            // MAX ENEMIES
        case 3:
            if (increase) {
                maxEnemies += 1;
                if (maxEnemies > 10)
                    maxEnemies = 10;
            }
            else {
                maxEnemies -= 1;
                if (maxEnemies == 0)
                    maxEnemies = 1;
            }
            break;

        default: break;
    }
}

void Program::updateLabelColors () {
    lblIterationsInfo->setColor (cocos2d::Color3B (200, 200, 200));
    lblMaxDistanceInfo->setColor (cocos2d::Color3B (200, 200, 200));
    lblMinHpInfo->setColor (cocos2d::Color3B (200, 200, 200));
    lblMaxEnemiesinfo->setColor (cocos2d::Color3B (200, 200, 200));

    switch (activeParam) {
        case 0:
            lblIterationsInfo->setColor (cocos2d::Color3B (225, 225, 0));
            break;
        case 1:
            lblMaxDistanceInfo->setColor (cocos2d::Color3B (225, 225, 0));
            break;
        case 2:
            lblMinHpInfo->setColor (cocos2d::Color3B (225, 225, 0));
            break;
        case 3:
            lblMaxEnemiesinfo->setColor (cocos2d::Color3B (225, 225, 0));
            break;
    }
}

void Program::simulateOne (float dt) {
    // Reload
    player->currentReloading += dt;

    // Shoot
    if (player->currentReloading >= player->reloadTime) {
        player->currentReloading -= player->reloadTime;

        // Kill first enemy
        vecEnemies[targetIndex]->removeFromParent ();
        vecEnemies[targetIndex] = nullptr;
        ++targetIndex;
        --enemies;
    }

    // Move enemies
    for (auto & e : vecEnemies) {
        if (e) {
            e->setPositionX (e->getPositionX () - e->speedPerSecond * dt);

            // Attack player if in range
            if (e->getPositionX () <= player->getPositionX () + player->getBoundingBox().size.width) {
                unsigned int tempDMG = e->minDMG + rand () % (e->maxDMG - e->minDMG + 1);
                tempDMG > hp ? hp = 0 : hp -= tempDMG;
               
                e->removeFromParent ();
                e = nullptr;
                ++targetIndex;
                --enemies;

                // Check player's hp
                if (hp <= 0) {

                    // DEFEAT
                    status = -1;
                }
            }
        }
    }

    // VICTORY
    if (enemies == 0)
        status = 1;
}

void Program::simulateMany () {
}

void Program::predict () {
}

void Program::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
