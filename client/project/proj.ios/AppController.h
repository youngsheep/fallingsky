#import <UIKit/UIKit.h>
#import "WeiboSDK.h"

@class RootViewController;
@class weiboViewController;

@interface AppController : NSObject <UIApplicationDelegate,WeiboSDKDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    
    NSString* wbtoken;
    NSString* wbuin;
}

@property (strong, retain) NSString* wbtoken;
@property (strong, retain) NSString* wbuin;

@end

