//
//  FamiliaScene.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/27.
//
//

#ifndef FamiliaScene_hpp
#define FamiliaScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "HelloWorldScene.h"


class FamiliaController : public cocos2d::Layer
{
protected:
    
    
public:
    static cocos2d::Scene* scene();
    
    //初期化処理を行う
    virtual bool init();
    void initGame();
    
    //create関数作成マクロ
    CREATE_FUNC(FamiliaController);
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};

#endif /* FamiliaScene_hpp */
