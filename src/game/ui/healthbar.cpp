#include "healthbar.h"
#include "../../game.h"

HealthBar::HealthBar(shared_ptr<Sprite> heart, shared_ptr<Player> player)
{
	this->heart = heart;
	this->player = player;
}

void HealthBar::Draw(Tmpl8::Surface* screen) const
{
	int health = player->GetHealth();

	if (health <= 0) Tmpl8::Game::instance()->Gameover();

	for (int i = 0; i < FULL_HEALTH; i++)
	{
		heart->SetFrame(i + 1 <= health ? 0 : 1);
		heart->Draw(screen, 4 + i * 10, 4);
	}
}
