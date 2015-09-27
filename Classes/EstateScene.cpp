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
    user_status = REGIST_KENCHIKU_CONSULT;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    auto _bg2 = LayerColor::create(Color4B(0x11,0x11,0x11,0x11), winSize.width, winSize.height);
    this->addChild(_bg2);
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
    
    showModal();

    return true;
}

void EstateController::menuStartCallback(Ref* Sender)
{
    MenuItem* menuItem = (MenuItem*)Sender;
    log("%d",menuItem->getTag());
    switch(menuItem->getTag()){
        case 1:
            initGame(1);
            break;
        case 2:
            initGame(2);
            break;
        case 3:
            initGame(3);
            break;
        case 4:
            initGame(4);
            break;
        case 5:
            initGame(5);
            break;
        case 6:
            initGame(6);
            break;
    }
    dialogClose();
}
void EstateController::dialogClose()
{
    UIDialog* dialog = static_cast<UIDialog*>(getChildByTag(30));
    dialog->close();
}

void EstateController::showModal()
{
    cocos2d::ccMenuCallback action = CC_CALLBACK_1(EstateController::menuStartCallback,this);
    std::vector<UIDialogButton*> buttons = {
        new UIDialogButton("住宅相談",action,1),
        new UIDialogButton("住宅基礎知識について",action,2),
        new UIDialogButton("賃貸住宅D-Room",action,3),
        new UIDialogButton("住宅相談（機能面）",action,4),
        new UIDialogButton("住宅リフォーム（機能面）",action,5),
        new UIDialogButton("住宅リフォーム（金額面）",action,6),
    };
    auto* dialog = UIDialog::create("住宅に関するお知らせです","興味のある案内を選択しましょう", buttons);
    addChild(dialog,31,30);
}

void EstateController::getMessage(char* result)
{
    const char *post_command;
    
    post_command = "http://127.0.0.1:3000/send_message?type=2";
    
    Get(post_command);
    
    return;
}

void EstateController::initGame(int type)
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

    std::string wording;
    switch (type) {
        case 1:
            wording = "住宅相談";
            break;
        case 2:
            wording = "リフォームしたいけど\n何から手をつけたらいいかわからない・・・。\nリフォームに関するおすすめ情報です";
            break;
        case 3:
            wording = "賃貸住宅D-Room";
            break;
        case 4:
            wording = "住宅相談（機能面）";
            break;
        case 5:
            wording = "住宅リフォーム（機能面）";
            break;
        case 6:
            wording = "住宅リフォーム（金額面）";
            break;
            
        default:
            break;
    }
    Label *label = Label::createWithSystemFont(wording, "Marker Felt.ttf", 24);
    
    label->setScale(1.0f);
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);
    
    auto move = MoveTo::create(MOVING_TIME, Vec2(visibleSize.width/2, visibleSize.height/3));
    
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

    if (user_status & REGIST_KENCHIKU_CONSULT){
        // 建築物の商品相談
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/shohin/index.html";
    }else if(user_status & KEEP_CHILD_BUILDING){
        // 子育てしやすい住宅
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=5";
    }else if(user_status & KEEP_2SETAI_BUILDING){
        // 二世帯住宅
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=7";
    }else if(user_status & KEEP_PET_BUILDING){
        // ペットと一緒の暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=6";
    }else if(user_status & KEEP_HIRAYA_BUILDING){
        // 平屋の暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=14";
    }else if(user_status & KEEP_CO_TINTAI_BUILDING){
        // 賃貸併用の暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=8";
    }else if(user_status & KEEP_HOISPITAL_BUILDING){
        //　医院併用の暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=37";
    }else if(user_status & KEEP_1ROOM_RENT_BUILDING){
        //　１部屋賃貸（習い事教室）の暮らし
        uri = "https://www.daiwahouse.co.jp/eventHP/regist.asp?event_id=110790";
    }else if(user_status & KEEP_RENT_MYHOME_BUILDING){
        //　マイホーム借り上げ制度
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=38";
    }else if(user_status & KEEP_SHUNOU_BUILDING){
        // 収納上手な暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=11";
    }else if(user_status & KEEP_LOVELY_KITCHIN_BUILDING){
        // 愛着キッチンのある暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=12";
    }else if(user_status & KEEP_SMART_BUILDING){
        // ダイワハウスのスマートハウス
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=4";
    }else if(user_status & KEEP_TAIYOU_BUILDING){
        // 太陽発電のある暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=1";
    }else if(user_status & KEEP_MOVIE_SOUND_BUILDING){
        // 映画、音楽のある暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=13";
    }else if(user_status & KEEP_WOMAN_BUILDING){
        //　女性のための空間提案
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=16";
    }else if(user_status & KEEP_DESIGNERS_BUILDING){
        //　デザイナーズ住宅
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=24";
    }else if(user_status & KEEP_CESON_BUILDING){
        //　キャトル、セゾンが似合う住宅
        uri = "https://www.daiwahouse.co.jp/eventHP/regist.asp?event_id=102344";
    }else if(user_status & KEEP_GREEN_BUILDING){
        //　緑に囲まれた暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=15";
    }
/*
    // 住まい体験
    uri = "http://www.daiwahouse.co.jp/jutaku/building/experience/index.html";

    
    // リフォーム：基礎知識
    // 住まいの隠れた問題点も発見。
    uri = "http://www.daiwahouse-reform.co.jp/guide/inspection/index.html";
    // リフォームの流れがわかる手順・段取
    uri = "http://www.daiwahouse-reform.co.jp/guide/flow/index.html";
    // 住まいのメンテナンススケジュール
    uri = "http://www.daiwahouse-reform.co.jp/guide/maintenance/index.html";
    // リフォームの「？」がわかるQ&A
    uri = "http://www.daiwahouse-reform.co.jp/guide/qa/index.html";

    // 賃貸相談：：
    uri = "https://www.daiwahouse.co.jp/chintai/";

    // 注文住宅：：土地探し
    uri = "http://www.daiwahouse.co.jp/jutaku/soudan/tochi/index.asp";
    // 間取り相談
    uri = "http://www.daiwahouse.co.jp/jutaku/soudan/madori/index.asp";
    // 建築相談
    uri = "https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3";
    // 帰国前相談
    uri = "http://www.daiwahouse.co.jp/jutaku/soudan/kaigai/index.asp";
    //　相続税軽減に関する相談
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=2";
    //　住まいの各種ほぞ金などの相談
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=3";
    //　住まいずくりに対する全般的な相談
    uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=32";

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
*/
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
