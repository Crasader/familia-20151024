//
//  MotionScene.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/25.
//
//

#ifndef MotionScene_hpp
#define MotionScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "HelloWorldScene.h"


class MotionController : public cocos2d::Layer
{
protected:
    cocos2d::Label* _label1;
    cocos2d::Label* _label2;
    
    
public:
    cocos2d::Sprite* _sprite1;
    
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* scene();
    
    
    //初期化処理を行う
    virtual bool init();
    void initGame();
    static void countUp(int numOfStep);
    static void motionStatus(int confidence,
                                        int stationary,
                                        int walking,
                                        int running,
                                        int automotive,
                                        int unknown);
    void drawString();

    void getMessage(char* result);
    void startWebView();
    void showSPrite();
    void startCallback();

    
    //create関数作成マクロ
    CREATE_FUNC(MotionController);
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};

#endif /* MotionScene_hpp */
