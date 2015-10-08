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

int estate_type;
Scene* EstateController::scene(int type)
{
    auto scene = Scene::create();
    auto layer = EstateController::create();
    
    scene->addChild(layer);
    estate_type = type;
    
    return scene;
}

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
    std::vector<UIDialogButton*> buttons;
    if (estate_type < 10) {
        buttons = {
            new UIDialogButton("住宅基礎知識について",action,2),
            new UIDialogButton("住宅リフォーム（機能面）",action,5),
            new UIDialogButton("住宅リフォーム（金額面）",action,6),
        };
    }else{
        buttons = {
            new UIDialogButton("住宅相談",action,1),
            new UIDialogButton("住宅相談（機能面）",action,4),
            new UIDialogButton("賃貸住宅D-Room",action,3),
        };
    }
    auto* dialog = UIDialog::create("住宅に関するプロに出会えます","", buttons);
    addChild(dialog,31,30);
}

void EstateController::getEstateInfoContent()
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/get_message?type=8";
    std::string recv = Get_data(post_command);
    Json* json = Json_create(recv.c_str());
    if (json) {
        std::string text_ext = Json_getString(json, "text", "");
        std::string uri_ext = Json_getString(json, "apn", "");
        std::string latitude = Json_getString(json, "latitude", "");
        std::string longitude = Json_getString(json, "longitude", "");
        std::string annualincome = Json_getString(json, "annualincome", "");
        std::string leisurecost = Json_getString(json, "leisurecost", "");
    }
    
    return;
}

