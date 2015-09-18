#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>

@interface AccelerometerViewController : UIViewController
{
    CMMotionManager *_motionManager;
}

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *xLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *yLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *zLabel;

- (void)control_accelerometer;

@end

