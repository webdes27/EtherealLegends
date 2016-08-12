// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once

#include "GameFramework/Character.h"
//#include "Sound/SoundCue.h"
#include "EtherealCharacterMaster.generated.h"

UCLASS()
class ETHEREAL_API AEtherealCharacterMaster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEtherealCharacterMaster(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Whether or not this character is dead
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsDead;

	// Whether or not this character is targetable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	bool Targetable;

	// Default Capsule Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCapsuleComponent* Capsule;

	// Targeting Notification Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	UAudioComponent* TargetingAudio;
	USoundCue* S_TargetingAudio;

	// Targeting Reticle Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	UStaticMeshComponent* TargetingReticle;
	UStaticMesh* SM_TargetingReticle;

	/** Sets Mesh visibility based on Weapon Type. */
	UFUNCTION(BlueprintCallable, Category = Targeting)
	void ToggleReticle(bool Visible);

	FORCEINLINE void SetupSMComponentsWithCollision(UStaticMeshComponent* Comp)
	{
		if (!Comp) return;

		Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldDynamic);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Comp->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
		Comp->SetHiddenInGame(false);
	}
	
};
