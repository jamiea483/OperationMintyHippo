#pragma once
#include "AbilityInterface.h"

class SpecialAbility : public AbilityInterface
{
public:
	virtual bool VInit(TiXmlElement* pData);
	virtual void VApply(WeakActorPtr pActor);
};