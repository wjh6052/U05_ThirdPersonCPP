#include "CDoor.h"
#include "Global.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"




ACDoor::ACDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Box, "Box", Root);
	CHelpers::CreateSceneComponent(this, &DoorFrame, "DoorFrame", Root);
	CHelpers::CreateSceneComponent(this, &Door, "Door", DoorFrame);

	UStaticMesh* doorFrameMeshAsset, * doorMeshAsset;
	CHelpers::GetAsset<UStaticMesh>(&doorFrameMeshAsset, "StaticMesh'/Game/DoorMesh/Props/SM_DoorFrame.SM_DoorFrame'");
	CHelpers::GetAsset<UStaticMesh>(&doorMeshAsset, "SStaticMesh'/Game/DoorMesh/Props/SM_Door.SM_Door'");

	DoorFrame->SetStaticMesh(doorFrameMeshAsset);
	Door->SetStaticMesh(doorMeshAsset);
	Door->SetRelativeLocation(FVector(0, 45, 0));

	Box->SetCollisionProfileName("Interact");
	Box->SetRelativeLocation(FVector(0, 0, 100));
	Box->SetBoxExtent(FVector(25, 60, 100));
	Box->bHiddenInGame = false;
}

void ACDoor::BeginPlay()
{
	Super::BeginPlay();
	
#ifdef VisibleDrawDebug

	DrawDebugDirectionalArrow
	(
		GetWorld(),
		GetActorLocation() + FVector(0, 0, 100),
		GetActorLocation() + FVector(0, 0, 100) + GetActorForwardVector() * 100.f,
		10,
		FColor::Red,
		true,
		-1,
		0,
		5.f
	);

#endif

}

void ACDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//실제 문을 열고 닫는 행위

	FRotator currentRotation = Door->GetRelativeRotation();
	CLog::Print(currentRotation, 1);

	if (bOpen)
	{
		//문을 여는 행위
		Door->SetRelativeRotation(FMath::Lerp(currentRotation, FRotator(0, MaxYawWithDirection, 0), ConstantRatio));
		return;
	}


	Door->SetRelativeRotation(FMath::Lerp(currentRotation, FRotator::ZeroRotator, ConstantRatio));
	return;
	//문을 닫는 행위
}

void ACDoor::Interact(class ACharacter* InCharacter)
{

	//문을 열기 위한 플래그만 세우다
	

	//앞뒤 판단
	FVector doorFoward = GetActorForwardVector();
	FVector characterForward = InCharacter->GetActorForwardVector();

	float bDirection = FMath::Sign(doorFoward | characterForward);

	MaxYawWithDirection = bDirection * MaxYaw;

	bOpen = !bOpen;

}


