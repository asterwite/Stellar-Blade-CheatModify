#pragma once
#include "..\Config\CofigLoodNeed.h"
#include "..\Cheat\Cheat.h"
class PlayerFlyCheat
{
public:
	float  原本的飞行数值;
	bool  飞行无碰撞 = false;
	float  飞行速度 = 10.f;
	bool  玩家飞行 = false;
	bool  玩家飞行执行一次 = true;
public:
	void PlayerFlyUI();
	void PlayerFly();
};

inline void PlayerFlyCheat::PlayerFlyUI()
{
	ImGui::Checkbox((const char*)u8"玩家飞行(空格上升，CTRL下降）", &玩家飞行);
	if (玩家飞行)
	{
		ImGui::Checkbox((const char*)u8"飞行无碰撞", &飞行无碰撞);
		ImGui::SliderFloat((const char*)u8"飞行速度", &飞行速度, 10.f, 100.f);
	}
}

inline void PlayerFlyCheat::PlayerFly()
{
	if (玩家飞行)
	{
		玩家飞行执行一次 = false;
		GetCharacter()->CharacterMovement->MovementMode = EMovementMode::MOVE_Flying;
		if (!原本的飞行数值)
		原本的飞行数值 = GetCharacter()->CharacterMovement->MaxAcceleration;

		GetCharacter()->CharacterMovement->MaxAcceleration = 100 * (int)飞行速度;

		auto NewVelocity = GetActor()->GetActorForwardVector() * 100.f *飞行速度;

		if(飞行无碰撞&& GetPawn()->GetActorEnableCollision())
		GetPawn()->SetActorEnableCollision(false,true);
		if(!飞行无碰撞 && !GetPawn()->GetActorEnableCollision())
		GetPawn()->SetActorEnableCollision(true,true);
		if (GetAsyncKeyState(VK_SPACE))
		GetCharacter()->CharacterMovement->Velocity.Z += 飞行速度;
		if (GetAsyncKeyState(VK_LCONTROL))
		GetCharacter()->CharacterMovement->Velocity.Z -= 飞行速度;
		if (GetAsyncKeyState(VK_SHIFT))
		GetCharacter()->CharacterMovement->Velocity = NewVelocity;


	};
	if (!玩家飞行&& !玩家飞行执行一次)
	{
		GetCharacter()->CharacterMovement->MovementMode = EMovementMode::MOVE_Walking;
		GetCharacter()->CharacterMovement->MaxAcceleration = 原本的飞行数值;
		GetPawn()->SetActorEnableCollision(true,true);
		玩家飞行执行一次 = true;
	}
}

inline PlayerFlyCheat PlayerFly;

