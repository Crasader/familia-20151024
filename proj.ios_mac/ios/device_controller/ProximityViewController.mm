
#import "ProximityViewController.h"

@interface ProximityViewController ()

@end

@implementation ProximityViewController

- (void)startProximityMonitor
{
    // 近接センサオン
    [UIDevice currentDevice].proximityMonitoringEnabled = YES;
    // 近接センサ監視
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(proximitySensorStateDidChange:)
                                                 name:UIDeviceProximityStateDidChangeNotification
                                               object:nil];
}

- (void)stopProximityMonitor
{
    // 近接センサオフ
    [UIDevice currentDevice].proximityMonitoringEnabled = NO;
    // 近接センサ監視解除
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIDeviceProximityStateDidChangeNotification
                                                  object:nil];
}




- (void)viewDidLoad
{
    [super viewDidLoad];

    // 近接センサオン
    [UIDevice currentDevice].proximityMonitoringEnabled = YES;

    // 近接センサ監視
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(proximitySensorStateDidChange:)
                                                 name:UIDeviceProximityStateDidChangeNotification
                                               object:nil];
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    // 近接センサオフ
    [UIDevice currentDevice].proximityMonitoringEnabled = NO;

    // 近接センサ監視解除
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIDeviceProximityStateDidChangeNotification
                                                  object:nil];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)proximitySensorStateDidChange:(NSNotification *)notification
{
    NSLog(@"%d", [UIDevice currentDevice].proximityState);
}

@end
