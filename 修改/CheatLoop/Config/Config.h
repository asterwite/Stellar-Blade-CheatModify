#pragma once
#include "..\Config\CofigLoodNeed.h"
#include "..\Cheat\MyCheat.h"
void static SaveConfig(const std::string& filename)
{
	nlohmann::json j;
	j[(const char*)u8"������ɫ"] = Config.������ɫ;

	j[(const char*)u8"��ʾFPS"] = FPSUnlock.��ʾFPS;
	j[(const char*)u8"�Զ���֡��"] = FPSUnlock.�Զ���֡��;

	j[(const char*)u8"ԭ���ķ�����ֵ"] = PlayerFly.ԭ���ķ�����ֵ;
	j[(const char*)u8"��������ײ"] = PlayerFly.��������ײ;
	j[(const char*)u8"�����ٶ�"] = PlayerFly.�����ٶ�;
	j[(const char*)u8"��ҷ���"] = PlayerFly.��ҷ���;

	j[(const char*)u8"�����ٶ�"] = PlayerAttributeUI.�����ٶ�;
	j[(const char*)u8"�޵�"] = PlayerAttributeUI.�޵�.����;
	j[(const char*)u8"��������"] = PlayerAttributeUI.��������;
	j[(const char*)u8"���޻���"] = PlayerAttributeUI.���޻���;
	j[(const char*)u8"���ޱ�������"] = PlayerAttributeUI.���ޱ�������.����;
	j[(const char*)u8"����ģʽ"] = PlayerAttributeUI.����ģʽ.����;
	j[(const char*)u8"����BU"] = PlayerAttributeUI.����BU.����;
	j[(const char*)u8"����Ѹ��"] = PlayerAttributeUI.����Ѹ��.����;
	j[(const char*)u8"�ر���������"] = PlayerAttributeUI.�ر���������.����;

	j[(const char*)u8"ʹ��Ѹ��װ��"] = PlayerStatusClothingUI.ʹ��Ѹ��װ��.����;
	j[(const char*)u8"�����ں���̬"] = PlayerStatusClothingUI.�����ں���̬.����;
	j[(const char*)u8"ֻ�޸��ں�״̬���޸ķ�װ"] = PlayerStatusClothingUI.ֻ�޸��ں�״̬���޸ķ�װ;
	j[(const char*)u8"�޸��ں�״̬Ҳ�޸ķ�װ"] = PlayerStatusClothingUI.�޸��ں�״̬Ҳ�޸ķ�װ;

	j[(const char*)u8"������Ļ��Ч"] = PlayerScreenAndSettingsUI.������Ļ��Ч.����;
	j[(const char*)u8"ǿ�ƽ������״̬"] = PlayerScreenAndSettingsUI.ǿ�ƽ������״̬.����;
	j[(const char*)u8"�������ģʽ"] = PlayerScreenAndSettingsUI.�������ģʽ.����;


	j[(const char*)u8"�����ٶ�����"] = PeopleLoop.�����ٶ�����;
	j[(const char*)u8"ɾ������"] = PeopleLoop.ɾ������;

	
	//j[(const char*)u8"�����;�"] = MeleeWeapon.�����;�;	
 //   j[(const char*)u8"��ս�и�����"] = MeleeWeapon.��ս�и�����;
	//j[(const char*)u8"��ս�����"] = MeleeWeapon.��ս�����;
	//j[(const char*)u8"��ս����֫��"] = MeleeWeapon.��ս����֫��;
	//j[(const char*)u8"��ս�������"] = MeleeWeapon.��ս�������;
	//j[(const char*)u8"��ս����ƽ��"] = MeleeWeapon.��ս����ƽ��;
	//j[(const char*)u8"��ս�ٷְٱ���"] = MeleeWeapon.��ս�ٷְٱ���;
	//j[(const char*)u8"��ս�ȶ�һ���ص�"] = MeleeWeapon.��ս�����ȶ�һ���ص�;
	//j[(const char*)u8"��ս��Զ����"] = MeleeWeapon.��ս��Զ����;
	//j[(const char*)u8"��սȫ������"] = MeleeWeapon.��սȫ������;

	//j[(const char*)u8"�����ӵ�"] = GunWeaponLoop.�����ӵ�;
	//j[(const char*)u8"ǹе�и�����"] = GunWeaponLoop.ǹе�и�����;
	//j[(const char*)u8"�������ӳ�"] = GunWeaponLoop.�������ӳ�;
	//j[(const char*)u8"ǹеһ����ɱ"] = GunWeaponLoop.ǹеһ����ɱ;
	//j[(const char*)u8"ǹе�����"] = GunWeaponLoop.ǹе�����;
	//j[(const char*)u8"ǹе����֫��"] = GunWeaponLoop.ǹе����֫��;
	//j[(const char*)u8"ǹе�������"] = GunWeaponLoop.ǹе�������;
	//j[(const char*)u8"ǹе����ƽ��"] = GunWeaponLoop.ǹе����ƽ��;
	//j[(const char*)u8"�����ȶ�һ���ص�"] = GunWeaponLoop.ǹе�����ȶ�һ���ص�;
	//j[(const char*)u8"ǹе�ٷְٱ���"] = GunWeaponLoop.ǹе�ٷְٱ���;

	//j[(const char*)u8"ESP���ƾ���"] = ESPDEBUG.ESP���ƾ���;
	//j[(const char*)u8"�������ƶ���"] = ESPDEBUG.�������ƶ���;
	//j[(const char*)u8"��ʾȫ��"] = ESPDEBUG.��ʾȫ��;
	//j[(const char*)u8"��ʾ��������"] = ESPDEBUG.��ʾ��������;
	//j[(const char*)u8"��ʾ������"] = ESPDEBUG.��ʾ������;
	//j[(const char*)u8"��ʾ����λ��"] = ESPDEBUG.��ʾ����λ��;
	//j[(const char*)u8"��ʾ���ҵľ���"] = ESPDEBUG.��ʾ���ҵľ���;
	//j[(const char*)u8"��ʾ��ַ"] = ESPDEBUG.��ʾ��ַ;

	//j[(const char*)u8"��������"] = GameLoop.��������;
	//j[(const char*)u8"ESPTEXTForPeople"] = GameLoop.ESPTEXTForPeople;
	//j[(const char*)u8"ESPFor2D"] = GameLoop.ESPFor2D;
	//j[(const char*)u8"��������"] = GameLoop.��������;
	//j[(const char*)u8"ESPFor3D"] = GameLoop.ESPFor3D;
	//j[(const char*)u8"�Ǻл���"] = GameLoop.�Ǻл���;
	//j[(const char*)u8"Ѫ����ʾ"] = GameLoop.Ѫ����ʾ;

	//j[(const char*)u8"��ʾ�״�"] = Rader.drawRadar;
	//j[(const char*)u8"����X"] = Rader.radarCenter.x;
	//j[(const char*)u8"����Y"] = Rader.radarCenter.y;
	//j[(const char*)u8"�״���Զ����"] = Rader.radarDist;
	//j[(const char*)u8"Բ����"] = Rader.radarCircleCount;
	//j[(const char*)u8"�뾶"] = Rader.radarRadius;

	//j[(const char*)u8"�����˵���ݼ�"] = FPSUnlock.ShowMenu;
	std::ofstream file(filename);
	if (file.is_open()) {
		file << j.dump(4); // 4������
		file.close();
	}
}

