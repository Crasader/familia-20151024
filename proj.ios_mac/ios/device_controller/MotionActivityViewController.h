
#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>

@interface MotionActivityViewController : UIViewController
{
    CMStepCounter           *_stepCounter;
    CMMotionActivityManager *_activityManager;
}

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *stepLabel;

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *stationaryLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *walkingLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *runningLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *automotiveLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *unknowLabel;

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *confidenceLabel;

- (void)startStepCountingManager;
- (void)stopStepCountingManager;

@end
