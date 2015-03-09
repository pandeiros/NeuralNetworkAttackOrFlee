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
    initLabels ();

    scheduleUpdate ();

    return true;
}

void Program::update (float dt) {
    lblIterations->setString (std::to_string (iterations));
    lblSpawns->setString (std::to_string (spawnCount));

    lblSpawns->setColor (Color3B (255, 255, (9 - spawnCount) * 255 / 8));
}

void Program::initLayers () {
    // >>> GAME LAYER <<<
    gameLayer = cocos2d::LayerColor::create (cocos2d::Color4B (10, 103, 163, 150));
    gameLayer->setPosition (visibleSize.width * 1 / 5.f, visibleSize.height * 2 / 5.f);
    gameLayer->changeHeight (visibleSize.height * 3 / 5);
    gameLayer->changeWidth (visibleSize.width * 4 / 5);
    this->addChild (gameLayer);

    // >>> NETWORK LAYER <<<
    infoLayer = cocos2d::LayerColor::create (cocos2d::Color4B (255, 65, 0, 150));
    infoLayer->setPosition (0, visibleSize.height * 2 / 5.f);
    infoLayer->changeHeight (visibleSize.height * 3 / 5);
    infoLayer->changeWidth (visibleSize.width * 1 / 5);
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

void Program::initLabels () {
    // >>> ITERATIONS <<<
    lblIterations = Label::createWithTTF (std::to_string (iterations), std::string (FONT_PATH), 60);
    lblIterations->setAnchorPoint (Vec2 (0, 0));
    lblIterations->setPosition (20, infoLayer->getBoundingBox ().size.height * 3 / 4 + 20);
    lblIterations->setColor (Color3B (220, 220, 220));
    infoLayer->addChild (lblIterations, 10);

    // >>> SPAWNS <<<
    lblSpawns = Label::createWithTTF (std::to_string (spawnCount), std::string (FONT_PATH), 60);
    lblSpawns->setAnchorPoint (Vec2 (0, 0));
    lblSpawns->setPosition (20, infoLayer->getBoundingBox ().size.height * 2 / 4 + 20);
    lblSpawns->setColor (Color3B (255, 255, (9 - spawnCount) * 255 / 8));
    infoLayer->addChild (lblSpawns, 10);
}

void Program::spawnEnemies () {
    auto vec = gameLayer->getChildren ();
    for (auto & e : vec) {
        if (e != player)
            e->removeFromParent ();
    }

    vecEnemies.clear ();

    for (unsigned int i = 0; i < spawnCount; ++i) {
        Enemy * enemy = Enemy::create ();
        enemy->setPosition (rand () % 700 + 150, gameLayer->getBoundingBox ().size.height / 2.f);
        gameLayer->addChild (enemy, 10);
        vecEnemies.push_back (enemy);
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
        case Key::KEY_KP_PLUS :
        case Key::KEY_PLUS :
            iterations *= 10;
            break;

        // ++ITERATIONS
        case Key::KEY_KP_MINUS:
        case Key::KEY_MINUS:
            iterations /= 10;
            if (iterations == 0)
                iterations = 1;
            break;

        // SPAWN
        case Key::KEY_SPACE :
            spawnEnemies ();
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
