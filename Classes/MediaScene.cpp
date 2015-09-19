//
//  MediaScene.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/13.
//
//

#include "MediaScene.h"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;


Scene* MediaController::scene()
{
    auto scene = Scene::create();
    auto layer = MediaController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool MediaController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(MediaController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MediaController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MediaController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MediaController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

// １番目画像Runアクションメソッド
void MediaController::Action01(float frame)
{

/*
    // 大きさ（縮小）アクションを適用 1.0秒 0倍
    auto scaleTo1 = ScaleTo::create(1.0f, 0.0f);
    
    //callbackでの消去処理
    auto removeSprite1 = CallFunc::create([this](){
        this->removeChild(Sprite01);
    });
    
    // 縮小、消去アクションを適用
    auto sequence1 = Sequence::create(scaleTo1, removeSprite1, NULL);
    
    // 縮小、消去runアクションを適用
    Sprite01->runAction(sequence1);
*/
    
}

void callback_func(Ref* ref,cocos2d::experimental::ui::VideoPlayer::EventType type)
{

    switch (type) {
        case cocos2d::experimental::ui::VideoPlayer::EventType::PLAYING:

            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::PAUSED:
            
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::STOPPED:
            
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::COMPLETED:
            // １番目１回実行画像Runアクションスケジュール 2秒後
            //上からシーンが移動。
            CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInB::create(2.0f,HelloWorld::scene()));
            break;
            
        default:
            break;
    }
    
}

void MediaController::initGame()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
    
    videoPlayer->setContentSize(visibleSize);
    videoPlayer->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    videoPlayer->setScale(1.0);
    
    videoPlayer->setKeepAspectRatioEnabled(true);
    this->addChild(videoPlayer);
    
    videoPlayer->setFullScreenEnabled(true);
    videoPlayer->addEventListener(&callback_func);
    videoPlayer->setFileName("video.mp4");

    videoPlayer->play();
    
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}


bool MediaController::onTouchBegan(Touch *touch, Event *unused_event)
{

    
    return false;
}

void MediaController::onTouchMoved(Touch *touch, Event *unused_event)
{
    //スワイプしているカードの位置を変更

}


void MediaController::onTouchEnded(Touch *touch, Event *unused_event)
{

    //    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(2.0f, HelloWorld::scene()));
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, MediaController::scene(), ccc3(0, 0, 0)));
    //    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
    
    //下からシーンが移動。
    //    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInB::create(2.0f,HelloWorld::scene()));
    
    //上からシーンが移動。
    //    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInT::create(2.0f,HelloWorld::scene()));
    
}

void MediaController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void MediaController::update(float dt)
{

}
