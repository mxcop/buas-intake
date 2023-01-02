#include "healthbar.h"

HealthBar::HealthBar(shared_ptr<Sprite> heart, shared_ptr<Player> player)
{
	this->heart = heart;
	this->player = player;
}

void HealthBar::Draw(Tmpl8::Surface* screen) const
{
	int health = player->GetHealth();

	for (int i = 0; i < FULL_HEALTH; i++)
	{
		heart->SetFrame(i <= health ? 0 : 1);
		heart->Draw(screen, 4 + i * 10, 4);
	}
}
