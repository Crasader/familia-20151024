//
//  SmartCity.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/10/05.
//
//

#include "SmartCity.hpp"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;


std::string city_text_ext;
std::string city_uri_ext;
int city_info_type;


Scene* SmartCityController::scene()
{
    auto scene = Scene::create();
    auto layer = SmartCityController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool SmartCityController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(SmartCityController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SmartCityController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SmartCityController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(SmartCityController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

void SmartCityController::initGame()
{
    city_text_ext.clear();
    city_uri_ext.clear();
    char commnad_name[2];
    getTargetStatus(commnad_name);
    
    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    if(city_text_ext.size()==0){
        city_text_ext = "【博物館】連鶴の原典「素雲鶴」復元事業ブログ【10月4日更新】\nhttp://www.city.kuwana.lg.jp/index.cfm/24,44469,235,414,html\n「平成27年度　緑のカーテン自慢！」を紹介します\nhttp://www.city.kuwana.lg.jp/index.cfm/24,47050,282,626,html";
    }
    
    //Scrollview
    auto *scroll = ScrollView::create(winSize);
    // 縦方向だけにスクロール
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    addChild(scroll);
    
    auto label = LabelTTF::create(city_text_ext, "Arial Rounded MT Bold", 36);
    label->setColor(Color3B::WHITE);

    label->setDimensions(Size(winSize.width,0));
    label->setDimensions
    (Size(label->getContentSize().width, label->getContentSize().height));
    // 左寄せにする
    label->setHorizontalAlignment(TextHAlignment::LEFT);
    
    // スクロールされるラベルの調整
    scroll->setContainer(label);
    scroll->setContentOffset
    (Point(0, 0 - (label->getContentSize().height - winSize.height)));
    
    showButton1();
    showButton2();

    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

void SmartCityController::playEffect()
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/blackout_harp1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/blackout_harp1.mp3");
    //    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("music/blackout_harp1.mp3");
}

void SmartCityController::showSPrite()
{
    char message[100];
    Size winSize = Director::getInstance()->getVisibleSize();
    
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
        scheduler->performFunctionInCocosThread(CC_CALLBACK_0(SmartCityController::dispatchThreadCallbacks, this));
    }, 1000);
    
    // スレッドの管理を手放す
    // スレッドの処理を待つ場合はt.join()かstd::asyncを使う
    t.detach();
}

void SmartCityController::dispatchThreadCallbacks()
{
    // std::lock_guardはunlockをスコープから抜ける時に自動的にやってくれる
    std::lock_guard<std::mutex> lock(mtx);
    CCDirector::sharedDirector()->replaceScene(TransitionFadeBL::create(3.0f,  HelloWorld::scene()));
}

void SmartCityController::showButton1()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    //ボタンを作成する
    auto button = ControlButton::create(Scale9Sprite::create("btn057_04.png"));
    
    //画像を引き延ばさない設定
    button->setAdjustBackgroundImage(false);
    
    Size a = button->getContentSize();
    
    //ボタンの位置設定
    button->setPosition(winSize.width/4, winSize.height/7);
    button->setScaleX(1.5);
    button->setScaleY(2);
    button->setScaleZ(2);
    button->setColor(Color3B(0,0,0));
    
    //ボタンをタップしたときに呼び出す関数の設定
    button->addTargetWithActionForControlEvents(this,
                                                cccontrol_selector(SmartCityController::onTapButton1),
                                                Control::EventType::TOUCH_UP_INSIDE);
    //ボタンに表示する文字
    button->setTitleForState("決定", Control::State::NORMAL);
    
    //画面に追加する
    addChild(button);
}

void SmartCityController::onTapButton1(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    if (city_uri_ext.size()==0) {
        city_uri_ext = "http://www.hotpepper.jp/";
    }
    startWebView(city_uri_ext);
    postUserInterest(city_info_type);
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void SmartCityController::showButton2()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    //ボタンを作成する
    auto button = ControlButton::create(Scale9Sprite::create("btn057_04.png"));
    
    //画像を引き延ばさない設定
    button->setAdjustBackgroundImage(false);
    
    Size a = button->getContentSize();
    
    //ボタンの位置設定
    button->setPosition(winSize.width*3/4, winSize.height/7);
    button->setScaleX(1.5);
    button->setScaleY(2);
    button->setScaleZ(2);
    button->setColor(Color3B(0,0,0));
    
    //ボタンをタップしたときに呼び出す関数の設定
    button->addTargetWithActionForControlEvents(this,
                                                cccontrol_selector(SmartCityController::onTapButton2),
                                                Control::EventType::TOUCH_UP_INSIDE);
    //ボタンに表示する文字
    button->setTitleForState("次の候補へ", Control::State::NORMAL);
    
    //画面に追加する
    addChild(button);
}

void SmartCityController::onTapButton2(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    city_text_ext.clear();
    city_uri_ext.clear();
    char commnad_name[2];
    getTargetStatus(commnad_name);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void SmartCityController::getTargetStatus(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/get_message?type=9";
    std::string recv = Get_data(post_command);
    Json* json = Json_create(recv.c_str());
    if (json) {
        city_text_ext = Json_getString(json, "text", "");
        city_uri_ext = Json_getString(json, "apn", "");
        city_info_type = Json_getInt(json, "interest", 0);
    }
    
    return;
}

void SmartCityController::postUserInterest(int userType)
{
    std::string post_command;
    
    post_command = "http://127.0.0.1:3000/send_message?type=65&userType=" + std::to_string(userType);
    
    Post(post_command.c_str());
    
    return;
}

void SmartCityController::startWebView(std::string uri)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto webView = cocos2d::experimental::ui::WebView::create();
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.9f, visibleSize.height * 0.8f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL(uri);
    this->addChild(webView, 1);
    
}

bool SmartCityController::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void SmartCityController::onTouchMoved(Touch *touch, Event *unused_event)
{
    Director::getInstance()->replaceScene(TransitionCrossFade::create(3.0f,HelloWorld::scene()));
    //    CCDirector::sharedDirector()->replaceScene(TransitionFade::create(3.0f,  HelloWorld::scene(), ccc3(0, 0, 0)));
}


void SmartCityController::onTouchEnded(Touch *touch, Event *unused_event)
{
    playEffect();
    
    showSPrite();
    
    return;
}

void SmartCityController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void SmartCityController::update(float dt)
{
    
}
