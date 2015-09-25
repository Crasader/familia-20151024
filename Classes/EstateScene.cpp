//
//  EstateScene.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/13.
//
//

#include "EstateScene.h"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;


Scene* EstateController::createScene()
{
    auto scene = Scene::create();
    auto layer = EstateController::create();
    
    scene->addChild(layer);
    
    return scene;
}

Scene* EstateController::scene()
{
    auto scene = Scene::create();
    auto layer = EstateController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool EstateController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(EstateController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(EstateController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(EstateController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(EstateController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

void EstateController::getMessage(char* result)
{
    const char *post_command;
    
    post_command = "http://127.0.0.1:3000/send_message?type=2";
    
    Get(post_command);
    
    return;
}

void EstateController::initGame()
{
    char message[100];
    getMessage(message);
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
    
    Label *label = Label::createWithSystemFont("TEST", "Marker Felt.ttf", 30);
    
    label->setScale(2.0f);
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);
    
    auto move = MoveTo::create(MOVING_TIME, Vec2(visibleSize.width/3, visibleSize.height/3));
    
    //アニメーションの実行
    label->runAction(move);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}


void EstateController::startWebView(const char* uri)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto webView = cocos2d::experimental::ui::WebView::create();
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.9f, visibleSize.height * 0.8f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL(uri);
    this->addChild(webView, 1);
    
}

bool EstateController::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void EstateController::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
}


void EstateController::onTouchEnded(Touch *touch, Event *unused_event)
{
    const char*uri;

    // 基礎知識
    // 住まいの隠れた問題点も発見。
    uri = "http://www.daiwahouse-reform.co.jp/guide/inspection/index.html";
    // リフォームの流れがわかる手順・段取
    uri = "http://www.daiwahouse-reform.co.jp/guide/flow/index.html";
    // 住まいのメンテナンススケジュール
    uri = "http://www.daiwahouse-reform.co.jp/guide/maintenance/index.html";
    // リフォームの「？」がわかるQ&A
    uri = "http://www.daiwahouse-reform.co.jp/guide/qa/index.html";

    
    
    // 賃貸相談
    uri = "https://www.daiwahouse.co.jp/chintai/";
    // 商品相談
    uri = "";
    // 土地探し
    uri = "http://www.daiwahouse.co.jp/jutaku/soudan/tochi/index.asp";
    // 間取り相談
    uri = "http://www.daiwahouse.co.jp/jutaku/soudan/madori/index.asp";
    // 帰国前相談
    uri = "http://www.daiwahouse.co.jp/jutaku/soudan/kaigai/index.asp";
    
    // 建築相談
    uri = "https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3";
    // 住まい体験
    uri = "http://www.daiwahouse.co.jp/jutaku/building/experience/index.html";

    
    // 子育てしやすい住宅
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=5";
    // 二世帯住宅
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=7";
    // ペットと一緒の暮らし
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=6";
    // 平屋の暮らし
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=14";
    // 賃貸併用の暮らし
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=8";
    //　医院併用の暮らし
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=37";
    //　１部屋賃貸（習い事教室）の暮らし
    uri = "https://www.daiwahouse.co.jp/eventHP/regist.asp?event_id=110790";
    //　マイホーム借り上げ制度
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=38";
    // 収納上手な暮らし
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=11";
    // 愛着キッチンのある暮らし
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=12";
    // ダイワハウスのスマートハウス
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=4";
    // 太陽発電のある暮らし
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=1";
    // 映画、音楽のある暮らし
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=13";
    //　女性のための空間提案
    uri = "";
    //　デザイナーズ住宅
    uri = "";
    //　キャトル、セゾンが似合う住宅
    uri = "";
    //　緑に囲まれた暮らし
    uri = "";
    //　相続税軽減に関する相談
    uri = "";
    //　住まいの各種ほぞ金などの相談
    uri = "";
    //　住まいずくりに対する全般的な相談
    uri = "";

    
    
    // リフォーム
    // 玄関
    uri = "http://www.daiwahouse-reform.co.jp/search/part/entrance_pricemap.html";
    // 外観
    uri = "http://www.daiwahouse-reform.co.jp/search/part/outside_pricemap.html";
    // 屋根
    uri = "http://www.daiwahouse-reform.co.jp/search/part/outside_pricemap.html";
    // 和室
    uri = "http://www.daiwahouse-reform.co.jp/search/part/japanese_pricemap.html";
    // 防音、ホームシアター
    uri = "http://www.daiwahouse-reform.co.jp/search/theme/hometheater_pricemap.html";
    // リビング
    uri = "http://www.daiwahouse-reform.co.jp/search/part/living_pricemap.html";
    // トイレ
    uri = "http://www.daiwahouse-reform.co.jp/search/part/lavatory_pricemap.html";
    // キッチン
    uri = "http://www.daiwahouse-reform.co.jp/search/part/kitchen_pricemap.html";
    //　洗面室
    uri = "http://www.daiwahouse-reform.co.jp/search/part/lavatory_pricemap.html";
    // 風呂場
    uri = "http://www.daiwahouse-reform.co.jp/search/part/bath_pricemap.html";
    
    // リフォーム予算
    // 100万円未満
    uri = "http://www.daiwahouse-reform.co.jp/search/price/under100_pricemap.html";
    // 200万円未満
    uri = "http://www.daiwahouse-reform.co.jp/search/price/100-200_pricemap.html";
    // 200万円から
    uri = "http://www.daiwahouse-reform.co.jp/search/price/200-300_pricemap.html";
    
    

    
    
    
    
    startWebView(uri);
    return;
}

void EstateController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void EstateController::update(float dt)
{
    
}
