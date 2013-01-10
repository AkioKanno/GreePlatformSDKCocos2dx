#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCLabelTTF* pGreeButtonText;

CCSprite* pSprite;
CCSprite* pIcon = NULL;

int gThumbFlag = 0;
CCImage *pThumb = NULL;

int gFriendFlag = 0;
CCArray *pFriends = NULL;
int gNumOfFriend = 0;

#define FRIEND_X_OFFSET (100)
#define FRIEND_Y_OFFSET (100)

void HelloWorld::showResult(std::string* str1, std::string* str2){
    CCMessageBox(str1->c_str(), str2->c_str());
}


void HelloWorld::authorizeAuthorized(){
    CCLog("++++++ %s", __func__);
    CCGreeUser *user = CCGreePlatform::getLocalUser();

    std::string str1 = "Callback";
    std::string str2 = "authorize Success";
    showResult(&str2, &str1);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    
    CCMoveTo *action = CCMoveTo::actionWithDuration(0.5f, ccp(0, size.height - 100));
    pSprite->runAction(action);
    
    CCMenu* pMenu = CCMenu::create(NULL, NULL);
    
    // User Information
    CCSprite *pSUser = CCSprite::create("friends.png");
    pSUser->setPosition( ccp(size.width/2 - 200, size.height - 120) );
    this->addChild(pSUser, 0);
    CCLabelTTF *textUser = CCLabelTTF::create("Get User Info", "Thonburi", 50);
    CCMenuItemLabel* pUser = CCMenuItemLabel::create(textUser, this, menu_selector(HelloWorld::menuUserCallback));
    pUser->setPosition(ccp(size.width/2 + 40, size.height - 120));
    
    
    // Friend Infomation
    CCSprite *pSFri = CCSprite::create("friends.png");
    pSFri->setPosition( ccp(size.width/2 - 200, size.height - 200) );
    this->addChild(pSFri, 0);
    CCLabelTTF *textFri = CCLabelTTF::create("Get Friend Info", "Thonburi", 50);
    CCMenuItemLabel* pFri = CCMenuItemLabel::create(textFri, this, menu_selector(HelloWorld::menuFriendCallback));
    pFri->setPosition(ccp(size.width/2 + 40, size.height - 200));
    
    
    CCLabelTTF *textLogout = CCLabelTTF::create("Logout User", "Thonburi", 50);
    CCMenuItemLabel* pLogout = CCMenuItemLabel::create(textLogout, this, menu_selector(HelloWorld::menuLogoutCallback));
    pLogout->setPosition(ccp(size.width/2 + 40, 50));
    
    
    pMenu->setPosition(CCPointZero);
    
    pMenu->addChild(pUser, 1000);
    //pMenu->addChild(pPay, 1001);
    pMenu->addChild(pFri, 1002);
    //pMenu->addChild(pAch, 1003);
    //pMenu->addChild(pLea, 1004);
    pMenu->addChild(pLogout, 1010);
    
    this->addChild(pMenu, 1);
    //authFlag = 1;


}

// User
void HelloWorld::loadThumbnailSuccess(CCGreeUser* user, CCImage *img){
    CCLog("++++++ %s", __func__);
    std::string str1 = "Callback";
    std::string str2 = "loadThumbnail Success";
    showResult(&str2, &str1);
    pThumb = img;
    gThumbFlag = 1;
}


void HelloWorld::loadFriendsSuccess(CCGreeUser *user, int index, int count, CCArray *userArray){
    CCLog("++++++ %s", __func__);
    std::string str1 = "Callback";
    std::string str2 = "loadFriends Success";
    showResult(&str2, &str1);
    gFriendFlag = 1;
    pFriends = userArray;
    CCObject *it;
    CCARRAY_FOREACH(userArray, it){
        CCGreeUser *user = dynamic_cast<CCGreeUser *>(it);
        dumpUserInfo(user);
        //CCLog(" name %s", user->getNickname()->getCString());
    }
    gNumOfFriend = count;
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    // GreeButton
    pGreeButtonText = CCLabelTTF::create("Log in", "Thonburi", 34);
    pGreeButtonText->setPosition(ccp(size.width - 100, size.height - 40));
    this->addChild(pGreeButtonText, 1);
    CCMenuItemImage *pGree = CCMenuItemImage::create("gree.png", "gree.png", this, menu_selector(HelloWorld::menuGreeButtonCallback));
    pGree->setPosition(ccp(size.width - 100, size.height - 100));
    CCMenu* pGreeMenu = CCMenu::create(pGree, NULL);
    this->addChild(pGreeMenu, 1);
    pGreeMenu->setPosition(CCPointZero);
    pGree->setScaleY(3.0);
    pGree->setScaleX(3.0);
 
    
    // Set Scheduled Func
    this->schedule(schedule_selector(HelloWorld::Func), 1.0);
    
    return true;
}

