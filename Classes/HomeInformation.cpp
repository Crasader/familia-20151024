//
//  HomeInformation.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/26.
//
//

#include "HomeInformation.h"


USING_NS_CC;
USING_NS_CC_EXT;

std::string home_text_ext;
std::string home_uri_ext;

Scene* HomeInfoController::createScene()
{
    auto scene = Scene::create();
    auto layer = HomeInfoController::create();
    
    scene->addChild(layer);
    
    return scene;
}

Scene* HomeInfoController::scene()
{
    auto scene = Scene::create();
    auto layer = HomeInfoController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool HomeInfoController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(HomeInfoController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HomeInfoController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HomeInfoController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HomeInfoController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

void HomeInfoController::getMessage(char* result)
{
    const char *post_command;
    
    post_command = "http://127.0.0.1:3000/send_message?type=2";
    
    Get(post_command);
    
    return;
}

//  文字列を置換する
std::string Replace( std::string String1, std::string String2, std::string String3 )
{
    std::string::size_type  Pos( String1.find( String2 ) );
    
    while( Pos != std::string::npos )
    {
        String1.replace( Pos, String2.length(), String3 );
        Pos = String1.find( String2, Pos + String3.length() );
    }
    
    return String1;
}

void HomeInfoController::initGame()
{
    home_text_ext.clear();
    home_uri_ext.clear();
    
//    char message[100];
//    getMessage(message);
    getHomeInfoContent();
    Size winSize = Director::getInstance()->getVisibleSize();
    
    auto _bg2 = LayerColor::create(Color4B(0,255,0,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    //画面サイズを取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //CCSpriteクラスで画像を設定します。
    _sprite1 = Sprite::create("button.png");
    _sprite1->setScale(2.0f);
    _sprite1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(_sprite1);
    
    //Scrollview
    auto *scroll = ScrollView::create(winSize);
    // 縦方向だけにスクロール
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    addChild(scroll);
    
    home_text_ext = Replace( home_text_ext, ",", "\n" );
    auto label = LabelTTF::create(home_text_ext, "Arial Rounded MT Bold", 36);
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

    
/*
    home_text_ext = Replace( home_text_ext, ",", "\n" );
    Label *label = Label::createWithSystemFont(home_text_ext, "Marker Felt.ttf", 30);
    label->setScale(2.0f);
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);
    
    auto move = MoveTo::create(MOVING_TIME, Vec2(visibleSize.width/3, visibleSize.height/3));
    
    //アニメーションの実行
    label->runAction(move);
*/
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

void HomeInfoController::getHomeInfoContent()
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/get_message?type=7";
    std::string recv = Get_data(post_command);
    Json* json = Json_create(recv.c_str());
    if (json) {
        home_text_ext = Json_getString(json, "text", "");
        home_uri_ext = Json_getString(json, "apn", "");
    }
    
    return;
}

void HomeInfoController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto webView = cocos2d::experimental::ui::WebView::create();
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.9f, visibleSize.height * 0.8f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    if (home_uri_ext.size()==0) {
        home_uri_ext = "https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3";
    }
    webView->loadURL(home_uri_ext);
    this->addChild(webView, 1);
    
}

bool HomeInfoController::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void HomeInfoController::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
}


void HomeInfoController::onTouchEnded(Touch *touch, Event *unused_event)
{
    startWebView();
    
    return;
}

void HomeInfoController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void HomeInfoController::update(float dt)
{
    
}
