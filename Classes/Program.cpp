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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
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

    // >>> GAME LAYER <<<
    gameLayer = cocos2d::LayerColor::create (cocos2d::Color4B(10,103,163,150));
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
    networkLayer->setPosition (0,0);
    networkLayer->changeHeight (visibleSize.height * 2 / 5);
    this->addChild (networkLayer);

    // >>> PLAYER <<<
    player = Player::create ();
    player->setPosition (50, gameLayer->getBoundingBox ().size.height / 2.f);
    gameLayer->addChild (player, 15);

    scheduleUpdate ();
    
    return true;
}

void Program::update (float dt) {

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
