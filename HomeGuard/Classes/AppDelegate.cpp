#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameMenu.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1136, 640);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if 0
       glview = GLViewImpl::create("My Game");
	   director->setOpenGLView(glview);
	   glview->setFrameSize(1280, 720);
#else
		glview = GLViewImpl::createWithRect("HeroicalYouth", Rect(0, 0, 1136, 640));
		//glview = GLViewImpl::create("My Game");

		director->setOpenGLView(glview);
		Size frameSize = glview->getFrameSize();

	//	glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);
		glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);


#endif
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
#if 0
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    Size frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
#else
	//从资源图片到设计尺寸的适配比例

	Size frameSize = glview->getFrameSize();
	//director->setContentScaleFactor(1534.0f / 1136.0);
	director->setContentScaleFactor(864.0 / 640.0);

#endif
	// 添加资源搜索路径
	auto fileUtils = FileUtils::getInstance();
	std::vector<std::string> searchPaths;
	searchPaths.push_back("publishRes");
	searchPaths.push_back("publishRes/img");
	searchPaths.push_back("publishRes/fonts");
	searchPaths.push_back("publishRes/level");
	searchPaths.push_back("publishRes/map");
	searchPaths.push_back("publishRes/sound");
	fileUtils->setSearchPaths(searchPaths);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = GameMenu::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
