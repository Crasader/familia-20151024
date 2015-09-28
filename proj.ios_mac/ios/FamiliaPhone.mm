//
//  FamiliaPhone.m
//  Card13
//
//  Created by Hiroki Ariji on 2015/09/19.
//
//

#import "FamiliaPhone.h"

@implementation FamiliaPhone


-(id)init
{
    if ( self = [super init] )
    {
        // Replace the URL with your Capabilities Token URL
        NSURL* url = [NSURL URLWithString:@"http://127.0.0.1:3000/send_message?type=100"];
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
                NSString* capabilityToken = [[[NSString alloc] initWithData:data
                                                                   encoding:NSUTF8StringEncoding]
                                             autorelease];
                
                _device = [[TCDevice alloc] initWithCapabilityToken:capabilityToken
                                                           delegate:nil];
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
    return self;
}


-(void)dealloc
{
    [_device release];
    [super dealloc];
}

-(void)connect
{
    _connection = [_device connect:nil delegate:nil];
    [_connection retain];
}


-(void)disconnect
{
    [_connection disconnect];
    [_connection release];
    _connection = nil;
}


@end