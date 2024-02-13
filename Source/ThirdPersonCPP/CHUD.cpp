#include "CHUD.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Engine/Canvas.h"
#include "Components/CStateComponent.h"
#include "Engine/Texture2D.h"

ACHUD::ACHUD()
{
	CHelpers::GetAsset<UTexture2D>(&CrossHairTexture, "Texture2D'/Game/Materials/T_Crosshair.T_Crosshair'");

}

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


	//Visible Player StateType
	CheckNull(StateComp);
	CheckNull(StateTypeAsUEnum);

	FString typeStr = StateTypeAsUEnum->GetNameStringByValue((int64)StateComp->GetType());

	DrawText(typeStr, FLinearColor::Red, 30.0f, Canvas->ClipY - 50.0f, nullptr, 1.5f);

	//Visible Aim(R-Button)
	CheckFalse(CrossHairTexture);
	CheckFalse(bVisbleCrossHair);

	FVector2D center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FVector2D imageHalfSize(CrossHairTexture->GetSizeX() * 0.5f, CrossHairTexture->GetSizeY() * 0.5f);
	center -= imageHalfSize;


	FCanvasTileItem imageItem(center, CrossHairTexture->Resource, FLinearColor::White);
	imageItem.BlendMode = ESimpleElementBlendMode::SE_BLEND_Translucent;
	Canvas->DrawItem(imageItem);
}
