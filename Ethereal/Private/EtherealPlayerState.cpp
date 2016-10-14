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

// These are all included here so that they can be referenced for the CreateGear() function. It's UGLY AS SHIT, and should probably be refactored.
#include "Gear/Magic/Spells/Cure.h"
#include "Gear/Magic/Spells/CureII.h"
#include "Gear/Magic/Spells/Regen.h"
#include "Gear/Magic/Spells/Refresh.h"
#include "Gear/Magic/Spells/Blizzard.h"
#include "Gear/Magic/Spells/Thunder.h"
#include "Gear/Magic/Spells/Fire.h"
#include "Gear/Magic/Spells/Berserk.h"
#include "Gear/Magic/Spells/Barrier.h"
#include "Gear/Magic/Spells/Haste.h"
#include "Gear/Magic/Spells/Dash.h"

#include "Gear/Weapons/OneHanded/IronSword.h"
#include "Gear/Weapons/OneHanded/Joyeuse.h"
#include "Gear/Weapons/OneHanded/Hauteclaire.h"
#include "Gear/Weapons/OneHanded/Excalibur.h"
#include "Gear/Weapons/OneHanded/BalloonSword.h"
#include "Gear/Weapons/OneHanded/BeamSaber.h"

#include "Gear/Weapons/OneHanded/Shields/Aegis.h"
#include "Gear/Weapons/OneHanded/Shields/DiablosDread.h"
#include "Gear/Weapons/OneHanded/Shields/SpartanShield.h"
#include "Gear/Weapons/OneHanded/Shields/WarAspis.h"

#include "Gear/Weapons/Ranged/ShortBow.h"
#include "Gear/Weapons/Ranged/EagleEye.h"
#include "Gear/Weapons/Ranged/EurytosBow.h"
#include "Gear/Weapons/Ranged/Annihilator.h"

#include "Gear/Weapons/Ranged/Ammo/DemonArrow.h"
#include "Gear/Weapons/Ranged/Ammo/FlameArrow.h"
#include "Gear/Weapons/Ranged/Ammo/IronArrow.h"
#include "Gear/Weapons/Ranged/Ammo/WoodenArrow.h"

#include "Gear/Weapons/TwoHanded/Marauder.h"
#include "Gear/Weapons/TwoHanded/Juggernaut.h"
#include "Gear/Weapons/TwoHanded/Claymore.h"
#include "Gear/Weapons/TwoHanded/Temperance.h"

#include "Gear/Weapons/Casting/MagicOrbs.h"

#include "Gear/Items/Consumable/Potion.h"
#include "Gear/Items/Consumable/HiPotion.h"
#include "Gear/Items/Consumable/Ether.h"
#include "Gear/Items/Consumable/HiEther.h"
#include "Gear/Items/Consumable/Reraise.h"
#include "Gear/Items/Consumable/Elixer.h"
#include "Gear/Items/Consumable/Adrenaline.h"
#include "Gear/Items/Consumable/SentinelBrew.h"

#include "Gear/Armor/Head/ClothCap.h"
#include "Gear/Armor/Head/AdamanHelm.h"
#include "Gear/Armor/Head/WarHelm.h"
#include "Gear/Armor/Head/ValhallaHelm.h"

#include "Gear/Armor/Cape/ClothCape.h"
#include "Gear/Armor/Cape/KnightsCape.h"
#include "Gear/Armor/Cape/ThiefsShroud.h"
#include "Gear/Armor/Cape/RestoreCloak.h"

#include "Gear/Armor/Body/ClothTunic.h"
#include "Gear/Armor/Body/AdamanCuirass.h"
#include "Gear/Armor/Body/WarCoat.h"
#include "Gear/Armor/Body/ValhallaBreastplate.h"

#include "Gear/Armor/Hand/ClothGloves.h"
#include "Gear/Armor/Hand/AdamanGauntlets.h"
#include "Gear/Armor/Hand/WarGloves.h"
#include "Gear/Armor/Hand/ValhallaGauntlets.h"

#include "Gear/Armor/Legs/ClothPants.h"
#include "Gear/Armor/Legs/AdamanCuisses.h"
#include "Gear/Armor/Legs/WarBrais.h"
#include "Gear/Armor/Legs/ValhallaFlanchard.h"

#include "Gear/Armor/Ring/SilverRing.h"
#include "Gear/Armor/Ring/DarksteelRing.h"
#include "Gear/Armor/Ring/ShadowRing.h"
#include "Gear/Armor/Ring/RestoreRing.h"

#include "Gear/Armor/Feet/ClothShoes.h"
#include "Gear/Armor/Feet/AdamanSabatons.h"
#include "Gear/Armor/Feet/WarBoots.h"
#include "Gear/Armor/Feet/ValhallaGreaves.h"

