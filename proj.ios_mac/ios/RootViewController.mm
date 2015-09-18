/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "HousingApiConstant.h"
#import "HousingApi.h"

@implementation RootViewController


//主幹瞬時電力取得
- (IBAction)onInstantPower:(id)sender {
    
    //定義値からコマンドを生成
    NSString* command = [NSString stringWithFormat:kLocalCommandRestGet,
                         kLocalDeviceIdMainBoard, kLocalKeyInstantPower];
    //生成されるコマンド：/smart/rest/request?deviceid=lite.boardMeter_1_1&type=get&key=instantPower";
    
    //接続処理
    HousingApi* housingApi = [self sendCommand:command];
    
    if (housingApi != nil) {
        //接続成功してデータが取得できている場合
        //<data>タグ内の情報を取得します。　引数には、<data>タグまでのXMLタグを全て指定します。「resultset」「dataset」「data」を設定しています。
        NSObject* data = [housingApi getResponseData:kLocalElementResultset,
                          kLocalElementDataSet, kLocalElementData, nil];
        
        if ([data isKindOfClass:[NSDictionary class]]) {
            NSDictionary* dataDic = (NSDictionary*)data;
            NSString* result = dataDic[kLocalElementResult]; //dataタグ内の<result>の値　true
            NSString* key = dataDic[kLocalElementKey];       //dataタグ内の<key>の値　instantPower
            NSString* value = dataDic[kLocalElementValue];   //dataタグ内の<value>の値　15
            
            //結果表示
            NSString* response = [NSString stringWithFormat:@"%@ : %@\n%@ : %@\n%@ : %@\n",
                                  kLocalElementResult, result,
                                  kLocalElementKey, key,
                                  kLocalElementValue, value];
            
//            txtResult.text = response;
        }
    }
}

//
- (IBAction)onBranch:(id)sender {
    
    //取得対象の全ての分岐回路のKeyを生成
    NSMutableArray* branchKyes = [NSMutableArray array];
    for (int i = 1; i < 6; i++) {
        [branchKyes addObject:[NSString stringWithFormat:kLocalKeyBranchCircuit, i]];
    }
    //Keyに設定する、カンマ区切りの文字列を生成
    NSString* key = [branchKyes componentsJoinedByString:kLocalCommandDelimiter];
    
    //定義値からコマンドを生成
    NSString* command = [NSString stringWithFormat:kLocalCommandRestGet, kLocalDeviceIdMainBoard, key];
    //生成されるコマンド：/smart/rest/request?deviceid=lite.boardMeter_1_1&type=get&key=branchCircuit_1,branchCircuit_2branchCircuit_3,branchCircuit_4,branchCircuit_5";
    
    //接続処理
    HousingApi* housingApi = [self sendCommand:command];
    
    if (housingApi != nil) {
        //接続成功してデータが取得できている場合
        //<data>タグ内の情報を取得します。　引数には、<data>タグまでのXMLタグを全て指定します。「resultset」「dataset」「data」を設定しています。
        NSObject* datas = [housingApi getResponseData:kLocalElementResultset,
                           kLocalElementDataSet, kLocalElementData, nil];
        
        NSString* response = @"";
        if ([datas isKindOfClass:[NSArray class]]) {
            NSArray* dataList = (NSArray*)datas;
            for (NSDictionary* data in dataList) {
                NSString* result = data[kLocalElementResult]; //dataタグ内の<result>の値　true
                NSString* key = data[kLocalElementKey];       //dataタグ内の<key>の値　instantPower
                NSString* value = data[kLocalElementValue];   //dataタグ内の<value>の値　15
                
                //結果表示
                response = [response stringByAppendingFormat:@"%@ : %@\n%@ : %@\n%@ : %@\n",
                            kLocalElementResult, result,
                            kLocalElementKey, key,
                            kLocalElementValue, value];
            }
            
//            txtResult.text = response;
//            [txtResult flashScrollIndicators];
        }
    }
}

