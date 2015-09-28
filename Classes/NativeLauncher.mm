//
//  NativeLauncher.m
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/24.
//
//

#import <Foundation/Foundation.h>

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



