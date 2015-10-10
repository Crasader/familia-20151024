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
    static void launchLocationController(int flag);

    static void connectPhamiliaPhone();
    static void disconnectPhamiliaPhone();
    static void initSendBtlPeripheraManager();
    static void sendBtlPeripheraManager();

    static void setNewLocation(float latitude,
                        float longitude,
                        float course,
                        float speed);
    static float getNewLocation_latitude();
    static float getNewLocation_longitude();
    static float getNewLocation_course();
    static float getNewLocation_speed();
    static void setDestance(float distance);
    static float getDestance();
    static void set_TargetLocationInfo_lati(float vl);
    static void set_TargetLocationInfo_longi(float val);
    static float get_TargetLocationInfo_lati();
    static float get_TargetLocationInfo_longi();


};


#endif /* Nativelauncher_hpp */