//エアコンの動作状態、温度設定、湿度設定、動作モード、風量設定、スイング設定を取得
- (IBAction)onAirconAll:(id)sender {
    //取得対象の全ての分岐回路のKeyを生成
    NSArray* airconKeys = @[kLocalKeyOperationStatus, kLocalKeyAirconTemperature,
                            kLocalKeyAirconHumidity, kLocalKeyCurrentMode,
                            kLocalKeyAirconAirFlow, kLocalKeyAirconSwing];
    //カンマ区切りの文字列を生成
    NSString* key = [airconKeys componentsJoinedByString:kLocalCommandDelimiter];
    //定義値からコマンドを生成
    NSString* command = [NSString stringWithFormat:kLocalCommandRestGet, kLocalDeviceIdAircon, key];
    //生成されるコマンド：/smart/rest/request?deviceid=lite.aircon_1_1&type=get&key=operationStatus,temeprature,humidity,currentMode,airFlow,swing";
    
    //接続処理
    HousingApi* housingApi = [self sendCommand:command];
    
    if (housingApi != nil) {
        //接続成功してデータが取得できている場合
        //<data>タグ内の情報を取得します。　引数には、<data>タグまでのXMLタグを全て指定します。「resultset」「dataset」「data」を設定しています。
        NSObject* datas = [housingApi getResponseData:kLocalElementResultset,
                           kLocalElementDataSet, kLocalElementData, nil];
        
        NSString* response = @"";
        if ([datas isKindOfClass:[NSArray class]]) {
            NSArray* dataList = (NSArray*)datas;
            for (NSDictionary* data in dataList) {
                NSString* result = data[kLocalElementResult]; //dataタグ内の<result>の値　true
                NSString* key = data[kLocalElementKey];       //dataタグ内の<key>の値　instantPower
                NSString* value = data[kLocalElementValue];   //dataタグ内の<value>の値　15
                
                //結果表示
                response = [response stringByAppendingFormat:@"%@ : %@\n%@ : %@\n%@ : %@\n",
                            kLocalElementResult, result,
                            kLocalElementKey, key,
                            kLocalElementValue, value];
            }
            
//            txtResult.text = response;
//            [txtResult flashScrollIndicators];
        }
    }
}

//エアコンの温度設定
- (IBAction)onAirconSet:(id)sender {
    //定義値からコマンドを生成
    NSString* command = [NSString stringWithFormat:kLocalCommandRestSet,
                         kLocalDeviceIdAircon, kLocalKeyAirconTemperature, @"20"];
    //生成されるコマンド：/smart/rest/request?deviceid=lite.aircon_1_1&type=set&key=temperature&value=20";
    
    //接続処理
    HousingApi* housingApi = [self sendCommand:command];
    
    if (housingApi != nil) {
        //接続成功してデータが取得できている場合
        //<data>タグ内の情報を取得します。　引数には、<data>タグまでのXMLタグを全て指定します。「resultset」「dataset」「data」を設定しています。
        NSObject* data = [housingApi getResponseData:kLocalElementResultset,
                          kLocalElementDataSet, kLocalElementData, nil];
        
        if ([data isKindOfClass:[NSDictionary class]]) {
            NSDictionary* dataDic = (NSDictionary*)data;
            NSString* result = dataDic[kLocalElementResult]; //dataタグ内の<result>の値　true
            NSString* key = dataDic[kLocalElementKey];       //dataタグ内の<key>の値　instantPower
            
            //結果表示
            NSString* response = [NSString stringWithFormat:@"%@ : %@\n%@ : %@\n",
                                  kLocalElementResult, result,
                                  kLocalElementKey, key];
            
//            txtResult.text = response;
//            [txtResult flashScrollIndicators];
        }
    }
}
//共通処理
- (HousingApi*) sendCommand:(NSString*)command {
    
    //画面の入力項目からIPアドレスとポート番号を取得
    NSString* ipAddress;// = txtIpAddress.text;
    NSString* portNo;// = txtPortNo.text;
    NSString* response = @"";
    
    HousingApi* housingApi = [[HousingApi alloc] init];
    //IPアドレス、ポート番号、コマンドを渡すと、ライブラリ内でHTTPリクエストを生成して送信し、応答メッセージを解析する。
    //戻り値には解析後の応答メッセージが格納されている。
    NSError* error;
    BOOL connectResulst = [housingApi sendCommand:ipAddress port:portNo command:command timeoutInterval:30 error:&error];
    
    if (connectResulst) {
        //応答メッセージから瞬時電力値を取得する
        //<result>タグの情報を取得します。　引数には、<result>タグまでのXMLタグを全て指定します。「resultset」「result」を設定しています。
        BOOL result = [housingApi getResponseResult:kLocalElementResultset, kLocalElementResult, nil];
        
        if (result) {
            //正常受信時の処理
            //呼び元によって必要な情報が違うので、応答メッセージを格納したApiを返却する
            return housingApi;
        } else {
            //エラー受信時の処理
            //<message>タグ内の情報を取得します。　引数には、<message>タグまでのXMLタグを全て指定します。「resultset」「message」を設定しています。
            NSString* error = (NSString*)[housingApi getResponseError:kLocalElementResultset, kLocalElementMessage, nil];
            response = [NSString stringWithFormat:@"%@ : %@\n%@ : %@",
                        kLocalElementResult, @"false",
                        kLocalElementMessage, error];
            
//            txtResult.text = response;
        }
    } else {
        //接続失敗時の処理
        //Apiが返却したエラー情報から、判断して処理を行う。
        if (error.userInfo != nil) {
            response = [NSString stringWithFormat:@"%@ : %@\n%@ : %@",
                        kLocalElementResult, @"false",
                        @"エラー内容", error.userInfo[NSLocalizedDescriptionKey]];
//            txtResult.text = response;
        }
    }
    return nil;
}

//テキストフィールドでEnter押下時にキーボードを非表示にするために追加されている処理
- (IBAction)didEndOnExit:(id)sender {
}

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


@end
