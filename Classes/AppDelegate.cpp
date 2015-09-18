#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}


AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
    {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    // 画面全体が表示できるように画像を伸縮させる
//    glview->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);
    glview->setDesignResolutionSize(640, 1136, ResolutionPolicy::FIXED_WIDTH);

    auto scene = HelloWorld::createScene();
    director->runWithScene(scene);
    
//    auto scene = GameLayer::createScene();
//    director->runWithScene(scene);
    
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