#include "Gear/Items/Item_Master.h"
#include "Characters/Player/EtherealPlayerMaster.h"
#include "Characters/Enemy/EtherealEnemyMaster.h"
#include "EtherealPlayerState.h"

AEtherealPlayerState::AEtherealPlayerState(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	// Set Default Stats
	PlayerLevel = 5;
	HP_Current = 0;
	HP_Max = 0;
	MP_Current = 0;
	MP_Max = 0;
	TP_Current = 0;
	TP_Max = 0;
	ATK = 0;
	DEF = 0;
	SPD = 0;
	RefreshRate = 0;
	RegenRate = 0;
	EXP_Current = 5000;
	Gold_Current = 0;

	Binding_Magic_Slot1 = EMasterGearList::GL_None;
	Binding_Magic_Slot2 = EMasterGearList::GL_None;
	Binding_Magic_Slot3 = EMasterGearList::GL_None;
	Binding_Magic_Slot4 = EMasterGearList::GL_None;
	Binding_Magic_Slot5 = EMasterGearList::GL_None;
	Binding_Magic_Slot6 = EMasterGearList::GL_None;

	Binding_Weapon_Main = EMasterGearList::GL_None;
	Binding_Weapon_Sub = EMasterGearList::GL_None;

	Binding_Armor_Head = EMasterGearList::GL_None;
	Binding_Armor_Cape = EMasterGearList::GL_None;
	Binding_Armor_Body = EMasterGearList::GL_None;
	Binding_Armor_Hand = EMasterGearList::GL_None;
	Binding_Armor_Legs = EMasterGearList::GL_None;
	Binding_Armor_Ring = EMasterGearList::GL_None;
	Binding_Armor_Feet = EMasterGearList::GL_None;

	Binding_Item_Current = EMasterGearList::GL_None;
}

// Called when the game starts or when spawned
void AEtherealPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

// SET BASE STATS
void AEtherealPlayerState::SetBaseStats()
{
	int32 BaseHP = PlayerLevel * 200;
	int32 BaseMP = PlayerLevel * 20;
	float BaseStats = PlayerLevel * 5.1f;

	HP_Current = BaseHP;
	HP_Max = BaseHP;
	MP_Current = BaseMP;
	MP_Max = BaseMP;
	ATK = BaseStats;
	DEF = BaseStats;
	SPD = BaseStats;
	RefreshRate = 1;
	RegenRate = 1;
}

// Completely Refill HP & MP 
void AEtherealPlayerState::RestoreAll()
{
	HP_Current = HP_Max;
	MP_Current = MP_Max;
}

// Force HP Caps
void AEtherealPlayerState::ForceHPCaps()
{
	// If HP is greater than Max, set HP to Max
	if (HP_Current > HP_Max)
	{
		HP_Current = HP_Max;
	}
	// If HP is less than Zero, set HP to Zero
	if (HP_Current < 0)
	{
		HP_Current = 0;
		Player->StartDeathCycle();  // start death cycle
	}
}

// Force MP Caps
void AEtherealPlayerState::ForceMPCaps()
{
	// If MP is greater than Max, set MP to Max
	if (MP_Current > MP_Max)
	{
		MP_Current = MP_Max;
	}
	// if MP is less than Zero, set MP to Zero
	if (MP_Current < 0)
	{
		MP_Current = 0;
	}
}

