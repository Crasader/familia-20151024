/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"

@interface AppController (){
    
    
}
@end

@implementation AppController


#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;


- (void)init_twilio
{
    // ACCOUNT SID
//    AC533b4bbecccf6f735a0eb5d8669a8d9c
    // AUTH TOKEN
//    1b8b9fcacfbb0d596c5289457d2cc9e8
#if TARGET_IPHONE_SIMULATOR
    NSString *name = @"tommy";
#else
    NSString *name = @"jenny";
#endif
    //check out https://github.com/twilio/mobile-quickstart to get a server up quickly
    NSString *urlString = [NSString stringWithFormat:@"http://companyfoo.com/token?client=%@", name];
    NSURL *url = [NSURL URLWithString:urlString];
    
//    NSURL *url = [NSURL URLWithString:@"http://companyfoo.com/1b8b9fcacfbb0d596c5289457d2cc9e8"];
    NSError *error = nil;
    NSString *token = [NSString stringWithContentsOfURL:url encoding:NSUTF8StringEncoding error:&error];
    if (token == nil) {
        NSLog(@"Error retrieving token: %@", [error localizedDescription]);
    } else {
        _phone = [[TCDevice alloc] initWithCapabilityToken:token delegate:nil];
    }
}

- (void)dialButtonPressed
{
    _connection = [_phone connect:nil delegate:nil];
}

- (void)hangupButtonPressed
{
    [_connection disconnect];
}

- (void)device:(TCDevice *)device didReceiveIncomingConnection:(TCConnection *)connection
{
    if (device.state == TCDeviceStateBusy) {
        [connection reject];
    } else {
//        _connection = [connection accept];
    }
}

- (void)deviceDidStartListeningForIncomingConnections:(TCDevice*)device
{
    NSLog(@"Device: %@ deviceDidStartListeningForIncomingConnections", device);
}

- (void)device:(TCDevice*)device didStopListeningForIncomingConnections:(NSError*)error
{
    NSLog(@"Device: %@ didStopListeningForIncomingConnections: %@", device, error);
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    cocos2d::Application *app = cocos2d::Application::getInstance();
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                         pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:NO];

    // Use RootViewController manage CCEAGLView 
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];

    // Twilio 初期化
    [self init_twilio];
/*
    self.btlCentralManager = [[BTLECentralViewController alloc] init];
    [self.btlCentralManager initBtlCentralManager];

    self.btlPeripheraManager = [[BTLEPeripheralViewController alloc] init];
    [self.btlPeripheraManager initBtlPeripheraManager];
*/
    
    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    app->run();

    return YES;
}


/*
 //加速度センサーを定義
 self.accelerometerManager = [[AccelerometerViewController alloc] init];
 [self.accelerometerManager control_accelerometer];
 
 // 位置情報
 self.altitudeManager = [[AltitudeViewController alloc] init];
 [self.altitudeManager startLocationManager];
 //    [self.altitudeManager stopLocationManager];
 
 // 音声コントローラ
 self.audioManager = [[AudioViewController alloc] init];
 [self.audioManager startUpdatingVolume];
 //    [self.audioManager stopUpdatingVolume];
 
 // バッテリーコントローラ
 self.batteryManager = [[BatteryViewController alloc] init];
 [self.batteryManager startBatteryMonitor];
 //    [self.batteryManager stopBatteryMonitor];
 
 // 輝度コントローラ
 self.brightnessManager = [[BrightnessViewController alloc] init];
 [self.brightnessManager startBrightness];
 //    [self.brightnessManager stopBrightness];
 
 // face detection コントローラ
 self.faceDetectionManager = [[FaceDetectionViewController alloc] init];
 [self.faceDetectionManager startFaceDetection];
 
 // 向き方向コントローラ
 self.headingManager = [[HeadingViewController alloc] init];
 [self.headingManager startLocationManager];
 //    [self.headingManager stopLocationManager];
 
 // 位置情報コントローラ
 self.locationManager = [[LocationViewController alloc] init];
 [self.locationManager startLocationManager];
 //    [self.locationManager stopLocationManager];
 
 // モーションコントローラ
 self.motionManager = [[MotionActivityViewController alloc] init];
 [self.motionManager startStepCountingManager];
 //    [self.motionManager stopStepCountingManager];
 
 // コントローラ
 self.proximityManager = [[ProximityViewController alloc] init];
 [self.proximityManager startProximityMonitor];
 [self.proximityManager stopProximityMonitor];
 
 // シェイクコントローラ
 self.shakeManager = [[ShakeViewController alloc] init];
 [self.shakeManager startLocationManager];
 
 // スピードコントローラ
 self.speedManager = [[SpeedViewController alloc] init];
 [self.speedManager startLocationService];
 [self.speedManager stopLocationService];
 */



- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
