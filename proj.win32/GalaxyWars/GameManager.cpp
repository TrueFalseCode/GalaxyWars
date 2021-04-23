#pragma once

#include "GameManager.h"

GameManager::GameManager() : _bGameOver(true)
{
	_text = make_shared<Actor>(Point(), 1.0f, Core::resourceManager.Get<Render::Texture>("Start"));
}

void GameManager::Draw(Render::RenderDeviceInterface& device)
{
	if (IsGameOver())
	{
		_text->Draw(device);

		return;
	}

	for (auto iter : _characterHealth)
	{
		iter->Draw(device);
	}

	if (_character)
	{
		_character->Draw(device);
	}

	for (auto iter : _enemies)
	{
		if(iter)
			iter->Draw(device);
	}
}

void GameManager::Update(const float & dt)
{
	if (IsGameOver())
		return;

	if (_character)
	{
		if (_enemies.empty())
		{
			EndGame();

			_text->SetTexture(Core::resourceManager.Get<Render::Texture>("YouWin"));
			_text->SetActorPosition(_character->GetGlobalCenter());

			return;
		}

		if (_character->IsDied())
		{
			EndGame();

			_text->SetTexture(Core::resourceManager.Get<Render::Texture>("YouLose"));
			_text->SetActorPosition(_character->GetGlobalCenter());

			return;
		}
		_character->CheckNProcessHits(_enemies);
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
					if (currEnemy->CheckNProcessHits(_character))
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

void GameManager::MoveCharacterByStep(const float & stepDegrees)
{
	if (_character)
	{
		_character->MoveByStep(stepDegrees);
	}
}

void GameManager::MoveCharacterTo(const float& newDegrees)
{
	if (_character)
	{
		_character->MoveTo(newDegrees);
	}
}

bool GameManager::IsGameOver()
{
	return _bGameOver;
}

void GameManager::RestartGame()
{
	EndGame();

	_bGameOver = false;
}

void GameManager::EndGame()
{
	_characterHealth.clear();
	_enemies.clear();

	_bGameOver = true;

	if(_text)
		_text->SetTexture(Core::resourceManager.Get<Render::Texture>("Start"));
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