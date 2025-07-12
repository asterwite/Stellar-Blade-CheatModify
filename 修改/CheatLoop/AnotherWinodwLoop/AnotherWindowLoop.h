#include "AnotherWindowUI/WeaponLoop.h"
class AnotherWindowCheat
{
public:
	void DrawAnotherWindowCheatUI();
	void AnotherWindowCheatStar();
};
inline AnotherWindowCheat AnotherWindowLoop;

inline void AnotherWindowCheat::DrawAnotherWindowCheatUI()
{
	UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
	USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
	WeaponLoop.DrawWeaponLoopUI(SBCheatManager, lib);
}

inline void AnotherWindowCheat::AnotherWindowCheatStar()
{
	UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
	USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
	WeaponLoop.DrawWeaponLoopCheat(SBCheatManager, lib);
}