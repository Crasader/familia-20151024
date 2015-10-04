//
//  HomeInformation.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/26.
//
//

#ifndef HomeInformation_hpp
#define HomeInformation_hpp

#include <stdio.h>

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "HelloWorldScene.h"


class HomeInfoController : public cocos2d::Layer
{
protected:
    
    
public:
    cocos2d::Sprite* _sprite1;
    
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* scene();
    
    
    //初期化処理を行う
    virtual bool init();
    void initGame();
    void getMessage(char* result);
    void startWebView();
    void showSPrite();
    
    
    void getHomeInfoContent();
    
    
    //create関数作成マクロ
    CREATE_FUNC(HomeInfoController);
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};



#endif /* HomeInformation_hpp */
