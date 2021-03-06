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

// レイヤーの大きさ
#define LAYER_WIDTH 480
#define LAYER_HEIGHT 900

// ビューの大きさ
#define VIEW_WIDTH 480
#define VIEW_HEIGHT 320


//std::string news_text_ext;
//std::string news_uri_ext;
int interest_type;
std::vector<std::string> news_type_name;
std::vector<std::string> news_type_uri;


bool NewsSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    return true;
}

void NewsSprite::onEnter()
{
    Sprite::onEnter();

//    //画像の表示
//    setTexture("card_back.png");
    
    //カードの位置とタグを指定
//    setTag(_posIndex.x + _posIndex.y * 5 + 1);

}

std::string NewsSprite::getFileName(int cardType)
{
    //ファイル名の取得
    std::string filename = "btn057_04.png";
    switch (cardType)
    {
        default: filename = "btn057_04.png"; break;
    }
    
    return filename;
}

void NewsSprite::moveBackToInitPos()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //移動アニメーションの作成
    float posX = NEWS_1_POS_X + NEWS_DISTANCE_X * _posIndex.x;
    float posY = visibleSize.height + NEWS_DISTANCE_Y * _posIndex.y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    
    //アニメーションの実行
    runAction(move);
}

void NewsSprite::moveToTrash()
{
/*
    //移動アニメーションの作成
    float posX = NEWS_1_POS_X + NEWS_DISTANCE_X * 4;
    float posY = NEWS_1_POS_Y - NEWS_DISTANCE_Y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    //アニメーション後に呼び出す関数の作成
    auto func = CallFunc::create([&](){
        this->setTag(TAG_TRUSH_CARD);
    });
    //アクションの直列結合
    auto seq = Sequence::create(move, func, nullptr);
 
    //アニメーションの実行
    runAction(seq);
 */
}

void NewsSprite::moveToInitPos()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //移動アニメーションの作成
    float posX = NEWS_1_POS_X + NEWS_DISTANCE_X * _posIndex.x;
//    float posY = NEWS_1_POS_Y + NEWS_DISTANCE_Y * _posIndex.y;
    float posY = visibleSize.height + NEWS_DISTANCE_Y * _posIndex.y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    
    //カード回転アニメーションの作成
    auto scale1 = ScaleTo::create(MOVING_TIME / 2, 1, 1);
    auto func1 = CallFunc::create([&](){
        //画像の表示
        setPosition(Vec2(visibleSize.width+250, visibleSize.height/2+20));
        
        setTexture(getFileName(_card.type));
        setTag(_card.number);
        
        //テキストの表示
        Size at = getContentSize();
        at.height = at.height/2;
        std::string temp = news_type_name[_card.number];
        if (temp.size() > 0){
            auto number = Label::createWithSystemFont(temp, "Arial", 36);
            //        auto number = Label::createWithSystemFont("testtest", "Arial", 24);
            number->setPosition(Point(at));
            number->setTextColor((Color4B)Color4B::BLACK);
            addChild(number);
        }
    });
    auto scale2 = ScaleTo::create(MOVING_TIME / 4, 2, 2);
    auto seq1 = Sequence::create(scale1, func1, scale2, nullptr);
    
    //アクションの並列結合
    auto spawn = Spawn::create(move, seq1, nullptr);
    
    //アニメーションの実行
    runAction(spawn);
}


Scene* InfoController::scene()
{
    auto scene = Scene::create();
    auto layer = InfoController::create();
    
    scene->addChild(layer);
    
    return scene;
}

void InfoController::initCards()
{
    //ゲームカードのクリア
    _cards.clear();
    
        for (int number = 0; number <= news_type_name.size(); number++)
        {
            //カード情報の作成
            NewsBox card;
            card.number = number;
            card.type = 0;
            
            //カードを追加する
            _cards.push_back(card);
        }
}

NewsBox InfoController::getCard(int index)
{
    auto card = _cards[index];
    
    return card;
}

