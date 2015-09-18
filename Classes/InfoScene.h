//
//  InfoScene.h
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/16.
//
//

#ifndef __Card13__InfoScene__
#define __Card13__InfoScene__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "ui/UIWebView.h"
#include "HelloWorldScene.h"


class InfoController : public cocos2d::Layer
{
protected:
    
    
public:
    static cocos2d::Scene* scene();
    
    //初期化処理を行う
    virtual bool init();
    void initGame();
    void getMessage(char* result);
    void startWebView();

    //create関数作成マクロ
    CREATE_FUNC(InfoController);
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};


#endif /* defined(__Card13__InfoScene__) */
