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




bool NewsSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    news_type_name =
    {
        "ビジネス＋ITニュース", // http://www.sbbit.jp/
        "日経ビジネス", // http://business.nikkeibp.co.jp/?rt=nocnt
        "スポーツナビ",  // http://sports.yahoo.co.jp/
        "ニュース",
        "書籍情報",
        "ビデオメッセージ",
        "メッセージ",
        "住宅情報",
        "yahooニュース"
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
        setPosition(Vec2(visibleSize.width+250, visibleSize.height/2));
        setTexture(getFileName(_card.type));
        setTag(_card.number);
        
        //テキストの表示
        Size at = getContentSize();
        at.height = at.height/2;
        std::string temp = news_type_name[_card.number];
        if (temp.size() > 0){
            auto number = Label::createWithSystemFont(temp, "Arial", 24);
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
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    auto _bg2 = LayerColor::create(Color4B(0x11,0x11,0x11,0x11), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    
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
    Size winSize = Director::getInstance()->getVisibleSize();
    auto _bg2 = LayerColor::create(Color4B(0,128,128,128), winSize.width, winSize.height);
    this->addChild(_bg2);

    news_type_name =
    {
        "ビジネス＋ITニュース", // http://www.sbbit.jp/
        "日経ビジネス", // http://business.nikkeibp.co.jp/?rt=nocnt
        "スポーツナビ",  // http://sports.yahoo.co.jp/
        "ニュース",
        "書籍情報",
        "ビデオメッセージ",
        "メッセージ",
        "住宅情報",
        "yahooニュース"
    };
    
    initCards();
    showInitCards();
}


void InfoController::startWebView(int type)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto webView = cocos2d::experimental::ui::WebView::create();

    webView->setAnchorPoint(Point(0.5f, 0.5f));
    webView->setContentSize(Size(visibleSize.width * 0.85f, visibleSize.height * 0.85f));
    webView->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
    
    switch (type) {
        case 0:
            webView->loadURL("http://www.sbbit.jp/");
            break;
        case 1:
            webView->loadURL("http://business.nikkeibp.co.jp/?rt=nocnt");
            break;
            
        default:
            webView->loadURL("http://sports.yahoo.co.jp/");
            break;
            break;
    }

    this->addChild(webView, 1);
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

    startWebView(indetifier);

}

void InfoController::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void InfoController::update(float dt)
{
    
}
