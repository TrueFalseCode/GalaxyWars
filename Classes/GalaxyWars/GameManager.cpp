#pragma once

#include "GameManager.h"

#include "cocos2d.h"
using cocos2d::Director;

GameManager::GameManager() : _bGameOver(true), _characterDegreesPerSecond(0.0f)
{
	// TMP CODE
	//_text = make_shared<Actor>(Point(), 1.0f, "Start.png");
}

void GameManager::Update(const float & dt)
{
	if (IsGameOver())
		return;

	if (_character)
	{
		// TMP CODE
		if (_enemies.empty())
		{
			EndGame();

			Director::getInstance()->replaceScene(Actor::GetCurrentScene());

			/*if (_text)
			{
				_text->SetSpriteTexture("YouWin.png");
				_text->SetActorPosition(_character->GetGlobalCenter());
			}*/

			return;
		}

		if (_character->IsDied())
		{
			EndGame();

			Director::getInstance()->replaceScene(Actor::GetCurrentScene());

			/*if (_text)
			{
				_text->SetSpriteTexture("YouLose.png");
				_text->SetActorPosition(_character->GetGlobalCenter());
			}*/

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

void GameManager::SetTextCenter(const Point & textCenter)
{
	if (_text)
		_text->SetActorPosition(textCenter);
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

bool GameManager::IsGameOver()
{
	return _bGameOver;
}

void GameManager::StartGame()
{
	_bGameOver = false;
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

	_bGameOver = true;

	//if(_text)
		//_text->SetSpriteTexture("Start.png");
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