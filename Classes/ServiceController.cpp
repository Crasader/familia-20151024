//
//  ServiceController.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/28.
//
//

#include "ServiceController.hpp"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;

std::string service_text_ext;
std::string service_uri_ext;
std::string service_image_ext;
int service_info_type;

Scene* ServiceController::scene()
{
    auto scene = Scene::create();
    auto layer = ServiceController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool ServiceController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(ServiceController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ServiceController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ServiceController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(ServiceController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    menu_lists = {
        ""
    };
    
    
    
    
    initGame();
    
    return true;
}

void ServiceController::initGame()
{
    service_text_ext.clear();
    service_uri_ext.clear();
    service_image_ext.clear();
    getServiceContent();

    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    if(service_text_ext.size()==0){
        service_text_ext = "本日のサービスです\nタイトル：ネコなび<\n著者：杉本ペロ\n出版社：小学館";
    }

    //Scrollview
    auto *scroll = ScrollView::create(winSize);
    // 縦方向だけにスクロール
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    addChild(scroll);
    
    label = LabelTTF::create(service_text_ext, "Arial Rounded MT Bold", 36);
    label->setColor(Color3B::WHITE);
    
    // 文字の開始位置を画面の上に合わせる
    // 文字データは、一番左上から表示させたいので、widthは0
    // heightはコンテンツサイズから画面縦を引いた負数にする
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

void ServiceController::showButton1()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    //ボタンを作成する
    auto button = ControlButton::create(Scale9Sprite::create("btn057_04.png"));
    
    //画像を引き延ばさない設定
    button->setAdjustBackgroundImage(false);
    
    Size a = button->getContentSize();
    
    //ボタンの位置設定
    button->setPosition(winSize.width/4, winSize.height/5);
    button->setScaleX(1.5);
    button->setScaleY(2);
    button->setScaleZ(2);
    button->setColor(Color3B(0,0,0));

    //ボタンをタップしたときに呼び出す関数の設定
    button->addTargetWithActionForControlEvents(this,
                                                cccontrol_selector(ServiceController::onTapButton1),
                                                Control::EventType::TOUCH_UP_INSIDE);
    //ボタンに表示する文字
    button->setTitleForState("決定", Control::State::NORMAL);
    
    //画面に追加する
    addChild(button);
}

void ServiceController::onTapButton1(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    if (service_uri_ext.size()==0) {
        service_uri_ext = "http://hon.jp/search/3.0/null/883546/";
    }
    startWebView(service_uri_ext);
    postUserInterest(service_info_type);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void ServiceController::showButton2()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    //ボタンを作成する
    auto button = ControlButton::create(Scale9Sprite::create("btn057_04.png"));
    
    //画像を引き延ばさない設定
    button->setAdjustBackgroundImage(false);
    
    Size a = button->getContentSize();
    
    //ボタンの位置設定
    button->setPosition(winSize.width*3/4, winSize.height/5);
    button->setScaleX(1.5);
    button->setScaleY(2);
    button->setScaleZ(2);
    button->setColor(Color3B(0,0,0));

    //ボタンをタップしたときに呼び出す関数の設定
    button->addTargetWithActionForControlEvents(this,
                                                cccontrol_selector(ServiceController::onTapButton2),
                                                Control::EventType::TOUCH_UP_INSIDE);
    //ボタンに表示する文字
    button->setTitleForState("次の候補へ", Control::State::NORMAL);
    
    //画面に追加する
    addChild(button);
}

void ServiceController::onTapButton2(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    service_text_ext.clear();
    service_uri_ext.clear();
    service_image_ext.clear();
    getServiceContent();

    label->setString(service_text_ext);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void ServiceController::getServiceContent()
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/get_message?type=6";
    std::string recv = Get_data(post_command);
    Json* json = Json_create(recv.c_str());
    if (json) {
        service_text_ext = Json_getString(json, "text", "");
        service_uri_ext = Json_getString(json, "apn", "");
        service_image_ext = Json_getString(json, "image", "");
        service_info_type = Json_getInt(json, "interest", 0);
    }
    
    return;
}

void ServiceController::postUserInterest(int userType)
{
    std::string post_command;
    
    post_command = "http://127.0.0.1:3000/send_message?type=66&userType=" + std::to_string(userType);
    
    Post(post_command.c_str());
    
    return;
}


void ServiceController::startWebView(std::string uri)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto webView = cocos2d::experimental::ui::WebView::create();
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.9f, visibleSize.height * 0.8f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL(uri);
    this->addChild(webView, 1);
    
}

bool ServiceController::onTouchBegan(Touch *touch, Event *unused_event)
{
    
    NativeLauncher::connectPhamiliaPhone();
    
    return true;
}

void ServiceController::onTouchMoved(Touch *touch, Event *unused_event)
{
    NativeLauncher::disconnectPhamiliaPhone();
    //スワイプしているカードの位置を変更
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
    
}


void ServiceController::onTouchEnded(Touch *touch, Event *unused_event)
{
    
    
    
}

void ServiceController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void ServiceController::update(float dt)
{
    
}
