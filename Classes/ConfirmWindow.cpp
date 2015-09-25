//
//  ConfirmWindow.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/25.
//
//

#include "ConfirmWindow.h"


USING_NS_CC;

ConfirmWindow *ConfirmWindow::create()
{
    ConfirmWindow *ret = new (std::nothrow) ConfirmWindow();
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

bool ConfirmWindow::init()
{
    if ( !ModalWindow::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //ダイアログ背景の設定
    _background = Sprite::create("cocosui/scrollviewbg.png");
    _background->setPosition( Vec2( visibleSize.width * 0.5, visibleSize.height * 0.5 ) );
    this->addChild( _background );
    
    Size size = _background->getContentSize();
    
    auto yes = MenuItemImage::create( "cocosui/CloseNormal.png",
                                     "cocosui/CloseSelected.png",
                                     [=](Ref*sender)
                                     {
                                         CCLOG("on Touch YES!!");
                                     });
    yes->setPosition( Vec2( size.width * 0.25, size.height * 0.2 ) );
    
    auto no = MenuItemImage::create( "cocosui/CloseNormal.png",
                                    "cocosui/CloseSelected.png",
                                    [=](Ref*sender)
                                    {
                                        CCLOG("on Touch NO!!!");
                                    });
    no->setPosition( Vec2( size.width * 0.75, size.height * 0.2 ) );
    
    auto menu = Menu::create( yes, no, NULL );
    menu->setPosition( Vec2::ZERO );
    _background->addChild( menu );
    
    return true;
}

void ConfirmWindow::close()
{
    ModalWindow::close();
}
