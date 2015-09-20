#include "HelloWorldScene.h"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;




bool CardSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    return true;
}

void CardSprite::onEnter()
{
    Sprite::onEnter();

    //画像の表示
    setTexture("card_back.png");
    
    //カードの位置とタグを指定
    setTag(_posIndex.x + _posIndex.y * 5 + 1);
}

std::string CardSprite::getFileName(CardType cardType)
{
    //ファイル名の取得
    std::string filename;
    switch (cardType)
    {
        case Clubs: filename = "card_clubs.png"; break;
        case Diamonds: filename = "card_diamonds.png"; break;
        case Hearts: filename = "card_hearts.png"; break;
        default: filename = "card_spades.png"; break;
    }
    
    return filename;
}

void CardSprite::showNumber()
{
    //表示する数字の取得
    std::string numberString;
    switch (_card.number)
    {
        case 1: numberString = MESSAGE_MOTHER; break;
        case 2: numberString = MESSAGE_FATHER; break;
        case 3: numberString = MESSAGE_GRANMOTHER; break;
        case 4: numberString = MESSAGE_BOY; break;
        case 5: numberString = MESSAGE_News; break;
        case 6: numberString = MESSAGE_BOOKS; break;
        case 7: numberString = MESSAGE_VIDEO_MESSAGE; break;
        case 8: numberString = MESSAGE_MESSAGE; break;
        case 9: numberString = MESSAGE_TELEPHONE; break;
        case 10: numberString = MESSAGE_REAL_ESTATE; break;
        case 11: numberString = MESSAGE_COMSUMPTION; break;
        case 12: numberString = MESSAGE_CHARGE; break;
        case 13: numberString = MESSAGE_SCHEDULE; break;
        default: numberString = StringUtils::format("%d", _card.number); break;
    }
    
    //表示する文字色の取得
    Color4B textColor;
    switch (_card.type)
    {
        case Clubs:
        case Spades:
            textColor = Color4B::BLACK;
            break;
            
        default:
            textColor = Color4B::RED;
            break;
    }
    
    //ラベルの生成
    auto number = Label::createWithSystemFont(numberString, "Arial", 16);
    number->setPosition(Point(getContentSize() / 2));
    number->setTextColor(textColor);
    addChild(number);
}

void CardSprite::moveBackToInitPos()
{
    //移動アニメーションの作成
    float posX = CARD_1_POS_X + CARD_DISTANCE_X * _posIndex.x;
    float posY = CARD_1_POS_Y + CARD_DISTANCE_Y * _posIndex.y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    
    //アニメーションの実行
    runAction(move);
}

void CardSprite::moveToTrash()
{
    //移動アニメーションの作成
    float posX = CARD_1_POS_X + CARD_DISTANCE_X * 4;
    float posY = CARD_1_POS_Y - CARD_DISTANCE_Y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    
    //アニメーション後に呼び出す関数の作成
    auto func = CallFunc::create([&](){
        this->setTag(TAG_TRUSH_CARD);
    });
    
    //アクションの直列結合
    auto seq = Sequence::create(move, func, nullptr);
    
    //アニメーションの実行
    runAction(seq);
}

void CardSprite::moveToInitPos()
{
    //移動アニメーションの作成
    float posX = CARD_1_POS_X + CARD_DISTANCE_X * _posIndex.x;
    float posY = CARD_1_POS_Y + CARD_DISTANCE_Y * _posIndex.y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    
    //カード回転アニメーションの作成
    auto scale1 = ScaleTo::create(MOVING_TIME / 2, 0, 1);
    auto func1 = CallFunc::create([&](){
        //画像の表示
        setTexture(getFileName(_card.type));
        
        //数字の表示
        showNumber();
    });
    auto scale2 = ScaleTo::create(MOVING_TIME / 2, 1, 1);
    auto seq1 = Sequence::create(scale1, func1, scale2, nullptr);
    
    //アクションの並列結合
    auto spawn = Spawn::create(move, seq1, nullptr);
    
    //アニメーションの実行
    runAction(spawn);
}

Scene* HelloWorld::createScene()
{
    //シーンを生成する
    auto scene = Scene::create();
    
    //HelloWorldクラスのレイヤーを生成する
    auto layer = HelloWorld::create();

    //シーンに対してレイヤーを追加する
    scene->addChild(layer);

    //シーンを返す
    return scene;
}

Scene* HelloWorld::scene()
{
    //シーンを生成する
    auto scene = Scene::create();
    
    //HelloWorldクラスのレイヤーを生成する
    auto layer = HelloWorld::create();
    
    //シーンに対してレイヤーを追加する
    scene->addChild(layer);
    
    //シーンを返す
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
/*
    emotion_status = ["akuma.png",
                      "ase.png",
                      "kiran.png",
                      "komaru.png",
                      "naki.png",
                      "sumairu.png",
                      "tehehe.png",
                      "tenshi.png",
                      "tere.png",
                      "yattane.png"
                      ];
*/
    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //ゲームを初期化する
    initGame();
    
    return true;
}

