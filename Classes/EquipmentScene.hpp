//
//  EquipmentScene.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/10/02.
//
//

#ifndef EquipmentScene_hpp
#define EquipmentScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "HelloWorldScene.h"

class AudioSlider;

class EquipmentController : public cocos2d::Layer
{
protected:
    
    
public:
    cocos2d::Sprite* _sprite1;
    cocos2d::Sprite* _sprite2;
    cocos2d::Sprite* _sprite3;
    cocos2d::Sprite* _sprite4;
    cocos2d::Sprite* _sprite5;
    cocos2d::Sprite* _sprite6;
    AudioSlider *_sliderPitch;
    AudioSlider *_sliderPitch1;
    AudioSlider *_sliderPitch2;

    
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
    
    //create関数作成マクロ
    CREATE_FUNC(EquipmentController);
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    void onTapButton1(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton2(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton3(Ref* sender, cocos2d::extension::Control::EventType controlEvent);

    //毎フレーム呼ばれる関数
    void update(float dt) override;
};

#endif /* EquipmentScene_hpp */
