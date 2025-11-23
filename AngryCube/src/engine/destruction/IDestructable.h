#pragma once
class IDestructable
{
public:
	virtual void Destroy() = 0;
	virtual void OnDestructon() = 0;
};

