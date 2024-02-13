#include "CAim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CHUD.h"

UCAim::UCAim()
{
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/Datas/Curve_FOV.Curve_FOV'");
}

void UCAim::BeginPlay(class ACharacter* InOwnerCharacter)
{
	OwnerCharacter = InOwnerCharacter;
	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	FOnTimelineFloat OnProgress;
	OnProgress.BindUFunction(this, "Zooming");
	AimTimeline.AddInterpFloat(Curve, OnProgress);
	AimTimeline.SetPlayRate(100);


	//수단 방법 가리지 않고 HUD 객체를 가져와서 저장
	HUD = OwnerCharacter->GetWorld()->GetFirstPlayerController()->GetHUD<ACHUD>();
}

void UCAim::Tick(float DeltaTime)
{
	AimTimeline.TickTimeline(DeltaTime);
}

void UCAim::On()
{
	CheckFalse(IsCanAim());
	CheckTrue(bZooming);

	bZooming = true;

	HUD->EnableCrossHair();

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	SpringArm->bEnableCameraLag = false;

	AimTimeline.PlayFromStart();
}

void UCAim::Off()
{
	CheckFalse(IsCanAim());
	CheckFalse(bZooming);

	bZooming = false;

	HUD->DisableCrossHair();

	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bEnableCameraLag = true;

	AimTimeline.ReverseFromEnd();
}

void UCAim::Zooming(float Output)
{
	Camera->SetFieldOfView(Output);
}
