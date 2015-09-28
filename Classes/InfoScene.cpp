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


// UIListViewTest_Vertical

UIListViewTest_Vertical::UIListViewTest_Vertical()
: _displayValueLabel(nullptr)
{
    
}

UIListViewTest_Vertical::~UIListViewTest_Vertical()
{
}

bool UIListViewTest_Vertical::init()
{
//    if (UIScene::init())
//    {
        Size widgetSize = Director::getInstance()->getVisibleSize();
//        Size widgetSize = _widget->getContentSize();
        
        _displayValueLabel = cocos2d::ui::Text::create("Move by vertical direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                             widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        this->addChild(_displayValueLabel);
//        _uiLayer->addChild(_displayValueLabel);
        
        
        cocos2d::ui::Text* alert = cocos2d::ui::Text::create("ListView vertical", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(51,255,153));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        this->addChild(alert);
        
//        cocos2d::ui::Layout* root = static_cast<cocos2d::ui::Layout*>(_uiLayer->getChildByTag(81));
//
//        cocos2d::ui::Layout* background = dynamic_cast<cocos2d::ui::Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = Director::getInstance()->getVisibleSize();
        
        
        // create list view ex data
        
        for (int i = 0; i < 20; ++i)
        {
            std::string ccstr = StringUtils::format("listview_item_%d", i);
            _array.push_back(ccstr);
        }
        
        
        // Create the list view ex
        cocos2d::ui::ListView* listView = cocos2d::ui::ListView::create();
        // set list view ex direction
        listView->setDirection(ui::ScrollView::Direction::VERTICAL);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setContentSize(Size(240, 130));
        listView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                   (backgroundSize.width - listView->getContentSize().width) / 2.0f,
                                   (widgetSize.height - backgroundSize.height) / 2.0f +
                                   (backgroundSize.height - listView->getContentSize().height) / 2.0f));
        listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(UIListViewTest_Vertical::selectedItemEvent, this));
        listView->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(UIListViewTest_Vertical::selectedItemEventScrollView,this));
//        listView->setScrollBarPositionFromCorner(Vec2(7, 7));
        this->addChild(listView);
        
        
        // create model
        cocos2d::ui::Button* default_button = cocos2d::ui::Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
        default_button->setName("Title Button");
        
        cocos2d::ui::Layout* default_item = cocos2d::ui::Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setContentSize(default_button->getContentSize());
        default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
                                         default_item->getContentSize().height / 2.0f));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        ssize_t count = _array.size();
        for (int i = 0; i < count / 4; ++i)
        {
            listView->pushBackDefaultItem();
        }
        // insert default item
        for (int i = 0; i < count / 4; ++i)
        {
            listView->insertDefaultItem(0);
        }
        
        listView->removeAllChildren();
        
        Sprite* testSprite = Sprite::create("cocosui/backtotoppressed.png");
        testSprite->setPosition(Vec2(200,200));
        listView->addChild(testSprite);
        
        // add custom item
        for (int i = 0; i < count / 4; ++i)
        {
            cocos2d::ui::Button* custom_button = cocos2d::ui::Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setContentSize(default_button->getContentSize());
            
            cocos2d::ui::Layout *custom_item = cocos2d::ui::Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->addChild(custom_item);
        }
        // insert custom item
        Vector<cocos2d::ui::Widget*>& items = listView->getItems();
        ssize_t items_count = items.size();
        for (int i = 0; i < count / 4; ++i)
        {
            cocos2d::ui::Button* custom_button = cocos2d::ui::Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setContentSize(default_button->getContentSize());
            
            cocos2d::ui::Layout *custom_item = cocos2d::ui::Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
            custom_item->addChild(custom_button);
            custom_item->setTag(1);
            
            listView->insertCustomItem(custom_item, items_count);
        }
        
        // set item data
        items_count = items.size();
        for (int i = 0; i < items_count; ++i)
        {
            cocos2d::ui::Widget* item = listView->getItem(i);
            cocos2d::ui::Button* button = static_cast<cocos2d::ui::Button*>(item->getChildByName("Title Button"));
            ssize_t index = listView->getIndex(item);
            button->setTitleText(_array[index]);
        }
        
        // remove last item
        listView->removeChildByTag(1);
        
        // remove item by index
        items_count = items.size();
        listView->removeItem(items_count - 1);
        
        // set all items layout gravity
        listView->setGravity(cocos2d::ui::ListView::Gravity::CENTER_VERTICAL);
        
        // set items margin
        listView->setItemsMargin(2.0f);
        
        return true;
//    }
    
    return false;
}

