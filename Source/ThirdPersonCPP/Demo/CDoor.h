#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "CDoor.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACDoor : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	ACDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Interact(class ACharacter* InCharacter) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Door;


private:
	UPROPERTY(EditAnywhere)
		float MaxYaw = 130.0f;

	UPROPERTY(EditAnywhere)
		float ConstantRatio = 0.05f;

private:
	float MaxYawWithDirection;
	bool bOpen;
};
