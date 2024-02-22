#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"


UCLASS()
class THIRDPERSONCPP_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()
	
public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 1;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;






};
