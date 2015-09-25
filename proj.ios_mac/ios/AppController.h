#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "HousingApi.h"
#import "TwilioClient.h"
#import <CoreLocation/CoreLocation.h>
#import "AccelerometerViewController.h"
#import "AltitudeViewController.h"
#import "AudioViewController.h"
#import "BatteryViewController.h"
#import "BrightnessViewController.h"
#import "FaceDetectionViewController.h"
#import "HeadingViewController.h"
#import "LocationViewController.h"
#import "MotionActivityViewController.h"
#import "ProximityViewController.h"
#import "ShakeViewController.h"
#import "SpeedViewController.h"
//#import "BTLECentralViewController.h"
//#import "BTLEPeripheralViewController.h"

@class RootViewController;

//#import <CoreBluetooth/CoreBluetooth.h>
//#import <CoreLocation/CoreLocation.h>


@interface AppController : NSObject <UIApplicationDelegate, UIAccelerometerDelegate, TCDeviceDelegate>
{
    UIWindow *window;
    TCDevice* _phone;
    TCConnection* _connection;
    
//    CBPeripheralManager *myPeripheralManager;
//    CBMutableCharacteristic *myCharacteristicsSample;

}

@property(nonatomic, readonly) RootViewController* viewController;

//@property (nonatomic) CLLocationManager *locationManager;
@property (unsafe_unretained, nonatomic) AccelerometerViewController *accelerometerManager;
@property (unsafe_unretained, nonatomic) AltitudeViewController *altitudeManager;
@property (unsafe_unretained, nonatomic) AudioViewController *audioManager;
@property (unsafe_unretained, nonatomic) BatteryViewController *batteryManager;
@property (unsafe_unretained, nonatomic) BrightnessViewController *brightnessManager;
@property (unsafe_unretained, nonatomic) FaceDetectionViewController *faceDetectionManager;
@property (unsafe_unretained, nonatomic) HeadingViewController *headingManager;
@property (unsafe_unretained, nonatomic) LocationViewController *locationManager;
@property (unsafe_unretained, nonatomic) MotionActivityViewController *motionManager;
@property (unsafe_unretained, nonatomic) ProximityViewController *proximityManager;
@property (unsafe_unretained, nonatomic) ShakeViewController *shakeManager;
@property (unsafe_unretained, nonatomic) SpeedViewController *speedManager;


- (void)launchNative;

@end

