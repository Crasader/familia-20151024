
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@interface LocationViewController : UIViewController <CLLocationManagerDelegate>
{
    CLLocationManager *_locationManager;
}

@property (unsafe_unretained, nonatomic) IBOutlet UITextField *latTextField;
@property (unsafe_unretained, nonatomic) IBOutlet UITextField *lonTextField;


- (void)startLocationManager;
- (void)stopLocationManager;

@end
