#include "CHUD.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Engine/Canvas.h"
#include "Components/CStateComponent.h"


void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	CheckNull(playerCharacter);

	StateComp = CHelpers::GetComponent<UCStateComponent>(playerCharacter);
	StateTypeAsUEnum = FindObject<UEnum>(ANY_PACKAGE, L"EStateType", true);
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();

	CheckNull(StateComp);
	CheckNull(StateTypeAsUEnum);

	FString typeStr = StateTypeAsUEnum->GetNameStringByValue((int64)StateComp->GetType());

	DrawText(typeStr, FLinearColor::Red, 30.0f, Canvas->ClipY - 50.0f, nullptr, 1.5f);
}
