#pragma once
#include "Windows.h"
#include "..\CppSDK/SDK.hpp"
#include <mutex>
#include <vector>
#include <stdio.h>
#include "..\..\CreatDx12\ImGui\imgui.h"
using namespace SDK;

std::uint8_t* find_sig(LPCSTR module_name, const std::string& byte_array);

class memory final
{
public:
	class allocator final
	{
	public:
		~allocator();

		void clear();

		void free(void* data);

		void free(const void* data);

		void* allocate(size_t length);

		template <typename T>
		T* allocate()
		{
			return this->allocate_array<T>(1);
		}
		template <typename T>
		T* allocate_array(const size_t count = 1)
		{
			auto base = static_cast<T*>(this->allocate(count * sizeof(T)));

			T();
			return base;
		}

		bool empty() const;

	private:
		std::mutex mutex_;
		std::vector<void*> pool_;
	};

	static void* allocate(size_t length);

	template <typename T>
	static inline T* allocate()
	{
		return allocate_array<T>(1);
	}

	template <typename T>
	static inline T* allocate_array(const size_t count = 1)
	{
		return static_cast<T*>(allocate(count * sizeof(T)));
	}

	static void free(void* data);
	static void free(const void* data);

	static bool is_set(const void* mem, char chr, size_t length);

	static allocator* get_allocator();

private:
	static allocator mem_allocator_;
};

class signature
{
public:

	signature(const std::string& sig);

	signature import(const std::string & module_name = ("SB-Win64-Shipping.exe"));

	signature add(uint32_t offset);
	signature sub(uint32_t offset);
	signature instruction(uint32_t offset);

	signature dump(const std::string& func_name);

#ifdef _WIN64
	uint64_t GetPointer();
#else
	uint32_t GetPointer();
#endif

private:
#ifdef _WIN64
	uint64_t pointer;
#else
	uint32_t pointer;
#endif

	bool imported;
	std::string sig;
	std::string module_name;

};

void swap_virtual_table(void* obj, uint32_t index, void* func);

bool get_key_state(int key, int flag = 1);


inline HMODULE ExeModule;

inline UWorld* gWorld = nullptr;


inline wchar_t* charToWchar(const char* str, int codePage = CP_UTF8) {
	if (!str) return nullptr;

	int size = MultiByteToWideChar(codePage, 0, str, -1, nullptr, 0);
	if (size <= 0) {
		std::cerr << "MultiByteToWideChar failed, error: " << GetLastError() << std::endl;
		return nullptr;
	}

	wchar_t* wstr = new wchar_t[size];
	if (!wstr) return nullptr;

	if (!MultiByteToWideChar(codePage, 0, str, -1, wstr, size)) {
		std::cerr << "MultiByteToWideChar conversion failed, error: " << GetLastError() << std::endl;
		delete[] wstr;
		return nullptr;
	}

	return wstr;
}

inline void ImGuiHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

inline UGameUserSettings* GetGameUserSettings()
{
	UEngine* Engine = UEngine::GetEngine();
	if(!Engine)
	return nullptr;
	UGameUserSettings* Setting = Engine->GameUserSettings;
	if (!Setting) 
	return nullptr;
	return Setting;
}

inline UWorld* GetUWorld()
{
	static uint64_t gworld_ptr = 0;
	if (!gworld_ptr)
	{
		auto gworld = signature("75 07 48 8B 05 ? ? ? ? C3 CC").instruction(5).add(9);//UE4 UE5非魔改通杀UWorld特征
		gworld_ptr = gworld.GetPointer();
		if (gworld_ptr)
			gWorld = *(UWorld**)gworld_ptr;
	}
	return (*(UWorld**)(gworld_ptr));
}

inline AGameStateBase* GetGameStateBase()
{
	UWorld* world = GetUWorld();
	if (!world)
		return nullptr;
	return world->GameState;
}
inline ULocalPlayer* GetLocalPlayer()
{
	UWorld* pWorld = GetUWorld();
	if (!pWorld)
		return nullptr;
	UGameInstance* pGameInstance = pWorld->OwningGameInstance;
	if (!pGameInstance)
		return nullptr;
	return pGameInstance->LocalPlayers[0];
}

inline APlayerController* GetPlayerController()
{
	ULocalPlayer* ALocalPlayer = GetLocalPlayer();
	if (!ALocalPlayer)
		return nullptr;
	return ALocalPlayer->PlayerController;
}

inline UCheatManager* GetCheatManager()
{
	APlayerController* MyPlayerController = GetPlayerController();
	if (!MyPlayerController)
		return nullptr;
	return MyPlayerController->CheatManager;
}


inline ACharacter* GetCharacter()
{
	APlayerController* MyPlayerController = GetPlayerController();
	if (!MyPlayerController)
		return nullptr;
	return MyPlayerController->Character;
}


inline APawn* GetPawn()
{
	APlayerController* MyPlayerController = GetPlayerController();
	if (!MyPlayerController)
		return nullptr;
	return MyPlayerController->AcknowledgedPawn;
}

inline APlayerState* GetPlayerState()
{
	APawn* MyPawn = GetPawn();
	if (!MyPawn)
		return nullptr;
	auto PlayerState = MyPawn->PlayerState;
	if(!PlayerState)
		return nullptr;
	return PlayerState;
}

inline AActor* GetActor()
{
	APawn* MyPawn = GetPawn();
	if (!MyPawn)
		return nullptr;
	return static_cast<AActor*>(MyPawn);
}

inline AActor* GetAllActor()
{
	UWorld* world = GetUWorld();
	if (!world)
		return nullptr;
	ULevel* level = world->PersistentLevel;
	if (!level)
		return nullptr;
	TArray<AActor*> Actors = level->Actors;
	if (!Actors)
		return nullptr;
	for (int a = 0;a < Actors.Num();a++)
		return Actors[a];
}
inline ASBCharacter* GetSBCharacter()
{
	ACharacter* Character = GetCharacter();
	if(!Character)
		return nullptr;
	return static_cast<ASBCharacter*>(Character);
}
