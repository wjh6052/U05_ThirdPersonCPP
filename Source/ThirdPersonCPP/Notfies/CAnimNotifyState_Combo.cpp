#include "CAnimNotifyState_Combo.h"
#include "Global.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CDoAction_Melee.h"


FString UCAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp->GetOwner());

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UCActionData* actionData = actionComp->GetCurrentData();
	CheckNull(actionData);

	ACDoAction_Melee* doAction_Melee = Cast<ACDoAction_Melee>(actionData->GetDoAction());
	CheckNull(doAction_Melee);

	doAction_Melee->OnCombo();

}

void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp->GetOwner());

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UCActionData* actionData = actionComp->GetCurrentData();
	CheckNull(actionData);

	ACDoAction_Melee* doAction_Melee = Cast<ACDoAction_Melee>(actionData->GetDoAction());
	CheckNull(doAction_Melee);

	doAction_Melee->OffCombo();
}
