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
	if (ImGui::CollapsingHeader((const char*)u8"��ս�޸�"))
	{
		MeleeWeapon.DrawMeleeWeaponUI();
	}
	if (ImGui::CollapsingHeader((const char*)u8"ǹе�޸�"))
	{
		GunWeaponLoop.DrawGunWeaponUI();
	}
}

inline void WeaponLoop::WeaponCheat()
{
	MeleeWeapon.MeleeWeaponCheat();
	GunWeaponLoop.GunWeaponCheat();
}



