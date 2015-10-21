//
//  OutgoingHome.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/22.
//
//

#include "OutgoingHome.h"

USING_NS_CC;
USING_NS_CC_EXT;


Scene* OutgoingController::scene()
{
    auto scene = Scene::create();
    auto layer = OutgoingController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool OutgoingController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(OutgoingController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(OutgoingController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(OutgoingController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(OutgoingController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

void OutgoingController::lockAllEquipment(char* result)
{
    std::string post_command;

    post_command = NativeLauncher::getNWAdress() + "/send_message?type=51";
    Post(post_command.c_str());

    post_command = NativeLauncher::getNWAdress() + "/send_message?type=3";
    Post(post_command.c_str());

    post_command = NativeLauncher::getNWAdress() + "/send_message?type=17";
    Post(post_command.c_str());

    post_command = NativeLauncher::getNWAdress() + "/send_message?type=21";
    Post(post_command.c_str());

    post_command = NativeLauncher::getNWAdress() + "/send_message?type=26";
    Post(post_command.c_str());
    
    post_command = NativeLauncher::getNWAdress() + "/send_message?type=32";
    Post(post_command.c_str());
    
    return;
}

void OutgoingController::initGame()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    _sprite1 = Sprite::create("seaside-955948_640.png");
    _sprite1->setScale(1.0f);
    _sprite1->setPosition(Vec2(winSize.width/2, winSize.height/2));
    addChild(_sprite1);
    
    Label *label = Label::createWithSystemFont("みんなお出かけ", "Marker Felt.ttf", 30);
    label->setScale(2.0f);
    label->setPosition(Vec2(winSize.width/2, winSize.height*3/4));
    this->addChild(label);
    
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

void OutgoingController::showSPrite()
{
    char message[100];
    
    lockAllEquipment(message);

    auto s = Director::getInstance()->getWinSize();
    auto action = Sequence::createWithTwoActions(ProgressTo::create(2, 100), ProgressTo::create(0, 0));
    /**
     *  Our image on the left should be a radial progress indicator, clockwise
     */
    auto left = ProgressTimer::create(Sprite::create("seaside-955948_640.png"));
    left->setType(ProgressTimer::Type::RADIAL);
    addChild(left);
    left->setMidpoint(Vec2(0.25f, 0.75f));
    left->setPosition(100, s.height/2);
    left->runAction(RepeatForever::create(action->clone()));
    
    /**
     *  Our image on the left should be a radial progress indicator, counter clockwise
     */
    auto right = ProgressTimer::create(Sprite::create("seaside-955948_640.png"));
    right->setType(ProgressTimer::Type::RADIAL);
    right->setMidpoint(Vec2(0.75f, 0.25f));
    
    /**
     *  Note the reverse property (default=NO) is only added to the right image. That's how
     *  we get a counter clockwise progress.
     */
    addChild(right);
    right->setPosition(s.width-100, s.height/2);
    right->runAction(RepeatForever::create(action->clone()));


    // 別スレッドを生成して引数を渡して実行する
     auto t = std::thread([this] (int n) {
     for (int i = 0; i < 100; i++) {
     mtx.lock();
     log("%d", n + i);
     mtx.unlock();
     }
     
     // 処理が一通り終わったのでメインスレッドに戻してメソッドを呼ぶ
     auto scheduler = Director::getInstance()->getScheduler();
     scheduler->performFunctionInCocosThread(CC_CALLBACK_0(OutgoingController::dispatchThreadCallbacks, this));
     }, 10000);
     
     // スレッドの管理を手放す
     // スレッドの処理を待つ場合はt.join()かstd::asyncを使う
     t.detach();

     
}

void OutgoingController::dispatchThreadCallbacks()
{
    // std::lock_guardはunlockをスコープから抜ける時に自動的にやってくれる
    std::lock_guard<std::mutex> lock(mtx);
    CCDirector::sharedDirector()->replaceScene(TransitionFadeTR::create(3.0f,  HelloWorld::scene()));
}

void OutgoingController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();
    
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL("https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3");
    this->addChild(webView, 1);
}

void OutgoingController::playEffect()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/machine_call.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/machine_call.mp3");
    //    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("music/blackout_harp1.mp3");
}

bool OutgoingController::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void OutgoingController::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
}


void OutgoingController::onTouchEnded(Touch *touch, Event *unused_event)
{
    showSPrite();
    playEffect();
    return;
}

void OutgoingController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void OutgoingController::update(float dt)
{
    
}
