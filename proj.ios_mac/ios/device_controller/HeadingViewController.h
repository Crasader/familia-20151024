
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@interface HeadingViewController : UIViewController <CLLocationManagerDelegate>
{
    CLLocationManager *_locationManager;
}

@property (unsafe_unretained, nonatomic) IBOutlet UITextField *textField;


- (void)startLocationManager;
- (void)stopLocationManager;

@end