void HelloWorld::initCards()
{
    //ゲームカードのクリア
    _cards.clear();
    
    //4種類 x 13枚分のループ
    for (int type = 0; type < CARD_TYPE_NUM; type++)
    {
        for (int number = 1; number <= CARD_NUM; number++)
        {
            //カード情報の作成
            Card card;
            card.number = number;
            card.type = (CardType)type;
            
            //カードを追加する
            _cards.push_back(card);
        }
    }
}

Card HelloWorld::getCard()
{
    std::random_device rd;
    std::mt19937 rand = std::mt19937(rd());
    
    //インデックスをランダムに取得する
    int index = std::uniform_int_distribution<int>(0, (int)_cards.size() - 1)(rand);
    
    //カードの数値を取得する
    auto card = _cards[index];
    
    //一時カードから削除する
    _cards.erase(_cards.begin() + index);
    
    return card;
}

void HelloWorld::createCard(PosIndex posIndex)
{
    float posX = CARD_1_POS_X;
    float posY = CARD_1_POS_Y - CARD_DISTANCE_Y;
    
    //新しいカードを作成する
    auto card = CardSprite::create();
    card->setCard(getCard());
    card->setPosition(posX, posY);
    card->setPosIndex(posIndex);
    card->moveToInitPos();
    addChild(card, ZORDER_SHOW_CARD);
}

void HelloWorld::showInitCards()
{
    for (int tag = 1; tag <= 10; tag++)
    {
        auto card = getChildByTag(tag);
        if (card)
        {
            //カードが残っている場合は、削除する
            card->removeFromParent();
        }
    }
    
    //5列 x 2行分のループ
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            PosIndex posIndex;
            posIndex.x = x;
            posIndex.y = y;
            
            //カードの生成
            createCard(posIndex);
        }
    }
}

void HelloWorld::initGame()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    
    auto _bg2 = LayerColor::create(Color4B(0,255,0,128), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    //CCSpriteクラスで画像を設定します。
    _sprite1 = Sprite::create("boy.png");
    _sprite1->setScale(2.0f);
    _sprite1->setPosition(Vec2(winSize.width*1/4, winSize.height/5));
    addChild(_sprite1);
    _sprite2 = Sprite::create("grandmother.png");
    _sprite2->setScale(2.0f);
    _sprite2->setPosition(Vec2(winSize.width*3/4, winSize.height/5));
    addChild(_sprite2, 0);
    sts_sprite1 = 0;
    sts_sprite2 = 0;
    
    // １番目１回実行画像Runアクションスケジュール 2秒後
    this->schedule(schedule_selector(HelloWorld::Action01), 2.0f);
    // ２番目１回実行画像Runアクションスケジュール 4秒後
    this->schedule(schedule_selector(HelloWorld::Action02), 4.0f);

/*
    //アニメーションを作成　MoveTo::create(時間, (X座標, Y座標));
    auto action1 = MoveTo::create(45,
                                  Vec2(winSize.width-_sprite1->getContentSize().width/2,
                                       winSize.height/4));
    auto action2 = MoveTo::create(30,
                                  Vec2(winSize.width-_sprite2->getContentSize().width/2,
                                       winSize.height/10));
    //アニメーション開始
    _sprite1->runAction(action1);
    _sprite2->runAction(action2);
 */


    
    //裏向いているカードを表示する
    showBackCards();
    
    //時間を表示する
    showTimerLabel();
    
    //ボタンを表示する
    // showButton();

    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    //カードを初期化する
    initCards();
    
    //カードを表示する
    showInitCards();
    
    //カードの山を表示する
    showBackCards();
    
    //ゴミ箱を初期化する
    initTrash();
    
    //時間を表示する
    showTimerLabel();
    
    //update関数の呼び出しを開始
    scheduleUpdate();

}

void HelloWorld::Sequence1()
{
    // 大きさ（縮小）アクションを適用 1.0秒 0倍
    auto scaleTo1 = ScaleTo::create(1.8f, 0.3f);
    //callbackでの消去処理
    auto removeSprite1 = CallFunc::create([this](){
//        this->removeChild(_sprite1);
    });
    // 縮小、消去アクションを適用
    auto sequence1 = Sequence::create(scaleTo1, removeSprite1, NULL);
    // 縮小、消去runアクションを適用
    _sprite1->runAction(sequence1);
}

