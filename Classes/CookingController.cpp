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
    
    
    Size winSize = Director::getInstance()->getVisibleSize();
    auto img = Scale9Sprite::create("hotpepper-m.png");
    img->setPosition(winSize.width*4/5, img->getContentSize().height);
    img->setScale(3);
    this->addChild(img);
    
    return true;
}

void CookingController::initGame()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    auto text = Label::createWithSystemFont("本日のオススメのお店です", "HiraKakuProN-W6", 48);
    text->setPosition(Point(300, winSize.height-50));
    this->addChild(text);
    
    showButton1();
    showButton2();
    
    
    
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
    button->setPosition(winSize.width/4, winSize.height/5);
    button->setScaleX(1.5);
    button->setScaleY(2);
    button->setScaleZ(2);
    
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
    button->setPosition(winSize.width*3/4, winSize.height/5);
    button->setScaleX(1.5);
    button->setScaleY(2);
    button->setScaleZ(2);
    
    //ボタンをタップしたときに呼び出す関数の設定
    button->addTargetWithActionForControlEvents(this,
                                                cccontrol_selector(CookingController::onTapButton1),
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
    
    
    
    //update関数の呼び出しを開始
    scheduleUpdate();
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
