//
//  ComsumeScene.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/10/02.
//
//

#ifndef ComsumeScene_hpp
#define ComsumeScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "HelloWorldScene.h"


class ComsumeController : public cocos2d::Layer
{
protected:
    
    
public:
    cocos2d::Sprite* _sprite1;
    cocos2d::Sprite* _sprite2;
    
    static cocos2d::Scene* scene();
    
    int _doorStatus;
    std::mutex mtx;
    
    //初期化処理を行う
    virtual bool init();
    void initGame();
    void dispatchThreadCallbacks();
    
    void getMessage(char* result);
    void lockAutoDoor(char* result);
    void unlockAutoDoor(char* result);
    bool getAutoDoorStatus(char* result);
    
    void startWebView();
    void showSPrite();
    void playEffect();
    void powerSavingMode(char* result);
    void getInfoContent();

    //create関数作成マクロ
    CREATE_FUNC(ComsumeController);
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};

#endif /* ComsumeScene_hpp */
