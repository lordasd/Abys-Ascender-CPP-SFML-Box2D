#include "ChasingState.h"
#include "Mob.h"

ChasingState::ChasingState(const std::function<void(Mob&)>& animationWalk)
	:	m_animationWalk(animationWalk) {}

void ChasingState::update(Mob& mob, float deltaTime)
{
	m_startWalking += deltaTime;
	if (m_startWalking > 0.5f) // Initial time to start walking and change animation
	{
		auto playerPos = mob.getPlayersPosition();
		float direction{ playerPos.x - mob.getBody()->GetPosition().x * PPM };
		mob.setDirection(direction < 0 ? Direction::Left : Direction::Right);
		mob.setOperation(Operation::Run);
		m_animationWalk(mob);
	}
}