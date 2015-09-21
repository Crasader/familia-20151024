//
//  SecurityScene.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/21.
//
//

#include "SecurityScene.h"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;


Scene* SecurityController::createScene()
{
    auto scene = Scene::create();
    auto layer = SecurityController::create();
    
    scene->addChild(layer);
    
    return scene;
}

Scene* SecurityController::scene()
{
    auto scene = Scene::create();
    auto layer = SecurityController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool SecurityController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(SecurityController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SecurityController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SecurityController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(SecurityController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

void SecurityController::getMessage(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/send_message?type=2";
    Get(post_command);
    return;
}

void SecurityController::getAutoDoorStatus(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/send_message?type=19";
    Get(post_command);
    return;
}

void SecurityController::lockAutoDoor(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/send_message?type=21";
    Get(post_command);
    return;
}

void SecurityController::unlockAutoDoor(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/send_message?type=22";
    Get(post_command);
    return;
}

void SecurityController::initGame()
{
    char message[100];
    getAutoDoorStatus(message);
    Size winSize = Director::getInstance()->getVisibleSize();
    
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    _doorStatus = 0;
    if(_doorStatus == 0){
        _sprite1 = Sprite::create("normal_door.png");
        _sprite1->setScale(1.0f);
        _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
    }else{
        _sprite1 = Sprite::create("normal_door_close.png");
        _sprite1->setScale(1.0f);
        _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
    }
    addChild(_sprite1);
    _sprite2 = Sprite::create("house-key.png");
    _sprite2->setScale(1.0f);
    _sprite2->setPosition(Vec2(winSize.width/2-150, winSize.height/2));
    addChild(_sprite2);
    
    Label *label = Label::createWithSystemFont("ドア開閉", "Marker Felt.ttf", 30);
    label->setScale(2.0f);
    label->setPosition(Vec2(winSize.width/2, winSize.height*3/4));
    this->addChild(label);
    
//    platform::NativeBridge::executeNative();
    
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

void SecurityController::showSPrite()
{
    char message[100];
    Size winSize = Director::getInstance()->getVisibleSize();
    if(_doorStatus == 0){
        lockAutoDoor(message);
    }else{
        unlockAutoDoor(message);
    }
    _doorStatus = 1;
    this->removeChild(_sprite1);
    if(_doorStatus == 0){
        _sprite1 = Sprite::create("normal_door.png");
        _sprite1->setScale(1.0f);
        _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));

    }else{
        _sprite1 = Sprite::create("normal_door_close.png");
        _sprite1->setScale(1.0f);
        _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
    }
    addChild(_sprite1);
}


void SecurityController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();
    
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL("https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3");
    this->addChild(webView, 1);
}

bool SecurityController::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void SecurityController::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
}


void SecurityController::onTouchEnded(Touch *touch, Event *unused_event)
{
    showSPrite();
    
    return;
}

void SecurityController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void SecurityController::update(float dt)
{
    
}
