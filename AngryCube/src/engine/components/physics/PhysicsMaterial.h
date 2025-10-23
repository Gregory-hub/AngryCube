#pragma once
struct PhysicsMaterial
{
	float FrictionCoefficient;
	float StictionThreshold;

	PhysicsMaterial(float frictionCoef, float stictionThreshold);
};

