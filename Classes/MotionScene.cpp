//
//  MotionScene.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/25.
//
//

#include "MotionScene.h"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;

class foo {
public:
    static void setNumOfStep(foo *f, int numOfStep);
    static int getNumOfStep(foo *f);
    static void setMotionConfidence(foo *f, int confidence);
    static int getMotionConfidence(foo *f);
    static void setMotionStationary(foo *f, int stationary);
    static int getMotionStationary(foo *f);
    static void setMotionWalking(foo *f, int walking);
    static int getMotionWalking(foo *f);
    static void setMotionRunning(foo *f, int running);
    static int getMotionRunningg(foo *f);
    static void setMotionAutomotive(foo *f, int automotive);
    static int getMotionAutomotive(foo *f);
    static void setMotionUnknown(foo *f, int unknown);
    static int getMotionUnknown(foo *f);

    void callBack(int numOfStep);
    void callBack1(int numOfStep);
    void callBack2(int numOfStep);
    void callBack3(int numOfStep);
    void callBack4(int numOfStep);
    void callBack5(int numOfStep);
    void callBack6(int numOfStep);
    
    int temp;
    int temp1;
    int temp2;
    int temp3;
    int temp4;
    int temp5;
    int temp6;
};
void foo::setNumOfStep(foo *f, int numOfStep)
{
    f->callBack(numOfStep);
}
void foo::setMotionConfidence(foo *f, int confidence)
{
    f->callBack1(confidence);
}
void foo::setMotionStationary(foo *f, int stationary)
{
    f->callBack2(stationary);
}
void foo::setMotionWalking(foo *f, int walking)
{
    f->callBack3(walking);
}
void foo::setMotionRunning(foo *f, int running)
{
    f->callBack4(running);
}
void foo::setMotionAutomotive(foo *f, int automotive)
{
    f->callBack5(automotive);
}
void foo::setMotionUnknown(foo *f, int unknown)
{
    f->callBack6(unknown);
}
void foo::callBack(int numOfStep)
{
    temp = numOfStep;
}
void foo::callBack1(int numOfStep)
{
    temp1 = numOfStep;
}
void foo::callBack2(int numOfStep)
{
    temp2 = numOfStep;
}
void foo::callBack3(int numOfStep)
{
    temp3 = numOfStep;
}
void foo::callBack4(int numOfStep)
{
    temp4 = numOfStep;
}
void foo::callBack5(int numOfStep)
{
    temp5 = numOfStep;
}
void foo::callBack6(int numOfStep)
{
    temp6 = numOfStep;
}
int foo::getNumOfStep(foo *f)
{
    return f->temp;
}
int foo::getMotionConfidence(foo *f)
{
    return f->temp1;
}
int foo::getMotionStationary(foo *f)
{
    return f->temp2;
}
int foo::getMotionWalking(foo *f)
{
    return f->temp3;
}
int foo::getMotionRunningg(foo *f)
{
    return f->temp4;
}
int foo::getMotionAutomotive(foo *f)
{
    return f->temp5;
}
int foo::getMotionUnknown(foo *f)
{
    return f->temp6;
}

foo f;
int step_count;

Scene* MotionController::createScene()
{
    auto scene = Scene::create();
    auto layer = MotionController::create();
    
    scene->addChild(layer);
    
    return scene;
}

