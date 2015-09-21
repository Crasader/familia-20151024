#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "MediaScene.h"
#include "EstateScene.h"
#include "InfoScene.h"


#define CARD_NUM 13 //1種類あたりのカード枚数
#define CARD_TYPE_NUM 4 //カードの種類

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

// InfoScene
#define MESSAGE_MOTHER  "母親からの\nお知らせ" // 1
#define MESSAGE_FATHER  "父親からの\nお知らせ" // 2
#define MESSAGE_GRANMOTHER  "祖母からの\nお知らせ" // 3
#define MESSAGE_BOY "息子からの\nお知らせ"  // 4
#define MESSAGE_News "ニュース"  // 5
#define MESSAGE_BOOKS "書籍情報"    // 6
// MediaScene
#define MESSAGE_VIDEO_MESSAGE "ビデオ\nメッセージ"   // 10
#define MESSAGE_MESSAGE "メッセージ"  // 11
#define MESSAGE_TELEPHONE "電話"    // 12
// EstateScene
#define MESSAGE_REAL_ESTATE "住宅情報" // 20
// InfoScene
#define MESSAGE_COMSUMPTION "消費電力"  // 30
#define MESSAGE_CHARGE "蓄電"   // 31
#define MESSAGE_SCHEDULE "スケジュール"  // 13




//カードの種類
enum CardType
{
    Clubs = 0,
    Diamonds,
    Hearts,
    Spades
};

//カード
struct Card
{
    int number;
    CardType type;
};

//カードを表示する位置
struct PosIndex
{
    int x;
    int y;
};

class CardSprite : public cocos2d::Sprite
{
protected:
    std::string getFileName(CardType cardType); //表画像ファイル名取得
    void showNumber(); //カードのマークと数字を表示

public:
    virtual bool init(); //初期化処理
    void onEnter() override; //表示前処理
    CREATE_FUNC(CardSprite); //create関数作成マクロ

    CC_SYNTHESIZE(Card, _card, Card); //カード情報
    CC_SYNTHESIZE(PosIndex, _posIndex, PosIndex); //表示位置

    void moveBackToInitPos(); //元の位置に移動する
    void moveToTrash(); //カードを捨てる
    void moveToInitPos (); //最初の位置に移動する
};

class HelloWorld : public cocos2d::Layer
{
protected:
    std::vector<Card> _cards; //カード情報
    CardSprite* _firstCard; //最初にタップされたカード
    float _timer; //経過時間
    cocos2d::Sprite* _sprite1;
    cocos2d::Sprite* _sprite2;
    cocos2d::Sprite* _sprite1_emotion;
    cocos2d::Sprite* _sprite2_emotion;
    cocos2d::Label* _label1;
    cocos2d::Label* _label2;
    int sts_sprite1;
    int sts_sprite2;
    
    int _target_status[2];
    std::vector<std::string> emotion_status;
    std::vector<std::string> family_menber;

    
    void initCards(); //カードを初期化する
    Card getCard(); //カードを取得する
    void createCard(PosIndex posIndex); //カードを作成する
    void showInitCards(); //ゲーム開始時にカードを10枚表示する
    void initGame(); //ゲームを初期化する
    CardSprite* getTouchCard(cocos2d::Touch *touch); //タップされたカードを取得
    void showButton(); //ボタンを表示する
    void initTrash(); //ゴミカードを初期化する
    void onTapButton(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent); //ボタンがタップされたときに呼ばれる
    void showBackCards(); //カードの山を表示する
    void showTimerLabel(); //経過時間を表示
    
    void Action01(float frame);
    void Action02(float frame);
    void Sequence1(int sts);
    void Sequence2(int sts);

public:
    //HelloWorldクラスのシーンを作成する
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* scene();

    //初期化処理を行う
    virtual bool init();  
    
    //create関数作成マクロ
    CREATE_FUNC(HelloWorld);

    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};

#endif // __HELLOWORLD_SCENE_H__
