#pragma once
#include "..\Config\CofigLoodNeed.h"
#include "..\Cheat\Cheat.h"
class PlayerFlyCheat
{
public:
	float  ԭ���ķ�����ֵ;
	bool  ��������ײ = false;
	float  �����ٶ� = 10.f;
	bool  ��ҷ��� = false;
	bool  ��ҷ���ִ��һ�� = true;
public:
	void PlayerFlyUI();
	void PlayerFly();
};

inline void PlayerFlyCheat::PlayerFlyUI()
{
	ImGui::Checkbox((const char*)u8"��ҷ���(�ո�������CTRL�½���", &��ҷ���);
	if (��ҷ���)
	{
		ImGui::Checkbox((const char*)u8"��������ײ", &��������ײ);
		ImGui::SliderFloat((const char*)u8"�����ٶ�", &�����ٶ�, 10.f, 100.f);
	}
}

inline void PlayerFlyCheat::PlayerFly()
{
	if (��ҷ���)
	{
		��ҷ���ִ��һ�� = false;
		GetCharacter()->CharacterMovement->MovementMode = EMovementMode::MOVE_Flying;
		if (!ԭ���ķ�����ֵ)
		ԭ���ķ�����ֵ = GetCharacter()->CharacterMovement->MaxAcceleration;

		GetCharacter()->CharacterMovement->MaxAcceleration = 100 * (int)�����ٶ�;

		auto NewVelocity = GetActor()->GetActorForwardVector() * 100.f *�����ٶ�;

		if(��������ײ&& GetPawn()->GetActorEnableCollision())
		GetPawn()->SetActorEnableCollision(false,true);
		if(!��������ײ && !GetPawn()->GetActorEnableCollision())
		GetPawn()->SetActorEnableCollision(true,true);
		if (GetAsyncKeyState(VK_SPACE))
		GetCharacter()->CharacterMovement->Velocity.Z += �����ٶ�;
		if (GetAsyncKeyState(VK_LCONTROL))
		GetCharacter()->CharacterMovement->Velocity.Z -= �����ٶ�;
		if (GetAsyncKeyState(VK_SHIFT))
		GetCharacter()->CharacterMovement->Velocity = NewVelocity;


	};
	if (!��ҷ���&& !��ҷ���ִ��һ��)
	{
		GetCharacter()->CharacterMovement->MovementMode = EMovementMode::MOVE_Walking;
		GetCharacter()->CharacterMovement->MaxAcceleration = ԭ���ķ�����ֵ;
		GetPawn()->SetActorEnableCollision(true,true);
		��ҷ���ִ��һ�� = true;
	}
}

inline PlayerFlyCheat PlayerFly;