void static LoadConfig(const std::string& filename)
{
	std::ifstream file(filename);
	if (file.is_open()) {
		nlohmann::json j;
		file >> j;
		Config.������ɫ = j.value((const char*)u8"������ɫ", 0);

		FPSUnlock.��ʾFPS = j.value((const char*)u8"��ʾFPS", true);
		FPSUnlock.�Զ���֡�� = j.value((const char*)u8"�Զ���֡��", 144.f);

		PlayerFly.ԭ���ķ�����ֵ = j.value((const char*)u8"ԭ���ķ�����ֵ", 0.f);
		PlayerFly.��������ײ = j.value((const char*)u8"��������ײ", false);
		PlayerFly.�����ٶ� = j.value((const char*)u8"�����ٶ�", 10.f);
		PlayerFly.��ҷ��� = j.value((const char*)u8"��ҷ���", false);

		PlayerAttributeUI.�����ٶ� = j.value((const char*)u8"�����ٶ�", 1.f);
		PlayerAttributeUI.�޵�.���� = j.value((const char*)u8"�޵�", false);
		PlayerAttributeUI.�������� = j.value((const char*)u8"��������", false);
		PlayerAttributeUI.���޻��� = j.value((const char*)u8"���޻���", false);

		PlayerAttributeUI.���ޱ�������.���� = j.value((const char*)u8"���ޱ�������", false);
		PlayerAttributeUI.����ģʽ.���� = j.value((const char*)u8"����ģʽ", false);
		PlayerAttributeUI.����BU.���� = j.value((const char*)u8"����BU", false);
		PlayerAttributeUI.����Ѹ��.���� = j.value((const char*)u8"����Ѹ��", false);
		PlayerAttributeUI.�ر���������.���� = j.value((const char*)u8"�ر���������", false);

		PlayerStatusClothingUI.ʹ��Ѹ��װ��.���� = j.value((const char*)u8"ʹ��Ѹ��װ��", false);
		PlayerStatusClothingUI.�����ں���̬.���� = j.value((const char*)u8"�����ں���̬", false);
		PlayerStatusClothingUI.�޸��ں�״̬Ҳ�޸ķ�װ = j.value((const char*)u8"�޸��ں�״̬Ҳ�޸ķ�װ", false);
		PlayerStatusClothingUI.ֻ�޸��ں�״̬���޸ķ�װ = j.value((const char*)u8"ֻ�޸��ں�״̬���޸ķ�װ", false);
		PlayerStatusClothingUI.�滻��װ���� = j.value((const char*)u8"�滻��װ����", false);

		PlayerScreenAndSettingsUI.ǿ�ƽ������״̬.���� = j.value((const char*)u8"ǿ�ƽ������״̬", false);
		PlayerScreenAndSettingsUI.�������ģʽ.���� = j.value((const char*)u8"ǿ�ƽ������״̬", false);
		PlayerScreenAndSettingsUI.������Ļ��Ч.���� = j.value((const char*)u8"ǿ�ƽ������״̬", false);

		PeopleLoop.�����ٶ����� = j.value((const char*)u8"�����ٶ�����", false);
		PeopleLoop.ɾ������ = j.value((const char*)u8"ɾ������", false);
	/*	MeleeWeapon.�����;� = j.value((const char*)u8"�����;�", false);
		MeleeWeapon.��ս�и����� = j.value((const char*)u8"��ս�и�����", false);	
		MeleeWeapon.��ս����� = j.value((const char*)u8"��ս�����", false);
		MeleeWeapon.��ս����֫�� = j.value((const char*)u8"��ս����֫��", false);
		MeleeWeapon.��ս������� = j.value((const char*)u8"��ս�������", false);
		MeleeWeapon.��ս����ƽ�� = j.value((const char*)u8"��ս����ƽ��", false);
		MeleeWeapon.��ս�����ȶ�һ���ص� = j.value((const char*)u8"��ս�����ȶ�һ���ص�", false);
		MeleeWeapon.��ս�ٷְٱ��� = j.value((const char*)u8"��ս�ٷְٱ���", false);
		MeleeWeapon.��ս��Զ���� = j.value((const char*)u8"��ս��Զ����", false);
		MeleeWeapon.��սȫ������ = j.value((const char*)u8"��սȫ������", false);

		GunWeaponLoop.�����ӵ� = j.value((const char*)u8"�����ӵ�", false);
		GunWeaponLoop.ǹеһ����ɱ = j.value((const char*)u8"ǹеһ����ɱ", false);
		GunWeaponLoop.�������ӳ� = j.value((const char*)u8"�������ӳ�", false);
		GunWeaponLoop.ǹе�и����� = j.value((const char*)u8"ǹе�и�����", false);
		GunWeaponLoop.ǹе�����= j.value((const char*)u8"ǹе�����", false);
		GunWeaponLoop.ǹе����֫��= j.value((const char*)u8"ǹе����֫��", false);
		GunWeaponLoop.ǹе�������= j.value((const char*)u8"ǹе�������", false);
		GunWeaponLoop.ǹе����ƽ��= j.value((const char*)u8"ǹе����ƽ��", false);
		GunWeaponLoop.ǹе�����ȶ�һ���ص� = j.value((const char*)u8"�����ȶ�һ���ص�", false);
		GunWeaponLoop.ǹе�ٷְٱ��� = j.value((const char*)u8"�ٷְٱ���", false);

		ESPDEBUG.ESP���ƾ��� = j.value((const char*)u8"ESP���ƾ���", 5.f);
		ESPDEBUG.�������ƶ��� = j.value((const char*)u8"�������ƶ���", false);
		ESPDEBUG.��ʾȫ�� = j.value((const char*)u8"��ʾȫ��", false);
		ESPDEBUG.��ʾ�������� = j.value((const char*)u8"��ʾ��������", false);
		ESPDEBUG.��ʾ������ = j.value((const char*)u8"��ʾ������", false);
		ESPDEBUG.��ʾ����λ�� = j.value((const char*)u8"��ʾ����λ��", false);
		ESPDEBUG.��ʾ���ҵľ��� = j.value((const char*)u8"��ʾ���ҵľ���", false);

		GameLoop.�������� = j.value((const char*)u8"��������", false);
		GameLoop.ESPTEXTForPeople = j.value((const char*)u8"ESPTEXTForPeople", false);
		GameLoop.ESPFor2D = j.value((const char*)u8"ESPFor2D", false);
		GameLoop.�������� = j.value((const char*)u8"��������", false);
		GameLoop.ESPFor3D = j.value((const char*)u8"ESPFor3D", false);
		GameLoop.�Ǻл��� = j.value((const char*)u8"�Ǻл���", false);
		GameLoop.Ѫ����ʾ = j.value((const char*)u8"Ѫ����ʾ", false);

		Rader.drawRadar = j.value((const char*)u8"��ʾ�״�", false);
		Rader.radarCenter.x = j.value((const char*)u8"����X", 250);
		Rader.radarCenter.y = j.value((const char*)u8"����Y", 250);
		Rader.radarDist = j.value((const char*)u8"�״���Զ����", 3000);
		Rader.radarCircleCount = j.value((const char*)u8"Բ����", 4);
		Rader.radarRadius = j.value((const char*)u8"�뾶", 200);		*/
		//FPSUnlock.ShowMenu = j.value((const char*)u8"�����˵���ݼ�", 0);
		file.close();
	}
}
 