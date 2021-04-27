
/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainMenu.h"
#include "PauseMenu.h"

USING_NS_CC;

cocos2d::Scene * PauseMenu::createScene()
{
	return PauseMenu::create();
}

bool PauseMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("PauseBackground.jpg");
	if (background)
	{
		background->setScale(1.5f);
		background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		this->addChild(background);
	}

	const Point globalCenterPoint(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	auto resumeButton = MenuItemImage::create(
		"ResumeButton.png",
		"ResumeButton.png",
		CC_CALLBACK_1(PauseMenu::resumeCallback, this));

	if (resumeButton)
	{
		resumeButton->setPosition(globalCenterPoint);
	}

	auto menu = Menu::create(resumeButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto listener = EventListenerKeyboard::create();
	if (listener)
	{
		listener->onKeyPressed = CC_CALLBACK_2(PauseMenu::onKeyPressed, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}

	return true;
}

void PauseMenu::resumeCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
}

void PauseMenu::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		resumeCallback(this);
	}
}
