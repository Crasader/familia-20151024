#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>

@interface AudioViewController : UIViewController
{
    AudioQueueRef   _queue;     // 音声入力用のキュー
    NSTimer         *_timer;    // 監視タイマー
}

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *loudLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UITextField *peakTextField;
@property (unsafe_unretained, nonatomic) IBOutlet UITextField *averageTextField;

- (void)startUpdatingVolume;
- (void)stopUpdatingVolume;

@end
