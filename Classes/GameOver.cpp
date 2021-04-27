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

#include "GameOver.h"
#include "GameField.h"

USING_NS_CC;

cocos2d::Scene * GameOver::createScene()
{
	return GameOver::create();
}

bool GameOver::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	const Point globalCenterPoint(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	auto background = Sprite::create("PauseBackground.jpg");
	if (background)
	{
		background->setScale(1.5f);
		background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		this->addChild(background);
	}

	auto label = Label::createWithTTF("GAME OVER", "fonts/Marker Felt.ttf", 64);
	if (label)
	{
		label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - (label->getContentSize().height * 4)));

		this->addChild(label, 1);
	}

	auto restartButton = MenuItemImage::create(
		"RestartButton.png",
		"RestartButton.png",
		CC_CALLBACK_1(GameOver::restartCallback, this));

	if (restartButton)
	{
		restartButton->setPosition(globalCenterPoint);
	}

	auto menu = Menu::create(restartButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void GameOver::restartCallback(cocos2d::Ref * pSender)
{
	auto gameField = GameField::create();
	Director::getInstance()->replaceScene(gameField);
}
