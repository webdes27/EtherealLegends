// © 2014 - 2017 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Ethereal.h"
#include "WarGloves.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AWarGloves::AWarGloves(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_WarGloves.ArmorIcon_WarGloves'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_WarGloves-small.ArmorIcon_WarGloves-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/WarGarb/WarGloves/WarGloves.WarGloves'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_WarGloves;
	NameText = LOCTEXT("WarGlovesName", "War Gloves");
	Type = EMasterGearTypes::GT_Hand;
	TypeText = LOCTEXT("WarGlovesType", "Hands");
	Description = "Armor of Ethereal Rangers.";
	Price = 20000;
	MPCost = 0;
	ATK = 5;
	DEF = 5;
	SPD = 5;
	HP = 100;
	MP = 50;
	SpecialEffectText = LOCTEXT("WarGlovesSpecialEffect", "Ranged Damage +25%.");
}

// Called when the game starts or when spawned
void AWarGloves::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &AWarGloves::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &AWarGloves::RemoveSpecialEffect);
}

// Custom code for Special Effect
void AWarGloves::DoSpecialEffect()
{
	OwnerReference->BoostRanged = true;
}

// Custom code for Special Effect
void AWarGloves::RemoveSpecialEffect()
{
	OwnerReference->BoostRanged = false;
}

#undef LOCTEXT_NAMESPACE
