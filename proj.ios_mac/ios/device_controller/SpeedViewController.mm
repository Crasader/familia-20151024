
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

- (void)sendSpeedLevel:(float)new_value
                   float:(float)old_value
{
    NSString *baseURLString = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"APIBaseURL"];
    NSString *str3 = [baseURLString stringByAppendingString:@"/send_message/"];

    NSData *query = [[NSString stringWithFormat:@"type=62&new=%.2f&old=%.2f", new_value, old_value]
                     dataUsingEncoding: NSUTF8StringEncoding];
    NSMutableURLRequest *request = [NSMutableURLRequest
                                    requestWithURL:[NSURL URLWithString:str3]
                                    cachePolicy:NSURLRequestUseProtocolCachePolicy
                                    timeoutInterval:60.0];
    [request setHTTPMethod:@"POST"];
    [request setValue:@"application/x-www-form-urlencoded"
   forHTTPHeaderField:@"Content-Type"];
    [request setValue:[NSString stringWithFormat:@"%d", [query length]]
   forHTTPHeaderField:@"Content-Length"];
    [request setHTTPBody:query];
    
    NSHTTPURLResponse *httpResponse;
    
    /* HTTP リクエスト送信 */
    NSData *contents = [NSURLConnection sendSynchronousRequest:request
                                             returningResponse:&httpResponse error:nil];
    NSString *contentsString = [[NSString alloc] initWithData:contents encoding:NSUTF8StringEncoding];
    NSLog(@"contents:\n%@", contentsString);
    
    /* HTTP レスポンスヘッダ取得 */
    NSDictionary *headers = httpResponse.allHeaderFields;
    for (id key in headers) {
        NSLog(@"%@: %@", key, [headers objectForKey:key]);
    }
}


// 位置情報が更新されるたびに呼ばれる
- (void)locationManager:(CLLocationManager *)manager
    didUpdateToLocation:(CLLocation *)newLocation
           fromLocation:(CLLocation *)oldLocation
{

    [self sendSpeedLevel:(float)newLocation.speed
                   float:oldLocation.speed];

    
}

@end
