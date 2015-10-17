#import "BatteryViewController.h"

@interface BatteryViewController ()

@end

@implementation BatteryViewController

- (void)startBatteryMonitor
{
    // バッテリー状態を監視できるようにする
    [UIDevice currentDevice].batteryMonitoringEnabled = YES;
    
    // バッテリー残量監視オン
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(batteryLevelDidChange:)
                                                 name:UIDeviceBatteryLevelDidChangeNotification
                                               object:nil];
    [self updateBatteryLevelLabel];
    
    // バッテリー充電状態監視オン
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(batteryStateDidChange:)
                                                 name:UIDeviceBatteryStateDidChangeNotification
                                               object:nil];
    
    [self updateBatteryStateLabel];
}

- (void)stopBatteryMonitor
{
    // バッテリー状態の監視を完了
    [UIDevice currentDevice].batteryMonitoringEnabled = NO;
    
    // バッテリー残量監視オフ
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIDeviceBatteryLevelDidChangeNotification
                                                  object:nil];
    // バッテリー充電状態監視オフ
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIDeviceBatteryStateDidChangeNotification
                                                  object:nil];
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

    // バッテリー状態を監視できるようにする
    [UIDevice currentDevice].batteryMonitoringEnabled = YES;

    // バッテリー残量監視オン
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(batteryLevelDidChange:)
                                                 name:UIDeviceBatteryLevelDidChangeNotification
                                               object:nil];
    [self updateBatteryLevelLabel];

    // バッテリー充電状態監視オン
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(batteryStateDidChange:)
                                                 name:UIDeviceBatteryStateDidChangeNotification
                                               object:nil];

    [self updateBatteryStateLabel];
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    // バッテリー状態の監視を完了
    [UIDevice currentDevice].batteryMonitoringEnabled = NO;

    // バッテリー残量監視オフ
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIDeviceBatteryLevelDidChangeNotification
                                                  object:nil];
    // バッテリー充電状態監視オフ
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIDeviceBatteryStateDidChangeNotification
                                                  object:nil];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)sendBatteryLevel:(float)value
{
    NSData *query = [[NSString stringWithFormat:@"type=60&battery=%.2f", value]
                     dataUsingEncoding: NSUTF8StringEncoding];
    NSMutableURLRequest *request = [NSMutableURLRequest
                                    requestWithURL:[NSURL URLWithString:@"http://54.199.206.175:3000/send_message/"]
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

- (void)sendBatteryStatus:(NSString*)value
{
    NSData *query = [[NSString stringWithFormat:@"type=61&battery=%@", value]
                     dataUsingEncoding: NSUTF8StringEncoding];
    NSMutableURLRequest *request = [NSMutableURLRequest
                                    requestWithURL:[NSURL URLWithString:@"http://54.199.206.175:3000/send_message/"]
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



#pragma mark -

- (void)updateBatteryLevelLabel
{
    // バッテリーの残量を取得する
    float batteryLevel = [UIDevice currentDevice].batteryLevel;

    [self sendBatteryLevel: batteryLevel];
}

- (void)updateBatteryStateLabel
{
    NSString *batteryStateString;

    // バッテリーの充電状態を取得する
    switch ([UIDevice currentDevice].batteryState)
    {
        case UIDeviceBatteryStateFull:
            batteryStateString = @"Full";
            break;

        case UIDeviceBatteryStateUnplugged:
            batteryStateString = @"Unplugged";
            break;

        case UIDeviceBatteryStateCharging:
            batteryStateString = @"Charging";
            break;

        case UIDeviceBatteryStateUnknown:
            batteryStateString = @"Unknown";
            break;

        default:
            break;
    }

    [self sendBatteryStatus: batteryStateString];
}

- (void)batteryLevelDidChange:(NSNotification *)notification
{
    [self updateBatteryLevelLabel];
}

- (void)batteryStateDidChange:(NSNotification *)notification
{
    [self updateBatteryStateLabel];
}

@end