void InfoController::createCard(BoxPosIndex posIndex)
{
    float posX = NEWS_1_POS_X;
    float posY = CARD_1_POS_Y - CARD_DISTANCE_Y;
    
    //新しいカードを作成する
    auto card = NewsSprite::create();
    card->setNewsBox(getCard(posIndex.y));
    card->setPosition(posX, posY);
    card->setBoxPosIndex(posIndex);
    card->moveToInitPos();
    card->setScale(2, 1.5);
    addChild(card, ZORDER_SHOW_CARD);

}

void InfoController::showInitCards()
{
    for (int tag = 1; tag <= news_type_name.size(); tag++)
    {
        auto card = getChildByTag(tag);
        if (card)
        {
            //カードが残っている場合は、削除する
            card->removeFromParent();
        }
    }
    
    for (int x = 0; x < 1; x++)
    {
        for (int y = 0; y < news_type_name.size(); y++)
        {
            BoxPosIndex posIndex;
            posIndex.x = x;
            posIndex.y = y;
            
            //カードの生成
            createCard(posIndex);
        }
    }
}

bool InfoController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    auto _bg2 = LayerColor::create(Color4B(0x11,0x11,0x11,0x11), winSize.width, winSize.height);
    this->addChild(_bg2);

    initGame();

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
    
    return true;
}

void InfoController::getTargetStatus()
{
    std::string post_command = NativeLauncher::getNWAdress() + "/get_message?type=4";
    std::string recv = Get_data(post_command.c_str());
    Json* json = Json_create(recv.c_str());
    if (json) {
        if (Json_getString(json, "text1", "")) {
            news_type_name.push_back(Json_getString(json, "text1", ""));
        }
        if (Json_getString(json, "text2", "")) {
            news_type_name.push_back(Json_getString(json, "text2", ""));
        }
        if (Json_getString(json, "text3", "")) {
            news_type_name.push_back(Json_getString(json, "text3", ""));
        }
        if (Json_getString(json, "text4", "")) {
            news_type_name.push_back(Json_getString(json, "text4", ""));
        }
        if (Json_getString(json, "text5", "")) {
            news_type_name.push_back(Json_getString(json, "text5", ""));
        }
        if (Json_getString(json, "text6", "")) {
            news_type_name.push_back(Json_getString(json, "text6", ""));
        }
        if (Json_getString(json, "text7", "")) {
            news_type_name.push_back(Json_getString(json, "text7", ""));
        }
        if (Json_getString(json, "text8", "")) {
            news_type_name.push_back(Json_getString(json, "text8", ""));
        }
        if (Json_getString(json, "text9", "")) {
            news_type_name.push_back(Json_getString(json, "text9", ""));
        }
        if (Json_getString(json, "uri1", "")) {
            news_type_uri.push_back(Json_getString(json, "uri1", ""));
        }
        if (Json_getString(json, "uri2", "")) {
            news_type_uri.push_back(Json_getString(json, "uri2", ""));
        }
        if (Json_getString(json, "uri3", "")) {
            news_type_uri.push_back(Json_getString(json, "uri3", ""));
        }
        if (Json_getString(json, "uri4", "")) {
            news_type_uri.push_back(Json_getString(json, "uri4", ""));
        }
        if (Json_getString(json, "uri5", "")) {
            news_type_uri.push_back(Json_getString(json, "uri5", ""));
        }
        if (Json_getString(json, "uri6", "")) {
            news_type_uri.push_back(Json_getString(json, "uri6", ""));
        }
        if (Json_getString(json, "uri7", "")) {
            news_type_uri.push_back(Json_getString(json, "uri7", ""));
        }
        if (Json_getString(json, "uri8", "")) {
            news_type_uri.push_back(Json_getString(json, "uri8", ""));
        }
        if (Json_getString(json, "uri9", "")) {
            news_type_uri.push_back(Json_getString(json, "uri9", ""));
        }
    }

    return;
}
void InfoController::getTargetUri()
{
    std::string post_command = NativeLauncher::getNWAdress() + "/get_message?type=13";
    std::string recv = Get_data(post_command.c_str());
    Json* json = Json_create(recv.c_str());
    if (json) {
        news_type_uri.push_back(Json_getString(json, "uri1", ""));
        news_type_uri.push_back(Json_getString(json, "uri2", ""));
        news_type_uri.push_back(Json_getString(json, "uri3", ""));
        news_type_uri.push_back(Json_getString(json, "uri4", ""));
        news_type_uri.push_back(Json_getString(json, "uri5", ""));
        news_type_uri.push_back(Json_getString(json, "uri6", ""));
        news_type_uri.push_back(Json_getString(json, "uri7", ""));
        news_type_uri.push_back(Json_getString(json, "uri8", ""));
        news_type_uri.push_back(Json_getString(json, "uri9", ""));
    }
    
    return;
}

