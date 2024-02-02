#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	Super::BeginPlay();
	
}

void ACAttachment::AttachTo(FName InSocketName)
{
	CheckNull(OwnerCharacter);

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}
