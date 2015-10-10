
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

#import "Nativelauncher.h"

@interface LocationViewController : UIViewController <CLLocationManagerDelegate>
{
    CLLocationManager *_locationManager;
    
    CLLocation *new_location;
    CLLocation *old_location;
    
    
}

@property (unsafe_unretained, nonatomic) IBOutlet UITextField *latTextField;
@property (unsafe_unretained, nonatomic) IBOutlet UITextField *lonTextField;


- (void)startLocationManager;
- (void)stopLocationManager;

@end
