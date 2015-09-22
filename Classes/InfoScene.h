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

#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "ui/UIWebView.h"
#include "HelloWorldScene.h"

#define NEWS_LIST_NUM 9 //ニュースリスト数

#define CARD_1_POS_X 70 //1番のカード位置(x)
#define CARD_1_POS_Y 480 //1番のカード位置(y)
#define CARD_DISTANCE_X 125 //カード間の距離(x方向)
#define CARD_DISTANCE_Y 185 //カード間の距離(y方向)

#define BUTTON_POS_X 340 //ボタンの位置(x)
#define BUTTON_POS_Y 120 //ボタンの位置(y)

#define TIMER_LABEL_POS_X 550 //ラベルの位置(x)
#define TIMER_LABEL_POS_Y 120 //ラベルの位置(y)

#define ZORDER_SHOW_CARD 1 //表示しているカードのZオーダー
#define ZORDER_MOVING_CARD 2 //移動しているカードのZオーダー

#define TAG_TRUSH_CARD 11 //捨てられたカードのタグ
#define TAG_BACK_CARD 12 //カードの山のタグ
#define TAG_TIMER_LABEL 13 //時間ラベルのタグ
#define TAG_TIMER_ACTION1 14 //Action1
#define TAG_TIMER_ACTION2 15 //Action2

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
    std::string getFileName(int boxType); //表画像ファイル名取得
    void showNumber(); //カードのマークと数字を表示

    std::vector<std::string> news_type_name;
    std::vector<std::string> estate_site_type_name;
    
public:
    virtual bool init(); //初期化処理
    void onEnter() override; //表示前処理
    CREATE_FUNC(NewsSprite); //create関数作成マクロ
    
    CC_SYNTHESIZE(NewsBox, _card, NewsBox); //カード情報
    CC_SYNTHESIZE(BoxPosIndex, _posIndex, BoxPosIndex); //表示位置
    
    void moveBackToInitPos(); //元の位置に移動する
    void moveToTrash(); //カードを捨てる
    void moveToInitPos (); //最初の位置に移動する
};


class InfoController : public cocos2d::Layer
{
protected:
    std::vector<NewsBox> _cards; //カード情報
    
    
public:
    static cocos2d::Scene* scene();
    
    //初期化処理を行う
    virtual bool init();
    void initGame();
    void getMessage(char* result);
    void startWebView();

    //create関数作成マクロ
    CREATE_FUNC(InfoController);
    
    void initCards();
    NewsBox getCard();
    void createCard(BoxPosIndex posIndex);
    void showInitCards();

    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};


#endif /* defined(__Card13__InfoScene__) */
