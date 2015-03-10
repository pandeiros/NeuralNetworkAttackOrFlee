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

    scheduleUpdate ();

    return true;
}

void Program::update (float dt) {
    // Update labels
    lblIterations->setString (std::to_string (iterations));
    lblDistance->setString (std::to_string (distance));
    lblSpawns->setString (std::to_string (spawnCount));
    lblHP->setString (std::to_string (hp));
    lblMaxDistance->setString (std::to_string (maxDistance));
    lblSpawns->setColor (Color3B (255, (9 - spawnCount) * 255 / 8, (9 - spawnCount) * 255 / 8));
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

    // >>> DISTANCE <<<
    lblDistance = Label::createWithTTF (std::to_string (distance), std::string (FONT_PATH), 60);
    lblDistance->setAnchorPoint (Vec2 (0, 0));
    lblDistance->setPosition (gameLayer->getBoundingBox ().size.width * 2 / 3 + 20, 20);
    lblDistance->setColor (Color3B (225, 225, 225));
    gameLayer->addChild (lblDistance, 10);

    // >>> HP <<<
    lblHP = Label::createWithTTF (std::to_string (hp), std::string (FONT_PATH), 60);
    lblHP->setAnchorPoint (Vec2 (0, 0));
    lblHP->setPosition (gameLayer->getBoundingBox ().size.width * 0 / 4 + 20, 20);
    lblHP->setColor (Color3B (225, 225, 225));
    gameLayer->addChild (lblHP, 10);

    // >>> SPAWNS <<<
    lblSpawns = Label::createWithTTF (std::to_string (spawnCount), std::string (FONT_PATH), 60);
    lblSpawns->setAnchorPoint (Vec2 (0, 0));
    lblSpawns->setPosition (gameLayer->getBoundingBox ().size.width * 1 / 3 + 20, 20);
    lblSpawns->setColor (Color3B (255, (9 - spawnCount) * 255 / 8, (9 - spawnCount) * 255 / 8));
    gameLayer->addChild (lblSpawns, 10);
}

void Program::initInfoLabels () {
    // >>> ITERATIONS INFO <<<
    lblIterationsInfo = Label::createWithTTF ("Iterations [Up/Down]", std::string (FONT_PATH), 30);
    lblIterationsInfo->setAnchorPoint (Vec2 (0, 0));
    lblIterationsInfo->setPosition (10, infoLayer->getBoundingBox ().size.height * 3 / 4 + 65);
    lblIterationsInfo->setColor (Color3B (200, 200, 200));
    infoLayer->addChild (lblIterationsInfo, 10);

    // >>> MAX DISTANCE INFO <<<
    lblMaxDistanceInfo = Label::createWithTTF ("Max dist. [Left/Right]", std::string (FONT_PATH), 30);
    lblMaxDistanceInfo->setAnchorPoint (Vec2 (0, 0));
    lblMaxDistanceInfo->setPosition (10, infoLayer->getBoundingBox ().size.height * 2 / 4 + 65);
    lblMaxDistanceInfo->setColor (Color3B (200, 200, 200));
    infoLayer->addChild (lblMaxDistanceInfo, 10);

    // >>> HP INFO <<<
    lblHPInfo = Label::createWithTTF ("HP", std::string (FONT_PATH), 30);
    lblHPInfo->setAnchorPoint (Vec2 (0, 0));
    lblHPInfo->setPosition (gameLayer->getBoundingBox ().size.width * 0 / 3 + 20, 80);
    lblHPInfo->setColor (Color3B (200, 200, 200));
    gameLayer->addChild (lblHPInfo, 10);

    // >>> SPAWNS INFO <<<
    lblSpawnsInfo = Label::createWithTTF ("Enemies", std::string (FONT_PATH), 30);
    lblSpawnsInfo->setAnchorPoint (Vec2 (0, 0));
    lblSpawnsInfo->setPosition (gameLayer->getBoundingBox ().size.width * 1 / 3 + 10, 80);
    lblSpawnsInfo->setColor (Color3B (200, 200, 200));
    gameLayer->addChild (lblSpawnsInfo, 10);

    // >>> DISTANCE INFO <<<
    lblDistanceInfo = Label::createWithTTF ("Distance", std::string (FONT_PATH), 30);
    lblDistanceInfo->setAnchorPoint (Vec2 (0, 0));
    lblDistanceInfo->setPosition (gameLayer->getBoundingBox ().size.width * 2 / 3 + 10, 80);
    lblDistanceInfo->setColor (Color3B (200, 200, 200));
    gameLayer->addChild (lblDistanceInfo, 10);
}

void Program::spawnEnemies () {
    for (auto & e : vecEnemies) {
        e->removeFromParent ();
    }
    vecEnemies.clear ();

    for (unsigned int i = 0; i < spawnCount; ++i) {
        Enemy * enemy = Enemy::create ();
        enemy->setPosition (rand () % maxDistance + 150, gameLayer->getBoundingBox ().size.height / 2.f);
        gameLayer->addChild (enemy, 10);
        vecEnemies.push_back (enemy);
    }

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

        // ++ITERATIONS
        case Key::KEY_UP_ARROW :
            iterations *= 10;
            if (iterations > 1000)
                iterations = 1000;
            break;

        // --ITERATIONS
        case Key::KEY_DOWN_ARROW:
            iterations /= 10;
            if (iterations == 0)
                iterations = 1;
            break;

        // ++MAXDISTANCE
        case Key::KEY_RIGHT_ARROW:
            maxDistance += 100;
            if (maxDistance > 2000)
                maxDistance = 2000;
            break;

        // --MAXDISTANCE
        case Key::KEY_LEFT_ARROW:
            maxDistance -= 100;
            if (maxDistance < 100)
                maxDistance = 100;
            break;

        // SPAWN / SHUFFLE
        case Key::KEY_S :
            spawnEnemies ();
            break;

        // LEARN
        case Key::KEY_SPACE :
            // learn ();
            break;

        // ATTACK
        case Key::KEY_ENTER :
        case Key::KEY_RETURN :
            // attack ();
            break;

        // FLEE
        case Key::KEY_BACKSPACE :
            // flee ();
            break;
    }

    // NUMBER OF SPAWNS
    if (keyCode >= Key::KEY_1 && keyCode <= Key::KEY_9) {
        spawnCount = (unsigned int)(keyCode) - 76;
    }
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
