//
//  CookingController.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/28.
//
//

#ifndef CookingController_hpp
#define CookingController_hpp

#include <stdio.h>

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "HelloWorldScene.h"


class CookingController : public cocos2d::Layer
{
protected:
    
    
public:
    static cocos2d::Scene* scene();
    std::vector<std::string> menu_lists;
    
    //初期化処理を行う
    virtual bool init();
    void initGame();
    
    //create関数作成マクロ
    CREATE_FUNC(CookingController);

    
    void showButton1();
    void onTapButton1(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void showButton2();
    void onTapButton2(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton3(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapWebButton(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    
    void startWebView(std::string uri);
    void getTargetStatus(char* result);
    
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};

#endif /* CookingController_hpp */
