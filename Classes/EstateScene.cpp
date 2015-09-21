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

void EstateController::showSPrite()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //            CCRotateBy::create((float)3.0f,(float)-60);
    //            CCTintTo::create((float)2.0f,ccc3(0, 0, 0));
    //        CCTurnOffTiles::create((float)2.0f,ccc3(0, 0, 0),(int)6);
    CCSprite* pSprite = CCSprite::create("Default.png");
    CCPoint pos = ccp(visibleSize.width/2, visibleSize.height/2);
    pSprite->setPosition(pos);
    this->addChild(pSprite);
    CCPointArray* pAry = CCPointArray::create(3);
    pAry->addControlPoint(ccp(0,0));
    pAry->addControlPoint(ccp(-300,30));
    pAry->addControlPoint(ccp(0,0));
    // スプライン曲線
//    pSprite->runAction(CCCardinalSplineBy::create(2.0f, pAry, 1.0f));
    // Catmull-Romスプライン曲線
//    pSprite->runAction(CCCatmullRomBy::create(2.0f, pAry));
    // camera 180度回転
    pSprite->runAction(CCOrbitCamera::create(1.0f, 1, 0, 0, 180, 90, 0));
//    pSprite->runAction(CCOrbitCamera::create(1.0f, 1, 0, 0, 180, 0, 0));

/*
    pSprite->runAction(CCRipple3D::create ((float)3.0f,
                                           　　　(CCSize)Director::getInstance()->getVisibleSize(),
                                           　　　(CCPoint)pos,
                                           　　　(float)50.0f,
                                           　　　(int) 5,
                                           　　　(float)3.0f));
*/
    //pSprite->runAction(CCShaky3D::create((int)5.0f,(CCSize)Director::getInstance()->getVisibleSize(),(int)5,(bool)true));

    //    pSprite->runAction(CCPageTurn3D::create((float)5.0f,(CCSize)Director::getInstance()->getVisibleSize()));
    
}


void EstateController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();
    
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL("https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3");
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
    showSPrite();

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