// SET TNL
void AEtherealPlayerState::SetTNL()
{
	switch (PlayerLevel)
	{
		case 1:
			EXP_ToNextLevel = 1250;
			break;
		case 2:
			EXP_ToNextLevel = 2250;
			break;
		case 3:
			EXP_ToNextLevel = 3500;
			break;
		case 4:
			EXP_ToNextLevel = 5000;
			break;
		case 5:
			EXP_ToNextLevel = 6750;
			break;
		case 6:
			EXP_ToNextLevel = 8750;
			break;
		case 7:
			EXP_ToNextLevel = 10950;
			break;
		case 8:
			EXP_ToNextLevel = 13350;
			break;
		case 9:
			EXP_ToNextLevel = 15950;
			break;
		case 10:
			EXP_ToNextLevel = 13350;
			break;
		case 11:
			EXP_ToNextLevel = 15950;
			break;
		case 12:
			EXP_ToNextLevel = 18750;
			break;
		case 13:
			EXP_ToNextLevel = 21750;
			break;
		case 14:
			EXP_ToNextLevel = 24950;
			break;
		case 15:
			EXP_ToNextLevel = 28350;
			break;
		case 16:
			EXP_ToNextLevel = 31950;
			break;
		case 17:
			EXP_ToNextLevel = 35750;
			break;
		case 18:
			EXP_ToNextLevel = 39750;
			break;
		case 19:
			EXP_ToNextLevel = 43950;
			break;
		case 20:
			EXP_ToNextLevel = 48350;
			break;
		case 21:
			EXP_ToNextLevel = 52950;
			break;
		case 22:
			EXP_ToNextLevel = 57750;
			break;
		case 23:
			EXP_ToNextLevel = 62750;
			break;
		case 24:
			EXP_ToNextLevel = 67850;
			break;
		case 25:
			EXP_ToNextLevel = 73050;
			break;
		case 26:
			EXP_ToNextLevel = 78350;
			break;
		case 27:
			EXP_ToNextLevel = 83750;
			break;
		case 28:
			EXP_ToNextLevel = 89250;
			break;
		case 29:
			EXP_ToNextLevel = 94850;
			break;
		case 30:
			EXP_ToNextLevel = 100550;
			break;
		case 31:
			EXP_ToNextLevel = 106350;
			break;
		case 32:
			EXP_ToNextLevel = 112250;
			break;
		case 33:
			EXP_ToNextLevel = 118250;
			break;
		case 34:
			EXP_ToNextLevel = 124350;
			break;
		case 35:
			EXP_ToNextLevel = 130550;
			break;
		case 36:
			EXP_ToNextLevel = 136850;
			break;
		case 37:
			EXP_ToNextLevel = 143250;
			break;
		case 38:
			EXP_ToNextLevel = 149750;
			break;
		case 39:
			EXP_ToNextLevel = 156350;
			break;
		case 40:
			EXP_ToNextLevel = 163050;
			break;
		case 41:
			EXP_ToNextLevel = 169850;
			break;
		case 42:
			EXP_ToNextLevel = 176750;
			break;
		case 43:
			EXP_ToNextLevel = 183750;
			break;
		case 44:
			EXP_ToNextLevel = 190850;
			break;
		case 45:
			EXP_ToNextLevel = 198050;
			break;
		case 46:
			EXP_ToNextLevel = 205350;
			break;
		case 47:
			EXP_ToNextLevel = 212750;
			break;
		case 48:
			EXP_ToNextLevel = 220250;
			break;
		case 49:
			EXP_ToNextLevel = 227850;
			break;
		case 50:
			EXP_ToNextLevel = 235550;
			break;
		case 51:
			EXP_ToNextLevel = 243350;
			break;
		case 52:
			EXP_ToNextLevel = 251350;
			break;
		case 53:
			EXP_ToNextLevel = 260550;
			break;
		case 54:
			EXP_ToNextLevel = 270950;
			break;
		case 55:
			EXP_ToNextLevel = 282550;
			break;
		case 56:
			EXP_ToNextLevel = 295350;
			break;
		case 57:
			EXP_ToNextLevel = 309350;
			break;
		case 58:
			EXP_ToNextLevel = 324550;
			break;
		case 59:
			EXP_ToNextLevel = 340950;
			break;
		case 60:
			EXP_ToNextLevel = 358550;
			break;
	}
}

// Add EXP
void AEtherealPlayerState::AddEXP(int modEXP)
{
	FString message = TEXT("+  ") + FString::FromInt(modEXP) + TEXT("  EXP");  // build the proper string
	FText displaytext = FText::FromString(message);  // convert it to text

	// 60 is the current level cap, so we only give EXP if the player is below that level
	if (PlayerLevel < 60)
	{
		EXP_Current = EXP_Current + modEXP;  // add EXP
		Player->CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_Text, displaytext);  // Display EXP gained on screen
	}	
}

// Add Gold
void AEtherealPlayerState::AddGold(int modGold)
{
	FString message = TEXT("+  ") + FString::FromInt(modGold) + TEXT("  GOLD");  // build the proper string
	FText displaytext = FText::FromString(message);  // convert it to text

	Gold_Current = Gold_Current + modGold;  // add Gold

	Player->CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_Text, displaytext);  // Display Gold gained on screen
}

// Drop Items
void AEtherealPlayerState::DropItems(EMasterGearList Common, EMasterGearList Uncommon, EMasterGearList Rare)
{
	// ENEMY KILL RANDOM DROPS
	int32 Drop = FMath::FloorToInt(FMath::FRandRange(0, 100));

	if (Drop <= 5)
	{
		// RARE DROP @ 5 %
		//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.25f); // Slow Motion because you got something cool
		AddToInventory(Rare, false, true);
	}
	if (Drop >= 70)
	{
		// UNCOMMON DROP @ 30 %
		//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.25f); // Slow Motion because you got something cool
		AddToInventory(Uncommon, false, true);
	}
	if (Drop > 5 && Drop < 70)
	{
		if (Common != EMasterGearList::GL_None)  // do nothing if common drop = none
		{
			// COMMON DROP @ 65 %
			AddToInventory(Common, false, true);
		}		
	}
}

