#import "GreePlatformDispatcher.h"
#import "GreePlatform.h"

#import "CCGreeAuthorizer.h"
#import "CCGreePlatform.h"

NS_CC_GREE_EXT_BEGIN


void CCGreeAuthorizer::authorize(){
	//authorize
    
    [GreePlatformDispatcher sharedGreePlatformDispatcher];
    
	[GreePlatform authorizeWithBlock:^(GreeUser* localUser, NSError* error){
		[[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
		if(error){
			NSLog(@"Authorization failed: %@.", [error localizedDescription]);
		}
		if(localUser){
		NSLog(@"Authorization finished with local user:%@.", localUser);
		}else{
			NSLog(@"Authorization finished with grade 0 user.");
		}
    }];
}

void CCGreeAuthorizer::logout(){
    if([GreePlatform sharedInstance].localUser){
    [GreePlatform revokeAuthorizationWithBlock:^(NSError *error) {
        NSLog(@"Logouted %s", __FUNCTION__);
        if(error){
            NSLog(@"RevokeAuthorization failed: %@.", [error localizedDescription]);
        }
    }];
    }
}


bool CCGreeAuthorizer::isAuthorized(){
    bool ret = false;
    ret = [GreePlatform isAuthorized];
    return ret;
}

CCString *CCGreeAuthorizer::getOAuthAccessToken(){
    NSString *pStr = [GreePlatform sharedInstance].accessToken;
    CCString *pCCStr = new CCString([pStr UTF8String]);
    pCCStr->autorelease();
    return pCCStr;
}

CCString *CCGreeAuthorizer::getOAuthAccessTokenSecret(){
    NSString *pStr = [GreePlatform sharedInstance].accessTokenSecret;
    CCString *pCCStr = new CCString([pStr UTF8String]);
    pCCStr->autorelease();
    return pCCStr;
}

void CCGreeAuthorizer::handleOnAuthorized(){
    NSLog(@"handleOnAuthorized()");
    CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
    if(delegate != NULL){
        delegate->authorizeAuthorized();
    }
}

void CCGreeAuthorizer::handleOnLogouted(){
    NSLog(@"handleOnLogouted()");
    CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
    if(delegate != NULL){
        delegate->logoutLogouted();
    }
}

NS_CC_GREE_EXT_END

