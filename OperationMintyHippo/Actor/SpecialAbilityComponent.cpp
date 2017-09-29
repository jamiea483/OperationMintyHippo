#include "SpecialAbilityComponent.h"
#include <iostream>
using namespace std;


bool SpecialAbility::VInit(TiXmlElement* pData)
{
	return true;
}

void SpecialAbility::VApply(WeakActorPtr pActor)
{
	StrongActorPtr pStrongActor = MakeStrongPtr(pActor);
	if (pStrongActor)
	{
		cout << "Applying ammo pickup to actor id " << (string)(pStrongActor->GetId());
	}