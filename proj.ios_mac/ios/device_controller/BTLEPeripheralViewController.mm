



#import "BTLEPeripheralViewController.h"





#define NOTIFY_MTU      20



@implementation BTLEPeripheralViewController


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }

    return self;
}

- (void)initBtlPeripheraManager
{
//    [super viewDidLoad];

    _peripheralManager = [[CBPeripheralManager alloc] initWithDelegate:self queue:nil];

/*
    // Start up the CBPeripheralManager
    self.title = @"Peipheral";
    self.proximityUUID = [[NSUUID alloc] initWithUUIDString:@"8D4DB809-032F-4771-96F3-99BD5C25F924"];
    self.peripheralManager = [[CBPeripheralManager alloc] initWithDelegate:self queue:nil options:nil];
    if (self.peripheralManager.state == CBPeripheralManagerStatePoweredOn) {
        [self startAdvertising];
    }
*/
}

- (void)startAdvertisingBtlPeripheraManager
{
//    peripheral.name
    // All we advertise is our service's UUID
    [self.peripheralManager startAdvertising:@{ CBAdvertisementDataServiceUUIDsKey : @[[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]] }];

    // Start sending again
    [self sendData];

/*
    NSString *kLocalName = @"Familia_test";
    NSDictionary *advertising = @{
                              CBAdvertisementDataLocalNameKey: kLocalName,
                              CBAdvertisementDataServiceUUIDsKey: TRANSFER_SERVICE_UUID,
                              };
    [self.peripheralManager startAdvertising:advertising];
 */
}



- (void)destroyBtlPeripheraManager
{
    // Don't keep it going while we're not showing.
    [self.peripheralManager stopAdvertising];    
}


#pragma mark - Peripheral Methods


/** Required protocol method.  A full app should take care of all the possible states,
 *  but we're just waiting for  to know when the CBPeripheralManager is ready
 */
- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral
{
    // Opt out from any other state
    if (peripheral.state != CBPeripheralManagerStatePoweredOn) {
        return;
    }
    
    // We're in CBPeripheralManagerStatePoweredOn state...
    NSLog(@"self.peripheralManager powered on.");

    // ... so build our service.
    
    // Start with the CBMutableCharacteristic
    self.transferCharacteristic = [[CBMutableCharacteristic alloc] initWithType:[CBUUID UUIDWithString:TRANSFER_CHARACTERISTIC_UUID]
                                                                      properties:CBCharacteristicPropertyNotify
                                                                           value:nil
                                                                     permissions:CBAttributePermissionsReadable];

    // Then the service
    CBMutableService *transferService = [[CBMutableService alloc] initWithType:[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]
                                                                        primary:YES];
    
    // Add the characteristic to the service
    transferService.characteristics = @[self.transferCharacteristic];
    
    // And add it to the peripheral manager
    [self.peripheralManager addService:transferService];
    
}


/** Catch when someone subscribes to our characteristic, then start sending them data
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic
{
    NSLog(@"Central subscribed to characteristic");
    
    // Get the data
    self.dataToSend = [@"test_phamilai" dataUsingEncoding:NSUTF8StringEncoding]; //[self.textView.text dataUsingEncoding:NSUTF8StringEncoding];
    
    // Reset the index
    self.sendDataIndex = 0;
    
    // Start sending
    [self sendData];
}


/** Recognise when the central unsubscribes
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic
{
    NSLog(@"Central unsubscribed from characteristic");
}


/** Sends the next amount of data to the connected central
 */
- (void)sendData
{
    // First up, check if we're meant to be sending an EOM
    static BOOL sendingEOM = NO;
    
    if (sendingEOM) {
        
        // send it
        BOOL didSend = [self.peripheralManager updateValue:[@"EOM" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.transferCharacteristic onSubscribedCentrals:nil];
        
        // Did it send?
        if (didSend) {
            
            // It did, so mark it as sent
            sendingEOM = NO;
            
            NSLog(@"Sent: EOM");
        }
        
        // It didn't send, so we'll exit and wait for peripheralManagerIsReadyToUpdateSubscribers to call sendData again
        return;
    }
    
    // We're not sending an EOM, so we're sending data
    
    // Is there any left to send?
    
    if (self.sendDataIndex >= self.dataToSend.length) {
        
        // No data left.  Do nothing
        return;
    }
    
    // There's data left, so send until the callback fails, or we're done.
    
    BOOL didSend = YES;
    
    while (didSend) {
        
        // Make the next chunk
        
        // Work out how big it should be
        NSInteger amountToSend = self.dataToSend.length - self.sendDataIndex;
        
        // Can't be longer than 20 bytes
        if (amountToSend > NOTIFY_MTU) amountToSend = NOTIFY_MTU;
        
        // It did send, so update our index
        self.sendDataIndex += amountToSend;
        
        // Was it the last one?
        if (self.sendDataIndex >= self.dataToSend.length) {
            
            // It was - send an EOM
            
            // Set this so if the send fails, we'll send it next time
            sendingEOM = YES;
            
            // Send it
            BOOL eomSent = [self.peripheralManager updateValue:[@"EOM" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.transferCharacteristic onSubscribedCentrals:nil];
            
            if (eomSent) {
                // It sent, we're all done
                sendingEOM = NO;
                
                NSLog(@"Sent: EOM");
            }
            
            return;
        }
    }
}


/** This callback comes in when the PeripheralManager is ready to send the next chunk of data.
 *  This is to ensure that packets will arrive in the order they are sent
 */
- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral
{
    // Start sending again
    [self sendData];
}



@end


namespace btle_peripher_plugin
{

    BTLEPeripheralViewController *btlPeripheraManager = NULL;
    
    BTLEPeripheral::BTLEPeripheral()
    {
        btlPeripheraManager = [[BTLEPeripheralViewController alloc] init];
        [btlPeripheraManager initBtlPeripheraManager];
    }
    
    BTLEPeripheral::~BTLEPeripheral()
    {

    }
    
    void BTLEPeripheral::start(const char *peerID, const char *message)
    {
        NSLog(@"start");
        

    }
    
    void BTLEPeripheral::stop()
    {
        NSLog(@"stop");
        

    }
}
