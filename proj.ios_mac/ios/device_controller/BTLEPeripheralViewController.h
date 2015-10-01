#import <UIKit/UIKit.h>

#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreLocation/CoreLocation.h>
#import "TransferService.h"
#include "HelloWorldScene.h"



@interface BTLEPeripheralViewController : UIViewController <CBPeripheralManagerDelegate, CLLocationManagerDelegate>

- (void)initBtlPeripheraManager;
- (void)destroyBtlPeripheraManager;
- (void)startAdvertisingBtlPeripheraManager;


//@property (strong, nonatomic) IBOutlet UITextView       *textView;
//@property (strong, nonatomic) IBOutlet UISwitch         *advertisingSwitch;
@property (strong, nonatomic) CBPeripheralManager       *peripheralManager;
@property (strong, nonatomic) CBMutableCharacteristic   *transferCharacteristic;
@property (strong, nonatomic) NSData                    *dataToSend;
@property (nonatomic, readwrite) NSInteger              sendDataIndex;
@property (strong, nonatomic) IBOutlet NSUUID *proximityUUID;

@end


namespace btle_peripher_plugin {
    
    class BTLEPeripheral;
    
    
    class BTLEPeripheral
    {
    public:
        BTLEPeripheral();
        ~BTLEPeripheral();
        
        void start(const char *peerID, const char *message);
        void stop();
        
    };
    
} // End of namespace bluetooth_plugin
