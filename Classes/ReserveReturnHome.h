//
//  ReserveReturnHome.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/22.
//
//

#ifndef ReserveReturnHome_hpp
#define ReserveReturnHome_hpp

#include <stdio.h>
#include <random>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "HelloWorldScene.h"


class ReserveRetunrHomeController : public cocos2d::Layer
{
protected:
    
    
public:
    cocos2d::Sprite* _sprite1;
    cocos2d::Sprite* _sprite2;
    
    static cocos2d::Scene* scene();
    
    std::mutex mtx;
    
    //初期化処理を行う
    virtual bool init();
    void initGame();
    void dispatchThreadCallbacks();
    
    void reserveEquipment(char* result);
    
    void startWebView();
    void showSPrite();
    void playEffect();
    
    //create関数作成マクロ
    CREATE_FUNC(ReserveRetunrHomeController);
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};


#endif /* ReserveReturnHome_hpp */
