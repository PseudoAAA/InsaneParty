// 2024, Pseudo / Ageev Daniil. All rights reserved ©


#include "InsaneWeaponPrimaryDataAsset.h"
#include "InsaneWeaponBase.h"


bool UInsaneWeaponPrimaryDataAsset::WeaponDataIsEmpty() const
{
	return this->WeaponData.Ability == nullptr &&
			this->WeaponData.WeaponName.IsNone() &&
			this->WeaponData.Weapon == nullptr;
}
