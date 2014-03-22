#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene() {
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
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()) {
		return false;
	}
	XY
	// 这个是我把下面两句直接做了一个宏来代替.
	//x0 = -1;y0 = -1;x1 = -1;y1 = -1;
	//isTwo = -1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			flag1[i][j] = false;
		}
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels(); //获得屏幕尺寸，这里要画个和屏幕等大的静态背景
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", this,
			menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(
			ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 -10 ,
					origin.y + pCloseItem->getContentSize().height/2 + 10));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	//这里是我加的试验背景的代码开始
	CCRect r(origin.x, origin.y, winSize.width, winSize.height);
	//CCLOG(
	//	"cDebug=%4.2f,origin.y=%4.2f,winsize.width=%6.2f,winsize.height=%6.2f", origin.x, origin.y, winSize.width, winSize.height);
	//CCLOG(
	//	"cDebug=visibleSize.width=%6.2f,visibleSize.height=%6.2f", visibleSize.width, visibleSize.height);
	CCSprite* shelfBG = CCSprite::create("bg03.png", r);
	ccTexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	shelfBG->getTexture()->setTexParameters(&tp);
	shelfBG->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(shelfBG);
	//这里是我加的试验背景的代码结束
	/////////////////////////////
	// create and initialize a label
	/*
	 //利用CCDictionary来读取xml
	 //stringscn.xml要放在assets这个目录下,在eclipse的android下
	 CCDictionary *strings = CCDictionary::createWithContentsOfFile(
	 "stringscn.xml");
	 //读取Hello键中的值 objectForKey根据key，获取对应的string
	 const char *hello =
	 ((CCString*) strings->objectForKey("Hello"))->m_sString.c_str();

	 CCLabelTTF* pLabel = CCLabelTTF::create(hello, "Arial", 34);

	 // position the label on the center of the screen
	 pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
	 origin.y + visibleSize.height - pLabel->getContentSize().height));

	 // add the label as a child to this layer
	 this->addChild(pLabel, 1);
	 */
	viewTitle(origin, visibleSize);
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("ss.plist", "ss.png");

	CCArray* temparry = CCArray::create();
	initArray(temparry);
	/*
	 CCSprite* temp1;
	 CCSprite* temp2;
	 // 一次生成两张一样的
	 for (int i = 0; i < 18; i++) {
	 int num = CCRANDOM_0_1() * 12; //因为是图片的张数是从0到36张 所以随机从0 到35
	 temp1 = CCSprite::createWithSpriteFrameName(g_Names[num].c_str());
	 temp1->setTag(num);
	 temp2 = CCSprite::createWithSpriteFrameName(g_Names[num].c_str());
	 temp2->setTag(num);
	 temparry->addObject(temp1);
	 temparry->addObject(temp2);
	 //CCLOG("cDebug GetTag = %d", temp1->getTag());
	 }
	 */
	initView(temparry, origin);
	/*
	 for (int i = 0; i < 6; i++) { //i相当于X轴,沿屏幕短的方向
	 for (int j = 0; j < 6; j++) { //J相当于Y轴,沿屏幕长的方向伸展
	 //CCLOG("cDebug 33=%d", j);
	 totalSprite[i][j] = (CCSprite*) temparry->randomObject();
	 //CCLOG("cDebug Num66=%d",temp3->getNum());
	 temparry->removeObject(totalSprite[i][j], false);
	 if (i == 0 && j == 0) {
	 totalSprite[i][j]->setPosition(
	 ccp(origin.x + totalSprite[i][j]->getContentSize().width/2, origin.y + totalSprite[i][j]->getContentSize().height/2));
	 } else if (j == 0) {
	 totalSprite[i][j]->setPosition(
	 ccp(totalSprite[i-1][j]->getPositionX(), totalSprite[i-1][j]->getContentSize().height + totalSprite[i-1][j]->getPositionY()));
	 } else {
	 totalSprite[i][j]->setPosition(
	 ccp(totalSprite[i][j-1]->getPositionX() + totalSprite[i][j-1]->getContentSize().width, totalSprite[i][j-1]->getPositionY()));
	 }
	 this->addChild(totalSprite[i][j]);
	 flag0[i][j] = true;
	 flag1[i + 1][j + 1] = true;
	 }
	 }
	 */
	this->setTouchEnabled(true);
	return true;
}

