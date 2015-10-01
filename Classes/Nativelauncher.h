//
//  Nativelauncher.hpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/24.
//
//

#ifndef Nativelauncher_hpp
#define Nativelauncher_hpp

#include <stdio.h>


class NativeLauncher
{
public:
    static void launchNative();
    static void launchMotionController(int flag);

    static void connectPhamiliaPhone();
    static void disconnectPhamiliaPhone();
    static void initSendBtlPeripheraManager();
    static void sendBtlPeripheraManager();


};


#endif /* Nativelauncher_hpp */
