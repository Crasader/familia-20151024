//
//  EquipmentScene.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/10/02.
//
//

#include "EquipmentScene.hpp"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;


Scene* EquipmentController::scene()
{
    auto scene = Scene::create();
    auto layer = EquipmentController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool EquipmentController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(EquipmentController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(EquipmentController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(EquipmentController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(EquipmentController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

void EquipmentController::powerSavingMode(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/api/send_message?type=53";
    Post(post_command);
    return;
}

void EquipmentController::initGame()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);

    
//    extern NSString* const kLocalDeviceIdMainBoard;
//    extern NSString* const kLocalDeviceIdSolarBoard;
//    extern NSString* const kLocalDeviceIdEneBoard;
//    extern NSString* const kLocalDeviceIdBattery;
//    extern NSString* const kLocalDeviceIdSwitch;
//    extern NSString* const kLocalDeviceIdAircon;
//    extern NSString* const kLocalDeviceIdLed;
//    extern NSString* const kLocalDeviceIdSmartMeter;
//    extern NSString* const kLocalDeviceIdWaterHeater;
//    extern NSString* const kLocalDeviceIdEV;
    
    
    _doorStatus = 0;
    _sprite1 = Sprite::create("sts/room_unit_bath.png");
    _sprite1->setScale(3.0f);
    _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
    addChild(_sprite1);

    Label *label = Label::createWithSystemFont("設備機器の状態制御", "Marker Felt.ttf", 30);
    label->setScale(2.0f);
    label->setPosition(Vec2(winSize.width/2, winSize.height*3/4));
    this->addChild(label);
    
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EquipmentController::playEffect()
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/blackout_harp1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/blackout_harp1.mp3");
    //    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("music/blackout_harp1.mp3");
}

void EquipmentController::showSPrite()
{
    char message[100];
    Size winSize = Director::getInstance()->getVisibleSize();
    powerSavingMode(message);
    
    this->removeChild(_sprite1);
    if(_doorStatus == 0){
        _sprite1 = Sprite::create("normal_door.png");
        _sprite1->setScale(1.0f);
        _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
        _doorStatus = 1;
    }else{
        _sprite1 = Sprite::create("normal_door_close.png");
        _sprite1->setScale(1.0f);
        _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
        _doorStatus = 0;
    }
    addChild(_sprite1);
    
    
    // 別スレッドを生成して引数を渡して実行する
    auto t = std::thread([this] (int n) {
        for (int i = 0; i < 100; i++) {
            mtx.lock();
            log("%d", n + i);
            mtx.unlock();
        }
        
        // 処理が一通り終わったのでメインスレッドに戻してメソッドを呼ぶ
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->performFunctionInCocosThread(CC_CALLBACK_0(EquipmentController::dispatchThreadCallbacks, this));
    }, 1000);
    
    // スレッドの管理を手放す
    // スレッドの処理を待つ場合はt.join()かstd::asyncを使う
    t.detach();
}

void EquipmentController::dispatchThreadCallbacks()
{
    // std::lock_guardはunlockをスコープから抜ける時に自動的にやってくれる
    std::lock_guard<std::mutex> lock(mtx);
//    CCDirector::sharedDirector()->replaceScene(TransitionFadeTR::create(6.0f,  HelloWorld::scene()));
    Director::getInstance()->replaceScene(TransitionMoveInT::create(3.0f,HelloWorld::scene()));
}

void EquipmentController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();
    
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL("https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3");
    this->addChild(webView, 1);
}

bool EquipmentController::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void EquipmentController::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCDirector::sharedDirector()->replaceScene(TransitionFade::create(3.0f,  HelloWorld::scene(), ccc3(0, 0, 0)));
}


void EquipmentController::onTouchEnded(Touch *touch, Event *unused_event)
{
    playEffect();
    
    showSPrite();
    
    return;
}

void EquipmentController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void EquipmentController::update(float dt)
{
    
}
