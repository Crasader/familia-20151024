//
//  EquipmentScene.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/10/02.
//
//

#include "EquipmentScene.hpp"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;

class AudioSlider : public Node
{
public:
    enum Direction {
        Vertical,
        Horizontal
    };
    
    static AudioSlider *create(Direction direction)
    {
        auto ret = new (std::nothrow) AudioSlider(direction);
        if (ret && !ret->init()) {
            delete ret;
            ret = nullptr;
        }
        ret->autorelease();
        return ret;
    }
    
    float getValue() const
    {
        return _slider->getValue();
    }
    
    void setValue(float minValue, float maxValue, float value)
    {
        _slider->setMinimumValue(minValue);
        _slider->setMaximumValue(maxValue);
        _slider->setValue(value);
        
        char buffer[32];
        
        sprintf(buffer, "%.2f", minValue);
        if (!_lblMinValue) {
            _lblMinValue = Label::createWithTTF(buffer, "fonts/arial.ttf", 8);
            addChild(_lblMinValue);
            if (_direction == Vertical)
                _lblMinValue->setPosition(12.0, -50.0);
            else
                _lblMinValue->setPosition(-50, 12.0);
        } else {
            _lblMinValue->setString(buffer);
        }
        
        sprintf(buffer, "%.2f", maxValue);
        if (!_lblMaxValue) {
            _lblMaxValue = Label::createWithTTF(buffer, "fonts/arial.ttf", 8);
            addChild(_lblMaxValue);
            if (_direction == Vertical)
                _lblMaxValue->setPosition(12.0, 50.0);
            else
                _lblMaxValue->setPosition(50, 12.0);
        } else {
            _lblMaxValue->setString(buffer);
        }
    }
    
private:
    AudioSlider(Direction direction)
    : _direction(direction)
    , _slider(nullptr)
    , _lblMinValue(nullptr)
    , _lblMaxValue(nullptr)
    {
    }
    
    bool init()
    {
        _slider = extension::ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
        _slider->setScale(0.5);
        if (_direction == Vertical)
            _slider->setRotation(-90.0);
        addChild(_slider);
        return true;
    }
    
    Direction _direction;
    extension::ControlSlider *_slider;
    Label *_lblMinValue;
    Label *_lblMaxValue;
};


int temprature_strength;
int huminity_strength;
int wing_strength;

