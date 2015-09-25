//
//  ScrollMenu.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/23.
//
//

#ifndef ScrollMenu_hpp
#define ScrollMenu_hpp

#include <stdio.h>
/**
 * cocos2d::Menuクラスを継承したスクロール用Menuクラス
 */
#include <cocos2d.h>

USING_NS_CC;

class ScrollMenu : public Menu {
public:
    // オブジェクト作成用function
    static ScrollMenu* createWithArray(const Vector<MenuItem*>& arrayOfItems);
    // オブジェクト作成時実行処理
    bool initWithArray(const Vector<MenuItem*>& arrayOfItems);
    
    // タッチイベントがスクロール中であるフラグをたてる
    void setMenuInMoving();
    
    // オーバーライドするタッチ開始イベント
    bool onTouchBegan(Touch* touch, Event* event) override;
    // オーバーライドするタッチ終了イベント
    void onTouchEnded(Touch* touch, Event* event) override;
    
protected:
    // コンストラクタ
    ScrollMenu();
    
private:
    // 現在スクロール中かを判断するフラグ
    bool _inMoving;
};
#endif /* ScrollMenu_hpp */