// Enemy Kill Reward
void AEtherealPlayerState::EnemyKillReward(int EnemyLevel, EMasterGearList Common, EMasterGearList Uncommon, EMasterGearList Rare)
{
	KillCount++;  // increment total kill count

	// create bonus values
	int32 modEXP = (EnemyLevel * 25);
	int32 modGold = (EnemyLevel * 15);

	// wait a bit before adding EXP (delays the UI display for readability).
	FTimerDelegate DelegateEXP;
	DelegateEXP.BindUFunction(this, FName("AddEXP"), modEXP);
	FTimerHandle EXPTimer;
	GetWorldTimerManager().SetTimer(EXPTimer, DelegateEXP, 0.1f, false);

	// wait a bit longer before adding Gold (delays the UI display, again for readability).
	FTimerDelegate DelegateGold;
	DelegateGold.BindUFunction(this, FName("AddGold"), modGold);
	FTimerHandle GoldTimer;
	GetWorldTimerManager().SetTimer(GoldTimer, DelegateGold, 0.5f, false);

	// wait just a bit longer to determine whether or not the player should level up
	FTimerHandle LevelUpTimer;
	GetWorldTimerManager().SetTimer(LevelUpTimer, this, &AEtherealPlayerState::LevelUp, 0.5f, false);

	// wait a just a bit longer to distribute drops (delays the UI display, again for readability).
	FTimerDelegate DelegateDrops;
	DelegateDrops.BindUFunction(this, FName("DropItems"), Common, Uncommon, Rare);
	FTimerHandle DropTimer;
	GetWorldTimerManager().SetTimer(DropTimer, DelegateDrops, 0.8f, false);
}

// Level Up
void AEtherealPlayerState::LevelUp()
{
	// Players gain no EXP after level 60
	if (PlayerLevel < 60)
	{
		// if Current EXP is greater than TNL
		if (EXP_Current >= EXP_ToNextLevel)
		{
			UGameplayStatics::PlayWorldCameraShake(GetWorld(), Player->LevelUpCamShake, Player->GetActorLocation(), 0, 10000, 1, false);  // level up cam shake 
			PlayerLevel++;  // player level + 1
			SetBaseStats();  // Reset the Base Stats
			
			// Reset the Player's currently equipped gear stat additions
			for (AEtherealGearMaster* Gear : Inventory)  // scan the inventory...
			{
				if (Gear->IsBound)  // if ItemToGet matches the name of an item currently in the inventory
				{
					Gear->AddGearStats();  // Add the Gear Stats for each currently bound item
				}
			}

			RestoreAll();  // restore all hp and mp
			Player->LevelUpFX->Activate(true);  // activate level up particle effect
			Player->AudioManager->Play_SFX_LevelUp();  // play level up audio sound effect
			SetTNL();  // set new TNL
			
			// Since this function is called whenever an enemy dies, we'll check to make sure it's not the last enemy in the aggro list
			if (Player->AggroList.Num() > 0)
			{
				AEtherealEnemyMaster* EnemyZero = Player->AggroList[0];  // get the enemy at index 0

				// if the aggro list still has enemies, you're still in battle, so continue to play the battle music
				FTimerDelegate DelegateBattle;
				DelegateBattle.BindUFunction(Player->AudioManager, FName("Play_BattleMusic"), EnemyZero->BattleType);
				FTimerHandle BattleTimer;
				GetWorldTimerManager().SetTimer(BattleTimer, DelegateBattle, 0.8f, false);
			}
			else
			{
				// the aggro list is empty, so you must be out of battle. Play the current Realm's BGM
				FTimerDelegate DelegateBGM;
				DelegateBGM.BindUFunction(Player->AudioManager, FName("Play_BGM"), Player->EtherealGameInstance->CurrentRealm);
				FTimerHandle BGMTimer;
				GetWorldTimerManager().SetTimer(BGMTimer, DelegateBGM, 0.8f, false);
			}
		}
	}	
}

// Regen Tick
void AEtherealPlayerState::Regen()
{
	if (!Player->IsDead) // do not tick if Player is dead
	{
		HP_Current = HP_Current + RegenRate;
		ForceHPCaps();
		// Call Regen again after 1 second
		FTimerHandle CastTimer;
		GetWorldTimerManager().SetTimer(CastTimer, this, &AEtherealPlayerState::Regen, 1.0f, false);
	}	
}

