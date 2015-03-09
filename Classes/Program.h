#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "cocos2d.h"

class Program : public cocos2d::Scene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Program);
};

#endif // __PROGRAM_H__
