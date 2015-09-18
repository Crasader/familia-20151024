
#import "SpeedViewController.h"

@interface SpeedViewController ()

@property (unsafe_unretained, nonatomic) IBOutlet UITextField *speedTextField;
@property (unsafe_unretained, nonatomic) IBOutlet UITextField *kphTextField;
@property (strong, nonatomic) CLLocationManager *locationManager;

@end

@implementation SpeedViewController

- (void)startLocationService
{
    if ([CLLocationManager locationServicesEnabled])
    {
        // インスタンスを生成
        self.locationManager = [[CLLocationManager alloc] init];
        
        // デリゲートを設定
        self.locationManager.delegate = self;
        
        // 位置情報の取得開始
        [self.locationManager startUpdatingLocation];
    }
}

- (void)stopLocationService
{
    // 位置情報の取得停止
    if ([CLLocationManager locationServicesEnabled]) {
        [self.locationManager stopUpdatingLocation];
    }
}



- (void)viewDidLoad
{
    [super viewDidLoad];

    if ([CLLocationManager locationServicesEnabled])
    {
        // インスタンスを生成
        self.locationManager = [[CLLocationManager alloc] init];

        // デリゲートを設定
        self.locationManager.delegate = self;

        // 位置情報の取得開始
        [self.locationManager startUpdatingLocation];
    }
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    // 位置情報の取得停止
    if ([CLLocationManager locationServicesEnabled]) {
        [self.locationManager stopUpdatingLocation];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

// 位置情報が更新されるたびに呼ばれる
- (void)locationManager:(CLLocationManager *)manager
    didUpdateToLocation:(CLLocation *)newLocation
           fromLocation:(CLLocation *)oldLocation
{
    // Speedを更新
    self.speedTextField.text = [NSString stringWithFormat:@"%.2f", newLocation.speed];
    self.kphTextField.text = [NSString stringWithFormat:@"%.2f", newLocation.speed * 3.600];
}

@end
