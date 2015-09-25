//
//  ModalLayer.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/24.
//
//

#include "ModalWindow.h"


USING_NS_CC;

ModalWindow *ModalWindow::create()
{
    ModalWindow *ret = new (std::nothrow) ModalWindow();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool ModalWindow::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //ダイアログ外透過カラーレイヤー生成
    _colorSheet = LayerColor::create( Color4B( 255, 64, 64, 64 ) );
    addChild( _colorSheet, 0, 999 );
    
    //タッチイベント設定
    _setupEventListener();
    
    return true;
}

void ModalWindow::_setupEventListener()
{
    //タッチ用イベントリスナーの生成
    auto touchListener = EventListenerTouchOneByOne::create();
    
    //自身より奥にある部品へタッチイベントを流さないための設定
    touchListener->setSwallowTouches( true );
    
    //タッチダウンイベント設定
    touchListener->onTouchBegan = CC_CALLBACK_2( ModalWindow::onTouchBegan, this );
    //タッチリリースイベント設定
    touchListener->onTouchEnded = CC_CALLBACK_2( ModalWindow::onTouchEnded, this );
    
    //生成したイベントリスナーをディスパッチャーへ登録
    _eventDispatcher->addEventListenerWithSceneGraphPriority( touchListener, this );
}

bool ModalWindow::onTouchBegan( Touch *touch, Event *event )
{
    //ダイアログ背景設定されている場合
    if ( _background != nullptr )
    {
        //背景の矩形範囲を取得
        Rect rect = _background->getBoundingBox();
        //タッチ座標取得
        Vec2 location = touch->getLocation();
        
        //タッチ座標が背景矩形範囲内かの判定
        if ( rect.containsPoint( location ) )
        {
            CCLOG("on Touch Background!!");
            
            //ダイアログ削除は、ダイアログ外タッチ(カラーレイヤーのタッチ)で行うため
            //背景がタッチされた場合は、リリース処理を行わないためにfalseを返却する
            return false;
        }
    }
    
    CCLOG("on Touch ColorSheet!!");
    
    //「ダイアログ背景内のタッチがない == ダイアログ外タッチ」のため
    //trueを返却し、タッチリリース処理を行う
    return true;
}

void ModalWindow::onTouchEnded( Touch *touch, Event *event )
{
    //タッチリリースのタイミングで、ダイアログ削除要求
    this->close();
}

void ModalWindow::close()
{
    //自身の削除
    this->removeFromParentAndCleanup( true );
}