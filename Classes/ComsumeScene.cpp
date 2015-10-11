//
//  ComsumeScene.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/10/02.
//
//

#include "ComsumeScene.hpp"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;

std::string com_text_ext;
std::string com_uri_ext;
std::string com_attend_ext;
int com_attend_type;

Scene* ComsumeController::scene()
{
    auto scene = Scene::create();
    auto layer = ComsumeController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool ComsumeController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(ComsumeController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ComsumeController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ComsumeController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(ComsumeController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    com_text_ext.clear();
    com_uri_ext.clear();
    com_attend_ext.clear();
    
    getInfoContent();
    initGame();
    
    return true;
}

void ComsumeController::powerSavingMode(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/send_message?type=54";
    Post(post_command);
    return;
}

void ComsumeController::getInfoContent()
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/get_message?type=10";
    std::string recv = Get_data(post_command);
    Json* json = Json_create(recv.c_str());
    if (json) {
        com_text_ext = Json_getString(json, "text", "");
        com_uri_ext = Json_getString(json, "apn", "");
        com_attend_ext = Json_getString(json, "attention", "");
        com_attend_type = Json_getInt(json, "attend_type", 0);
    }
    
    return;
}

//  文字列を置換する
std::string Replace1( std::string String1, std::string String2, std::string String3 )
{
    std::string::size_type  Pos( String1.find( String2 ) );
    
    while( Pos != std::string::npos )
    {
        String1.replace( Pos, String2.length(), String3 );
        Pos = String1.find( String2, Pos + String3.length() );
    }
    
    return String1;
}

void ComsumeController::initGame()
{
    char message[100];
    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    _doorStatus = 0;
    switch (com_attend_type) {
        case 1:
            _sprite1 = Sprite::create("sts/sentakumono.png");
            break;
        case 2:
            _sprite1 = Sprite::create("sts/jiko_jishin_himoto.png");
            break;
        case 3:
            _sprite1 = Sprite::create("sts/mizumore_toilet.png");
            break;
        case 4:
            _sprite1 = Sprite::create("sts/jiko_mizumore.png");
            break;
            
        default:
            _sprite1 = Sprite::create("sts/sentakumono.png");
            break;
    }
    _sprite1->setScale(2.0f);
    _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
    addChild(_sprite1);

    //Scrollview
    auto *scroll = ScrollView::create(winSize);
    // 縦方向だけにスクロール
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    addChild(scroll);
    
    com_text_ext = Replace1( com_text_ext, ",", "\n" );
    if (com_text_ext.size()==0) {
        com_text_ext = "電力消費量の予測";
    }
    com_text_ext = com_text_ext + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n" + com_attend_ext;
    auto label = LabelTTF::create(com_text_ext, "Arial Rounded MT Bold", 36);
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
    
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

void ComsumeController::playEffect()
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/blackout_harp1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/blackout_harp1.mp3");
    //    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("music/blackout_harp1.mp3");
}

void ComsumeController::showSPrite()
{
    char message[100];
    Size winSize = Director::getInstance()->getVisibleSize();
    powerSavingMode(message);
    
    this->removeChild(_sprite1);
    if(_doorStatus == 0){
        _sprite1 = Sprite::create("normal_door.png");
        _sprite1->setScale(1.0f);
        _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
        _doorStatus = 1;
    }else{
        _sprite1 = Sprite::create("normal_door_close.png");
        _sprite1->setScale(1.0f);
        _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
        _doorStatus = 0;
    }
    addChild(_sprite1);
    
    
    // 別スレッドを生成して引数を渡して実行する
    auto t = std::thread([this] (int n) {
        for (int i = 0; i < 100; i++) {
            mtx.lock();
            log("%d", n + i);
            mtx.unlock();
        }
        
        // 処理が一通り終わったのでメインスレッドに戻してメソッドを呼ぶ
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ComsumeController::dispatchThreadCallbacks, this));
    }, 1000);
    
    // スレッドの管理を手放す
    // スレッドの処理を待つ場合はt.join()かstd::asyncを使う
    t.detach();
}

void ComsumeController::dispatchThreadCallbacks()
{
    // std::lock_guardはunlockをスコープから抜ける時に自動的にやってくれる
    std::lock_guard<std::mutex> lock(mtx);
//    CCDirector::sharedDirector()->replaceScene(TransitionFadeTR::create(6.0f,  HelloWorld::scene()));
    Director::getInstance()->replaceScene(TransitionMoveInB::create(3.0f,HelloWorld::scene()));
}

void ComsumeController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();
    
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL(com_uri_ext);
    this->addChild(webView, 1);
}

bool ComsumeController::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void ComsumeController::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCDirector::sharedDirector()->replaceScene(TransitionFade::create(3.0f,  HelloWorld::scene(), ccc3(0, 0, 0)));
}


void ComsumeController::onTouchEnded(Touch *touch, Event *unused_event)
{
    playEffect();
    
    showSPrite();
    
    return;
}

void ComsumeController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void ComsumeController::update(float dt)
{
    
}