void HelloWorld::registerWithTouchDispatcher(void) {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
			this, 0, true);
}

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {

	return true;
}

void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
	//pSprite->setPosition(ccp(pTouch->getLocation().x, pTouch->getLocation().y));
	CCPoint touchLocation = convertTouchToNodeSpace(pTouch);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (totalSprite[i][j]->boundingBox().containsPoint(touchLocation)) {
				//CCMessageBox("mSprite1 touched", "");
				if (isTwo < 1) {
					totalSprite[i][j]->setScale(0.9);
					flag0[i][j] = false;
					isTwo = 1;
					x0 = i;
					y0 = j;
				} else if (isTwo == 1) {
					x1 = i;
					y1 = j;
					if (totalSprite[x0][y0]->getTag()
							== totalSprite[x1][y1]->getTag()) {
						if ((y0 == y1) && checkTwoLinex(x0, y0, x1, y1)) {
							setSprite();
							break;
						}
						if (x0 == x1) {
							if (checkTwoLiney(x0, y0, x1, y1)) {
								setSprite();
								break;
							}
						}
						if (checkOneCorner(x0, y0, x1, y1)
								|| checkTwoCorner(x0, y0, x1, y1)) {
							setSprite();
							break;
						}
					}
					isTwo = 1;
					totalSprite[x0][y0]->setScale(1.0);
					totalSprite[i][j]->setScale(0.9);
					flag0[i][j] = true;
					x0 = i;
					y0 = j;

				}
				break;
			}
		}
	}
}

void HelloWorld::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {
}