// Refresh Tick
void AEtherealPlayerState::Refresh()
{
	if (!Player->IsDead)  // do not tick if Player is dead
	{
		MP_Current = MP_Current + RefreshRate;
		ForceMPCaps();
		// Call Refresh again after 1 second
		FTimerHandle CastTimer;
		GetWorldTimerManager().SetTimer(CastTimer, this, &AEtherealPlayerState::Refresh, 1.0f, false);
	}	
}

// Creates a Gear Item, when given a name
AEtherealGearMaster* AEtherealPlayerState::CreateGear(EMasterGearList ItemToCreate)
{
	AEtherealGearMaster* Item = nullptr; // set a false item

	switch (ItemToCreate)  // This switch will run through and spawn a piece of Gear based on the name
	{
	case EMasterGearList::GL_None:
		// Do nothing, because the item is set to NONE!
		break;

	///////////////////////////////
	// MAGIC

	case EMasterGearList::GL_Cure:
		Item = GetWorld()->SpawnActor<ACure>();
		break;
	case EMasterGearList::GL_Cure2:
		Item = GetWorld()->SpawnActor<ACureII>();
		break;
	case EMasterGearList::GL_Raise:
		// Do nothing, because Raise does not yet exist
		break;
	case EMasterGearList::GL_Regen:
		Item = GetWorld()->SpawnActor<ARegen>();
		break;
	case EMasterGearList::GL_Refresh:
		Item = GetWorld()->SpawnActor<ARefresh>();
		break;
	case EMasterGearList::GL_Esuna:
		// Do nothing, because Esuna does not yet exist
		break;
	case EMasterGearList::GL_Comet:
		// Do nothing, because Comet does not yet exist
		break;
	case EMasterGearList::GL_Blizzard:
		Item = GetWorld()->SpawnActor<ABlizzard>();
		break;
	case EMasterGearList::GL_Thunder:
		Item = GetWorld()->SpawnActor<AThunder>();
		break;
	case EMasterGearList::GL_Fire:
		Item = GetWorld()->SpawnActor<AFire>();
		break;
	case EMasterGearList::GL_Poison:
		// Do nothing, because Poison does not yet exist
		break;
	case EMasterGearList::GL_Sleep:
		// Do nothing, because Sleep does not yet exist
		break;
	case EMasterGearList::GL_Berserk:
		Item = GetWorld()->SpawnActor<ABerserk>();
		break;
	case EMasterGearList::GL_Barrier:
		Item = GetWorld()->SpawnActor<ABarrier>();
		break;
	case EMasterGearList::GL_Haste:
		Item = GetWorld()->SpawnActor<AHaste>();
		break;
	case EMasterGearList::GL_Slow:
		// Do nothing, because Slow does not yet exist
		break;
	case EMasterGearList::GL_Counter:
		// Do nothing, because Counter does not yet exist
		break;
	case EMasterGearList::GL_Stun:
		// Do nothing, because Stun does not yet exist
		break;
	case EMasterGearList::GL_Dash:
		Item = GetWorld()->SpawnActor<ADash>();
		break;
	case EMasterGearList::GL_Gravity:
		// Do nothing, because Gravity does not yet exist
		break;

	///////////////////////////////
	// ONE-HANDED

	case EMasterGearList::GL_IronSword:
		Item = GetWorld()->SpawnActor<AIronSword>();
		break;
	case EMasterGearList::GL_Joyeuse:
		Item = GetWorld()->SpawnActor<AJoyeuse>();
		break;
	case EMasterGearList::GL_Hauteclaire:
		Item = GetWorld()->SpawnActor<AHauteclaire>();
		break;
	case EMasterGearList::GL_Excalibur:
		Item = GetWorld()->SpawnActor<AExcalibur>();
		break;
	case EMasterGearList::GL_BalloonSword:
		Item = GetWorld()->SpawnActor<ABalloonSword>();
		break;
	case EMasterGearList::GL_BeamSaber:
		Item = GetWorld()->SpawnActor<ABeamSaber>();
		break;

	///////////////////////////////
	// SHIELDS

	case EMasterGearList::GL_WarAspis:
		Item = GetWorld()->SpawnActor<AWarAspis>();
		break;
	case EMasterGearList::GL_SpartanShield:
		Item = GetWorld()->SpawnActor<ASpartanShield>();
		break;
	case EMasterGearList::GL_DiablosDread:
		Item = GetWorld()->SpawnActor<ADiablosDread>();
		break;
	case EMasterGearList::GL_Aegis:
		Item = GetWorld()->SpawnActor<AAegis>();
		break;

	///////////////////////////////
	// RANGED

	case EMasterGearList::GL_ShortBow:
		Item = GetWorld()->SpawnActor<AShortBow>();
		break;
	case EMasterGearList::GL_EagleEye:
		Item = GetWorld()->SpawnActor<AEagleEye>();
		break;
	case EMasterGearList::GL_EurytosBow:
		Item = GetWorld()->SpawnActor<AEurytosBow>();
		break;
	case EMasterGearList::GL_Annihilator:
		Item = GetWorld()->SpawnActor<AAnnihilator>();
		break;

	///////////////////////////////
	// AMMUNITION

	case EMasterGearList::GL_DemonArrow:
		Item = GetWorld()->SpawnActor<ADemonArrow>();
		break;
	case EMasterGearList::GL_FlameArrow:
		Item = GetWorld()->SpawnActor<AFlameArrow>();
		break;
	case EMasterGearList::GL_IronArrow:
		Item = GetWorld()->SpawnActor<AIronArrow>();
		break;
	case EMasterGearList::GL_WoodenArrow:
		Item = GetWorld()->SpawnActor<AWoodenArrow>();
		break;

	///////////////////////////////
	// TWO-HANDED

	case EMasterGearList::GL_Juggernaut:
		Item = GetWorld()->SpawnActor<AJuggernaut>();
		break;
	case EMasterGearList::GL_Claymore:
		Item = GetWorld()->SpawnActor<AClaymore>();
		break;
	case EMasterGearList::GL_Marauder:
		Item = GetWorld()->SpawnActor<AMarauder>();
		break;
	case EMasterGearList::GL_Temperance:
		Item = GetWorld()->SpawnActor<ATemperance>();
		break;

	///////////////////////////////
	// CASTING ORBS

	case EMasterGearList::GL_MagicOrbs:
		Item = GetWorld()->SpawnActor<AMagicOrbs>();
		break;

	///////////////////////////////
	// CONSUMABLE ITEMS

	case EMasterGearList::GL_Potion:
		Item = GetWorld()->SpawnActor<APotion>();
		break;
	case EMasterGearList::GL_HiPotion:
		Item = GetWorld()->SpawnActor<AHiPotion>();
		break;
	case EMasterGearList::GL_Ether:
		Item = GetWorld()->SpawnActor<AEther>();
		break;
	case EMasterGearList::GL_HiEther:
		Item = GetWorld()->SpawnActor<AHiEther>();
		break;
	case EMasterGearList::GL_Elixer:
		Item = GetWorld()->SpawnActor<AElixer>();
		break;
	case EMasterGearList::GL_Reraise:
		Item = GetWorld()->SpawnActor<AReraise>();
		break;
	case EMasterGearList::GL_Adrenaline:
		Item = GetWorld()->SpawnActor<AAdrenaline>();
		break;
	case EMasterGearList::GL_SentinelBrew:
		Item = GetWorld()->SpawnActor<ASentinelBrew>();
		break;

	///////////////////////////////
	// ARMOR - HEAD
	case EMasterGearList::GL_ClothCap:
		Item = GetWorld()->SpawnActor<AClothCap>();
		break;
	case EMasterGearList::GL_AdamanHelm:
		Item = GetWorld()->SpawnActor<AAdamanHelm>();
		break;
	case EMasterGearList::GL_WarHelm:
		Item = GetWorld()->SpawnActor<AWarHelm>();
		break;
	case EMasterGearList::GL_ValhallaHelm:
		Item = GetWorld()->SpawnActor<AValhallaHelm>();
		break;

	///////////////////////////////
	// ARMOR - CAPE
	case EMasterGearList::GL_ClothCape:
		Item = GetWorld()->SpawnActor<AClothCape>();
		break;
	case EMasterGearList::GL_KnightsCape:
		Item = GetWorld()->SpawnActor<AKnightsCape>();
		break;
	case EMasterGearList::GL_ThiefsShroud:
		Item = GetWorld()->SpawnActor<AThiefsShroud>();
		break;
	case EMasterGearList::GL_RestoreCloak:
		Item = GetWorld()->SpawnActor<ARestoreCloak>();
		break;

	///////////////////////////////
	// ARMOR - BODY
	case EMasterGearList::GL_ClothTunic:
		Item = GetWorld()->SpawnActor<AClothTunic>();
		break;
	case EMasterGearList::GL_AdamanCuirass:
		Item = GetWorld()->SpawnActor<AAdamanCuirass>();
		break;
	case EMasterGearList::GL_WarCoat:
		Item = GetWorld()->SpawnActor<AWarCoat>();
		break;
	case EMasterGearList::GL_ValhallaBreastplate:
		Item = GetWorld()->SpawnActor<AValhallaBreastplate>();
		break;

	//////////////////////////////
	// ARMOR - HANDS
	case EMasterGearList::GL_ClothGloves:
		Item = GetWorld()->SpawnActor<AClothGloves>();
		break;
	case EMasterGearList::GL_AdamanGauntlets:
		Item = GetWorld()->SpawnActor<AAdamanGauntlets>();
		break;
	case EMasterGearList::GL_WarGloves:
		Item = GetWorld()->SpawnActor<AWarGloves>();
		break;
	case EMasterGearList::GL_ValhallaGauntlets:
		Item = GetWorld()->SpawnActor<AValhallaGauntlets>();
		break;

	///////////////////////////////
	// ARMOR - LEGS
	case EMasterGearList::GL_ClothPants:
		Item = GetWorld()->SpawnActor<AClothPants>();
		break;
	case EMasterGearList::GL_AdamanCuisses:
		Item = GetWorld()->SpawnActor<AAdamanCuisses>();
		break;
	case EMasterGearList::GL_WarBrais:
		Item = GetWorld()->SpawnActor<AWarBrais>();
		break;
	case EMasterGearList::GL_ValhallaFlanchard:
		Item = GetWorld()->SpawnActor<AValhallaFlanchard>();
		break;

	///////////////////////////////
	// ARMOR - RING
	case EMasterGearList::GL_SilverRing:
		Item = GetWorld()->SpawnActor<ASilverRing>();
		break;
	case EMasterGearList::GL_DarksteelRing:
		Item = GetWorld()->SpawnActor<ADarksteelRing>();
		break;
	case EMasterGearList::GL_ShadowRing:
		Item = GetWorld()->SpawnActor<AShadowRing>();
		break;
	case EMasterGearList::GL_RestoreRing:
		Item = GetWorld()->SpawnActor<ARestoreRing>();
		break;

	///////////////////////////////
	// ARMOR - FEET
	case EMasterGearList::GL_ClothShoes:
		Item = GetWorld()->SpawnActor<AClothShoes>();
		break;
	case EMasterGearList::GL_AdamanSabatons:
		Item = GetWorld()->SpawnActor<AAdamanSabatons>();
		break;
	case EMasterGearList::GL_WarBoots:
		Item = GetWorld()->SpawnActor<AWarBoots>();
		break;
	case EMasterGearList::GL_ValhallaGreaves:
		Item = GetWorld()->SpawnActor<AValhallaGreaves>();
		break;

	}

	//////////////////////////////
	// END
	return Item;
}

