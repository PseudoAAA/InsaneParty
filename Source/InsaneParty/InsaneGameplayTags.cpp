// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneGameplayTags.h"

namespace InsaneGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayStatus_IsDead, "GameplayStatus.IsDead", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayStatus_RemoveOnDeath, "GameplayStatus.RemoveOnDeath", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayEffect_Damage, "GameplayEffect.Damage", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayEffect_Heal, "GameplayEffect.Heal", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayEffect_ShootDelay, "GameplayEffect.ShootDelay", "");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_IsDead, "Activation.Fail.IsDead", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_OnCooldown, "Activation.Fail.OnCooldown", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_CantAffordCost, "Activation.Fail.CantAffordCost", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_BlockedByTags, "Activation.Fail.BlockedByTags", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_MissingTags, "Activation.Fail.MissingTags", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_Networking, "Activation.Fail.Networking", "")

	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Inventory_Slot1, "Inventory.Slot1", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Inventory_Slot2, "Inventory.Slot2", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Inventory_Slot3, "Inventory.Slot3", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Inventory_DropWeapon, "Inventory.DropWeapon", "")
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Weapon_SwitchFireMode, "Weapon.SwitchFireMode", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Weapon_FireMode_None, "Weapon.FireMode.None", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Weapon_FireMode_Single, "Weapon.FireMode.Single", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Weapon_FireMode_FullAuto, "Weapon.FireMode.FullAuto", "")

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(PlayerActions_Shoot, "PlayerActions.Shoot", "")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(PlayerActions_Aiming, "PlayerActions.Aiming", "")
}

