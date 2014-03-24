#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>

#define XY x0 = -1;y0 = -1;x1 = -1;y1 = -1;isTwo = -1;
#define HANG 8
#define LIE 10
enum {
	PIG = 0,
	HORSE,
	MONKEY,
	COCK,
	COW,
	DOG,
	DRAGON,
	SNAKE,
	RABBIT,
	RAT,
	SHEEP,
	TIGER,
	COUNT
};

const std::string g_Names[COUNT] = { "pig.png", "cow.png", "dragon.png",
		"monkey.png", "rabbit.png", "sheep.png", "rat.png", "horse.png",
		"dog.png", "snake.png", "tiger.png", "cock.png" };

class Line {
public:
	int x6;
	int y6;
	int x7;
	int y7;
	int direct;
	Line(int x6,int y6,int x7,int y7,int direct);
};


class HelloWorld: public cocos2d::CCLayer {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);
	cocos2d::CCLabelTTF* _down_Label;
	int _dowmTime;
	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld)
	;
	bool checkTwoLinex(int a0,int b0,int a1,int b1);
	bool checkTwoLiney(int a0,int b0,int a1,int b1);
	bool checkOneCorner(int a0,int b0,int a1,int b1);
	std::vector<Line> scan(int x0,int y0,int x1,int y1);
	bool checkTwoCorner(int x0,int y0,int x1,int y1);
	bool viewTitle(cocos2d::CCPoint origin,cocos2d::CCSize visibleSize);
	void initArray(cocos2d::CCArray* temparry);//这个函数用来初始化数组
	void initView(cocos2d::CCArray* temparry,cocos2d::CCPoint origin);
	void setSprite();
	void downTime(float dt);

	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);

	cocos2d::CCSprite* pSprite;
	cocos2d::CCSprite* totalSprite[HANG-2][LIE-2];
	bool flag0[HANG-2][LIE-2];
	bool flag1[HANG][LIE];
	int x0, y0 ,x1,y1;
	int isTwo;
	int SpriteNum;
};

#endif // __HELLOWORLD_SCENE_H__
