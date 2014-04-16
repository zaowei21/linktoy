/*
 * LoadMenu.h
 *
 *  Created on: 2014-3-26
 *      Author: toms1
 */

#ifndef LOADMENU_H_
#define LOADMENU_H_

#include "cocos2d.h"
#include "HelloWorldScene.h"

class LoadMenu: public cocos2d::CCLayer {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();
	CREATE_FUNC(LoadMenu);
	void menuCallback(CCObject* pSender);
	void menuCallbackHighScores(CCObject* pSender);
	void menuCallbackAbout(CCObject* pSender);
	void menuCloseCallback(CCObject* pSender);
};

#endif /* LOADMENU_H_ */