// Attaches a piece of Gear to the player
void AEtherealPlayerState::AttachGear(AEtherealGearMaster* Item)
{
	if (Item) // be sure Item is valid
	{
		if (Item->OwnerReference) // ensure the item has a reference to the player
		{
			AWeapon_Master* Weapon = Cast<AWeapon_Master>(Item);  // check if the item is a weapon, and if so, store it's reference.

			switch (Item->Type)
			{
			case EMasterGearTypes::GT_None:
				break;
			case EMasterGearTypes::GT_OneHanded:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket_Right"));
				break;
			case EMasterGearTypes::GT_TwoHanded:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket_GreatSword"));
				break;
			case EMasterGearTypes::GT_Ranged:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket_Bow"));
				break;
			case EMasterGearTypes::GT_Casting:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("CastingOrb_R"));
				if (Weapon)
				{
					Weapon->WeaponOffhandMesh->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("CastingOrb_L"));
				}
				break;
			case EMasterGearTypes::GT_White:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Black:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Support:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Ancient:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Shield:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket_Shield"));
				break;
			case EMasterGearTypes::GT_Ammo:
				//Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket_Ammo"));
				break;
			case EMasterGearTypes::GT_Head:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Cape:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Body:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Hand:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Legs:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Ring:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Feet:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_Consumable:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			case EMasterGearTypes::GT_KeyItem:
				Item->AttachToComponent(Item->OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PowerSocket"));
				break;
			}
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, "Gear was attached to player.");
		}
	}	
}