void HelloWorld::menuCloseCallback(CCObject* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

//这个函数检查同一行是不是相同的可以连通.
bool HelloWorld::checkTwoLinex(int a0, int b0, int a1, int b1) {
	if (a0 == a1 && b0 == b1)
		return false;
	int begin = a0 < a1 ? a0 : a1;
	int end = a0 < a1 ? a1 : a0;
	//CCLOG("cDebug begin-XX=%d XX-end=%d  XXXXX", begin,end);
	//CCLOG("cDebug end-y=%d", end);
	//CCLOG("cDebug XX x0=%d,y0=%d,x1=%d,y1=%d XXXXX", a0, b0, a1, b1);
	for (int i = begin + 1; i < end; i++) {
		if (flag1[i + 1][b0 + 1]) {
			//CCLOG("cDebug X-FALSE-i=%d XXXXX", i);
			return false;
		}
	}
	//CCLOG("cDebug X-TRUE");
	return true;
}

//这个函数检查同一列是不是相同的可以连通
bool HelloWorld::checkTwoLiney(int a0, int b0, int a1, int b1) {
	if (a0 == a1 && b0 == b1)
		return false;
	int begin = b0 < b1 ? b0 : b1;
	int end = b0 < b1 ? b1 : b0;
	//CCLOG("cDebug begin-YY=%d YY-end=%d  YYYYY", begin,end);
	//CCLOG("cDebug end-y=%d", end);
	//CCLOG("cDebug YY x0=%d,y0=%d,x1=%d,y1=%d YYYYY", a0, b0, a1, b1);
	for (int i = begin + 1; i < end; i++) {
		if (flag1[a0 + 1][i + 1]) {
			//CCLOG("cDebug Y-FALSE-i=%d", i);
			return false;
		}
	}
	//CCLOG("cDebug Y-TRUE YYYYY");
	return true;
}

bool HelloWorld::checkOneCorner(int a0, int b0, int a1, int b1) {
	bool isSuccess = false;
	int c0, c1, d0, d1;
	c0 = a1;
	c1 = a0;
	d0 = b0;
	d1 = b1;
	if (!(flag1[c0 + 1][d0 + 1])) {
		//return (checkTwoLinex(a1, b1, c0, d0) && checkTwoLiney(a0, b0, c0, d0));
		isSuccess = (checkTwoLinex(a0, b0, c0, d0)
				&& checkTwoLiney(a1, b1, c0, d0));
	}
	if ((!(flag1[c1 + 1][d1 + 1])) && !isSuccess) {
		isSuccess = (checkTwoLinex(a1, b1, c1, d1)
				&& checkTwoLiney(a0, b0, c1, d1));
	}
	CCLOG("cDebug checkOneCorner----------checkOneCorner");
	return isSuccess;

}

std::vector<Line> HelloWorld::scan(int x0, int y0, int x1, int y1) {
	std::vector<Line> linkList;
	for (int i = y0; i >= 0; i--) {
		if (flag1[x0 + 1][i] == false && flag1[x1 + 1][i] == false
				&& checkTwoLinex(x0 - 1, i - 1, x1 - 1, i - 1)) {
			linkList.push_back(Line(x0, i - 1, x1, i - 1, 0));
		}
		//CCLOG("cDebug SCAN1 x0=%d,y0=%d,x1=%d,y1=%d ", x0, y0, x1, y1);
		//CCLOG("cDebug SCAN1 FLAG1[X0+1][i]=FLAG1[%d][%d] = %d",x0+1,i,flag1[x0 + 1][i]);
		//CCLOG("cDebug SCAN1 FLAG1[X1+1][i]=FLAG1[%d][%d] = %d",x1+1,i,flag1[x1 + 1][i]);
		//CCLOG("cDebug SCAN1 CheckTwoLinex=%d ", checkTwoLinex(x0-1, i-1, x1-1, i-1));
	}

	for (int i = y0; i < 8; i++) {
		if (flag1[x0 + 1][i] == false && flag1[x1 + 1][i] == false
				&& checkTwoLinex(x0 - 1, i - 1, x1 - 1, i - 1)) {
			linkList.push_back(Line(x0, i - 1, x1, i - 1, 0));
		}
		CCLOG("cDebug SCAN2 x0=%d,y0=%d,x1=%d,y1=%d ", x0, y0, x1, y1);
		CCLOG("cDebug SCAN2 FLAG1[X0+1][i]=FLAG1[%d][%d] = %d", x0+1, i,
				flag1[x0 + 1][i]);
		CCLOG("cDebug SCAN2 FLAG1[X1+1][i]=FLAG1[%d][%d] = %d", x1+1, i,
				flag1[x1 + 1][i]);
		CCLOG("cDebug SCAN2 CheckTwoLinex=%d ",
				checkTwoLinex(x0-1, i-1, x1-1, i-1));
	}

	for (int j = x0; j >= 0; j--) {
		if (flag1[j][y0 + 1] == false && flag1[j][y1 + 1] == false
				&& checkTwoLiney(j - 1, y0 - 1, j - 1, y1 - 1)) {
			linkList.push_back(Line(j - 1, y0, j - 1, y1, 1));
		}
		//CCLOG("cDebug SCAN2 x0=%d,y0=%d,x1=%d,y1=%d ", x0, y0, x1, y1);
		//CCLOG("cDebug SCAN2 FLAG1[j][y0+1]=FLAG1[%d][%d] = %d",j,y0+1,flag1[j][y0+1]);
		//CCLOG("cDebug SCAN2 FLAG1[j][y1+1]=FLAG1[%d][%d] = %d",j,y1+1,flag1[j][y1+1]);
		//CCLOG("cDebug SCAN2 CheckTwoLiney=%d ", checkTwoLinex(j-1, y0-1, j-1, y1-1));
	}

	for (int j = x0; j < 8; j++) {
		if (flag1[j][y0 + 1] == false && flag1[j][y1 + 1] == false
				&& checkTwoLiney(j - 1, y0 - 1, j - 1, y1 - 1)) {
			linkList.push_back(Line(j - 1, y0, j - 1, y1, 1));
		}
	}

	return linkList;
}

bool HelloWorld::checkTwoCorner(int x0, int y0, int x1, int y1) {
	std::vector<Line> ll = scan(x0, y0, x1, y1);
	if (ll.empty()) {
		return false;
	}
	CCLOG("cDebug Line.Size=%d", ll.size());
	for (int i = 0; i < ll.size(); i++) {
		Line tmpLine = ll[i];
		if (tmpLine.direct == 1) {
			if (checkTwoLinex(x0, y0, tmpLine.x6, tmpLine.y6)
					&& checkTwoLinex(x1, y1, tmpLine.x7, tmpLine.y7)) {
				return true;
			}
		} else if (tmpLine.direct == 0) {
			if (checkTwoLiney(x0, y0, tmpLine.x6, tmpLine.y6)
					&& checkTwoLiney(x1, y1, tmpLine.x7, tmpLine.y7)) {
				return true;
			}
		}
	}
	return false;
}

bool HelloWorld::viewTitle(CCPoint origin, CCSize visibleSize) {
	//利用CCDictionary来读取xml
	//stringscn.xml要放在assets这个目录下,在eclipse的android下
	CCDictionary *strings = CCDictionary::createWithContentsOfFile(
			"stringscn.xml");
	//读取Hello键中的值 objectForKey根据key，获取对应的string
	const char *hello =
			((CCString*) strings->objectForKey("Hello"))->m_sString.c_str();

	CCLabelTTF* pLabel = CCLabelTTF::create(hello, "Arial", 34);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
			origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);
	return true;
}

