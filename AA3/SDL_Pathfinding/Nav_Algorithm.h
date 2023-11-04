#pragma once
#include "Graph.h"

class Nav_Algorithm {
public:
	virtual std::vector<Vector2D> CalculatePathNodes(Vector2D agentPos, Vector2D goalPos, Graph* graph) = 0;
	virtual std::vector<Vector2D> CalculatePath(Vector2D agentPos, Vector2D goalPos, std::vector<Connection*> cameFrom) = 0;
};