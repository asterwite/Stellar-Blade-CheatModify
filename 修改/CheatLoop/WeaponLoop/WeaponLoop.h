#include "GunWeaponLoop.h"
class WeaponLoop
{
public:

public:
	void DrawWeaponUI();
	void WeaponCheat();
};
inline WeaponLoop Weapon;

inline void WeaponLoop::DrawWeaponUI()
{
	if (ImGui::CollapsingHeader((const char*)u8"近战修改"))
	{
		MeleeWeapon.DrawMeleeWeaponUI();
	}
	if (ImGui::CollapsingHeader((const char*)u8"枪械修改"))
	{
		GunWeaponLoop.DrawGunWeaponUI();
	}
}

inline void WeaponLoop::WeaponCheat()
{
	MeleeWeapon.MeleeWeaponCheat();
	GunWeaponLoop.GunWeaponCheat();
}