void HelloWorld::Sequence2()
{
    // 大きさ（縮小）アクションを適用 2.5秒 0倍
    auto scaleTo2 = ScaleTo::create(1.8f, 0.2f);
    //callbackでの画像消去処理
    auto removeSprite2 = CallFunc::create([this](){
//        this->removeChild(_sprite2);
    });
    // 縮小、消去アクションを適用
    auto sequence2 = Sequence::create(scaleTo2, removeSprite2, NULL);
    // 縮小、消去runアクションを適用
    _sprite2->runAction(sequence2);
}

void HelloWorld::Sequence3()
{
//    _sprite1->setScale(2.0f);

    // 大きさ（縮小）アクションを適用 1.0秒 0倍
    auto scaleTo1 = ScaleTo::create(1.8f, 3.0f);
    //callbackでの消去処理
    auto removeSprite1 = CallFunc::create([this](){
//        this->removeChild(_sprite1);
    });
    // 縮小、消去アクションを適用
    auto sequence1 = Sequence::create(scaleTo1, removeSprite1, NULL);
    // 縮小、消去runアクションを適用
    _sprite1->runAction(sequence1);
}

void HelloWorld::Sequence4()
{
    // 大きさ（縮小）アクションを適用 2.5秒 0倍
    auto scaleTo2 = ScaleTo::create(1.8f, 4.2f);
    //callbackでの画像消去処理
    auto removeSprite2 = CallFunc::create([this](){
//        this->removeChild(_sprite2);
    });
    // 縮小、消去アクションを適用
    auto sequence2 = Sequence::create(scaleTo2, removeSprite2, NULL);
    // 縮小、消去runアクションを適用
    _sprite2->runAction(sequence2);
}

// １番目画像Runアクションメソッド
void HelloWorld::Action01(float frame)
{
    switch (sts_sprite1) {
        case 0:
            Sequence1();
            sts_sprite1 = 1;
            break;

        case 1:
            Sequence3();
            sts_sprite1 = 0;
            break;
            
        default:
            break;
    }
}

// ２番目画像Runアクションメソッド
void HelloWorld::Action02(float frame)
{
    switch (sts_sprite2) {
        case 0:
            Sequence2();
            sts_sprite2 = 1;
            break;
            
        case 1:
            Sequence4();
            sts_sprite2 = 0;
            break;
            
        default:
            break;
    }
}

CardSprite* HelloWorld::getTouchCard(Touch *touch)
{
    for (int tag = 1; tag <= 15; tag++)
    {
        //表示されているカードを取得する
        auto card = (CardSprite*)getChildByTag(tag);
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

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    //タップされたカードを取得する
    _firstCard = getTouchCard(touch);
    if (_firstCard)
    {
        //場に出ているカードがタップされた場合
        
        //Zオーダーを変更する
        _firstCard->setLocalZOrder(ZORDER_MOVING_CARD);
        
        return true;
    }
    
    return false;
}

bool HelloWorld::onTouchBegan1(Touch *touch, Event *unused_event)
{
    printf("onTouchBegan1");
    
    return false;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
    //スワイプしているカードの位置を変更
    _firstCard->setPosition(_firstCard->getPosition() + touch->getDelta());
}

void HelloWorld::onTouchMoved1(Touch *touch, Event *unused_event)
{
    printf("onTouchMoved1");
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    int indetifier = 0;
    int indetifier_sub = 0;
    
    //タップしたカードの取得
    auto _secondSprite = getTouchCard(touch);
    indetifier = _firstCard->getCard().number;
    if (_secondSprite)
    {
        indetifier_sub = _secondSprite->getCard().number;
    }
    
    //新しいカードを配置する
    if ((int)_cards.size() > 0)
    {
        createCard(_firstCard->getPosIndex());
    }
        
    //カードを捨てる
    _firstCard->moveToTrash();
        
    if (_secondSprite)
    {
        //もう1枚の新しいカードを配置する
        if ((int)_cards.size() > 0)
        {
            createCard(_secondSprite->getPosIndex());
        }
            
        //カードを捨てる
        _secondSprite->moveToTrash();
    }
        
    if ((int)_cards.size() <= 0)
    {
        //カードの山を削除する
        removeChildByTag(TAG_BACK_CARD);
    }
    
    //タップしているカードの指定を外す
    _firstCard = nullptr;

    switch(indetifier){
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        CCDirector::sharedDirector()->replaceScene(
                                                   CCTransitionFade::create(2.0f,
                                                                            EstateController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 6:
    case 7:
    case 8:
//            CCTintTo::create((float)2.0f,ccc3(0, 0, 0));
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, MediaController::scene(), ccc3(0, 0, 0)));
        break;
    case 9:
//            CCTintTo::create((float)2.0f,ccc3(0, 0, 0));
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, EstateController::scene(), ccc3(0, 0, 0)));
        break;
    case 10:
    case 11:
    case 12:
//            CCTintTo::create((float)2.0f,ccc3(0, 0, 0));
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, EstateController::scene(), ccc3(0, 0, 0)));
        break;
    }

    //    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(2.0f, HelloWorld::scene()));
    
    //    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
    
    


}

