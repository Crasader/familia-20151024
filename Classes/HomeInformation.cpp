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
    
    getHomeInfoContent();
    Size winSize = Director::getInstance()->getVisibleSize();
    
    auto _bg2 = LayerColor::create(Color4B(0,255,0,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    //画面サイズを取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //CCSpriteクラスで画像を設定します。
    _sprite1 = Sprite::create("river-932131_640.png");
    _sprite1->setScale(2.0f);
    _sprite1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(_sprite1);
    
    //Scrollview
    auto *scroll = ScrollView::create(winSize);
    // 縦方向だけにスクロール
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    addChild(scroll);
    
    auto label = LabelTTF::create(home_text_ext, "Arial Rounded MT Bold", 36);
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

    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

/*
emotion_status =
{
    "sumairu.png", // スマイル（通常）
    "akuma.png", // 怒り
    "ase.png",  // 汗（緊張）
    "kiran.png", // キラーん（やる気）
    "komaru.png", // 困り（トラブル）
    "naki.png", // 泣き
    "tehehe.png", // てへへ（いたずらしちゃった）
    "tenshi.png", // 天使　（絶好調）
    "tere.png", // てれる
    "yattane.png" // やったね！
};
family_menber =
{
    "mother.png",
    "grandmother.png",
    "boy.png",
    "brother.png",
    "randfather.png"
};
*/

void HomeInfoController::getHomeInfoContent()
{
    const char *post_command;
    post_command = "http://54.199.206.175:3000/get_message?type=7";
    std::string recv = Get_data(post_command);
    Json* json = Json_create(recv.c_str());
    if (json) {
        home_text_ext = Json_getString(json, "text", "");
        home_uri_ext = Json_getString(json, "apn", "");
        
        home_text_ext = Replace( home_text_ext, ",", "\n" );
        home_text_ext = home_text_ext + "\n\n\nご子息は現在" + Json_getString(json, "desc1", "") + "です\n";
        int sts_sprite1 = Json_getInt(json, "sts1", 0);
        switch (sts_sprite1) {
            case 0:
                // "sumairu.png", // スマイル（通常）
                home_text_ext = home_text_ext + "今日はご機嫌のようですね！\n";
                break;
            case 1:
                // "akuma.png", // 怒り
                home_text_ext = home_text_ext + "今日は何か嫌なことがあったようです。\n";
                break;
            case 2:
                // "ase.png",  // 汗（緊張）
                home_text_ext = home_text_ext + "現在、大変緊張しているような状態のようです。\n";
                break;
            case 3:
                // "kiran.png", // キラーん（やる気）
                home_text_ext = home_text_ext + "現在、やる気のようですね！\n";
                break;
            case 4:
                // "komaru.png", // 困り（トラブル）
                home_text_ext = home_text_ext + "今、何か困っているようです！\n";
                break;
            case 5:
                // "naki.png", // 泣き
                home_text_ext = home_text_ext + "今、泣いているようです。そっとしておいてあげましょう。\n";
                break;
            case 6:
                // "tehehe.png", // てへへ（いたずらしちゃった）
                home_text_ext = home_text_ext + "何か、いたずらをしてしまったようですね。\n";
                break;
            case 7:
                // "tehehe.png", // 天使　（絶好調）
                home_text_ext = home_text_ext + "今日は調子がいいようですね！\n";
                break;
            case 8:
                // "tehehe.png", // てれる
                home_text_ext = home_text_ext + "今日は何かいいことあったようですね\n";
                break;
            case 9:
                // "tehehe.png", // やったね！
                home_text_ext = home_text_ext + "大成功のようです！\n";
                break;
            default:
                break;
        }
        int emo_sprite1 = Json_getInt(json, "emo1", 0);

        
        home_text_ext = home_text_ext + "\n\n\n祖母は現在" + Json_getString(json, "desc2", "") + "です\n";
        int sts_sprite2 = Json_getInt(json, "sts2", 0);
        switch (sts_sprite2) {
            case 0:
                // "sumairu.png", // スマイル（通常）
                home_text_ext = home_text_ext + "今日はご機嫌のようですね！\n";
                break;
            case 1:
                // "akuma.png", // 怒り
                home_text_ext = home_text_ext + "今日は何か嫌なことがあったようです\n";
                break;
            case 2:
                // "ase.png",  // 汗（緊張）
                home_text_ext = home_text_ext + "現在、大変緊張しているような状態のようです\n";
                break;
            case 3:
                // "kiran.png", // キラーん（やる気）
                home_text_ext = home_text_ext + "現在、やる気のようですね！\n";
                break;
            case 4:
                // "komaru.png", // 困り（トラブル）
                home_text_ext = home_text_ext + "今、何か困っているようです！電話してあげましょう！\n";
                break;
            case 5:
                // "naki.png", // 泣き
                home_text_ext = home_text_ext + "今、泣いているようです。さりげなく話を聞いてあげましょう。\n";
                break;
            case 6:
                // "tehehe.png", // てへへ（いたずらしちゃった）
                home_text_ext = home_text_ext + "何か、いたずらをしてしまったようですね。たいしたことなければいいのですが。\n";
                break;
            case 7:
                // "tehehe.png", // 天使　（絶好調）
                home_text_ext = home_text_ext + "今日は調子がいいようですね！\n";
                break;
            case 8:
                // "tehehe.png", // てれる
                home_text_ext = home_text_ext + "今日は何かいいことあったようですね\n";
                break;
            case 9:
                // "tehehe.png", // やったね！
                home_text_ext = home_text_ext + "大成功のようです！\n";
                break;
            default:
                break;
        }
        int emo_sprite2 = Json_getInt(json, "emo2", 0);

    }else{
        home_text_ext = "\n\nHEMSサービス利用停止中です。\nしばらくお待ちください。";
    }
    
    return;
}

void HomeInfoController::postUserInterest(int userType)
{
    std::string post_command;
    
    post_command = "http://54.199.206.175:3000/send_message?type=71&userType=" + std::to_string(userType);
    
    Post(post_command.c_str());
    
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
        home_uri_ext = "http://www.ienecons.jp/";
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
