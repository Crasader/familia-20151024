
#import <Foundation/Foundation.h>
#import "TCDevice.h"
#import "TCConnection.h"

@interface FamiliaPhone : NSObject
{
@private
    TCDevice* _device;
    TCConnection* _connection;
}

-(void)connect;
-(void)disconnect;

@end