// Get Inventory Item
AEtherealGearMaster* AEtherealPlayerState::GetInventoryItem(EMasterGearList ItemToGet)
{
	AEtherealGearMaster* Item = nullptr; // set a false item

	for (AEtherealGearMaster* GearItem : Inventory)  // scan the inventory...
	{
		if (GearItem->Name == ItemToGet)  // if ItemToGet matches the name of an item currently in the inventory
		{
			Item = GearItem;  // set the Item reference to be returned
			return Item;
		}
		else
		{
			Item = nullptr;  // no item name match was found, so return null
		}
	}
	return Item;
}

// Create and Add Inventory Item, based on given item name
void AEtherealPlayerState::AddToInventory(EMasterGearList ItemToAdd, bool ShouldBind, bool ShowNameText)
{
	bool CanAdd = true;  // always start by assuming you can add the item

	if (Inventory.Num() > 0)  // check if the inventory is empty
	{
		for (AEtherealGearMaster* GearItem : Inventory)  // inventory wasn't empty, so for each item in the inventory...
		{
			if (GearItem->Name == ItemToAdd) // check if ItemToAdd matches anything currently in the inventory
			{
				CanAdd = false; // if so, set CanAdd to false				

				if (GearItem->Type == EMasterGearTypes::GT_Consumable) // check to ensure the item is consumable
				{
					AItem_Master* ConsumableItem = Cast<AItem_Master>(GearItem);
					
					// Only add consumable items if their quantity is less than 99
					if (ConsumableItem->Quantity < 99)
					{
						IncrementItemQuantity(GearItem);  // increase item's quantity
					}
					else
					{
						ConsumableItem->Destroy();  // You were maxed out, so destroy this item instead
					}
				}
			}
		}
	}

	if (CanAdd) // if CanAdd is still true, because no existing match was found in inventory
	{
		AEtherealGearMaster* Gear = CreateGear(ItemToAdd); // create the new item

		if (Gear) // ensure gear was created successfully
		{
			Gear->ConfigureGear(Player); // configure this gear item
			Inventory.AddUnique(Gear); // add the item to the player's inventory
			AttachGear(Gear); // attach the Gear to the player
			
			// Bind this Gear to the player if required
			if (ShouldBind)
			{
				if (Gear->Type == EMasterGearTypes::GT_Consumable || Gear->Type == EMasterGearTypes::GT_KeyItem)
				{
					return;  // do not bind if Gear is a Consumable or a Key Item
				}
				else
				{
					Gear->Bind();  // Bind the item if necessary (this is usually only true when first loading the game)
				}				
			}
			if (ShowNameText)
			{
				// if this function was called with ShowNameText set to TRUE, then we'll display the item's name on screen
				FText Name = Gear->NameText;
				Player->CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_Drop, Name);  // display text on screen
			}
		}		
	}
}

