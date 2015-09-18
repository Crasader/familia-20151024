#import <UIKit/UIKit.h>

@interface FaceDetectionViewController : UIViewController

@property (strong, nonatomic) IBOutlet UIImageView *imageView;


- (void)startFaceDetection;

@end
