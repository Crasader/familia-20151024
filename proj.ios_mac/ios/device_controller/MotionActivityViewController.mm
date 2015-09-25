
#import "MotionActivityViewController.h"


@interface MotionActivityViewController ()

@end

@implementation MotionActivityViewController

- (void)startStepCountingManager
{
    // 歩数カウント開始
    [self startStepCounting];
    // 移動状況取得開始
    [self startUpdatingActivity];
}

- (void)stopStepCountingManager
{
    // 取得を停止
    [_stepCounter stopStepCountingUpdates];
    [_activityManager stopActivityUpdates];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // 歩数カウント開始
    [self startStepCounting];
    
    // 移動状況取得開始
    [self startUpdatingActivity];
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    // 取得を停止
    [_stepCounter stopStepCountingUpdates];
    [_activityManager stopActivityUpdates];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)startStepCounting
{
    if (![CMStepCounter isStepCountingAvailable])
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                        message:@"CMStepCounter is unavailable."
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
        return;
    }
    
    _stepCounter = [[CMStepCounter alloc] init];
    [_stepCounter startStepCountingUpdatesToQueue:[NSOperationQueue mainQueue]
                                         updateOn:1
                                      withHandler:^(NSInteger numberOfSteps, NSDate *timestamp, NSError *error) {

                                          MotionController::countUp(numberOfSteps);
                                          
                                          
                                          
                                      }];

}

- (void)startUpdatingActivity
{
    if (![CMMotionActivityManager isActivityAvailable])
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                        message:@"CMMotionActivityManager is unavailable."
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
        return;
    }

    _activityManager = [[CMMotionActivityManager alloc] init];
    [_activityManager startActivityUpdatesToQueue:[NSOperationQueue mainQueue]
                                      withHandler:^(CMMotionActivity *activity) {

                                          MotionController::motionStatus(activity.confidence,
                                                                         activity.stationary,
                                                                         activity.walking,
                                                                         activity.running,
                                                                         activity.automotive,
                                                                         activity.unknown);
                                          
                                      }];

}

@end
