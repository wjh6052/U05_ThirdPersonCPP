#include "CMagicBall.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACMagicBall::ACMagicBall()
{
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere");
	CHelpers::CreateSceneComponent(this, &Particle, "Particle", Sphere);

	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	InitialLifeSpan = 3.0f;

	Projectile->InitialSpeed = 2000.0f;
	Projectile->MaxSpeed = 4000.0f;
	Projectile->ProjectileGravityScale = 0.0f;
}


void ACMagicBall::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACMagicBall::OnBeginOverlap);
}


void ACMagicBall::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Play ImpactPartice
	if (!!Data.Effect)
	{
		FTransform transform = Data.EffectTransform;
		transform.AddToTranslation(GetActorLocation());
		transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Data.Effect, transform);
	}

	//Damage Event
	if (OnMagicBallOverlap.IsBound())
		OnMagicBallOverlap.Broadcast(SweepResult);

	Destroy();
}
