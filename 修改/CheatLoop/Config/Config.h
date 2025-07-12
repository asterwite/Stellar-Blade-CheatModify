#pragma once
#include "..\Config\CofigLoodNeed.h"
#include "..\Cheat\MyCheat.h"
void static SaveConfig(const std::string& filename)
{
	nlohmann::json j;
	j[(const char*)u8"主题颜色"] = Config.主题颜色;

	j[(const char*)u8"显示FPS"] = FPSUnlock.显示FPS;
	j[(const char*)u8"自定义帧数"] = FPSUnlock.自定义帧数;

	j[(const char*)u8"原本的飞行数值"] = PlayerFly.原本的飞行数值;
	j[(const char*)u8"飞行无碰撞"] = PlayerFly.飞行无碰撞;
	j[(const char*)u8"飞行速度"] = PlayerFly.飞行速度;
	j[(const char*)u8"玩家飞行"] = PlayerFly.玩家飞行;

	j[(const char*)u8"人物速度"] = PlayerAttributeUI.人物速度;
	j[(const char*)u8"无敌"] = PlayerAttributeUI.无敌.启动;
	j[(const char*)u8"无限生命"] = PlayerAttributeUI.无限生命;
	j[(const char*)u8"无限护盾"] = PlayerAttributeUI.无限护盾;
	j[(const char*)u8"无限贝塔能量"] = PlayerAttributeUI.无限贝塔能量.启动;
	j[(const char*)u8"隐身模式"] = PlayerAttributeUI.隐身模式.启动;
	j[(const char*)u8"无限BU"] = PlayerAttributeUI.无限BU.启动;
	j[(const char*)u8"无限迅驰"] = PlayerAttributeUI.无限迅驰.启动;
	j[(const char*)u8"关闭锁定敌人"] = PlayerAttributeUI.关闭锁定敌人.启动;

	j[(const char*)u8"使用迅驰装备"] = PlayerStatusClothingUI.使用迅驰装备.启动;
	j[(const char*)u8"进入融合姿态"] = PlayerStatusClothingUI.进入融合姿态.启动;
	j[(const char*)u8"只修改融合状态不修改服装"] = PlayerStatusClothingUI.只修改融合状态不修改服装;
	j[(const char*)u8"修改融合状态也修改服装"] = PlayerStatusClothingUI.修改融合状态也修改服装;

	j[(const char*)u8"濒死屏幕特效"] = PlayerScreenAndSettingsUI.濒死屏幕特效.启动;
	j[(const char*)u8"强制进入射击状态"] = PlayerScreenAndSettingsUI.强制进入射击状态.启动;
	j[(const char*)u8"解锁射击模式"] = PlayerScreenAndSettingsUI.解锁射击模式.启动;


	j[(const char*)u8"怪物速度清零"] = PeopleLoop.怪物速度清零;
	j[(const char*)u8"删除怪物"] = PeopleLoop.删除怪物;

	
	//j[(const char*)u8"无限耐久"] = MeleeWeapon.无限耐久;	
 //   j[(const char*)u8"近战切割启动"] = MeleeWeapon.近战切割启动;
	//j[(const char*)u8"近战允许打洞"] = MeleeWeapon.近战允许打洞;
	//j[(const char*)u8"近战允许肢解"] = MeleeWeapon.近战允许肢解;
	//j[(const char*)u8"近战允许剪切"] = MeleeWeapon.近战允许剪切;
	//j[(const char*)u8"近战允许平分"] = MeleeWeapon.近战允许平分;
	//j[(const char*)u8"近战百分百暴击"] = MeleeWeapon.近战百分百暴击;
	//j[(const char*)u8"近战稳定一击必倒"] = MeleeWeapon.近战敌人稳定一击必倒;
	//j[(const char*)u8"近战超远刀距"] = MeleeWeapon.近战超远刀距;
	//j[(const char*)u8"近战全屏攻击"] = MeleeWeapon.近战全屏攻击;

	//j[(const char*)u8"无限子弹"] = GunWeaponLoop.无限子弹;
	//j[(const char*)u8"枪械切割启动"] = GunWeaponLoop.枪械切割启动;
	//j[(const char*)u8"点射无延迟"] = GunWeaponLoop.点射无延迟;
	//j[(const char*)u8"枪械一击必杀"] = GunWeaponLoop.枪械一击必杀;
	//j[(const char*)u8"枪械允许打洞"] = GunWeaponLoop.枪械允许打洞;
	//j[(const char*)u8"枪械允许肢解"] = GunWeaponLoop.枪械允许肢解;
	//j[(const char*)u8"枪械允许剪切"] = GunWeaponLoop.枪械允许剪切;
	//j[(const char*)u8"枪械允许平分"] = GunWeaponLoop.枪械允许平分;
	//j[(const char*)u8"敌人稳定一击必倒"] = GunWeaponLoop.枪械敌人稳定一击必倒;
	//j[(const char*)u8"枪械百分百暴击"] = GunWeaponLoop.枪械百分百暴击;

	//j[(const char*)u8"ESP绘制距离"] = ESPDEBUG.ESP绘制距离;
	//j[(const char*)u8"启动绘制对象"] = ESPDEBUG.启动绘制对象;
	//j[(const char*)u8"显示全部"] = ESPDEBUG.显示全部;
	//j[(const char*)u8"显示对象名称"] = ESPDEBUG.显示对象名称;
	//j[(const char*)u8"显示类名称"] = ESPDEBUG.显示类名称;
	//j[(const char*)u8"显示坐标位置"] = ESPDEBUG.显示坐标位置;
	//j[(const char*)u8"显示离我的距离"] = ESPDEBUG.显示离我的距离;
	//j[(const char*)u8"显示地址"] = ESPDEBUG.显示地址;

	//j[(const char*)u8"骨骼绘制"] = GameLoop.骨骼绘制;
	//j[(const char*)u8"ESPTEXTForPeople"] = GameLoop.ESPTEXTForPeople;
	//j[(const char*)u8"ESPFor2D"] = GameLoop.ESPFor2D;
	//j[(const char*)u8"线条绘制"] = GameLoop.线条绘制;
	//j[(const char*)u8"ESPFor3D"] = GameLoop.ESPFor3D;
	//j[(const char*)u8"角盒绘制"] = GameLoop.角盒绘制;
	//j[(const char*)u8"血量显示"] = GameLoop.血量显示;

	//j[(const char*)u8"显示雷达"] = Rader.drawRadar;
	//j[(const char*)u8"坐标X"] = Rader.radarCenter.x;
	//j[(const char*)u8"坐标Y"] = Rader.radarCenter.y;
	//j[(const char*)u8"雷达最远距离"] = Rader.radarDist;
	//j[(const char*)u8"圆数量"] = Rader.radarCircleCount;
	//j[(const char*)u8"半径"] = Rader.radarRadius;

	//j[(const char*)u8"呼出菜单快捷键"] = FPSUnlock.ShowMenu;
	std::ofstream file(filename);
	if (file.is_open()) {
		file << j.dump(4); // 4是缩进
		file.close();
	}
}