// Increment Item Quantity
void AEtherealPlayerState::IncrementItemQuantity(AEtherealGearMaster* Item)
{
	AItem_Master* ConsumableItem = Cast<AItem_Master>(Item);  // cast to the Master Item class
	ConsumableItem->Quantity = ConsumableItem->Quantity + 1;  // increment the item's quantity by 1
}

// REMOVE GEAR STATS
void AEtherealPlayerState::RemoveGearStats(EMasterGearList GearName)
{
	// Get the inventory item
	AEtherealGearMaster* Gear = GetInventoryItem(GearName);

	// Add stats from gear to the player's stats
	ATK = (ATK - Gear->ATK);
	DEF = (DEF - Gear->DEF);
	SPD = (SPD - Gear->SPD);
	HP_Max = (HP_Max - Gear->HP);
	MP_Max = (MP_Max - Gear->MP);
}

// Adds default items to the player's inventory. Used when starting a new game without previous save data, so the player doesn't have to start with nothing.
void AEtherealPlayerState::AddDefaultItems()
{
	AddToInventory(EMasterGearList::GL_ClothTunic, false, false);
	AddToInventory(EMasterGearList::GL_IronSword, false, false);
	AddToInventory(EMasterGearList::GL_WarAspis, false, false);
	AddToInventory(EMasterGearList::GL_Cure, false, false);
	AddToInventory(EMasterGearList::GL_Thunder, false, false);
	AddToInventory(EMasterGearList::GL_Dash, false, false);
	AddToInventory(EMasterGearList::GL_Potion, false, false);
	AddToInventory(EMasterGearList::GL_Potion, false, false);
}

// Unbind all Items
void AEtherealPlayerState::UnbindAll()
{
	for (AEtherealGearMaster* GearItem : Inventory)  // for each item in the inventory...
	{
		GearItem->Unbind(); // Unbind item
		// TO DO : these should be destroyed after they're unbound, since this function is currently only being called from the main menu, when you've chosen to start a new game (which deletes your old save file)
	}

	// Set all Magic Bindings to None
	Binding_Magic_Slot1 = EMasterGearList::GL_None;
	Binding_Magic_Slot2 = EMasterGearList::GL_None;
	Binding_Magic_Slot3 = EMasterGearList::GL_None;
	Binding_Magic_Slot4 = EMasterGearList::GL_None;
	Binding_Magic_Slot5 = EMasterGearList::GL_None;
	Binding_Magic_Slot6 = EMasterGearList::GL_None;

	// Set All Weapon Bindings to None
	Binding_Weapon_Main = EMasterGearList::GL_None;
	Binding_Weapon_Sub = EMasterGearList::GL_None;

	Inventory.Empty();  // clear the player's inventory

	AddDefaultItems();  // Give the player default items, so they're not fully useless
}