void InfoController::initGame()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    news_type_name.clear();
    news_type_uri.clear();
    getTargetStatus();
//    getTargetUri();
    if(news_type_name.size() == 0)
    {
        news_type_name =
        {
            "ビジネス＋ITニュース",
            "日経ビジネス",
            "スポーツナビ",
            "日経新聞",
            "読売新聞",
            "毎日新聞",
            "Naverまとめ",
            "住宅情報",
            "yahooニュース"
        };
    }
    if (news_type_uri.size() == 0) {
        news_type_uri =
        {
            "http://www.sbbit.jp/",
            "http://business.nikkeibp.co.jp/?rt=nocnt",
            "http://sports.yahoo.co.jp/",
            "http://mw.nikkei.com/sp/#!/",
            "http://sp.yomiuri.co.jp/",
            "http://sp.mainichi.jp/",
            "http://matome.naver.jp/m/topic/1Hio8",
            "http://www.jyuikulife.com/",
            "http://yahoo.co.jp"
        };
    }

    for (int i = 0; i < news_type_name.size(); i++) {
        showButton1(news_type_name[i], i);
    }

}

void InfoController::postUserInterest(int userType)
{
    std::string post_command = NativeLauncher::getNWAdress() + "/send_message?type=71&userType=" + std::to_string(userType);

    Post(post_command.c_str());

    return;
}

void InfoController::startWebView(int type)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();

    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.85f, visibleSize.height * 0.85f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    
    webView->loadURL(news_type_uri[type]);

    this->addChild(webView, 1);
    postUserInterest(type);
}

NewsSprite* InfoController::getTouchCard(Touch *touch)
{
    for (int tag = 1; tag <= news_type_name.size(); tag++)
    {
        //表示されているカードを取得する
        auto card = (NewsSprite*)getChildByTag(tag);
        if (card &&
            card != _firstCard &&
            card->getBoundingBox().containsPoint(touch->getLocation()))
        {
            //タップされたカードの場合は、そのカードを返す
            return card;
        }
    }
    
    return nullptr;
}