void static LoadConfig(const std::string& filename)
{
	std::ifstream file(filename);
	if (file.is_open()) {
		nlohmann::json j;
		file >> j;
		Config.主题颜色 = j.value((const char*)u8"主题颜色", 0);

		FPSUnlock.显示FPS = j.value((const char*)u8"显示FPS", true);
		FPSUnlock.自定义帧数 = j.value((const char*)u8"自定义帧数", 144.f);

		PlayerFly.原本的飞行数值 = j.value((const char*)u8"原本的飞行数值", 0.f);
		PlayerFly.飞行无碰撞 = j.value((const char*)u8"飞行无碰撞", false);
		PlayerFly.飞行速度 = j.value((const char*)u8"飞行速度", 10.f);
		PlayerFly.玩家飞行 = j.value((const char*)u8"玩家飞行", false);

		PlayerAttributeUI.人物速度 = j.value((const char*)u8"人物速度", 1.f);
		PlayerAttributeUI.无敌.启动 = j.value((const char*)u8"无敌", false);
		PlayerAttributeUI.无限生命 = j.value((const char*)u8"无限生命", false);
		PlayerAttributeUI.无限护盾 = j.value((const char*)u8"无限护盾", false);

		PlayerAttributeUI.无限贝塔能量.启动 = j.value((const char*)u8"无限贝塔能量", false);
		PlayerAttributeUI.隐身模式.启动 = j.value((const char*)u8"隐身模式", false);
		PlayerAttributeUI.无限BU.启动 = j.value((const char*)u8"无限BU", false);
		PlayerAttributeUI.无限迅驰.启动 = j.value((const char*)u8"无限迅驰", false);
		PlayerAttributeUI.关闭锁定敌人.启动 = j.value((const char*)u8"关闭锁定敌人", false);

		PlayerStatusClothingUI.使用迅驰装备.启动 = j.value((const char*)u8"使用迅驰装备", false);
		PlayerStatusClothingUI.进入融合姿态.启动 = j.value((const char*)u8"进入融合姿态", false);
		PlayerStatusClothingUI.修改融合状态也修改服装 = j.value((const char*)u8"修改融合状态也修改服装", false);
		PlayerStatusClothingUI.只修改融合状态不修改服装 = j.value((const char*)u8"只修改融合状态不修改服装", false);
		PlayerStatusClothingUI.替换服装启动 = j.value((const char*)u8"替换服装启动", false);

		PlayerScreenAndSettingsUI.强制进入射击状态.启动 = j.value((const char*)u8"强制进入射击状态", false);
		PlayerScreenAndSettingsUI.解锁射击模式.启动 = j.value((const char*)u8"强制进入射击状态", false);
		PlayerScreenAndSettingsUI.濒死屏幕特效.启动 = j.value((const char*)u8"强制进入射击状态", false);

		PeopleLoop.怪物速度清零 = j.value((const char*)u8"怪物速度清零", false);
		PeopleLoop.删除怪物 = j.value((const char*)u8"删除怪物", false);
	/*	MeleeWeapon.无限耐久 = j.value((const char*)u8"无限耐久", false);
		MeleeWeapon.近战切割启动 = j.value((const char*)u8"近战切割启动", false);	
		MeleeWeapon.近战允许打洞 = j.value((const char*)u8"近战允许打洞", false);
		MeleeWeapon.近战允许肢解 = j.value((const char*)u8"近战允许肢解", false);
		MeleeWeapon.近战允许剪切 = j.value((const char*)u8"近战允许剪切", false);
		MeleeWeapon.近战允许平分 = j.value((const char*)u8"近战允许平分", false);
		MeleeWeapon.近战敌人稳定一击必倒 = j.value((const char*)u8"近战敌人稳定一击必倒", false);
		MeleeWeapon.近战百分百暴击 = j.value((const char*)u8"近战百分百暴击", false);
		MeleeWeapon.近战超远刀距 = j.value((const char*)u8"近战超远刀距", false);
		MeleeWeapon.近战全屏攻击 = j.value((const char*)u8"近战全屏攻击", false);

		GunWeaponLoop.无限子弹 = j.value((const char*)u8"无限子弹", false);
		GunWeaponLoop.枪械一击必杀 = j.value((const char*)u8"枪械一击必杀", false);
		GunWeaponLoop.点射无延迟 = j.value((const char*)u8"点射无延迟", false);
		GunWeaponLoop.枪械切割启动 = j.value((const char*)u8"枪械切割启动", false);
		GunWeaponLoop.枪械允许打洞= j.value((const char*)u8"枪械允许打洞", false);
		GunWeaponLoop.枪械允许肢解= j.value((const char*)u8"枪械允许肢解", false);
		GunWeaponLoop.枪械允许剪切= j.value((const char*)u8"枪械允许剪切", false);
		GunWeaponLoop.枪械允许平分= j.value((const char*)u8"枪械允许平分", false);
		GunWeaponLoop.枪械敌人稳定一击必倒 = j.value((const char*)u8"敌人稳定一击必倒", false);
		GunWeaponLoop.枪械百分百暴击 = j.value((const char*)u8"百分百暴击", false);

		ESPDEBUG.ESP绘制距离 = j.value((const char*)u8"ESP绘制距离", 5.f);
		ESPDEBUG.启动绘制对象 = j.value((const char*)u8"启动绘制对象", false);
		ESPDEBUG.显示全部 = j.value((const char*)u8"显示全部", false);
		ESPDEBUG.显示对象名称 = j.value((const char*)u8"显示对象名称", false);
		ESPDEBUG.显示类名称 = j.value((const char*)u8"显示类名称", false);
		ESPDEBUG.显示坐标位置 = j.value((const char*)u8"显示坐标位置", false);
		ESPDEBUG.显示离我的距离 = j.value((const char*)u8"显示离我的距离", false);

		GameLoop.骨骼绘制 = j.value((const char*)u8"骨骼绘制", false);
		GameLoop.ESPTEXTForPeople = j.value((const char*)u8"ESPTEXTForPeople", false);
		GameLoop.ESPFor2D = j.value((const char*)u8"ESPFor2D", false);
		GameLoop.线条绘制 = j.value((const char*)u8"线条绘制", false);
		GameLoop.ESPFor3D = j.value((const char*)u8"ESPFor3D", false);
		GameLoop.角盒绘制 = j.value((const char*)u8"角盒绘制", false);
		GameLoop.血量显示 = j.value((const char*)u8"血量显示", false);

		Rader.drawRadar = j.value((const char*)u8"显示雷达", false);
		Rader.radarCenter.x = j.value((const char*)u8"坐标X", 250);
		Rader.radarCenter.y = j.value((const char*)u8"坐标Y", 250);
		Rader.radarDist = j.value((const char*)u8"雷达最远距离", 3000);
		Rader.radarCircleCount = j.value((const char*)u8"圆数量", 4);
		Rader.radarRadius = j.value((const char*)u8"半径", 200);		*/
		//FPSUnlock.ShowMenu = j.value((const char*)u8"呼出菜单快捷键", 0);
		file.close();
	}
}
 