//
//  ScrollMenuView.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/23.
//
//

#include "ScrollMenuView.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

ScrollMenuView::ScrollMenuView() : ScrollView() {
    
}

ScrollMenuView* ScrollMenuView::create(ScrollMenu *menu) {
    ScrollMenuView* widget = new (std::nothrow) ScrollMenuView();
    if (widget && widget->init(menu))
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool ScrollMenuView::init(ScrollMenu *menu) {
    if(!ScrollView::init()) {
        return false;
    }
    
    this->setInnerContainerSize(menu->getContentSize());
    this->addChild(menu, 1, "menu");
    
    return true;
}

bool ScrollMenuView::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    // タッチ開始時の座標を取得しておく
    this->_touchStartPoint = touch->getLocationInView();
    return ScrollView::onTouchBegan(touch, unusedEvent);
}

void ScrollMenuView::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) {
    /*
     * タッチ開始時からの5.0f以上となった場合，子Nodeにセットしたメニューのスクロール中フラグを立てる
     * メニューをタップするだけのつもりでも多少タッチが移動してしまう場合を考慮し，
     * 5.0f以下の距離の移動ではメニューを有効とする
     */
    if(5.0f < touch->getLocationInView().distance(this->_touchStartPoint)) {
        ScrollMenu* menu = (ScrollMenu*)this->getChildByName("menu");
        menu->setMenuInMoving();
    }
    ScrollView::onTouchMoved(touch, unusedEvent);
}