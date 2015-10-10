//
//  InfoScene.h
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/16.
//
//

#ifndef __Card13__InfoScene__
#define __Card13__InfoScene__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#include <string.h>

#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "ui/UIWebView.h"
#include "HelloWorldScene.h"
#include "UIScene.h"
#include "ui/UIScrollView.h"
#include "Nativelauncher.h"




#define NEWS_LIST_NUM 9 //ニュースリスト数

#define NEWS_1_POS_X 70 //1番のカード位置(x)
#define NEWS_1_POS_Y 900 //1番のカード位置(y)
#define NEWS_DISTANCE_X 125 //カード間の距離(x方向)
#define NEWS_DISTANCE_Y 140 //カード間の距離(y方向)

#define ZORDER_SHOW_CARD 1 //表示しているカードのZオーダー
#define ZORDER_MOVING_CARD 2 //移動しているカードのZオーダー

#define MOVING_TIME 0.8 //カードのアニメーションの時間


//カード
struct NewsBox
{
    int number;
    int type;
};

//カードを表示する位置
struct BoxPosIndex
{
    int x;
    int y;
};

class NewsSprite : public cocos2d::Sprite
{
protected:
    std::vector<NewsBox> _cards; //カード情報
    NewsSprite* _firstCard; //最初にタップされたカード
//    std::vector<std::string> news_type_name;

public:
    virtual bool init(); //初期化処理
    void onEnter() override; //表示前処理
    CREATE_FUNC(NewsSprite); //create関数作成マクロ
    std::string getFileName(int boxType);
    void showNumber(int index);
    
    CC_SYNTHESIZE(NewsBox, _card, NewsBox); //カード情報
    CC_SYNTHESIZE(BoxPosIndex, _posIndex, BoxPosIndex); //表示位置
    
    void moveBackToInitPos(); //元の位置に移動する
    void moveToTrash(); //カードを捨てる
    void moveToInitPos (); //最初の位置に移動する

};




class UIListViewTest_Vertical : public UIScene
{
public:
    CREATE_FUNC(UIListViewTest_Vertical);
    
    UIListViewTest_Vertical();
    ~UIListViewTest_Vertical();
    
    virtual bool init() override;
    void selectedItemEvent(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(cocos2d::Ref* sender, cocos2d::ui::ScrollView::EventType type);
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
    
    std::vector<std::string> _array;
};




class InfoController : public cocos2d::Layer
{
protected:
    std::vector<NewsBox> _cards; //カード情報
    NewsSprite* _firstCard; //最初にタップされたカード
    std::vector<std::string> news_type_name;
    std::vector<std::string> news_type_uri;
    

public:
    static cocos2d::Scene* scene();
    cocos2d::ui::ScrollView* _scrollView;
    
    //初期化処理を行う
    virtual bool init();
    void initMenuItem();
    void initGame();
    void initGame_scroll();
    void getMessage(char* result);
    void startWebView(int type);

    //create関数作成マクロ
    CREATE_FUNC(InfoController);
    
    void initCards();
    NewsBox getCard(int index);
    void createCard(BoxPosIndex posIndex);
    void showInitCards();
    NewsSprite* getTouchCard(cocos2d::Touch *touch);
    void getTargetStatus();
    void getTargetUri();
    void playEffect();
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    
    void showButton1(std::string wirding, int i);
    void onTapButton1(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton2(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton3(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton4(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton5(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton6(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton7(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton8(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton9(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};


#endif /* defined(__Card13__InfoScene__) */
