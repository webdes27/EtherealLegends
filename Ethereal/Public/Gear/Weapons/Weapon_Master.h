// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once

#include "Gear/EtherealGearMaster.h"
#include "Weapon_Master.generated.h"

/**
 * 
 */
UCLASS()
class ETHEREAL_API AWeapon_Master : public AEtherealGearMaster
{
	GENERATED_BODY()
	
public:

	AWeapon_Master(const FObjectInitializer& ObjectInitializer);

	/** Whether or not this weapon is visible on screen. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsVisible;
	/** Sets Mesh visibility based on Weapon Type. */
	UFUNCTION(BlueprintCallable, Category = Controls)
	void SetVisible();

	/** Weapon Meshes. */
	// Weapon Skeletal Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	USkeletalMeshComponent* WeaponSkeletalMesh;
	USkeletalMesh* SK_WeaponSkeletalMesh;
	// Weapon Static Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	UStaticMeshComponent* WeaponStaticMesh;
	UStaticMesh* SM_WeaponStaticMesh;
	// Weapon Offhand (used mainly for Magic Orb type weapons).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	UStaticMeshComponent* WeaponOffhandMesh;
	UStaticMesh* SM_WeaponOffhandMesh;

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

	FORCEINLINE void SetupSKComponentsWithCollision(USkeletalMeshComponent* Comp)
	{
		if (!Comp) return;

		Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldDynamic);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Comp->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
		Comp->SetVisibility(false);
		Comp->SetHiddenInGame(false);
	}

	UFUNCTION(BlueprintCallable, Category = Combat)
	void OnHit(UObject* CharacterMaster);
};
