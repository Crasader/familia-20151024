//
//  ConfirmWindow.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/25.
//
//

#ifndef ConfirmWindow_hpp
#define ConfirmWindow_hpp

#include <stdio.h>
#include "ModalWindow.h"


USING_NS_CC;

class ConfirmWindow : public ModalWindow
{
public:
    
    static ConfirmWindow *create();
    virtual bool init();
    
    virtual void close();
};



#endif /* ConfirmWindow_hpp */
