// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"

// ==================== Primary Attribute ====================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Strength,
	"Attribute.Primary.Strength", "Increases physical damage")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Intelligence,
	"Attribute.Primary.Intelligence", "Increases magical damage")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Vigor,
	"Attribute.Primary.Vigor", "Increases Health")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Resilience,
	"Attribute.Primary.Resilience", "Increases Armor and Armor Penetration")

// ==================== Secondary Attribute ====================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_Armor,
	"Attribute.Secondary.Armor", "Reduce damage taken, improve block chance")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_ArmorPenetration,
	"Attribute.Secondary.ArmorPenetration", "Ignores percentage of enemy Armor, increases Crit Hit Chance")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_BlockChance,
	"Attribute.Secondary.BlockChance", "Chance to cut incoming damage in half")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_CriticalHitChance,
	"Attribute.Secondary.CriticalHitChance", "Chance to double damage plus critical hit bonus")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_CriticalHitDamage,
	"Attribute.Secondary.CriticalHitDamage", "Bonus damage added when a critical hit is scored")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_CriticalHitResistance,
	"Attribute.Secondary.CriticalHitResistance", "Reduces critical hit chance of attacking enemies")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_HealthRegeneration,
	"Attribute.Secondary.HealthRegeneration", "Amount of Health regenerated every 1 second")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_ManaRegeneration,
	"Attribute.Secondary.ManaRegeneration", "Amount of Mana regenerated every 1 second")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_MaxHealth,
	"Attribute.Secondary.MaxHealth", "Maximum amount of Health obtainable")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_MaxMana,
	"Attribute.Secondary.MaxMana", "Maximum amount of Mana obtainable")
// ==================== InputTag ====================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_LMB_1,
	"Input.LMB_1", "Left Mouse Key Input")
UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_RMB_1,
	"Input.RMB_1", "Right Mouse Key Input")