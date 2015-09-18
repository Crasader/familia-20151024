//
//  EstateScene.h
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/13.
//
//

#ifndef __Card13__EstateScene__
#define __Card13__EstateScene__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "HelloWorldScene.h"


class EstateController : public cocos2d::Layer
{
protected:
    
    
public:
    //HelloWorldクラスのシーンを作成する
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* scene();
    

    //初期化処理を行う
    virtual bool init();
    void initGame();
    void getMessage(char* result);
    
    //create関数作成マクロ
    CREATE_FUNC(EstateController);
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};

#endif /* defined(__Card13__EstateScene__) */
