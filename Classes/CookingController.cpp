//
//  CookingController.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/28.
//
//

#include "CookingController.hpp"
USING_NS_CC;
USING_NS_CC_EXT;

std::string cooking_text_ext;
std::string cooking_uri_ext;
std::string cooking_image_ext;
int cooking_info_type;


Scene* CookingController::scene()
{
    auto scene = Scene::create();
    auto layer = CookingController::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool CookingController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(CookingController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CookingController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CookingController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(CookingController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    menu_lists = {
        ""
    };
    
    
    
    
    initGame();
    
    return true;
}

void CookingController::initGame()
{
    cooking_text_ext.clear();
    cooking_uri_ext.clear();
    cooking_image_ext.clear();
    char commnad_name[2];
    getTargetStatus(commnad_name);

    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    if(cooking_text_ext.size()==0){
        cooking_text_ext = "本日のオススメのお店です\n店名：塚田農場 立川北口店\nジャンル：居酒屋 郷土料理\nメニュー：地頭鶏　地豚　冷汁　当地野菜\n平均価格：4000円（各種飲み放題付きコース等をご用意しております♪）\nアクセス：JR立川駅から徒歩2分/立川北駅から徒歩1分";
    }
    
    //Scrollview
    auto *scroll = ScrollView::create(winSize);
    // 縦方向だけにスクロール
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    addChild(scroll);
    
    label = LabelTTF::create(cooking_text_ext, "Arial Rounded MT Bold", 36);
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
    auto button2 = ControlButton::create(Scale9Sprite::create("hotpepper-m.png"));
    //画像を引き延ばさない設定
    button2->setAdjustBackgroundImage(false);
    //ボタンの位置設定
    button2->setPosition(winSize.width*4/5-50, button2->getContentSize().height+30);
    button2->setScale(3.0f);
    //ボタンをタップしたときに呼び出す関数の設定
    button2->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(CookingController::onTapButton3),
                                                 Control::EventType::TOUCH_UP_INSIDE);
    addChild(button2);

    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

void CookingController::showButton1()
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
                                                cccontrol_selector(CookingController::onTapButton1),
                                                Control::EventType::TOUCH_UP_INSIDE);
    //ボタンに表示する文字
    button->setTitleForState("決定", Control::State::NORMAL);
    
    //画面に追加する
    addChild(button);
}

void CookingController::onTapButton1(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    if (cooking_uri_ext.size()==0) {
        cooking_uri_ext = "http://www.hotpepper.jp/";
    }
    startWebView(cooking_uri_ext);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void CookingController::onTapButton3(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    if (cooking_uri_ext.size()==0) {
        cooking_uri_ext = "http://www.hotpepper.jp/";
    }
    startWebView(cooking_uri_ext);
    postUserInterest(cooking_info_type);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void CookingController::showButton2()
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
                                                cccontrol_selector(CookingController::onTapButton2),
                                                Control::EventType::TOUCH_UP_INSIDE);
    //ボタンに表示する文字
    button->setTitleForState("次の候補へ", Control::State::NORMAL);
    
    //画面に追加する
    addChild(button);
}

void CookingController::onTapButton2(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    cooking_text_ext.clear();
    cooking_uri_ext.clear();
    cooking_image_ext.clear();
    char commnad_name[2];
    getTargetStatus(commnad_name);

    label->setString(cooking_text_ext);
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void CookingController::getTargetStatus(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/get_message?type=5";
    std::string recv = Get_data(post_command);
    Json* json = Json_create(recv.c_str());
    if (json) {
        cooking_text_ext = Json_getString(json, "text", "");
        cooking_uri_ext = Json_getString(json, "apn", "");
        cooking_image_ext = Json_getString(json, "image", "");
        cooking_info_type = Json_getInt(json, "interest", 0);
    }

    return;
}

void CookingController::postUserInterest(int userType)
{
    std::string post_command;
    
    post_command = "http://127.0.0.1:3000/send_message?type=67&userType=" + std::to_string(userType);
    
    Post(post_command.c_str());
    
    return;
}

void CookingController::onTapWebButton(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    if (cooking_uri_ext.size()==0) {
        cooking_uri_ext = "http://www.hotpepper.jp/";
    }
    startWebView(cooking_uri_ext);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void CookingController::startWebView(std::string uri)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto webView = cocos2d::experimental::ui::WebView::create();
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.9f, visibleSize.height * 0.8f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL(uri);
    this->addChild(webView, 1);
    
}

bool CookingController::onTouchBegan(Touch *touch, Event *unused_event)
{
    
    NativeLauncher::connectPhamiliaPhone();
    
    return true;
}

void CookingController::onTouchMoved(Touch *touch, Event *unused_event)
{
    NativeLauncher::disconnectPhamiliaPhone();
    //スワイプしているカードの位置を変更
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
    
}


void CookingController::onTouchEnded(Touch *touch, Event *unused_event)
{
    
    
    
}

void CookingController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void CookingController::update(float dt)
{
    
}
