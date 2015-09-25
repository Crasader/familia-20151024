//
//  ScrollMenuView.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/23.
//
//

#ifndef ScrollMenuView_hpp
#define ScrollMenuView_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "ScrollMenu.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class ScrollMenuView : public ScrollView {
private:
    // タッチ開始時の座標
    Vec2 _touchStartPoint;
    
protected:
    // コンストラクタ
    ScrollMenuView();
    // オブジェクト作成時実行処理
    bool init(ScrollMenu* menu);
    
public:
    // オブジェクト作成用function
    static ScrollMenuView* create(ScrollMenu* menu);
    
    // オーバーライドするタッチ開始イベント
    bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    // オーバーライドするタッチ終了イベント
    void onTouchMoved(Touch *touch, Event *unusedEvent) override;
};

#endif /* ScrollMenuView_hpp */
