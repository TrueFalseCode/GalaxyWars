#pragma once

#include "GameManager.h"
#include "GameOver.h"

#include "cocos2d.h"
using cocos2d::Director;

GameManager::GameManager() : _bGameOver(true), _bLevelUp(false), _characterDegreesPerSecond(0.0f)
{
}

void GameManager::Update(const float & dt)
{
	if (IsGameOver())
		return;

	if (_character)
	{
		if (_enemies.empty())
		{
			auto flag = make_shared<Actor>(Point(200.0f + (_flags.size() * (64.0f + 10.0f)), 100.0f), 1.0f, "Flag.png");
			_flags.push_back(flag);

			_bLevelUp = true;

			return;
		}

		if (_character->IsDied())
		{
			EndGame();

			auto gameOverScene = GameOver::create();
			Director::getInstance()->replaceScene(gameOverScene);

			return;
		}

		_character->CheckAndProcessHits(_enemies);
		_character->Update(dt);

		for (auto beg = _enemies.begin(); beg != _enemies.cend(); )
		{
			auto currEnemy = (*beg);
			if (currEnemy)
			{
				// Если враг "умер", то он должен удалиться со сцены и из контейнера,
				// который хранит список всех врагов
				if (currEnemy->IsDied())
				{
					beg = _enemies.erase(beg);
				}
				else
				{
					if (currEnemy->CheckAndProcessHits(_character) && !_characterHealth.empty())
					{
						_characterHealth.erase(_characterHealth.begin());
					}
					currEnemy->Update(dt);
					++beg;
				}
			}
		}
	}
}

void GameManager::CharacterAttack()
{
	if (_character)
	{
		_character->DoAttack(_character.get(), _character->GetGlobalCenter());
	}
}

void GameManager::MoveCharacterLeft()
{
	if (_character)
	{
		_character->SetDegreesPerSecond(-_characterDegreesPerSecond);
	}
}

void GameManager::MoveCharacterRight()
{
	if (_character)
	{
		_character->SetDegreesPerSecond(_characterDegreesPerSecond);
	}
}

void GameManager::MoveCharacterBy(const float & stepDegrees)
{
	if (_character)
	{
		_character->MoveBy(stepDegrees);
	}
}

void GameManager::MoveCharacterTo(const float& newDegrees)
{
	if (_character)
	{
		_character->MoveTo(newDegrees);
	}
}

void GameManager::StopCharacter()
{
	if (_character)
	{
		_character->SetDegreesPerSecond(0.0f);
	}
}

bool GameManager::IsLevelUp()
{
	return _bLevelUp;
}

bool GameManager::IsGameOver()
{
	return _bGameOver;
}

void GameManager::StartGame()
{
	_bGameOver = false;
	_bLevelUp = false;
	MoveCharacterTo(270.0f);
}

void GameManager::RestartGame()
{
	EndGame();
	StartGame();
}

void GameManager::EndGame()
{
	_characterHealth.clear();
	_enemies.clear();
	_flags.clear();

	_bGameOver = true;
}

GameManager::~GameManager()
{
	EndGame();
}

void GameManager::FillEnemy(shared_ptr<Enemy> enemy, const shared_ptr<Weapon> weapon, const float & visibleZone, const float & stormtrooperEffect)
{
	if (enemy)
	{
		enemy->SetVisibleZone(visibleZone);
		enemy->SetStormtrooperEffect(stormtrooperEffect);
		if (_character)
		{
			enemy->SetCharacter(_character);
		}
		if (weapon)
		{
			enemy->SetWeapon(weapon);
		}
	}
}