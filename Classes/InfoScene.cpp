//
//  InfoScene.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/16.
//
//

#include "InfoScene.h"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;



Scene* InfoController::scene()
{
    auto scene = Scene::create();
    auto layer = InfoController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool InfoController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(InfoController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(InfoController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(InfoController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(InfoController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    
    return true;
}

void InfoController::getMessage(char* result)
{
    const char *post_command;
    
    post_command = "http://127.0.0.1:3000/send_message?type=2";
    
    Get(post_command);
    
    return;
}

void InfoController::initGame()
{
    char message[100];
    getMessage(message);
//    Size winSize = Director::getInstance()->getVisibleSize();
    
    //auto _bg2 = LayerColor::create(Color4B(0,255,0,128), winSize.width, winSize.height);
    //this->addChild(_bg2);
    //    auto _Gbg = LayerGradient::create(Color4B::GREEN, Color4B::BLUE);
    //    this->addChild(_Gbg);
    auto _Gbg = LayerGradient::create(Color4B::GREEN, Color4B::BLUE);
    _Gbg->setVector(Point(1,0));
    this->addChild(_Gbg);
    
    //画面サイズを取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //テキストの設定　Label::createWithSystemFont("文字列", "フォントの種類", 文字サイズ);
    Label *label = Label::createWithSystemFont("TEST", "Marker Felt.ttf", 30);
    
    //画面の中央に表示
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);
    
    auto move = MoveTo::create(MOVING_TIME, Vec2(visibleSize.width/3, visibleSize.height/3));
    
    //アニメーションの実行
    label->runAction(move);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

void InfoController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();

    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL("http://www.yahoo.co.jp/");
    this->addChild(webView, 1);
}


bool InfoController::onTouchBegan(Touch *touch, Event *unused_event)
{
    
    
    return true;
}

void InfoController::onTouchMoved(Touch *touch, Event *unused_event)
{
    //スワイプしているカードの位置を変更
    
}


void InfoController::onTouchEnded(Touch *touch, Event *unused_event)
{
    //    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(2.0f, HelloWorld::scene()));
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, HelloWorld::scene(), ccc3(0, 0, 0)));
    //    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
    
    //下からシーンが移動。
    //    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInB::create(2.0f,HelloWorld::scene()));
    
    //上からシーンが移動。
    //    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInT::create(2.0f,HelloWorld::scene()));
    
}

void InfoController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void InfoController::update(float dt)
{
    
}
