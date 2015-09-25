
#import "LocationViewController.h"

@interface LocationViewController ()

@end

@implementation LocationViewController

- (void)startLocationManager
{
    if ([CLLocationManager locationServicesEnabled])
    {
        // インスタンスを生成
        _locationManager = [[CLLocationManager alloc] init];
        
        // デリゲートを設定
        _locationManager.delegate = self;
        
        // 位置情報の取得開始
        [_locationManager startUpdatingLocation];
    }
}

- (void)stopLocationManager
{
    // 位置情報の取得停止
    if ([CLLocationManager locationServicesEnabled]) {
        [_locationManager stopUpdatingLocation];
    }
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

    if ([CLLocationManager locationServicesEnabled])
    {
        // インスタンスを生成
        _locationManager = [[CLLocationManager alloc] init];

        // デリゲートを設定
        _locationManager.delegate = self;

        // 位置情報の取得開始
        [_locationManager startUpdatingLocation];
    }
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    // 位置情報の取得停止
    if ([CLLocationManager locationServicesEnabled]) {
        [_locationManager stopUpdatingLocation];
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
    
    newLocation.coordinate.latitude;
    newLocation.coordinate.longitude;
    newLocation.course;
    newLocation.speed;
    newLocation.timestamp;
    
    oldLocation.coordinate.latitude;
    oldLocation.coordinate.longitude;
    oldLocation.course;
    oldLocation.speed;
    oldLocation.timestamp;
    
    // Replace the URL with your Capabilities Token URL
    NSURL* url = [NSURL URLWithString:@"http://127.0.0.1:3000/send_message?type=101"];
    NSURLResponse*  response = nil;
    NSError*    error = nil;
    NSData* data = [NSURLConnection sendSynchronousRequest:
                    [NSURLRequest requestWithURL:url]
                                         returningResponse:&response
                                                     error:&error];
    if (data)
    {
        NSHTTPURLResponse*  httpResponse = (NSHTTPURLResponse*)response;
        
        if (httpResponse.statusCode == 200)
        {

        }
        else
        {
            NSString*  errorString = [NSString stringWithFormat:
                                      @"HTTP status code %d",
                                      httpResponse.statusCode];
            NSLog(@"Error logging in: %@", errorString);
        }
    }
    else
    {
        NSLog(@"Error logging in: %@", [error localizedDescription]);
    }
    
    
}

@end