void HelloWorld::initArray(CCArray* temparry) {
	CCSprite* temp1;
	CCSprite* temp2;
	// 一次生成两张一样的
	for (int i = 0; i < 18; i++) {
		int num = CCRANDOM_0_1() * 12; //因为是图片的张数是从0到36张 所以随机从0 到35
		temp1 = CCSprite::createWithSpriteFrameName(g_Names[num].c_str());
		temp1->setTag(num);
		temp2 = CCSprite::createWithSpriteFrameName(g_Names[num].c_str());
		temp2->setTag(num);
		temparry->addObject(temp1);
		temparry->addObject(temp2);
		//CCLOG("cDebug GetTag = %d", temp1->getTag());
	}
}

void HelloWorld::initView(CCArray* temparry, CCPoint origin) {
	for (int i = 0; i < 6; i++) { //i相当于X轴,沿屏幕短的方向
		for (int j = 0; j < 6; j++) { //J相当于Y轴,沿屏幕长的方向伸展

			totalSprite[i][j] = (CCSprite*) temparry->randomObject();
			temparry->removeObject(totalSprite[i][j], false);
			if (i == 0 && j == 0) {
				totalSprite[i][j]->setPosition(
						ccp(origin.x + totalSprite[i][j]->getContentSize().width/2, origin.y + totalSprite[i][j]->getContentSize().height/2));
					} else if (j == 0) {
						totalSprite[i][j]->setPosition(
								ccp(totalSprite[i-1][j]->getPositionX(), totalSprite[i-1][j]->getContentSize().height + totalSprite[i-1][j]->getPositionY()));
					} else {
						totalSprite[i][j]->setPosition(
								ccp(totalSprite[i][j-1]->getPositionX() + totalSprite[i][j-1]->getContentSize().width, totalSprite[i][j-1]->getPositionY()));
					}
			this->addChild(totalSprite[i][j]);
			flag0[i][j] = true;
			flag1[i + 1][j + 1] = true;
		}
	}
}

void HelloWorld::setSprite() {
	this->removeChild(totalSprite[x0][y0], true);
	this->removeChild(totalSprite[x1][y1], true);
	totalSprite[x0][y0]->setTag(999 * CCRANDOM_0_1());
	totalSprite[x1][y1]->setTag(999 * CCRANDOM_0_1());
	flag1[x0 + 1][y0 + 1] = false;
	flag1[x1 + 1][y1 + 1] = false;
	isTwo = 0;
}

Line::Line(int x6, int y6, int x7, int y7, int direct) {
	this->x6 = x6;
	this->y6 = y6;
	this->x7 = x7;
	this->y7 = y7;
	this->direct = direct;
}