Scene* EquipmentController::scene()
{
    auto scene = Scene::create();
    auto layer = EquipmentController::create();
    
    scene->addChild(layer);
    
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool EquipmentController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(EquipmentController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(EquipmentController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(EquipmentController::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(EquipmentController::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    initGame();
    
    return true;
}

void EquipmentController::powerSavingMode(char* result)
{
    std::string post_command = NativeLauncher::getNWAdress() + "/send_message?type=53";
    Post(post_command.c_str());
    return;
}

void EquipmentController::getTargetStatus()
{
    std::string post_command = NativeLauncher::getNWAdress() + "/get_message?type=14";
    std::string recv = Get_data(post_command.c_str());
    Json* json = Json_create(recv.c_str());
    if (json) {
        temprature_strength = std::atoi(Json_getString(json, "temperature", "32"));
        huminity_strength = std::atoi(Json_getString(json, "huminity", "60"));
        wing_strength = std::atoi(Json_getString(json, "wing", "6"));
    }
    
    return;
}

void EquipmentController::initGame()
{
    getTargetStatus();
    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);

    
//    extern NSString* const kLocalDeviceIdMainBoard;
//    extern NSString* const kLocalDeviceIdSolarBoard;
//    extern NSString* const kLocalDeviceIdEneBoard;
//    extern NSString* const kLocalDeviceIdBattery;
//    extern NSString* const kLocalDeviceIdSwitch;
//    extern NSString* const kLocalDeviceIdAircon;
//    extern NSString* const kLocalDeviceIdLed;
//    extern NSString* const kLocalDeviceIdSmartMeter;
//    extern NSString* const kLocalDeviceIdWaterHeater;
//    extern NSString* const kLocalDeviceIdEV;
    
    
    _doorStatus = 0;
    _sprite1 = Sprite::create("sts/light_hakunetsu.png");
    _sprite1->setScale(1.0f);
    _sprite1->setPosition(Vec2(winSize.width/3, winSize.height*4/5+30));
    addChild(_sprite1);
    auto button = ControlButton::create(Scale9Sprite::create("cocosui/btn_exercise02_p.png"));
//    auto button = ControlButton::create(Scale9Sprite::create("cocosui/btn_exercise02_n.png"));
    //画像を引き延ばさない設定
    button->setAdjustBackgroundImage(false);
    //ボタンの位置設定
    button->setPosition(Vec2(winSize.width*4/5, winSize.height*4/5));
    button->setScale(1.0f);
    //ボタンをタップしたときに呼び出す関数の設定
    button->addTargetWithActionForControlEvents(this,
                                                cccontrol_selector(EquipmentController::onTapButton1),
                                                Control::EventType::TOUCH_UP_INSIDE);
    addChild(button);

    _sprite3 = Sprite::create("sts/lgi01a201409050200.png");
    _sprite3->setScale(0.3f);
    _sprite3->setPosition(Vec2(winSize.width/3, winSize.height*3/5+50));
    addChild(_sprite3);
    auto button2 = ControlButton::create(Scale9Sprite::create("cocosui/btn_exercise02_p.png"));
    //    auto button = ControlButton::create(Scale9Sprite::create("cocosui/btn_exercise02_n.png"));
    //画像を引き延ばさない設定
    button2->setAdjustBackgroundImage(false);
    //ボタンの位置設定
    button2->setPosition(Vec2(winSize.width*4/5, winSize.height*3/5));
    button2->setScale(1.0f);
    //ボタンをタップしたときに呼び出す関数の設定
    button2->addTargetWithActionForControlEvents(this,
                                                cccontrol_selector(EquipmentController::onTapButton2),
                                                Control::EventType::TOUCH_UP_INSIDE);
    addChild(button2);

    _sprite5 = Sprite::create("sts/kyutouki.png");
    _sprite5->setScale(1.0f);
    _sprite5->setPosition(Vec2(winSize.width/3, winSize.height*1/7));
    addChild(_sprite5);
    auto button3 = ControlButton::create(Scale9Sprite::create("cocosui/btn_exercise02_p.png"));
    //    auto button = ControlButton::create(Scale9Sprite::create("cocosui/btn_exercise02_n.png"));
    //画像を引き延ばさない設定
    button3->setAdjustBackgroundImage(false);
    //ボタンの位置設定
    button3->setPosition(Vec2(winSize.width*4/5, winSize.height*1/7));
    button3->setScale(1.0f);
    //ボタンをタップしたときに呼び出す関数の設定
    button3->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(EquipmentController::onTapButton3),
                                                 Control::EventType::TOUCH_UP_INSIDE);
    addChild(button3);

    Label *label = Label::createWithSystemFont("温度", "Marker Felt.ttf", 30);
    label->setPosition(Vec2(winSize.width/10, winSize.height*1/2));
    addChild(label);
    _sliderPitch = AudioSlider::create(AudioSlider::Horizontal);
    _sliderPitch->setPosition(Vec2(winSize.width/2, winSize.height*1/2));
    _sliderPitch->setScale(3.0f);
    _sliderPitch->setValue(17, 32, temprature_strength);
    addChild(_sliderPitch);

    Label *label1 = Label::createWithSystemFont("湿度", "Marker Felt.ttf", 30);
    label1->setPosition(Vec2(winSize.width/10, winSize.height*1/2-70));
    addChild(label1);
    _sliderPitch1 = AudioSlider::create(AudioSlider::Horizontal);
    _sliderPitch1->setPosition(Vec2(winSize.width/2, winSize.height*1/2-70));
    _sliderPitch1->setScale(3.0f);
    _sliderPitch1->setValue(40, 60, huminity_strength);
    addChild(_sliderPitch1);

    Label *label2 = Label::createWithSystemFont("風量", "Marker Felt.ttf", 30);
    label2->setPosition(Vec2(winSize.width/10, winSize.height*1/2-140));
    addChild(label2);
    _sliderPitch2 = AudioSlider::create(AudioSlider::Horizontal);
    _sliderPitch2->setPosition(Vec2(winSize.width/2, winSize.height*1/2-140));
    _sliderPitch2->setScale(3.0f);
    _sliderPitch2->setValue(0, 6, wing_strength);
    addChild(_sliderPitch2);

    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EquipmentController::onTapButton1(Ref* sender, Control::EventType controlEvent)
{
    playEffect(1);

    //update関数の呼び出しを停止
    unscheduleUpdate();
    std::string post_command = NativeLauncher::getNWAdress() + "/send_message?type=16";
    Post(post_command.c_str());

    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EquipmentController::onTapButton2(Ref* sender, Control::EventType controlEvent)
{
    playEffect(2);
    
    //update関数の呼び出しを停止
    unscheduleUpdate();
    const float pitch = _sliderPitch->getValue();
    const float pitch1 = _sliderPitch1->getValue();
    const float pitch2 = _sliderPitch2->getValue();

    std::string post_command = NativeLauncher::getNWAdress() + "/send_message?type=2&temperature=" + std::to_string(pitch) + "&wing=" + std::to_string(pitch2) + "&huminity=" + std::to_string(pitch1) + "";
    Post(post_command.c_str());

    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EquipmentController::onTapButton3(Ref* sender, Control::EventType controlEvent)
{
    playEffect(3);
    
    //update関数の呼び出しを停止
    unscheduleUpdate();
    showModal(0);
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void EquipmentController::menuStartCallback(Ref* Sender)
{
    MenuItem* menuItem = (MenuItem*)Sender;
    log("%d",menuItem->getTag());
    switch(menuItem->getTag()){
        case 1:
            break;
        case 2:
            break;
    }
    dialogClose();
}
void EquipmentController::dialogClose()
{
    UIDialog* dialog = static_cast<UIDialog*>(getChildByTag(30));
    dialog->close();
}

void EquipmentController::showModal(int type)
{
    std::string title;
    std::string content1;
    std::string content2;
    switch (type) {
        case 0:
            title = "他の機能を利用する";
            content1 = "お知らせです";
            content2 = "この機能は現在利用できません\n運用が開始されるまでお待ち下さい※";
            break;
        case 1:
            title = "メインへ戻る";
            content1 = "工事中";
            content2 = "遷移先の機能は現在利用できません\n運用が開始されるまでお待ち下さい※";
            break;
            
        default:
            break;
    }
    cocos2d::ccMenuCallback action = CC_CALLBACK_1(EquipmentController::menuStartCallback,this);
    std::vector<UIDialogButton*> buttons = {
        new UIDialogButton(title,action,1),
    };
    auto* dialog = UIDialog::create(content1,content2, buttons);
    addChild(dialog,31,30);
}



void EquipmentController::playEffect(int type)
{
    switch (type) {
        case 1:
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/switch1.mp3");
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/switch1.mp3");
            //    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("music/blackout_harp1.mp3");
            break;

        case 2:
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/select09.mp3");
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/select09.mp3");
            //    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("music/blackout_harp1.mp3");
            break;
        
        case 3:
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/poka.mp3");
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/poka.mp3");
            //    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("music/blackout_harp1.mp3");
            break;
            
        default:
            break;
    }

    
}

void EquipmentController::showSPrite()
{
    char message[100];
    Size winSize = Director::getInstance()->getVisibleSize();
    
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
        scheduler->performFunctionInCocosThread(CC_CALLBACK_0(EquipmentController::dispatchThreadCallbacks, this));
    }, 1000);
    
    // スレッドの管理を手放す
    // スレッドの処理を待つ場合はt.join()かstd::asyncを使う
    t.detach();
}

void EquipmentController::dispatchThreadCallbacks()
{
    // std::lock_guardはunlockをスコープから抜ける時に自動的にやってくれる
    std::lock_guard<std::mutex> lock(mtx);
//    CCDirector::sharedDirector()->replaceScene(TransitionFadeTR::create(6.0f,  HelloWorld::scene()));
    Director::getInstance()->replaceScene(TransitionMoveInT::create(3.0f,HelloWorld::scene()));
}

void EquipmentController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();
    
    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL("https://www.daiwahouse.co.jp/smp/business/kenchiku/script/regist_kenchiku.asp?ken_toi_kbn=3");
    this->addChild(webView, 1);
}

bool EquipmentController::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void EquipmentController::onTouchMoved(Touch *touch, Event *unused_event)
{
//    CCDirector::sharedDirector()->replaceScene(TransitionFade::create(3.0f,  HelloWorld::scene(), ccc3(0, 0, 0)));
}


void EquipmentController::onTouchEnded(Touch *touch, Event *unused_event)
{
    showSPrite();
    
    return;
}

void EquipmentController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void EquipmentController::update(float dt)
{
    
}
