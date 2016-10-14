// © 2014 - 2016 Soverance Studios
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
#include "ClothCap.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AClothCap::AClothCap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ClothCap.ArmorIcon_ClothCap'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ClothCap-small.ArmorIcon_ClothCap-small'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	
	// Set Default Values
	Name = EMasterGearList::GL_ClothCap;
	NameText = LOCTEXT("ClothCapeText", "Cloth Cap");
	Type = EMasterGearTypes::GT_Head;
	Description = "A simple cloth armor set with no special qualities.";
	MPCost = 0;
	ATK = 0;
	DEF = 1;
	SPD = 0;
	HP = 10;
	MP = 0;
}

// Called when the game starts or when spawned
void AClothCap::BeginPlay()
{
	Super::BeginPlay();
}

#undef LOCTEXT_NAMESPACE