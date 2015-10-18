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
int initGame_type;
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
        case 7:
            CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
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
            new UIDialogButton("リフォームについて",action,2),
            new UIDialogButton("住宅リフォーム（機能面）",action,5),
            new UIDialogButton("住宅リフォーム（金額面）",action,6),
            new UIDialogButton("ホームに戻る",action,7),
        };
    }else{
        buttons = {
            new UIDialogButton("住宅相談",action,1),
            new UIDialogButton("住宅相談（機能面）",action,4),
            new UIDialogButton("賃貸住宅D-Room",action,3),
            new UIDialogButton("ホームに戻る",action,7),
        };
    }
    auto* dialog = UIDialog::create("暮らしに関するプロに出会えます","", buttons);
    addChild(dialog,31,30);
}

void EstateController::getEstateInfoContent()
{
    const char *post_command;
    post_command = "http://54.199.206.175:3000/get_message?type=8";
    std::string recv = Get_data(post_command);
    Json* json = Json_create(recv.c_str());
    if (json) {
        std::string text_ext = Json_getString(json, "text", "");
        std::string annualincome = Json_getString(json, "annualincome", "");
        std::string leisurecost = Json_getString(json, "leisurecost", "");
        std::string floorspace = Json_getString(json, "floorspace", "");
        std::string buildyear = Json_getString(json, "buildyear", "");
        std::string architect = Json_getString(json, "architect", "");
        std::string roomsnum = Json_getString(json, "roomsnum", "");
        std::string electype = Json_getString(json, "electype", "");
        std::string waterheater = Json_getString(json, "waterheater", "");
        std::string cookingdevice = Json_getString(json, "cookingdevice", "");
        int recommend = Json_getInt(json, "recommend", 0);
    }
    
    return;
}

