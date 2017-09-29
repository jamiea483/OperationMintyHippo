#pragma once
using namespace std;

class AbilityInterface : public ActorComponent
{
public:
	const static ComponentId COMPONENT_ID;
	virtual ComponentId VGetComponentId(void) const
	{
		return COMPONENT_ID;
	}
	// Pickup interface
	virtual void VApply(WeakActorPtr pActor) = 0;
};