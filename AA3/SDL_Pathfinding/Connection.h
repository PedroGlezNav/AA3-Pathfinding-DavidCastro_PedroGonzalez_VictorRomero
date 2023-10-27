#pragma once
#include "Vector2D.h"

class Connection
{
private:
	float cost;
	Vector2D fromNode;
	Vector2D toNode;

public:
	Connection(float _cost, Vector2D _fromNode, Vector2D _toNode) : cost(_cost), fromNode(_fromNode), toNode(_toNode) {}

	float GetCost() {
		return cost;
	}

	Vector2D GetFromNode() {
		return fromNode;
	}

	Vector2D GetToNode() {
		return toNode;
	}
};