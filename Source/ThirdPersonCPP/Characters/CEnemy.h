#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ICharacter.h"
#include "Components/TimelineComponent.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACEnemy : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:	
	virtual void SetBodyColor(FLinearColor InColor);

	UFUNCTION()
		void ResetLogoColor();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void Hitted();
	void Dead();

	UFUNCTION()
		void End_Dead();

	
	
	//Scene Component
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;


	//Actor Compoentn
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

private:
	UPROPERTY(EditAnywhere)
		float LaunchValue = 25.0f;

	UPROPERTY(EditAnywhere)
		float DestroyPendingTime = 5.0f;

	UPROPERTY(EditAnywhere)
		class UCurveFloat* DissolveCurve;

	UPROPERTY(VisibleInstanceOnly)
		class UMaterialInstanceDynamic* DissolveMaterial;


private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;


	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;

	FTimeline DissolveTimeline;
};