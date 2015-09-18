#import <UIKit/UIKit.h>

@interface BatteryViewController : UIViewController

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *batteryLevelLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *batteryStateLabel;


- (void)startBatteryMonitor;
- (void)stopBatteryMonitor;


@end
