//
//  ReserveReturnHome.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/22.
//
//

#include "ReserveReturnHome.h"

USING_NS_CC;
USING_NS_CC_EXT;


Scene* ReserveRetunrHomeController::scene()
{
    auto scene = Scene::create();
    auto layer = ReserveRetunrHomeController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool ReserveRetunrHomeController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(ReserveRetunrHomeController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ReserveRetunrHomeController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ReserveRetunrHomeController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(ReserveRetunrHomeController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

void ReserveRetunrHomeController::reserveEquipment(char* result)
{
    std::string post_command = NativeLauncher::getNWAdress() + "/send_message?type=50";
    Post(post_command.c_str());

    return;
}

void ReserveRetunrHomeController::initGame()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    std::vector<std::string>filename = {
        "river-932131_640.png",
        "city-918523_640.png",
        "avenue-957201_640.png"
    };
    std::random_device device;
    
    std::mt19937 mt(device());
    std::default_random_engine _engine = std::default_random_engine(mt());
    
    //取り出す値を設定(int型)
    std::discrete_distribution<int>  distForNumbers = std::discrete_distribution<int>{0,1,2};
    //実際に利用
    int index = distForNumbers(_engine);
    
    
    if(_reserveReturne){
        Label *label = Label::createWithSystemFont("帰宅予約の案内中", "Marker Felt.ttf", 24);
        label->setScale(2.0f);
        label->setPosition(Vec2(winSize.width/2, winSize.height*3/4));
        this->addChild(label);

        Label *label1 = Label::createWithSystemFont("ご自宅までの残り時間と残り距離", "Marker Felt.ttf", 18);
        label1->setScale(2.0f);
        label1->setPosition(Vec2(winSize.width/2, winSize.height/2));
        this->addChild(label1);
        
        NativeLauncher::getNewLocation_latitude();
        NativeLauncher::getNewLocation_longitude();
        NativeLauncher::getNewLocation_speed();
        NativeLauncher::getNewLocation_course();

        NativeLauncher::getDestance();

        std::string temo = std::to_string(round(NativeLauncher::getDestance()/1000)) + "km\n残り" + std::to_string(round((NativeLauncher::getDestance()/NativeLauncher::getNewLocation_speed())/60)) + "分";
        Label *label3 = Label::createWithSystemFont(temo, "Marker Felt.ttf", 18);
        label3->setScale(2.0f);
        label3->setPosition(Vec2(winSize.width/2, winSize.height/2-70));
        this->addChild(label3);
        
    }else{
        _sprite1 = Sprite::create(filename[index]);
        _sprite1->setScale(1.0f);
        _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
        addChild(_sprite1);

        Label *label = Label::createWithSystemFont("帰宅予約を案内できます", "Marker Felt.ttf", 24);
        label->setScale(2.0f);
        label->setPosition(Vec2(winSize.width/2, winSize.height*3/4));
        this->addChild(label);
    }
    
    
    
    
    //    platform::NativeBridge::executeNative();
    
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

void ReserveRetunrHomeController::showSPrite()
{
    char message[100];

    NativeLauncher::launchLocationController(0);
    
    reserveEquipment(message);
    
    // 別スレッドを生成して引数を渡して実行する
    auto t = std::thread([this] (int n) {
        for (int i = 0; i < 100; i++) {
            mtx.lock();
            log("%d", n + i);
            mtx.unlock();
        }
        
        // 処理が一通り終わったのでメインスレッドに戻してメソッドを呼ぶ
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ReserveRetunrHomeController::dispatchThreadCallbacks, this));
    }, 1000);
    
    // スレッドの管理を手放す
    // スレッドの処理を待つ場合はt.join()かstd::asyncを使う
    t.detach();
}

void ReserveRetunrHomeController::dispatchThreadCallbacks()
{
    // std::lock_guardはunlockをスコープから抜ける時に自動的にやってくれる
    std::lock_guard<std::mutex> lock(mtx);
    CCDirector::sharedDirector()->replaceScene(TransitionFadeTR::create(3.0f,  HelloWorld::scene()));
}

void ReserveRetunrHomeController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();
    
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL("https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3");
    this->addChild(webView, 1);
}

void ReserveRetunrHomeController::playEffect()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/pager.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pager.mp3");
    //    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("music/blackout_harp1.mp3");
}

bool ReserveRetunrHomeController::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void ReserveRetunrHomeController::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
}


void ReserveRetunrHomeController::onTouchEnded(Touch *touch, Event *unused_event)
{
    showSPrite();
    _reserveReturne = true;
    playEffect();
    return;
}

void ReserveRetunrHomeController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void ReserveRetunrHomeController::update(float dt)
{
    
    std::string post_command;
    if(_reserveReturne){
        float remain = (NativeLauncher::getDestance())/(NativeLauncher::getNewLocation_speed());
        if(remain > 0)
        {
            if(remain < 300){
                // AirConditionaeer・５分前にエアコンスイッチ
                post_command = NativeLauncher::getNWAdress() + "/send_message?type=2";
                Post(post_command.c_str());
            }
    
            if(remain < 60){
                // LED・１分前にLEDスイッチ
                post_command = NativeLauncher::getNWAdress() + "/send_message?type=16";
                Post(post_command.c_str());
            }

            if(remain < 30){
                //
                post_command = NativeLauncher::getNWAdress() + "/send_message?type=22";
                Post(post_command.c_str());
                _reserveReturne = false;
            }

            if(remain < 15){
                // ・目の間に着いたら、電動シャッター窓開放 : 輝度センサーで判断
                post_command = NativeLauncher::getNWAdress() + "/send_message?type=27";
                Post(post_command.c_str());
                post_command = NativeLauncher::getNWAdress() + "/send_message?type=31";
                Post(post_command.c_str());
            }
        }
    
    }
    
    
    std::string temo = std::to_string(NativeLauncher::getDestance()/1000) + "km 残り" + std::to_string((NativeLauncher::getDestance()/NativeLauncher::getNewLocation_speed())/60) + "分";
    
    
}
