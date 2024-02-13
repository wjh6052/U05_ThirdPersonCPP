#include "CDoAction_MagicBall.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "CAim.h"

void ACDoAction_MagicBall::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);
	
}

void ACDoAction_MagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
}

void ACDoAction_MagicBall::DoAction()
{
	Super::DoAction();

	CheckFalse(Datas.Num() > 0);


	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_MagicBall::Begin_DoAction()
{
	Super::Begin_DoAction();

	//Spawn Projectile Actor
}

void ACDoAction_MagicBall::End_DoAction()
{
	Super::End_DoAction();

	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACDoAction_MagicBall::BeginSubAction()
{
	//On Zoom
	CheckNull(Aim);

	Aim->On();
}

void ACDoAction_MagicBall::EndSubAction()
{
	//Off Zoom
	CheckNull(Aim);

	Aim->Off();

}
