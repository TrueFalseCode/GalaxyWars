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
#include "PauseMenu.h"

USING_NS_CC;

Scene* GameField::createScene()
{
	return GameField::create();
}

bool GameField::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("GameBackground.jpg");
	if (background)
	{
		background->setScale(1.5f);
		background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		this->addChild(background);
	}

	_globalCenterPoint.setPoint(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	auto listener = EventListenerKeyboard::create();
	if (listener)
	{
		listener->onKeyPressed = CC_CALLBACK_2(GameField::onKeyPressed, this);
		listener->onKeyReleased = CC_CALLBACK_2(GameField::onKeyReleased, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}

	Actor::SetCurrentScene(this);

	// *
	// Создание главного персонажа, которым управляет игрок, а также его оружия
	// *
	shared_ptr<Weapon> CharacterWeapon = make_shared<Firearms>(1.0f,						// НаносимыйУрон
																0.3f,						// ЗадержкаМеждуАтаками
																2.0f,						// СкоростьСнаряда
																"PlayerProjectile.png");	// ИмяФайлаДляСпрайта

	_gameManager.CreateCharacter<Character>(10.0f,				// КоличествоЖизней
											CharacterWeapon,	// УказательНаОружие
											"Player.png",		// ИмяФайлаДляСпрайта
											_globalCenterPoint,	// ЦентральнаяТочкаИгровогоПоля 
											500.0f,				// РасстояниеОтЦентральнойТочки
											0.0f,				// НачальнаяПозицияНаОкружности (в градусах)
											70.0f);				// Скорость передвижения в заданной окружности (градусов в секунду)

	_currentDifficalt = 0.1f;
	createGameObjects(_currentDifficalt);

	_gameManager.StartGame();

	return true;
}

void GameField::update(float dt)
{
	if (_gameManager.IsLevelUp())
	{
		_currentDifficalt += 0.1f;
		if (_currentDifficalt >= 1.0f)
		{
			_gameManager.EndGame();
			_currentDifficalt = 0.1f;
		}
		createGameObjects(_currentDifficalt);
		_gameManager.StartGame();
	}
	_gameManager.Update(dt);
}

void GameField::createGameObjects(const float & difficalt)
{
	_rightArrowDown = false;
	_leftArrowDown = false;		

	vector<shared_ptr<Weapon>> enemyWeapons;
	// *
	// Создание первого круга врагов (ближнего к центру игрового поля) и их оружия : тип врагов Sniper : Circle 1
	// *
	int numberOfEnemy_firstCircle = 8 * difficalt;
	for (int i = 0; i < numberOfEnemy_firstCircle; ++i)
	{
		enemyWeapons.push_back(make_shared<Firearms>(1.0f,						// НаносимыйУрон
													8.0f - difficalt,			// ЗадержкаМеждуАтаками
													1.0f + difficalt,			// СкоростьСнаряда
													"EnemyProjectile.png"));	// ИмяФайлаДляСпрайта
	}
	_gameManager.CreateEnemies<Sniper>(numberOfEnemy_firstCircle,				// Количество врагов в заданной окружности
										4.0f,									// Количество жизней
										enemyWeapons,							// Указатель на список оружия (для каждого врага одно из списка)
										0.0f,									// Начальная позиция на окружности (для первого создаваемого врага; в градусах)
										(360.0f / numberOfEnemy_firstCircle),	// Расстояние между врагами в заданной окружности
										"SniperEnemy.png",						// Имя файла для спрайта
										_globalCenterPoint,						// Центральная точка игрового поля
										100.0f,									// Расстояние от центральной точки
										50.0f + (difficalt * 50.0f),			// Скорость передвижения врагов в заданной окружности (градусов в секунду)
										90.0f,									// Зона видимости врагов в заданной окружности, в пределах которой они атакуют (в градусах)
										0.1f);									// Эффект штурмовика(Stormtrooper effect), задает точность попадания врага в цель (от 0.0 до 1.0)

	enemyWeapons.clear();

	// *
	// Создание вторго круга врагов и их оружия : тип врагов Enemy : Circle 2
	// *
	int numberOfEnemy_secondCircle = 15 * difficalt;
	for (int i = 0; i < numberOfEnemy_secondCircle; ++i)
	{
		enemyWeapons.push_back(make_shared<Firearms>(1.0f,						// НаносимыйУрон
													5.0f - difficalt,			// ЗадержкаМеждуАтаками
													1.0f + difficalt,			// СкоростьСнаряда
													"EnemyProjectile.png"));	// ИмяФайлаДляСпрайта
	}
	_gameManager.CreateEnemies<Enemy>(numberOfEnemy_secondCircle,				// Количество врагов в заданной окружности
										2.0f,									// Количество жизней
										enemyWeapons,							// Указатель на список оружия (для каждого врага одно из списка)
										0.0f,									// Начальная позиция на окружности (для первого создаваемого врага; в градусах)
										(360.0f / numberOfEnemy_secondCircle),	// Расстояние между врагами в заданной окружности
										"SimpleEnemy.png",						// Имя файла для спрайта
										_globalCenterPoint,						// Центральная точка игрового поля
										200.0f,									// Расстояние от центральной точки
										-10.0f - (difficalt * 50.0f),			// Скорость передвижения врагов в заданной окружности (градусов в секунду)
										45.0f,									// Зона видимости врагов в заданной окружности, в пределах которой они атакуют (в градусах)
										1.0f);									// Эффект штурмовика(Stormtrooper effect), задает точность попадания врага в цель (от 0.0 до 1.0)

	enemyWeapons.clear();

	// *
	// Создание третьего круга врагов и их оружия : тип врагов Enemy : Circle 3
	// *
	int numberOfEnemy_thirdCircle = 24 * difficalt;
	for (int i = 0; i < numberOfEnemy_thirdCircle; ++i)
	{
		enemyWeapons.push_back(make_shared<Firearms>(1.0f,						// НаносимыйУрон
													5.0f - difficalt,			// ЗадержкаМеждуАтаками
													1.0f + difficalt,			// СкоростьСнаряда
													"EnemyProjectile.png"));	// ИмяФайлаДляСпрайта
	}
	_gameManager.CreateEnemies<Enemy>(numberOfEnemy_thirdCircle,				// Количество врагов в заданной окружности
										2.0f,									// Количество жизней
										enemyWeapons,							// Указатель на список оружия (для каждого врага одно из списка)
										0.0f,									// Начальная позиция на окружности (для первого создаваемого врага; в градусах)
										(360.0f / numberOfEnemy_thirdCircle),	// Расстояние между врагами в заданной окружности
										"SimpleEnemy.png",						// Имя файла для спрайта
										_globalCenterPoint,						// Центральная точка игрового поля
										300.0f,									// Расстояние от центральной точки
										40.0f + (difficalt * 50.0f),			// Скорость передвижения врагов в заданной окружности (градусов в секунду)
										45.0f,									// Зона видимости врагов в заданной окружности, в пределах которой они атакуют (в градусах)
										1.0f);									// Эффект штурмовика(Stormtrooper effect), задает точность попадания врага в цель (от 0.0 до 1.0)

	enemyWeapons.clear();
}


void GameField::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	//Director::getInstance()->end();

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
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		auto pauseMenu = PauseMenu::create();
		Director::getInstance()->pushScene(pauseMenu);
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
