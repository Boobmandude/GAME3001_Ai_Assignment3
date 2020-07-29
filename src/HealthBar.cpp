#include "HealthBar.h"
#include "Util.h"
void HealthBar::update()
{
	getTransform()->position.x = m_gameObject->getTransform()->position.x - 16;
	getTransform()->position.y = m_gameObject->getTransform()->position.y - 40;
	float scale = ((float)m_gameObject->getHealth() / (float)m_gameObject->getMaxHealth());
	m_life = m_barSize * scale;
}

void HealthBar::draw()
{
	Util::DrawHealth(getTransform()->position, m_barSize, 10, { 1,0,0,1 });
	if (m_life > 0) 
	{
		Util::DrawHealth(getTransform()->position, m_life, 10.0f, { 0,1,0,1 });
	}
	
}

void HealthBar::clean()
{
}

HealthBar::HealthBar(GameObject* obj)
{
	
	m_gameObject = obj;
	m_barSize = 32.0f;
}

HealthBar::~HealthBar() = default;