void EstateController::initGame(int type)
{
    initGame_type = type;
    Size winSize = Director::getInstance()->getVisibleSize();
    getEstateInfoContent();

    auto _bg2 = LayerColor::create(Color4B(0,255,0,128), winSize.width, winSize.height);
    this->addChild(_bg2);

    std::string wording;
    std::vector<std::string> files;
    switch (type) {
        case 1:
            wording = "住宅相談";
            user_status = BUILD_SHOHIN_CONSULT;
            files.push_back("res/iecoram.png");
            files.push_back("res/ad.png");
            showButton1(files);
            break;
        case 2:
            wording = "リフォームに関するプロに出会えるおすすめ情報です";
            user_status = BASIC_REFORM_FLOW;
            files.push_back("res/inspection.png");
            files.push_back("res/mentschedule.png");
            files.push_back("res/refflow.png");
            files.push_back("res/refquestion.png");
            showButton1(files);
            break;
        case 3:
            wording = "賃貸住宅D-Room";
            user_status = RENT_HOUSE;
            files.push_back("res/d-room.png");
            files.push_back("res/d-roomlife.png");
            files.push_back("res/d-room-clum.png");
            showButton1(files);
            break;
        case 4:
            wording = "住宅相談（機能面）";
            user_status = REGIST_KENCHIKU_CONSULT;
            files.push_back("res/childhouse.png");
            files.push_back("res/forwoman.png");
            files.push_back("res/hiraya.png");
            files.push_back("res/hospitakhouse.png");
            files.push_back("res/kitchen.png");
            files.push_back("res/makeplus.png");
            files.push_back("res/parahouse.png");
            files.push_back("res/pethouse.png");
            files.push_back("res/powerfulsolor.png");
            files.push_back("res/proofsound.png");
            files.push_back("res/renthouse.png");
            files.push_back("res/rentmayhome.png");
            files.push_back("res/shunou.png");
            files.push_back("res/smarteco.png");
            files.push_back("res/taiyodiscount.png");
            files.push_back("res/toshinaka.png");
            showButton1(files);
            break;
        case 5:
            wording = "住宅リフォーム（機能面）";
            user_status = KEEP_LIVING_BUILDING;
            files.push_back("res/genkan.png");
            files.push_back("res/kabe.png");
            files.push_back("res/washitu.png");
            files.push_back("res/proof.png");
            files.push_back("res/living.png");
            files.push_back("res/toilet.png");
            files.push_back("res/kitchen-ref.png");
            files.push_back("res/bathroom.png");
            showButton1(files);
            break;
        case 6:
            wording = "住宅リフォーム（金額面）";
            user_status = KEEP_PROCE100_BUILDING;
            files.push_back("res/ref-under100.png");
            files.push_back("res/ref-100-200.png");
            files.push_back("res/ref-over200.png");
            files.push_back("res/ref-300-500.png");
            files.push_back("res/ref-500-1000.png");
            files.push_back("res/ad.png");
            showButton1(files);
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

void EstateController::showButton1(std::vector<std::string> filename)
{
    Size winSize = Director::getInstance()->getVisibleSize();
    int temp_h = 0;
    int i = 0;
    for (std::vector<std::string>::iterator it = filename.begin(); it != filename.end(); ++it) {
        //        cout << *it << '\n';
        //ボタンを作成する
        auto button = ControlButton::create(Scale9Sprite::create(*it));
        //画像を引き延ばさない設定
        button->setAdjustBackgroundImage(false);
        Size a = button->getContentSize();
        //ボタンの位置設定
        button->setPosition(winSize.width/2, winSize.height-temp_h-a.height);
        temp_h += a.height;
        button->setScaleRatio(0.5f);
        //ボタンをタップしたときに呼び出す関数の設定
        switch (i) {
            case 0:
                button->addTargetWithActionForControlEvents(this,
                                                            cccontrol_selector(EstateController::onTapButton1),
                                                            Control::EventType::TOUCH_UP_INSIDE);
                break;
            case 1:
                button->addTargetWithActionForControlEvents(this,
                                                            cccontrol_selector(EstateController::onTapButton2),
                                                            Control::EventType::TOUCH_UP_INSIDE);
                break;
            case 2:
                button->addTargetWithActionForControlEvents(this,
                                                            cccontrol_selector(EstateController::onTapButton3),
                                                            Control::EventType::TOUCH_UP_INSIDE);
                break;
            case 3:
                button->addTargetWithActionForControlEvents(this,
                                                            cccontrol_selector(EstateController::onTapButton4),
                                                            Control::EventType::TOUCH_UP_INSIDE);
                break;
            case 4:
                button->addTargetWithActionForControlEvents(this,
                                                            cccontrol_selector(EstateController::onTapButton5),
                                                            Control::EventType::TOUCH_UP_INSIDE);
                break;
            case 5:
                button->addTargetWithActionForControlEvents(this,
                                                            cccontrol_selector(EstateController::onTapButton6),
                                                            Control::EventType::TOUCH_UP_INSIDE);
                break;
            case 6:
                button->addTargetWithActionForControlEvents(this,
                                                            cccontrol_selector(EstateController::onTapButton7),
                                                            Control::EventType::TOUCH_UP_INSIDE);
                break;
            case 7:
                button->addTargetWithActionForControlEvents(this,
                                                            cccontrol_selector(EstateController::onTapButton8),
                                                            Control::EventType::TOUCH_UP_INSIDE);
                break;
                
            default:
                break;
        }
        i++;
        //ボタンに表示する文字
        button->setTitleForState("", Control::State::NORMAL);
        //画面に追加する
        addChild(button);
    }
}

void EstateController::onTapButton1(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    const char*uri;
    
    switch (initGame_type) {
        case 1:

            break;
        case 2:
            uri = "http://www.daiwahouse-reform.co.jp/guide/inspection/index.html";
            postBuildingInterest(1);
            break;
        case 3:
            // 賃貸相談：：
            uri = "https://www.daiwahouse.co.jp/chintai/";
            break;
        case 4:
            
            break;
        case 5:
            // 玄関
            uri = "http://www.daiwahouse-reform.co.jp/search/part/entrance_pricemap.html";
            postBuildingInterest(5);
            break;
        case 6:
            uri = "http://www.daiwahouse-reform.co.jp/search/price/under100_pricemap.html";
            postBuildingInterest(13);
            break;
            
        default:
            break;
    }
    startWebView(uri);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EstateController::onTapButton2(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    const char*uri;
    switch (initGame_type) {
        case 1:
            
            break;
        case 2:
            uri = "http://www.daiwahouse-reform.co.jp/guide/maintenance/index.html";
            postBuildingInterest(2);
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            // 外観
            uri = "http://www.daiwahouse-reform.co.jp/search/part/outside_pricemap.html";
            postBuildingInterest(6);
            break;
        case 6:
            uri = "http://www.daiwahouse-reform.co.jp/search/price/100-200_pricemap.html";
            postBuildingInterest(14);
            break;
            
        default:
            break;
    }
    startWebView(uri);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EstateController::onTapButton3(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    const char*uri;
    switch (initGame_type) {
        case 1:
            
            break;
        case 2:
            uri = "http://www.daiwahouse-reform.co.jp/guide/flow/index.html";
            postBuildingInterest(3);
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            // 和室
            uri = "http://www.daiwahouse-reform.co.jp/search/part/japanese_pricemap.html";
            postBuildingInterest(7);
            break;
        case 6:
            uri = "http://www.daiwahouse-reform.co.jp/search/price/200-300_pricemap.html";
            postBuildingInterest(15);
            break;
            
        default:
            break;
    }
    startWebView(uri);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EstateController::onTapButton4(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    const char*uri;
    switch (initGame_type) {
        case 1:
            
            break;
        case 2:
            // リフォームの「？」がわかるQ&A
            uri = "http://www.daiwahouse-reform.co.jp/guide/qa/index.html";
            postBuildingInterest(4);
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            // 防音、ホームシアター
            uri = "http://www.daiwahouse-reform.co.jp/search/theme/hometheater_pricemap.html";
            postBuildingInterest(8);
            break;
        case 6:
            uri = "http://www.daiwahouse-reform.co.jp/search/price/index.asp?t_cd=14";
            postBuildingInterest(16);
            break;
            
        default:
            break;
    }
    startWebView(uri);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EstateController::onTapButton5(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    const char*uri;
    switch (initGame_type) {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            // リビング
            uri = "http://www.daiwahouse-reform.co.jp/search/part/living_pricemap.html";
            postBuildingInterest(9);
            break;
        case 6:
            uri = "http://www.daiwahouse-reform.co.jp/search/price/index.asp?t_cd=15";
            postBuildingInterest(17);
            break;
            
        default:
            break;
    }
    startWebView(uri);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EstateController::onTapButton6(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    const char*uri;

    switch (initGame_type) {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            // トイレ
            uri = "http://www.daiwahouse-reform.co.jp/search/part/lavatory_pricemap.html";
            postBuildingInterest(10);
            break;
        case 6:
            uri = "//http://www.daiwahouse.co.jp/jutaku/fair/index.html?page=column";
            postBuildingInterest(18);
            break;
            
        default:
            break;
    }
    
    startWebView(uri);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}
void EstateController::onTapButton7(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    const char*uri;
    switch (initGame_type) {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            // キッチン
            uri = "http://www.daiwahouse-reform.co.jp/search/part/kitchen_pricemap.html";
            postBuildingInterest(11);
            break;
        case 6:
            
            break;
            
        default:
            break;
    }
    
    startWebView(uri);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}
void EstateController::onTapButton8(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    const char*uri;
    switch (initGame_type) {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            // 風呂場
            uri = "http://www.daiwahouse-reform.co.jp/search/part/bath_pricemap.html";
            postBuildingInterest(12);
            break;
        case 6:
            
            break;
            
        default:
            break;
    }
    
    startWebView(uri);
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EstateController::postBuildingInterest(int buldingType)
{
    std::string post_command;
    
    post_command = "http://54.199.206.175:3000/send_message?type=69&building=" + std::to_string(buldingType);
    
    Post(post_command.c_str());
    
    return;
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
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  EstateController::scene(estate_type)));
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


//http://www.daiwahouse.co.jp/column/index.html
    
    
//http://www.daiwahouse.co.jp/jutaku/fair/index.html?page=column

    
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
