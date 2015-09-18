//
//  MediaScene.h
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/13.
//
//

#ifndef __Card13__MediaScene__
#define __Card13__MediaScene__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "HelloWorldScene.h"


class MediaController : public cocos2d::Layer
{
protected:

    
public:
    static cocos2d::Scene* scene();
    
    //初期化処理を行う
    virtual bool init();
    void initGame();
    
    //create関数作成マクロ
    CREATE_FUNC(MediaController);
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    virtual void Action01(float frame);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};


#endif /* defined(__Card13__MediaScene__) */