void HelloWorld::dumpUserInfo(CCGreeUser *user){
    CCString *nickName = user->getNickname();
    CCString *dispName = user->getDisplayName();
    CCString *id = user->getId();
    CCString *region = user->getRegion();
    CCString *subRegion = user->getSubregion();
    CCString *lang = user->getLanguage();
    CCString *timeZone = user->getTimezone();
    CCString *me = user->getAboutMe();
    CCString *birthDay = user->getBirthday();
    //CCString *url = pUser->getProfileUrl();
    //CCLog("++++++ ProfileUrl %s", url->getCString());
    CCString *gender = user->getGender();
    CCString *age = user->getAge();
    CCString *blood = user->getBloodType();
    bool hasApp = user->getHasApp();
    CCString *hash = user->getUserHash();
    CCString *type = user->getUserType();
    int grade = user->getUserGrade();
    CCLog("++++++ NickName %s", nickName->getCString());
    CCLog("++++++ DisplayName %s", dispName->getCString());
    CCLog("++++++ Id %s", id->getCString());
    CCLog("++++++ Region %s", region->getCString());
    CCLog("++++++ Subregion %s", subRegion->getCString());
    CCLog("++++++ Language %s", lang->getCString());
    CCLog("++++++ Timezone %s", timeZone->getCString());
    CCLog("++++++ me %s", me->getCString());
    CCLog("++++++ BirthDay %s", birthDay->getCString());
    CCLog("++++++ Gender %s", gender->getCString());
    CCLog("++++++ Age %s", age->getCString());
    CCLog("++++++ BloodType %s", blood->getCString());
    CCLog("++++++ HasApp %d", hasApp);
    CCLog("++++++ UserHash %s", hash->getCString());
    CCLog("++++++ UserType %s", type->getCString());
    CCLog("++++++ grade %d", grade);
}


void HelloWorld::Func(float dt){
    CCLog("++++++ %s", __func__);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // User Information
    if(gThumbFlag == 1){
        CCGreeUser *pUser = CCGreePlatform::getLocalUser();
        dumpUserInfo(pUser);
        
        if(pThumb != NULL){
            CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addUIImage(pThumb, "key_name");
            pIcon = CCSprite::spriteWithTexture(tex);
            pIcon->setPosition(ccp(100, size.height - 100));
            this->addChild(pIcon, 0);
        }
        gThumbFlag = 0;
    }
    // Friend List
    if(gFriendFlag == 1){
        
        CCLabelTTF *lname[gNumOfFriend];
        CCLabelTTF *lbir[gNumOfFriend];
        CCLabelTTF *lage[gNumOfFriend];
        CCObject *it;
        int i = 0;
        CCLabelTTF *fList = CCLabelTTF::create("Friends List", "Thonburi", 40);
        fList->setPosition(ccp(FRIEND_X_OFFSET, size.height - FRIEND_Y_OFFSET));
        this->addChild(fList, 1);
        
        CCARRAY_FOREACH(pFriends, it){
            CCGreeUser *user = dynamic_cast<CCGreeUser *>(it);
            dumpUserInfo(user);
            lname[i] = CCLabelTTF::create(user->getNickname()->getCString(), "Thonburi", 30);
            lbir[i] = CCLabelTTF::create(user->getBirthday()->getCString(), "Thonburi", 30);
            lage[i] = CCLabelTTF::create(user->getAge()->getCString(), "Thonburi", 30);
            lname[i]->setPosition(ccp(FRIEND_X_OFFSET, size.height - FRIEND_Y_OFFSET - 50 - i*100));
            lbir[i]->setPosition(ccp(FRIEND_X_OFFSET, size.height - FRIEND_Y_OFFSET - 50 - 30 - i*100));
            lage[i]->setPosition(ccp(FRIEND_X_OFFSET, size.height - FRIEND_Y_OFFSET - 50 - 60 - i*100));
            this->addChild(lname[i], 1);
            this->addChild(lbir[i], 1);
            this->addChild(lage[i], 1);
            i++;
        }
        gFriendFlag = 0;
    }

}


void HelloWorld::menuGreeButtonCallback(CCObject *pSender){
    if(CCGreeAuthorizer::isAuthorized() != true){
        CCGreePlatform::setAuthorizerDelegate(this);
        CCGreePlatform::setUserDelegate(this);
        CCGreeAuthorizer::authorize();
    }
}

void HelloWorld::menuUserCallback(CCObject *pSender){
    // Load Thumbnail
    //CCGreeUser::loadUserWithId("1000020828");
    
    CCGreeUser *user = CCGreePlatform::getLocalUser();
    //user->load
    user->loadThumbnail(UserThumbnailSizeHuge);
    
    //user->loadIgnoredUserIds(0, 10);
}

void HelloWorld::menuFriendCallback(CCObject *pSender){
    // Load Friend list
    CCGreeUser *user = CCGreePlatform::getLocalUser();
    user->loadFriends(1, 10);
}


void HelloWorld::menuLogoutCallback(CCObject *pSender){
    CCGreeAuthorizer::logout();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
