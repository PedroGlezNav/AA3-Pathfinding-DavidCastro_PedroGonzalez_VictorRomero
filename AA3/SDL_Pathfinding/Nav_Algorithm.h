#pragma once
#include "Graph.h"

class Nav_Algorithm {
protected:
	int nodesInFrontier;
public:
	virtual std::vector<Vector2D> CalculatePathNodes(Vector2D agentPos, Vector2D goalPos, Graph* graph) = 0;
	virtual std::vector<Vector2D> CalculatePath(Vector2D agentPos, Vector2D goalPos, std::vector<Connection*> cameFrom) = 0;

	int GetNodesInFrontier() {
		return nodesInFrontier;
	}
};