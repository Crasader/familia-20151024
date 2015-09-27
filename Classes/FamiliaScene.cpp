//
//  FamiliaScene.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/27.
//
//

#include "FamiliaScene.hpp"
USING_NS_CC;
USING_NS_CC_EXT;


Scene* FamiliaController::scene()
{
    auto scene = Scene::create();
    auto layer = FamiliaController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool FamiliaController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(FamiliaController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(FamiliaController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(FamiliaController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(FamiliaController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

// １番目画像Runアクションメソッド
void FamiliaController::Action01(float frame)
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



void FamiliaController::initGame()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
    
    videoPlayer->setContentSize(visibleSize);
    videoPlayer->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    videoPlayer->setScale(1.0);
    
    videoPlayer->setKeepAspectRatioEnabled(true);
    this->addChild(videoPlayer);
    
    videoPlayer->setFullScreenEnabled(true);
    videoPlayer->setFileName("video.mp4");
    
    videoPlayer->play();
    
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}


bool FamiliaController::onTouchBegan(Touch *touch, Event *unused_event)
{
    
    
    return false;
}

void FamiliaController::onTouchMoved(Touch *touch, Event *unused_event)
{
    //スワイプしているカードの位置を変更
    
}


void FamiliaController::onTouchEnded(Touch *touch, Event *unused_event)
{
    

    
}

void FamiliaController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void FamiliaController::update(float dt)
{
    
}
