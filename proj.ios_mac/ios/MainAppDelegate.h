#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#if (DEFINE_APPSTORE || DEFINE_DEVELOPMENT)
@interface MainAppDelegate : NSObject {
    UIView* mainView;
}
#else
@interface MainAppDelegate : NSObject {
    UIView* mainView;
}
#endif
@property(nonatomic,retain) UIViewController* viewController;
@property (nonatomic, retain) UIWindow *window;
+ (MainAppDelegate *) GetInstance;
- (void)setUIWindow:(UIWindow *)window;
- (void)setUIViewController:(UIViewController *)viewController;
- (UIView*)GetMainView;
- (void)Start;
- (void)applicationWillResignActive:(UIApplication *)application;
- (void)applicationDidBecomeActive:(UIApplication *)application;
- (void)applicationDidEnterBackground:(UIApplication *)application;
- (void)applicationWillEnterForeground:(UIApplication *)application;
- (void)applicationWillTerminate:(UIApplication *)application;
- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application;

- (void)exitApplication;

@end


//#ifdef __cplusplus
//extern "C" {
//#endif
//    MainAppDelegate* GetAppDelegate();
//#ifdef __cplusplus
//}
//#endif
