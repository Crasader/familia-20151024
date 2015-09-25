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

