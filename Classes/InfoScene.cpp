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
    
    news_type_name =
    {
        "ソフトバンク　ビジネス＋ITニュース" // http://www.sbbit.jp/
        "日経ビジネス", // http://business.nikkeibp.co.jp/?rt=nocnt
        "スポーツナビ",  // http://sports.yahoo.co.jp/
        "ニュース",
        "書籍情報",
        "ビデオ\nメッセージ",
        "メッセージ",
        "住宅情報",
        "",
        "蓄電情報",
        "消費電力\n情報",
        "設備機器\n稼働情報",
        "お出かけ\nまとめ処理",
        "帰宅予約",
        "玄関ドア\nの開閉"
    };
    
    estate_site_type_name =
    {
        "テンポス", // http://www.temposmart.jp/
        
    };
    
    
    
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
    
    Post(post_command);
    
    return;
}

void InfoController::initGame()
{
    char message[100];
    getMessage(message);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto _bg2 = LayerColor::create(Color4B(0,120,120,120), visibleSize.width, visibleSize.height);
    this->addChild(_bg2);

    Label *label[10];
    
    //テキストの設定　Label::createWithSystemFont("文字列", "フォントの種類", 文字サイズ);
    label[0] = Label::createWithSystemFont("TEST", "Marker Felt.ttf", 30);
    
    //画面の中央に表示
    label[0]->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label[0]);
        
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

void InfoController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();

    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.85f, visibleSize.height * 0.85f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL("http://www.daiwahouse.co.jp/jutaku/visit/vol113/index.html");
    this->addChild(webView, 1);
}


bool InfoController::onTouchBegan(Touch *touch, Event *unused_event)
{
    
    return true;
}

void InfoController::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
}


void InfoController::onTouchEnded(Touch *touch, Event *unused_event)
{
}

void InfoController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void InfoController::update(float dt)
{
    
}
