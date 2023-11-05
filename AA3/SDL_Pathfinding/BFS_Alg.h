#pragma once
#include "Nav_Algorithm.h"

class BFS_Alg : public Nav_Algorithm
{
public:
	virtual std::vector<Vector2D> CalculatePathNodes(Vector2D agentPos, Vector2D goalPos, Graph* graph) override;
};