void InfoController::onTapButton1(Ref* sender, Control::EventType controlEvent)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("My Event");
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    startWebView(0);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}
void InfoController::onTapButton2(Ref* sender, Control::EventType controlEvent)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("My Event");
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    startWebView(1);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}
void InfoController::onTapButton3(Ref* sender, Control::EventType controlEvent)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("My Event");
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    startWebView(2);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}
void InfoController::onTapButton4(Ref* sender, Control::EventType controlEvent)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("My Event");
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    startWebView(3);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}
void InfoController::onTapButton5(Ref* sender, Control::EventType controlEvent)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("My Event");
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    startWebView(4);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}
void InfoController::onTapButton6(Ref* sender, Control::EventType controlEvent)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("My Event");
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    startWebView(5);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}
void InfoController::onTapButton7(Ref* sender, Control::EventType controlEvent)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("My Event");
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    startWebView(6);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}
void InfoController::onTapButton8(Ref* sender, Control::EventType controlEvent)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("My Event");
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    startWebView(7);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}
void InfoController::onTapButton9(Ref* sender, Control::EventType controlEvent)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("My Event");
    
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    startWebView(8);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void InfoController::showButton1(std::string wording, int i)
{
    Size winSize = Director::getInstance()->getVisibleSize();
    //ボタンを作成する
    auto button = ControlButton::create(Scale9Sprite::create("btn057_04.png"));
    
    //画像を引き延ばさない設定
    button->setAdjustBackgroundImage(false);
    
    Size a = button->getContentSize();
    
    //ボタンの位置設定
    button->setPosition(winSize.width/2, winSize.height/3 + a.height * 2 * i);
    button->setScaleX(winSize.width / a.width);
    button->setScaleY(2);
    button->setScaleZ(2);
    
    auto _callback = cccontrol_selector(InfoController::onTapButton1);
    switch (i) {
        case 0:
            _callback = cccontrol_selector(InfoController::onTapButton1);
            break;
        case 1:
            _callback = cccontrol_selector(InfoController::onTapButton2);
            break;
        case 2:
            _callback = cccontrol_selector(InfoController::onTapButton3);
            break;
        case 3:
            _callback = cccontrol_selector(InfoController::onTapButton4);
            break;
        case 4:
            _callback = cccontrol_selector(InfoController::onTapButton5);
            break;
        case 5:
            _callback = cccontrol_selector(InfoController::onTapButton6);
            break;
        case 6:
            _callback = cccontrol_selector(InfoController::onTapButton7);
            break;
        case 7:
            _callback = cccontrol_selector(InfoController::onTapButton8);
            break;
        case 8:
            _callback = cccontrol_selector(InfoController::onTapButton9);
            break;
            
    }
    
    //ボタンをタップしたときに呼び出す関数の設定
    button->addTargetWithActionForControlEvents(this,
                                                _callback,
                                                Control::EventType::TOUCH_UP_INSIDE);
    this->addChild(button);

    auto text = Label::createWithSystemFont(wording, "HiraKakuProN-W6", 24);
    text->setPosition(winSize.width/2, winSize.height/3 + a.height * 2 * i);
    text->setColor(ccc3(255, 0, 127));
    this->addChild(text);

    Director::getInstance()->getEventDispatcher()->addCustomEventListener("My Event",[=](cocos2d::EventCustom *event) {
        CCLOG("イベント受け取ったよ > %s",event->getEventName().c_str());
    });
    
}


void InfoController::playEffect()
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/switch1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/switch1.mp3");
//    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("music/blackout_harp1.mp3");
}

bool InfoController::onTouchBegan(Touch *touch, Event *unused_event)
{
    _firstCard = getTouchCard(touch);
    if (_firstCard)
    {
        //場に出ているカードがタップされた場合
        
        //Zオーダーを変更する
        _firstCard->setLocalZOrder(ZORDER_MOVING_CARD);
        return true;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                        HelloWorld::scene(),
                                                                        ccc3(0, 0, 0)));
    return false;
}

void InfoController::onTouchMoved(Touch *touch, Event *unused_event)
{
    printf("onTouchMoved!!");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //スワイプしているカードの位置を変更
    _firstCard->setPosition(_firstCard->getPosition() + touch->getDelta());
    if (_firstCard->getPosition().x < 30 || _firstCard->getPosition().x < (visibleSize.width-30)) {
        _firstCard->moveToTrash();
        //タップしているカードの指定を外す
        _firstCard = nullptr;
    }
}


void InfoController::onTouchEnded(Touch *touch, Event *unused_event)
{
    printf("onTouchEnded!!");
    
    int indetifier = 0;

    //タップしたカードの取得
    indetifier = _firstCard->getNewsBox().number;
    
    
    //新しいカードを配置する
    if ((int)_cards.size() > 0)
    {
        createCard(_firstCard->getBoxPosIndex());
    }

    //カードを捨てる
    _firstCard->moveToTrash();
    
    if ((int)_cards.size() <= 0)
    {
        //カードの山を削除する
        removeChildByTag(TAG_BACK_CARD);
    }

    //タップしているカードの指定を外す
    _firstCard = nullptr;

}

void InfoController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void InfoController::update(float dt)
{
    
}