void HelloWorld::onTouchEnded1(Touch *touch, Event *unused_event)
{
    printf("onTouchEnded1");
}

void HelloWorld::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void HelloWorld::onTouchCancelled1(Touch *touch, Event *unused_event)
{
    printf("onTouchCancelled1");
}

void HelloWorld::showButton()
{
    //ボタンを作成する
    auto button = ControlButton::create(Scale9Sprite::create("button.png"));
    
    //画像を引き延ばさない設定
    button->setAdjustBackgroundImage(false);
    
    //ボタンの位置設定
    button->setPosition(BUTTON_POS_X, BUTTON_POS_Y);
    
    //ボタンをタップしたときに呼び出す関数の設定
    button->addTargetWithActionForControlEvents(this,
                                                cccontrol_selector(HelloWorld::onTapButton),
                                                Control::EventType::TOUCH_UP_INSIDE);
    
    //ボタンに表示する文字
    button->setTitleForState("Start", Control::State::NORMAL);
    
    //画面に追加する
    addChild(button);
}

void HelloWorld::initTrash()
{
    while (true)
    {
        //ゴミカードがなくなるまでループする
        auto card = getChildByTag(TAG_TRUSH_CARD);
        if (card)
        {
            //ゴミカードが見つかったら削除する
            card->removeFromParent();
        }
        else
        {
            break;
        }
    }
}

void HelloWorld::showBackCards()
{
    return;
/*
    auto backCards = getChildByTag(TAG_BACK_CARD);
    if (!backCards)
    {
        //表示されていない場合
        
        float posX = CARD_1_POS_X;
        float posY = CARD_1_POS_Y - CARD_DISTANCE_Y;
        
        //カードの山を表示する
        backCards = Sprite::create("card_back.png");
        backCards->setPosition(posX, posY);
        backCards->setTag(TAG_BACK_CARD);
        addChild(backCards);
    }
*/
}

void HelloWorld::onTapButton(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    //カードを初期化する
    initCards();
    
    //カードを表示する
    showInitCards();
    
    //カードの山を表示する
    showBackCards();
    
    //ゴミ箱を初期化する
    initTrash();
    
    //時間を表示する
    showTimerLabel();
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void HelloWorld::showTimerLabel()
{
    _timer = 0;
    
    auto timerLabel = (Label*)getChildByTag(TAG_TIMER_LABEL);
    if (!timerLabel)
    {
        //時間のラベルを表示する
        timerLabel = Label::createWithSystemFont("", "Arial", 48);
        timerLabel->setPosition(TIMER_LABEL_POS_X, TIMER_LABEL_POS_Y);
        timerLabel->setTag(TAG_TIMER_LABEL);
        addChild(timerLabel);
    }
    
    timerLabel->setString(StringUtils::format("%0.2fs", _timer));
}

#define ONE 1
#define TWO 2

void HelloWorld::update(float dt)
{
/*
    // 見守り対象のケア
    Size winSize = Director::getInstance()->getVisibleSize();
//    _sprite1->setPosition(Vec2(0, winSize.height/5));
    _sprite1->setPosition(Point(_sprite1->getPositionX() + 100*dt, _sprite1->getPositionY()));
//    _sprite2->setPosition(Vec2(winSize.width/2, winSize.height/5));
    _sprite2->setPosition(Point(_sprite2->getPositionX() + 100*dt, _sprite2->getPositionY()));
    
    //これは画面の右端に達したら、左端に位置を移動します。
    if (_sprite1->getPositionX() > 480+64) {
        _sprite1->setPosition(Vec2(0, winSize.height/5));
        _sprite2->setPosition(Vec2(winSize.width/2, winSize.height/5));
    }
    
    if(_target_status[0]==ONE){
        _sprite1->setPosition(Vec2(0, winSize.height/5));
    }
    
    if(_target_status[1]==ONE){
        _sprite2->setPosition(Vec2(winSize.width/2, winSize.height/5));
    }
*/
    
    //時間の積算
    _timer += dt;
    
    auto timerLabel = (Label*)getChildByTag(TAG_TIMER_LABEL);
    if (timerLabel)
    {
        //時間の表示
        timerLabel->setString(StringUtils::format("%0.2fs", _timer));
    }

    //ゲーム終了判定
    bool finish = true;
    for (int tag = 1; tag <= 10; tag++)
    {
        auto node = getChildByTag(tag);
        if (node)
        {
            //場にカードがある
            finish = false;
            break;
        }
    }
    
    if (finish)
    {
        //ゲーム終了
        unscheduleUpdate();
    }
}
