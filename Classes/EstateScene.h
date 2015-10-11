//
//  EstateScene.h
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/13.
//
//

#ifndef __Card13__EstateScene__
#define __Card13__EstateScene__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "NetworkLibCurl.h"
#include "ui/UIVideoPlayer.h"
#include "HelloWorldScene.h"


#define  BASIC_REFORM_INSPECT 0x01 // 住まいの隠れた問題点も発見。
#define  BASIC_REFORM_FLOW 0x02 // リフォームの流れがわかる手順・段取
#define  BASIC_REFORM_MAINTENANCE 0x03 // 住まいのメンテナンススケジュール
#define  BASIC_REFORM_QA 0x04 // リフォームの「？」がわかるQ&A
#define  EXPERIENCE_BUILDING 0x0B // 住まい体験
#define  BUILD_SHOHIN_CONSULT 0x06 // 建築物の商品相談

#define  RENT_HOUSE 0x05 // 賃貸相談
#define  SEARCH_ESTATE_CONSULT 0x07 // 土地探し
#define  MADORI_CONSULT 0x08 // 間取り相談
#define  KAIGAI_MOVE_CONSULT 0x09 // 帰国前相談
#define  KEEP_TAX_BUILDING 0x0A //　相続税軽減に関する相談
#define  KEEP_OTHERMONEY_BUILDING 0x0B //　住まいの各種ほぞ金などの相談
#define  KEEP_OVERALL_BUILDING 0x0C //　住まいずくりに対する全般的な相談

#define  REGIST_KENCHIKU_CONSULT 0x0D // 建築相談
#define  KEEP_CHILD_BUILDING 0x0E // 子育てしやすい住宅
#define  KEEP_2SETAI_BUILDING 0x0F // 二世帯住宅
#define  KEEP_PET_BUILDING 0x10 // ペットと一緒の暮らし
#define  KEEP_HIRAYA_BUILDING 0x11 // 平屋の暮らし
#define  KEEP_CO_TINTAI_BUILDING 0x12 // 賃貸併用の暮らし
#define  KEEP_HOISPITAL_BUILDING 0x13 //　医院併用の暮らし
#define  KEEP_1ROOM_RENT_BUILDING 0x14 //　１部屋賃貸（習い事教室）の暮らし
#define  KEEP_RENT_MYHOME_BUILDING 0x15 //　マイホーム借り上げ制度
#define  KEEP_SHUNOU_BUILDING 0x16 // 収納上手な暮らし
#define  KEEP_LOVELY_KITCHIN_BUILDING 0x17 // 愛着キッチンのある暮らし
#define  KEEP_SMART_BUILDING 0x18 // ダイワハウスのスマートハウス
#define  KEEP_TAIYOU_BUILDING 0x19 // 太陽発電のある暮らし
#define  KEEP_MOVIE_SOUND_BUILDING 0x1A // 映画、音楽のある暮らし
#define  KEEP_WOMAN_BUILDING 0x1B //　女性のための空間提案
#define  KEEP_DESIGNERS_BUILDING 0x1C //　デザイナーズ住宅
#define  KEEP_CESON_BUILDING 0x1D //　キャトル、セゾンが似合う住宅
#define  KEEP_GREEN_BUILDING 0x1E //　緑に囲まれた暮らし

// リフォーム
#define  KEEP_ENTRANCE_BUILDING 0x1F // 玄関
#define  KEEP_OUTSIDE_BUILDING 0x20 // 外観
#define  KEEP_UPPER_OUTSIDE_BUILDING 0x21 // 屋根
#define  KEEP_JAPANESE_BUILDING 0x22 // 和室
#define  KEEP_HOMETHEATER_BUILDING 0x23 // 防音、ホームシアター
#define  KEEP_LIVING_BUILDING 0x24 // リビング
#define  KEEP_TOILET_BUILDING 0x25 // トイレ
#define  KEEP_KITCHEN_BUILDING 0x26 // キッチン
#define  KEEP_LAVATORY_BUILDING 0x27 //　洗面室
#define  KEEP_BATH_BUILDING 0x28 // 風呂場

#define  KEEP_PROCE100_BUILDING 0x29 // リフォーム予算// 100万円未満
#define  KEEP_PRICE200_BUILDING 0x2A // 200万円未満
#define  KEEP_PRICE_OVER200_BUILDING 0x2B // 200万円から


class EstateController : public cocos2d::Layer
{
protected:
    
    
public:
    cocos2d::Sprite* _sprite1;
    static cocos2d::Scene* scene(int type);
    int user_status;

    //初期化処理を行う
    virtual bool init();
    void initGame(int type);
    void startWebView(const char* uri);
    void showSPrite();
    void showModal();
    void menuStartCallback(Ref* Sender);
    void dialogClose();
    
    void showButton1(std::vector<std::string> filename);
    void onTapButton1(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void showButton2(std::vector<std::string> filename);
    void onTapButton2(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void showButton3(std::vector<std::string> filename);
    void onTapButton3(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void showButton4(std::vector<std::string> filename);
    void onTapButton4(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void showButton5(std::vector<std::string> filename);
    void onTapButton5(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void showButton6(std::vector<std::string> filename);
    void onTapButton6(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton7(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTapButton8(Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    
    void postBuildingInterest(int buldingType);
    
    
    
    
    //create関数作成マクロ
    CREATE_FUNC(EstateController);
    
    void getEstateInfoContent();
    
    //タップイベント
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //毎フレーム呼ばれる関数
    void update(float dt) override;
};

#endif /* defined(__Card13__EstateScene__) */
