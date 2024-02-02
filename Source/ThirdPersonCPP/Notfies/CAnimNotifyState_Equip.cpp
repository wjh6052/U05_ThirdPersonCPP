#include "CAnimNotifyState_Equip.h"
#include "Global.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}
void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp->GetOwner());

	UCActionComponent* actioncomp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actioncomp);
	
	CheckNull(actioncomp->GetCurrentData());
	ACEquipment* equipment = actioncomp->GetCurrentData()->GetEquipment();

	CheckNull(equipment);
	equipment->Begin_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);


	CheckNull(MeshComp->GetOwner());

	UCActionComponent* actioncomp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actioncomp);

	CheckNull(actioncomp->GetCurrentData());
	ACEquipment* equipment = actioncomp->GetCurrentData()->GetEquipment();

	CheckNull(equipment);
	equipment->End_Equip();
}
