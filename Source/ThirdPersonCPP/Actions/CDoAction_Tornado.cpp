#include "CDoAction_Tornado.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "CAttachment.h"




void ACDoAction_Tornado::BeginPlay()
{
	Super::BeginPlay();

	//Attahcment->Box
	for (AActor* child : OwnerCharacter->Children)
	{
		if (child->IsA<ACAttachment>() && child->GetActorLabel().Contains("Tornado"))
		{
			Box = CHelpers::GetComponent<UBoxComponent>(child);
			break;
		}
	}

}

void ACDoAction_Tornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = OwnerCharacter->GetActorLocation();

	CurrentYaw += AroundSpeed * DeltaTime;
	CurrentYaw = FMath::Fmod(CurrentYaw, 360.0f);

	FVector awayFrom = FVector(Radius, 0, 0);
	FVector rotVector = awayFrom.RotateAngleAxis(CurrentYaw, FVector::UpVector);

	location += rotVector;

	Box->SetWorldLocation(location);
}

void ACDoAction_Tornado::DoAction()
{
	Super::DoAction();

	CheckFalse(StateComp->IsIdleMode());
	CheckTrue(bActivating);


	bActivating = true;
	StateComp->SetActionMode();


	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();

}

void ACDoAction_Tornado::Begin_DoAction()
{
	Super::Begin_DoAction();

	CurrentYaw = OwnerCharacter->GetActorForwardVector().Rotation().Yaw;


	//Spawn Particle
	Particle = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, "");
	Particle->SetRelativeLocation(Datas[0].EffectTransform.GetLocation());
	Particle->SetRelativeScale3D(Datas[0].EffectTransform.GetScale3D());


	//On Collosion
	//Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	if (!!attachment)
		attachment->OnCollision();


	//DamageTime Timer Event
	UKismetSystemLibrary::K2_SetTimer(this, "TickDamege", DamageTime, true);
}

void ACDoAction_Tornado::End_DoAction()
{
	Super::End_DoAction();

	StateComp->SetIdleMode();
	StatusComp->SetMove();


	FTimerDynamicDelegate onFinish;
	onFinish.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(onFinish, ActiveTime, false);
}



void ACDoAction_Tornado::TickDamege()
{
	FDamageEvent damageEvent;

	for (int32 i = 0; i < HittedCharacters.Num(); i++)
	{
		//�̹� ���� ���x
		UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(HittedCharacters[i]);
		
		bool bIgnore = false;
		bIgnore |= (StateComp == nullptr);					//Already Dead
		bIgnore |= (HittedCharacters[i]->IsPendingKill());	//GBC Ready to Relese
		bIgnore |= (HittedCharacters[i] == nullptr);		//Released from Memory 


		//�޸𸮿��� ������ �� X
		if (bIgnore) continue;


		//TakeDemege
		HittedCharacters[i]->TakeDamage(Datas[0].Power, damageEvent, OwnerCharacter->GetController(), this);
	
	}
}

void ACDoAction_Tornado::OnAttachmentBeginOverlap(UPrimitiveComponent* InOverlappedComponent, ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InOverlappedComponent, InAttacker, InCauser, InOtherCharacter);

	HittedCharacters.AddUnique(InOtherCharacter);
}

void ACDoAction_Tornado::OnAttachmentEndOverlap(UPrimitiveComponent* InOverlappedComponent, ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InOverlappedComponent, InAttacker, InCauser, InOtherCharacter);

	HittedCharacters.Remove(InOtherCharacter);
}

void ACDoAction_Tornado::Finish()
{
	bActivating = false;

	// ��ƼŬ ����
	if(!!Particle)
		Particle->DestroyComponent();


	//�浹ü ����
	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	if (!!attachment)
		attachment->OffCollision();


	//Ÿ�̸� ����
	UKismetSystemLibrary::K2_ClearTimer(this, "TickDamege");
}


void ACDoAction_Tornado::Abort()
{
	Finish();
}