void EstateController::initGame(int type)
{
    Size winSize = Director::getInstance()->getVisibleSize();
    getEstateInfoContent();

    auto _bg2 = LayerColor::create(Color4B(0,255,0,128), winSize.width, winSize.height);
    this->addChild(_bg2);

    _sprite1 = Sprite::create("sts/room_unit_bath.png");
    _sprite1->setScale(3.0f);
    _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
    addChild(_sprite1);
/*
    //CCSpriteクラスで画像を設定します。
    _sprite1 = Sprite::create("button.png");
    _sprite1->setScale(2.0f);
    _sprite1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(_sprite1);
*/
    std::string wording;
    switch (type) {
        case 1:
            wording = "住宅相談";
            user_status = BUILD_SHOHIN_CONSULT;
            break;
        case 2:
            wording = "リフォームしたいけど\n何から手をつけたらいいかわからない・・・。\nリフォームに関するおすすめ情報です";
            user_status = BASIC_REFORM_FLOW;
            break;
        case 3:
            wording = "賃貸住宅D-Room";
            user_status = RENT_HOUSE;
            break;
        case 4:
            wording = "住宅相談（機能面）";
            user_status = REGIST_KENCHIKU_CONSULT;
            break;
        case 5:
            wording = "住宅リフォーム（機能面）";
            user_status = KEEP_LIVING_BUILDING;
            break;
        case 6:
            wording = "住宅リフォーム（金額面）";
            user_status = KEEP_PROCE100_BUILDING;
            break;
        default:
            break;
    }

    //Scrollview
    auto *scroll = ScrollView::create(winSize);
    // 縦方向だけにスクロール
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    addChild(scroll);

    auto labelcont = LabelTTF::create(wording, "Arial Rounded MT Bold", 36);
    labelcont->setColor(Color3B::WHITE);
    labelcont->setDimensions(Size(winSize.width,0));
    labelcont->setDimensions(Size(labelcont->getContentSize().width, labelcont->getContentSize().height));
    labelcont->setHorizontalAlignment(TextHAlignment::LEFT);

    // スクロールされるラベルの調整
    scroll->setContainer(labelcont);
    scroll->setContentOffset(Point(0, 0 - (labelcont->getContentSize().height - winSize.height)));
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

    if (user_status == REGIST_KENCHIKU_CONSULT){
        // 建築物の商品相談
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/shohin/index.html";
    }else if(user_status == KEEP_CHILD_BUILDING){
        // 子育てしやすい住宅
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=5";
    }else if(user_status == KEEP_2SETAI_BUILDING){
        // 二世帯住宅
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=7";
    }else if(user_status == KEEP_PET_BUILDING){
        // ペットと一緒の暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=6";
    }else if(user_status == KEEP_HIRAYA_BUILDING){
        // 平屋の暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=14";
    }else if(user_status == KEEP_CO_TINTAI_BUILDING){
        // 賃貸併用の暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=8";
    }else if(user_status == KEEP_HOISPITAL_BUILDING){
        //　医院併用の暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=37";
    }else if(user_status == KEEP_1ROOM_RENT_BUILDING){
        //　１部屋賃貸（習い事教室）の暮らし
        uri = "https://www.daiwahouse.co.jp/eventHP/regist.asp?event_id=110790";
    }else if(user_status == KEEP_RENT_MYHOME_BUILDING){
        //　マイホーム借り上げ制度
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=38";
    }else if(user_status == KEEP_SHUNOU_BUILDING){
        // 収納上手な暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=11";
    }else if(user_status == KEEP_LOVELY_KITCHIN_BUILDING){
        // 愛着キッチンのある暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=12";
    }else if(user_status == KEEP_SMART_BUILDING){
        // ダイワハウスのスマートハウス
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=4";
    }else if(user_status == KEEP_TAIYOU_BUILDING){
        // 太陽発電のある暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=1";
    }else if(user_status == KEEP_MOVIE_SOUND_BUILDING){
        // 映画、音楽のある暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=13";
    }else if(user_status == KEEP_WOMAN_BUILDING){
        //　女性のための空間提案
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=16";
    }else if(user_status == KEEP_DESIGNERS_BUILDING){
        //　デザイナーズ住宅
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=24";
    }else if(user_status == KEEP_CESON_BUILDING){
        //　キャトル、セゾンが似合う住宅
        uri = "https://www.daiwahouse.co.jp/eventHP/regist.asp?event_id=102344";
    }else if(user_status == KEEP_GREEN_BUILDING){
        //　緑に囲まれた暮らし
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=15";
    }

    if(user_status == EXPERIENCE_BUILDING){
        // 住まい体験
        uri = "http://www.daiwahouse.co.jp/jutaku/building/experience/index.html";
    }

    
    // リフォーム：基礎知識
    if(user_status == BASIC_REFORM_INSPECT){
        // 住まいの隠れた問題点も発見。
        uri = "http://www.daiwahouse-reform.co.jp/guide/inspection/index.html";
    }else if(user_status == BASIC_REFORM_FLOW){
        // リフォームの流れがわかる手順・段取
        uri = "http://www.daiwahouse-reform.co.jp/guide/flow/index.html";
    }else if(user_status == BASIC_REFORM_MAINTENANCE){
        // 住まいのメンテナンススケジュール
        uri = "http://www.daiwahouse-reform.co.jp/guide/maintenance/index.html";
    }else if(user_status == BASIC_REFORM_QA){
        // リフォームの「？」がわかるQ&A
        uri = "http://www.daiwahouse-reform.co.jp/guide/qa/index.html";
    }
        
    if(user_status == RENT_HOUSE){
        // 賃貸相談：：
        uri = "https://www.daiwahouse.co.jp/chintai/";
    }
    
    if(user_status == SEARCH_ESTATE_CONSULT){
        // 注文住宅：：土地探し
        uri = "http://www.daiwahouse.co.jp/jutaku/soudan/tochi/index.asp";
    }else if(user_status == MADORI_CONSULT){
        // 間取り相談
        uri = "http://www.daiwahouse.co.jp/jutaku/soudan/madori/index.asp";
    }else if(user_status == BUILD_SHOHIN_CONSULT){
        // 建築相談
        uri = "https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3";
    }else if(user_status == KAIGAI_MOVE_CONSULT){
        // 帰国前相談
        uri = "http://www.daiwahouse.co.jp/jutaku/soudan/kaigai/index.asp";
    }else if(user_status == KEEP_TAX_BUILDING){
        //　相続税軽減に関する相談
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=2";
    }else if(user_status == KEEP_OTHERMONEY_BUILDING){
        //　住まいの各種ほぞ金などの相談
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=3";
    }else if(user_status == KEEP_OVERALL_BUILDING){
        //　住まいずくりに対する全般的な相談
        uri = "https://www.daiwahouse.co.jp/jutaku/soudan/qa/regist.asp?type=32";
    }

    // リフォーム
    if(user_status == KEEP_ENTRANCE_BUILDING){
        // 玄関
        uri = "http://www.daiwahouse-reform.co.jp/search/part/entrance_pricemap.html";
    }else if(user_status == KEEP_OUTSIDE_BUILDING){
        // 外観
        uri = "http://www.daiwahouse-reform.co.jp/search/part/outside_pricemap.html";
    }else if(user_status == KEEP_UPPER_OUTSIDE_BUILDING){
        // 屋根
        uri = "http://www.daiwahouse-reform.co.jp/search/part/outside_pricemap.html";
    }else if(user_status == KEEP_JAPANESE_BUILDING){
        // 和室
        uri = "http://www.daiwahouse-reform.co.jp/search/part/japanese_pricemap.html";
    }else if(user_status == KEEP_HOMETHEATER_BUILDING){
        // 防音、ホームシアター
        uri = "http://www.daiwahouse-reform.co.jp/search/theme/hometheater_pricemap.html";
    }else if(user_status == KEEP_LIVING_BUILDING){
        // リビング
        uri = "http://www.daiwahouse-reform.co.jp/search/part/living_pricemap.html";
    }else if(user_status == KEEP_TOILET_BUILDING){
        // トイレ
        uri = "http://www.daiwahouse-reform.co.jp/search/part/lavatory_pricemap.html";
    }else if(user_status == KEEP_KITCHEN_BUILDING){
        // キッチン
        uri = "http://www.daiwahouse-reform.co.jp/search/part/kitchen_pricemap.html";
    }else if(user_status == KEEP_LAVATORY_BUILDING){
        //　洗面室
        uri = "http://www.daiwahouse-reform.co.jp/search/part/lavatory_pricemap.html";
    }else if(user_status == KEEP_BATH_BUILDING){
        // 風呂場
        uri = "http://www.daiwahouse-reform.co.jp/search/part/bath_pricemap.html";
    }

    // リフォーム予算
    if(user_status == KEEP_PROCE100_BUILDING){
        // 100万円未満
        uri = "http://www.daiwahouse-reform.co.jp/search/price/under100_pricemap.html";
    }else if(user_status == KEEP_PRICE200_BUILDING){
        // 200万円未満
        uri = "http://www.daiwahouse-reform.co.jp/search/price/100-200_pricemap.html";
    }else  if(user_status == KEEP_PRICE_OVER200_BUILDING){
        // 200万円から
        uri = "http://www.daiwahouse-reform.co.jp/search/price/200-300_pricemap.html";
    }

    
    
    // カラーコーディネート
    // btn_to01.gif
    // http://www.daiwahouse.co.jp/column/lifestyle/coordinate/part02.html

    
    // メルマガ登録
    // https://letter.daiwahouse.co.jp/form/31307-1070/


    
    
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
