#pragma once
#include "Cheat/Cheat.h"
#include "Shlwapi.h"

inline ImColor  Green { 33,255,0,200 };
inline ImColor  Bule { 0, 217, 255, 200 };
inline ImColor  White { 255,255,255,255 };
inline ImColor  Black (0.f, 0.f, 0.f);
inline ImColor Red	(255.f, 0.f, 0.f);

inline FName StrToName(std::string str)
{
	std::wstring wstr(str.begin(), str.end());
	const wchar_t* wstr_cstr = wstr.c_str();

	return UKismetStringLibrary::Conv_StringToName(FString((wstr_cstr)));
}

bool static GetAllActorsofType(UClass* mType, std::vector<AActor*>* outArray, bool bLoopAllLevels, bool bSkipLocalPlayer)
{
	UWorld* pWorld = GetUWorld();
	if (!pWorld)
		return false;

	AActor* pLocalPlayer =GetActor();
	std::vector<AActor*> result;

	TArray<ULevel*> pLevelsArray = pWorld->Levels;
	__int32 levelsCount = pLevelsArray.Num();

	for (int i = 0; i < levelsCount; i++)
	{
		if (!pLevelsArray.IsValidIndex(i))
			continue;

		ULevel* pLevel = pLevelsArray[i];
		if (!pLevel && bLoopAllLevels)
			continue;
		else if (!pLevel && !bLoopAllLevels)
			break;

		TArray<AActor*> pActorsArray = pLevelsArray[i]->Actors;
		__int32 actorsCount = pActorsArray.Num();

		for (int j = 0; j < actorsCount; j++)
		{
			if (!pActorsArray.IsValidIndex(j))
				continue;

			AActor* pActor = pActorsArray[j];
			if (!pActor || !pActor->RootComponent || (pActor == pLocalPlayer && bSkipLocalPlayer))
				continue;

			if (!pActor->IsA(mType))
				continue;

			result.push_back(pActor);
		}

		if (bLoopAllLevels)
			continue;
		else
			break;
	}
	*outArray = result;
	return result.size() > 0;
}
