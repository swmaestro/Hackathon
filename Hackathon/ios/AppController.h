//
//  HackathonAppController.h
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 21..
//  Copyright __MyCompanyName__ 2012년. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

