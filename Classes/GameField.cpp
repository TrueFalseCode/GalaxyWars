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

#include "GameField.h"

USING_NS_CC;

Scene* GameField::createScene()
{
	return GameField::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameFieldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameField::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	this->scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	const Point globalCenterPoint(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameField::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	Actor::SetCurrentScene(this);
	_rightArrowDown = false;
	_leftArrowDown = false;

	// *
	// �������� �������� ���������, ������� ��������� �����, � ����� ��� ������
	// *
	shared_ptr<Weapon> CharacterWeapon = make_shared<Firearms>(1.0f,						// �������������
		0.3f,						// ��������������������
		2.0f,						// ���������������
		"PlayerProjectile.png");	// ������������������

	_gameManager.CreateCharacter<Character>(10.0f,				// ����������������
		CharacterWeapon,	// �����������������
		"Player.png",		// ������������������
		globalCenterPoint,	// ���������������������������� 
		500.0f,				// ����������������������������
		0.0f,				// ���������������������������� (� ��������)
		70.0f);				// �������� ������������ � �������� ���������� (�������� � �������)		

	vector<shared_ptr<Weapon>> enemyWeapons;
	// *
	// �������� ������� ����� ������ (�������� � ������ �������� ����) � �� ������ : ��� ������ Sniper : Circle 1
	// *
	int numberOfEnemy_firstCircle = 8;
	for (int i = 0; i < numberOfEnemy_firstCircle; ++i)
	{
		enemyWeapons.push_back(make_shared<Firearms>(1.0f,						// �������������
			8.0f,						// ��������������������
			1.0f,						// ���������������
			"EnemyProjectile.png"));	// ������������������
	}
	_gameManager.CreateEnemies<Sniper>(numberOfEnemy_firstCircle,				// ���������� ������ � �������� ����������
		4.0f,									// ���������� ������
		enemyWeapons,							// ��������� �� ������ ������ (��� ������� ����� ���� �� ������)
		0.0f,									// ��������� ������� �� ���������� (��� ������� ������������ �����; � ��������)
		(360.0f / numberOfEnemy_firstCircle),	// ���������� ����� ������� � �������� ����������
		"SniperEnemy.png",						// ��� ����� ��� �������
		globalCenterPoint,						// ����������� ����� �������� ����
		100.0f,									// ���������� �� ����������� �����
		50.0f,									// �������� ������������ ������ � �������� ���������� (�������� � �������)
		90.0f,									// ���� ��������� ������ � �������� ����������, � �������� ������� ��� ������� (� ��������)
		0.1f);									// ������ ����������(Stormtrooper effect), ������ �������� ��������� ����� � ���� (�� 0.0 �� 1.0)

	enemyWeapons.clear();

	// *
	// �������� ������ ����� ������ � �� ������ : ��� ������ Enemy : Circle 2
	// *
	int numberOfEnemy_secondCircle = 15;
	for (int i = 0; i < numberOfEnemy_secondCircle; ++i)
	{
		enemyWeapons.push_back(make_shared<Firearms>(1.0f,						// �������������
			5.0f,						// ��������������������
			1.0f,						// ���������������
			"EnemyProjectile.png"));	// ������������������
	}
	_gameManager.CreateEnemies<Enemy>(numberOfEnemy_secondCircle,				// ���������� ������ � �������� ����������
		2.0f,									// ���������� ������
		enemyWeapons,							// ��������� �� ������ ������ (��� ������� ����� ���� �� ������)
		0.0f,									// ��������� ������� �� ���������� (��� ������� ������������ �����; � ��������)
		(360.0f / numberOfEnemy_secondCircle),	// ���������� ����� ������� � �������� ����������
		"SimpleEnemy.png",						// ��� ����� ��� �������
		globalCenterPoint,						// ����������� ����� �������� ����
		200.0f,									// ���������� �� ����������� �����
		-10.0f,									// �������� ������������ ������ � �������� ���������� (�������� � �������)
		45.0f,									// ���� ��������� ������ � �������� ����������, � �������� ������� ��� ������� (� ��������)
		1.0f);									// ������ ����������(Stormtrooper effect), ������ �������� ��������� ����� � ���� (�� 0.0 �� 1.0)

	enemyWeapons.clear();

	// *
	// �������� �������� ����� ������ � �� ������ : ��� ������ Enemy : Circle 3
	// *
	int numberOfEnemy_thirdCircle = 24;
	for (int i = 0; i < numberOfEnemy_thirdCircle; ++i)
	{
		enemyWeapons.push_back(make_shared<Firearms>(1.0f,						// �������������
			5.0f,						// ��������������������
			1.0f,						// ���������������
			"EnemyProjectile.png"));	// ������������������
	}
	_gameManager.CreateEnemies<Enemy>(numberOfEnemy_thirdCircle,				// ���������� ������ � �������� ����������
		2.0f,									// ���������� ������
		enemyWeapons,							// ��������� �� ������ ������ (��� ������� ����� ���� �� ������)
		0.0f,									// ��������� ������� �� ���������� (��� ������� ������������ �����; � ��������)
		(360.0f / numberOfEnemy_thirdCircle),	// ���������� ����� ������� � �������� ����������
		"SimpleEnemy.png",						// ��� ����� ��� �������
		globalCenterPoint,						// ����������� ����� �������� ����
		300.0f,									// ���������� �� ����������� �����
		40.0f,									// �������� ������������ ������ � �������� ���������� (�������� � �������)
		45.0f,									// ���� ��������� ������ � �������� ����������, � �������� ������� ��� ������� (� ��������)
		1.0f);									// ������ ����������(Stormtrooper effect), ������ �������� ��������� ����� � ���� (�� 0.0 �� 1.0)

	enemyWeapons.clear();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameField::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameField::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// add "GameField" splash screen"
	/*auto sprite = Sprite::create("GameField.png");
	if (sprite == nullptr)
	{
		problemLoading("'GameField.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}*/
	return true;
}

void GameField::update(float dt)
{
	_gameManager.Update(dt);
}


void GameField::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void GameField::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_rightArrowDown = true;
		_gameManager.MoveCharacterRight();
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_leftArrowDown = true;
		_gameManager.MoveCharacterLeft();
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		_gameManager.CharacterAttack();
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		_gameManager.StartGame();
		break;
	}
}

void GameField::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

		_rightArrowDown = false;
		if (_leftArrowDown)
			_gameManager.MoveCharacterLeft();
		else
			_gameManager.StopCharacter();

		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:

		_leftArrowDown = false;
		if (_rightArrowDown)
			_gameManager.MoveCharacterRight();
		else
			_gameManager.StopCharacter();

		break;
	}
}