Scene* MotionController::scene()
{
    auto scene = Scene::create();
    auto layer = MotionController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool MotionController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(MotionController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MotionController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MotionController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MotionController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

void MotionController::postNumOfStep(char* result, int numOf)
{
//    const char *post_command;
    std::string post_command;
    
    post_command = "http://127.0.0.1:3000/send_message?type=64&numStep=" + std::to_string(foo::getNumOfStep(&f));
    
    Post(post_command.c_str());
    
    return;
}

void MotionController::drawString()
{
    std::string result = "歩数: ";
    
    if(step_count < foo::getNumOfStep(&f)){
        step_count = foo::getNumOfStep(&f);
    }
    result = result + std::to_string(foo::getNumOfStep(&f));
    _label1->setString(result.c_str());

    char message[100];
    postNumOfStep(message, step_count);
    
    std::string result1 = "";
    if (foo::getMotionConfidence(&f) != 0){
    }
    if (foo::getMotionStationary(&f) != 0){
        result1 = "階段：" + std::to_string(foo::getMotionStationary(&f)) + ":";
    }
    if (foo::getMotionWalking(&f) != 0){
        result1 = result1 + "歩行中：" + std::to_string(foo::getMotionWalking(&f)) + ":";
    }
    if (foo::getMotionRunningg(&f) != 0){
        result1 = result1 + "走行中：" + std::to_string(foo::getMotionRunningg(&f)) + ":";
    }
    if (foo::getMotionAutomotive(&f) != 0){
        result1 = result1 + "乗り物中：" + std::to_string(foo::getMotionAutomotive(&f)) + ":";
    }
    if (foo::getMotionUnknown(&f) != 0){
        
    }
    
    printf("%s",result1.c_str());
    _label2->setString(result1.c_str());


    
    
}

void MotionController::countUp(int numOfStep)
{
    printf("Number of Step is %d",numOfStep);


    foo::setNumOfStep(&f, numOfStep);

    
    
}

void MotionController::motionStatus(int confidence,
                               int stationary,
                               int walking,
                               int running,
                               int automotive,
                               int unknown)

{

    printf("Number of Step is %d %d %d %d %d %d ",confidence,
            stationary,
            walking,
            running,
            automotive,
            unknown);
    
    foo::setMotionConfidence(&f, confidence);
    foo::setMotionStationary(&f, stationary);
    foo::setMotionWalking(&f, walking);
    foo::setMotionRunning(&f, running);
    foo::setMotionAutomotive(&f, automotive);
    foo::setMotionUnknown(&f, unknown);

}

void MotionController::startCallback()
{
    
}

void MotionController::initGame()
{
    Size winSize = Director::getInstance()->getWinSize();

    auto _bg2 = LayerColor::create(Color4B(0,255,0,128), winSize.width, winSize.height);
    this->addChild(_bg2);

    auto item1 = MenuItemLabel::create(LabelTTF::create("[START!]", "Courier New.ttf", 51),
                                       [](Object *obj) {
                                           NativeLauncher::launchMotionController(0);
                                       });
    
    auto item2 = MenuItemLabel::create(LabelTTF::create("[STOP!]", "Courier New.ttf", 51),
                                       [](Object *obj) {
                                           NativeLauncher::launchMotionController(1);
                                           step_count = 0;
                                       });

    auto item3 = MenuItemLabel::create(LabelTTF::create("[EXIT]", "Courier New.ttf", 51),
                                       [](Object *obj) {
                                           CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
                                       });
    
    
    Menu *menu = Menu::create(item1, item2, NULL);
//    menu->alignItemsHorizontallyWithPadding(10);
    menu->alignItemsVerticallyWithPadding(20);
    addChild(menu);

    Label *label = Label::createWithSystemFont("これは万歩計です", "Marker Felt.ttf", 30);
    label->setScale(2.0f);
    label->setPosition(Vec2(winSize.width/2, winSize.height*3/4));
    this->addChild(label);

    _label1 = Label::createWithSystemFont("検索中", "Marker Felt.ttf", 30);
    _label1->setScale(2.0f);
    _label1->setPosition(Vec2(winSize.width*1/2, winSize.height/5));
    _label1->setTag(1);
    this->addChild(_label1);
    
    _label2 = Label::createWithSystemFont("検索中", "Marker Felt.ttf", 30);
    _label2->setScale(2.0f);
    _label2->setPosition(Vec2(winSize.width*1/2, winSize.height/9));
    _label2->setTag(2);
    this->addChild(_label2);
    
    
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}


void MotionController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto webView = cocos2d::experimental::ui::WebView::create();
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.9f, visibleSize.height * 0.8f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL("https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3");
    this->addChild(webView, 1);
    
}

bool MotionController::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void MotionController::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
}


void MotionController::onTouchEnded(Touch *touch, Event *unused_event)
{

    return;
}

void MotionController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void MotionController::update(float dt)
{
    drawString();
    
}
