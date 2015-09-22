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


bool NewsSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    news_type_name =
    {
        "ソフトバンク　ビジネス＋ITニュース" // http://www.sbbit.jp/
        "日経ビジネス", // http://business.nikkeibp.co.jp/?rt=nocnt
        "スポーツナビ",  // http://sports.yahoo.co.jp/
        "ニュース",
        "書籍情報",
        "ビデオ\nメッセージ",
        "メッセージ",
        "住宅情報",
        "",
        "蓄電情報",
        "消費電力\n情報",
        "設備機器\n稼働情報",
        "お出かけ\nまとめ処理",
        "帰宅予約",
        "玄関ドア\nの開閉"
    };
    
    estate_site_type_name =
    {
        "テンポス", // http://www.temposmart.jp/
        
    };
    
    return true;
}

void NewsSprite::onEnter()
{
    Sprite::onEnter();
/*
    //画像の表示
    setTexture("card_back.png");
    
    //カードの位置とタグを指定
    setTag(_posIndex.x + _posIndex.y * 5 + 1);
*/
}

std::string NewsSprite::getFileName(int cardType)
{
    //ファイル名の取得
    std::string filename = "button.png";
    switch (cardType)
    {
        default: filename = "button.png"; break;
    }
    
    return filename;
}

void NewsSprite::showNumber()
{
    //表示する数字の取得
    std::string numberString;
    int temp_num = 0;
    
    
    numberString = news_type_name[temp_num];
    
    //ラベルの生成
    auto number = Label::createWithSystemFont(numberString, "Arial", 24);
    number->setPosition(Point(getContentSize() / 2));
    number->setTextColor((Color4B)Color4B::BLACK);
    addChild(number);
}

void NewsSprite::moveBackToInitPos()
{
    //移動アニメーションの作成
    float posX = CARD_1_POS_X + CARD_DISTANCE_X * _posIndex.x;
    float posY = CARD_1_POS_Y + CARD_DISTANCE_Y * _posIndex.y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    
    //アニメーションの実行
    runAction(move);
}

void NewsSprite::moveToTrash()
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

void NewsSprite::moveToInitPos()
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
    
        for (int number = 0; number <= NEWS_LIST_NUM; number++)
        {
            //カード情報の作成
            NewsBox card;
            card.number = number;
            card.type = 0;
            
            //カードを追加する
            _cards.push_back(card);
        }
}

NewsBox InfoController::getCard()
{
    auto card = _cards[0];
    
    return card;
}

void InfoController::createCard(BoxPosIndex posIndex)
{
    float posX = CARD_1_POS_X;
    float posY = CARD_1_POS_Y - CARD_DISTANCE_Y;
    
    //新しいカードを作成する
    auto card = NewsSprite::create();
    card->setNewsBox(getCard());
    card->setPosition(posX, posY);
    card->setBoxPosIndex(posIndex);
    card->moveToInitPos();
    addChild(card, ZORDER_SHOW_CARD);
}

void InfoController::showInitCards()
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
    
    for (int x = 0; x < 1; x++)
    {
        for (int y = 0; y < NEWS_LIST_NUM; y++)
        {
            BoxPosIndex posIndex;
            posIndex.x = x;
            posIndex.y = y;
            
            //カードの生成
            createCard(posIndex);
        }
    }
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool InfoController::init()
{
    if (!Layer::init())
    {
        return false;
    }
    

    
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

    initCards();
    initGame();
    
    
    return true;
}

void InfoController::getMessage(char* result)
{
    const char *post_command;
    
    post_command = "http://127.0.0.1:3000/send_message?type=2";
    
    Post(post_command);
    
    return;
}

void InfoController::initGame()
{
    char message[100];
    getMessage(message);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto _bg2 = LayerColor::create(Color4B(0,120,120,120), visibleSize.width, visibleSize.height);
    this->addChild(_bg2);

    Label *label[10];
    
    //テキストの設定　Label::createWithSystemFont("文字列", "フォントの種類", 文字サイズ);
    label[0] = Label::createWithSystemFont("TEST", "Marker Felt.ttf", 30);
    
    //画面の中央に表示
    label[0]->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label[0]);
    
    showInitCards();
    
    //update関数の呼び出しを開始
    scheduleUpdate();
    
}

void InfoController::startWebView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();

    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.85f, visibleSize.height * 0.85f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    webView->loadURL("http://www.daiwahouse.co.jp/jutaku/visit/vol113/index.html");
    this->addChild(webView, 1);
}


bool InfoController::onTouchBegan(Touch *touch, Event *unused_event)
{
    
    return true;
}

void InfoController::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(3.0f,  HelloWorld::scene()));
}


void InfoController::onTouchEnded(Touch *touch, Event *unused_event)
{
}

void InfoController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void InfoController::update(float dt)
{
    
}