void UIListViewTest_Vertical::selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            cocos2d::ui::ListView* listView = static_cast<cocos2d::ui::ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            cocos2d::ui::ListView* listView = static_cast<cocos2d::ui::ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            break;
        }
        default:
            break;
    }
}

void UIListViewTest_Vertical::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
{
    switch (type) {
        case ui::ScrollView::EventType::SCROLL_TO_BOTTOM:
            CCLOG("SCROLL_TO_BOTTOM");
            break;
        case ui::ScrollView::EventType::SCROLL_TO_TOP:
            CCLOG("SCROLL_TO_TOP");
            break;
        default:
            break;
    }
}



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
    //移動アニメーションの作成
    float posX = NEWS_1_POS_X + NEWS_DISTANCE_X * _posIndex.x;
    float posY = NEWS_1_POS_Y + NEWS_DISTANCE_Y * _posIndex.y;
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
    float posY = NEWS_1_POS_Y + NEWS_DISTANCE_Y * _posIndex.y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    
    //カード回転アニメーションの作成
    auto scale1 = ScaleTo::create(MOVING_TIME / 2, 1, 1);
    auto func1 = CallFunc::create([&](){
        //画像の表示
        setPosition(Vec2(visibleSize.width+250, visibleSize.height/2));
        setTexture(getFileName(_card.type));
        setTag(_card.number);
        
        
        printf("hog::%d",_card.number);
        
        //テキストの表示
        Size at = getContentSize();
        at.height = at.height/2;
        std::string temp = news_type_name[_card.number];
        if (temp.size() > 0){
            auto number = Label::createWithSystemFont(temp, "Arial", 24);
            //        auto number = Label::createWithSystemFont("testtest", "Arial", 24);
            number->setPosition(Point(at));
            number->setTextColor((Color4B)Color4B::WHITE);
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
//    card->setScale(20, 5);
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

void InfoController::selectTouchMode(Control::EventType controlEvent)
{
    switch (controlEvent) {
        case Control::EventType::TOUCH_DOWN:
            printf("TOUCH_DOWN");
            break;
        case Control::EventType::DRAG_INSIDE:
            printf("DRAG_INSIDE");
            _button1->setPosition(_button1->getPosition());
            break;
        case Control::EventType::DRAG_OUTSIDE:
            printf("DRAG_OUTSIDE");
            break;
        case Control::EventType::DRAG_ENTER:
            printf("DRAG_ENTER");
            break;
        case Control::EventType::DRAG_EXIT:
            printf("DRAG_EXIT");
            break;
        case Control::EventType::TOUCH_UP_INSIDE:
            printf("TOUCH_UP_INSIDE");
            break;
        case Control::EventType::TOUCH_UP_OUTSIDE:
            printf("TOUCH_UP_OUTSIDE");
            break;
        case Control::EventType::TOUCH_CANCEL:
            printf("TOUCH_CANCEL");
            break;
        default:
            break;
    }
}

void InfoController::buttonCallback(Ref *sender, Control::EventType controlEvent)
{
    Touch *touch = (Touch*)sender;

    Vec2 a = touch->getLocationInView();
    Vec2 b = _button1->getPosition();
    
    printf("%f::%f::",a.x,a.y);
    printf("%f::%f::",b.x,b.y);
    for(int i = 0;i < news_type_name.size();i++)
    {
        if(touch->getLocationInView() == _button1->getPosition())
        {
            printf("find it ! : %d ::", i);
        }
    }
    
    
    touch->getDelta();
    selectTouchMode(controlEvent);

    switch (controlEvent) {
        case Control::EventType::TOUCH_DOWN:
            printf("TOUCH_DOWN");
            break;
        case Control::EventType::DRAG_INSIDE:
            printf("DRAG_INSIDE");
            _button1->setPosition(_button1->getPosition()+touch->getDelta());
            break;
        case Control::EventType::DRAG_OUTSIDE:
            printf("DRAG_OUTSIDE");
            break;
        case Control::EventType::DRAG_EXIT:
            printf("DRAG_EXIT");
            break;
        case Control::EventType::TOUCH_UP_INSIDE:
            printf("TOUCH_UP_INSIDE");
            break;
        case Control::EventType::TOUCH_UP_OUTSIDE:
            printf("TOUCH_UP_OUTSIDE");
            break;
        case Control::EventType::TOUCH_CANCEL:
            printf("TOUCH_CANCEL");
            break;
        default:
            break;
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
    //スワイプしているカードの位置を変更
    _firstCard->setPosition(_firstCard->getPosition() + touch->getDelta());
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
