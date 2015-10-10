//
//  NativeLauncher.m
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/24.
//
//

#import <Foundation/Foundation.h>
#import "BTLEPeripheralViewController.h"

#include "NativeLauncher.h"
#include "AppController.h"

void NativeLauncher::launchNative()
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    [appController launchNative];
}

void NativeLauncher::launchMotionController(int flag)
{
    // モーションコントローラ
    MotionActivityViewController *motionManager = [[MotionActivityViewController alloc] init];
    if (flag == 0){
        [motionManager startStepCountingManager];
    }else{
        [motionManager stopStepCountingManager];
    }
}

LocationViewController *_locationManager;
float target_location_latitude;
float target_location_longitude;
float new_location_latitude;
float new_location_longitude;
float new_location_course;
float new_location_speed;
float new_destance;
float old_location;
void NativeLauncher::launchLocationController(int flag)
{
    _locationManager = [[LocationViewController alloc] init];
    if (flag == 0){
        [_locationManager startLocationManager];
    }else{
        [_locationManager stopLocationManager];
    }
}

void NativeLauncher::setDestance(float distance)
{
    new_destance = distance;
}
float NativeLauncher::getDestance()
{
    return new_destance;
}
void NativeLauncher::set_TargetLocationInfo_lati(float vl)
{
    target_location_latitude = vl;
}
void NativeLauncher::set_TargetLocationInfo_longi(float val)
{
    target_location_longitude = val;
}
float NativeLauncher::get_TargetLocationInfo_lati()
{
    return target_location_latitude;
}
float NativeLauncher::get_TargetLocationInfo_longi()
{
    return target_location_longitude;
}

void NativeLauncher::setNewLocation(float latitude,
                                    float longitude,
                                    float course,
                                    float speed)
{
    new_location_latitude = latitude;
    new_location_longitude = longitude;
    new_location_course = course;
    new_location_speed = speed;
}

float NativeLauncher::getNewLocation_latitude()
{
    return new_location_latitude;
}
float NativeLauncher::getNewLocation_longitude()
{
    return new_location_longitude;
}
float NativeLauncher::getNewLocation_course()
{
    return new_location_course;
}
float NativeLauncher::getNewLocation_speed()
{
    return new_location_speed;
}


void NativeLauncher::connectPhamiliaPhone()
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    [appController dialButtonPressed];
}

void NativeLauncher::disconnectPhamiliaPhone()
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    [appController hangupButtonPressed];
}


void NativeLauncher::initSendBtlPeripheraManager()
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    [appController initBTLEPheripher];
    [appController startAdvertising];
}

void NativeLauncher::sendBtlPeripheraManager()
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    [appController startAdvertising];
}

