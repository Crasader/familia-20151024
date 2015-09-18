
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@interface SpeedViewController : UIViewController <CLLocationManagerDelegate>

- (void)startLocationService;
- (void)stopLocationService;

@end
