/*
 * LoadMenu.cpp
 *
 *  Created on: 2014-3-26
 *      Author: toms1
 */

#include "LoadMenu.h"

USING_NS_CC;

CCScene* LoadMenu::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	LoadMenu *layer = LoadMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LoadMenu::init() {
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()) {
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels(); //获得屏幕尺寸，这里要画个和屏幕等大的静态背景
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("Close.png",
			"Closeed.png", this, menu_selector(LoadMenu::menuCloseCallback));

	pCloseItem->setPosition(
			ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 -10 ,
					origin.y + pCloseItem->getContentSize().height/2 + 10));

	CCDictionary *strings = CCDictionary::createWithContentsOfFile(
			"stringscn.xml");
	//读取Hello键中的值 objectForKey根据key，获取对应的string
	const char *menuTitle =
			((CCString*) strings->objectForKey("MenuTitle"))->m_sString.c_str();
	CCLabelTTF *label = CCLabelTTF::create(menuTitle, "Arial", 63);
	label->setPosition(
			ccp(visibleSize.width/2,visibleSize.height-label->getContentSize().height));
	this->addChild(label);

	CCMenuItemImage* item1 = CCMenuItemImage::create("btn-play-normal.png",
			"btn-play-selected.png", this,
			menu_selector(LoadMenu::menuCallback));
	CCMenuItemImage* item2 = CCMenuItemImage::create(
			"btn-highscores-normal.png", "btn-highscores-selected.png", this,
			menu_selector(LoadMenu::menuCallbackHighScores));
	CCMenuItemImage* item3 = CCMenuItemImage::create("btn-about-normal.png",
			"btn-about-selected.png", this,
			menu_selector(LoadMenu::menuCallbackAbout));

	item1->setPosition(
			ccp(visibleSize.width/2,visibleSize.height-item1->getContentSize().height*5));
	item2->setPosition(
			ccp(visibleSize.width/2,visibleSize.height-item1->getContentSize().height*9));
	item3->setPosition(
			ccp(visibleSize.width/2,visibleSize.height-item1->getContentSize().height*13));

	item1->setScaleX(3.0f);
	item2->setScaleX(3.0f);
	item3->setScaleX(3.0f);
	item1->setScaleY(3.0f);
	item2->setScaleY(3.0f);
	item3->setScaleY(3.0f);

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem,item1,item2,item3, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	return true;
}

void LoadMenu::menuCallback(CCObject* pSender) {
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = HelloWorld::scene();
	pDirector->replaceScene(CCTransitionFade::create(2, pScene));
	//pScene->release();
}

void LoadMenu::menuCallbackHighScores(CCObject* pSender){

}

void LoadMenu::menuCallbackAbout(CCObject* pSender){

}

void LoadMenu::menuCloseCallback(CCObject* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
