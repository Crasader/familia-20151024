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

void FamiliaController::initGame()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //update関数の呼び出しを開始
    scheduleUpdate();
    
}


bool FamiliaController::onTouchBegan(Touch *touch, Event *unused_event)
{
    
    
    return true;
}

void FamiliaController::onTouchMoved(Touch *touch, Event *unused_event)
{
    //スワイプしているカードの位置を変更
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
    
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
