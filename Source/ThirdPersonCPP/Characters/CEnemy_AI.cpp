#include "CEnemy_AI.h"
#include "Global.h"

#include "BehaviorTree/BehaviorTree.h"

#include "Components/CPatrolComponent.h"



ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent(this, &Patrol, "Patrol");
}