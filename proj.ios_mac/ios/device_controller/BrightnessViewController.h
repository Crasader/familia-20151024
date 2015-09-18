
#import <UIKit/UIKit.h>

@interface BrightnessViewController : UIViewController

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *brightnessLabel;

- (IBAction)upButtonTapped:(id)sender;
- (IBAction)downButtonTapped:(id)sender;

- (void)startBrightness;
- (void)stopBrightness;

@end
