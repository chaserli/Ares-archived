#pragma once

/*
 * This file contains the macro fu needed to make the 100 unit bug fixes work better
 * Don't get it? Don't touch it!
 */
extern std::vector<int> CreationFrames;
extern std::vector<int> Values;
extern std::vector<int> BestChoices;

// Westwood, meet my friend the resizable array
// what? copy pasting original code, leave it be
template <class TClass, class TType>
void GetTypeToProduce(HouseClass* pThis, int& ProducingTypeIndex) {
	CreationFrames.assign(TType::Array->Count, 0x7FFFFFFF);
	Values.assign(TType::Array->Count, 0);

	for(auto CurrentTeam : *TeamClass::Array) {
		if(!CurrentTeam || CurrentTeam->Owner != pThis) {
			continue;
		}

		int TeamCreationFrame = CurrentTeam->CreationFrame;

		if((!CurrentTeam->Type->Reinforce || CurrentTeam->unknown_79)
		  && (CurrentTeam->unknown_77 || CurrentTeam->unknown_78))
		{
			continue;
		}

		DynamicVectorClass<TechnoTypeClass *> TaskForceMembers;
		CurrentTeam->GetTaskForceMissingMemberTypes(TaskForceMembers);
		for(auto CurrentMember : TaskForceMembers) {
			if(CurrentMember->WhatAmI() != TType::AbsID) {
				continue;
			}
			int Idx = CurrentMember->GetArrayIndex();
			++Values[Idx];
			if(TeamCreationFrame < CreationFrames[Idx]) {
				CreationFrames[Idx] = TeamCreationFrame;
			}
		}
	}

	for(auto T : *TClass::Array) {
		int Idx = T->GetType()->GetArrayIndex();
		if(Values[Idx] > 0 && T->CanBeRecruited(pThis)) {
			--Values[Idx];
		}
	}

	BestChoices.clear();

	int BestValue = -1;
	int EarliestTypenameIndex = -1;
	int EarliestFrame = 0x7FFFFFFF;

	for(int i = 0; i < TType::Array->Count; ++i) {
		TType *TT = TType::Array->GetItem(i);
		int CurrentValue = Values[i];
		if(CurrentValue <= 0 || !pThis->CanBuild(TT, false, false)
			|| TT->GetActualCost(pThis) > pThis->Available_Money())
		{
			continue;
		}

		if(BestValue < CurrentValue || BestValue == -1) {
			BestValue = CurrentValue;
			BestChoices.clear();
		}
		BestChoices.push_back(i);
		if(EarliestFrame > CreationFrames[i] || EarliestTypenameIndex == -1) {
			EarliestTypenameIndex = i;
			EarliestFrame = CreationFrames[i];
		}
	}

	auto AIDiff = pThis->GetAIDifficultyIndex();
	int EarliestOdds = RulesClass::Instance->FillEarliestTeamProbability[AIDiff];
	if(ScenarioClass::Instance->Random.RandomRanged(0, 99) < EarliestOdds) {
		ProducingTypeIndex = EarliestTypenameIndex;
	} else if(BestChoices.size()) {
		int RandomChoice = ScenarioClass::Instance->Random.RandomRanged(0, BestChoices.size() - 1);
		int RandomIndex = BestChoices.at(RandomChoice);
		ProducingTypeIndex = RandomIndex;
	}
}
