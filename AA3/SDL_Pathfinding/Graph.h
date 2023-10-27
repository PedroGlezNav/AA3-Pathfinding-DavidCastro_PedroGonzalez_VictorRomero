#pragma once

#include <vector>
#include "Connection.h"

class Graph {
private:
	std::vector<Connection*> connections;

public:
	Graph(std::vector<Connection*> _connections) :connections(_connections) {}

	std::vector<Connection*> GetConnectionsFromNode(Vector2D fromNode) {

		std::vector<Connection*> fromNodeConnections;

		for (int iter = 0; iter < connections.size(); iter++) {
			if (connections[iter]->GetFromNode() == fromNode) {
				fromNodeConnections.push_back(connections[iter]);
			}
		}

		return fromNodeConnections;
	}
};