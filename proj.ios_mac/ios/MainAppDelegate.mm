#import "MainAppDelegate.h"
#import "AppDelegate.h"
#import "cocos2d.h"
#import "platform/CCGLView.h"

static AppDelegate s_sharedApplication;

@implementation MainAppDelegate
@synthesize viewController=_viewController;
@synthesize window=_window;

+ (MainAppDelegate *) GetInstance
{
    static MainAppDelegate* instance=NULL;
    if(instance==NULL)
    {
        instance=[[MainAppDelegate alloc] init];
    }
    return instance;
}
- (void)setUIWindow:(UIWindow *)window
{
    _window=window;
}
- (void)setUIViewController:(UIViewController *)viewController
{
    _viewController=viewController;
}

-(void)dealloc
{
    [mainView release];
    [_viewController release];
    [_window release];
    [super dealloc];
}

- (UIView*)GetMainView
{
    if(mainView==nil)
    {
        cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView((__bridge void *)_viewController.view);
        cocos2d::Director::getInstance()->setOpenGLView(glview);
     
        mainView = _viewController.view;
        [mainView setMultipleTouchEnabled:YES];
    }
    return mainView;
}
-(void)Start
{
    // 隐藏状态栏
    [[UIApplication sharedApplication] setStatusBarHidden:true];
    cocos2d::CCApplication::sharedApplication()->run();
}

- (void)applicationWillResignActive:(UIApplication *)application {
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    application.applicationIconBadgeNumber = 0;
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
    [self HideSystemAlertView];
}

-(void)HideSystemAlertView{
    NSArray* views =  [_viewController.view subviews];
    UIView* view;
    for (view in views) {
        if([view isKindOfClass: [UIAlertView class]])
        {
            [view setHidden:YES];
        }
    }
}

- (void)applicationWillTerminate:(UIApplication *)application {
}

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
//    cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)pToken {
    
}

- (void) exitApplication {
    [self performSelector:@selector(notExistCall)];
    abort();
}

@end
