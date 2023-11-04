#pragma once

#include "Connection.h"

class Graph {
private:
	std::vector<Connection*> connections;

public:
	Graph(std::vector<std::vector<int>> grid_terrain){
		for (int i = 0; i < grid_terrain.size(); i++) {
			for (int j = 0; j < grid_terrain[i].size(); j++) {
				if (grid_terrain[i][j] == 1) {
					//Left
					if (i - 1 > 0 && grid_terrain[i - 1][j] == 1) {
						Connection *newConnection = new Connection(0, Vector2D(j,i), Vector2D(j,i - 1));
						connections.push_back(newConnection);
					}
					//Right
					if (i + 1 < grid_terrain.size() && grid_terrain[i + 1][j] == 1) {
						Connection* newConnection = new Connection(0, Vector2D(j, i), Vector2D(j, i + 1));
						connections.push_back(newConnection);
					}
					//Down
					if (j + 1 < grid_terrain[i].size() && grid_terrain[i][j + 1] == 1) {
						Connection* newConnection = new Connection(0, Vector2D(j, i), Vector2D(j + 1, i));
						connections.push_back(newConnection);
					}
					//Up
					if (j - 1 > 0 && grid_terrain[i][j - 1] == 1) {
						Connection* newConnection = new Connection(0, Vector2D(j, i), Vector2D(j - 1, i));
						connections.push_back(newConnection);
					}
				}
			}
		}
	}

	std::vector<Connection*> GetConnectionsFromNode(Vector2D fromNode) {

		std::vector<Connection*> fromNodeConnections;

		for (int iter = 0; iter < connections.size(); iter++) {
			if (connections[iter]->GetFromNode().x == fromNode.x && connections[iter]->GetFromNode().y == fromNode.y) {
				fromNodeConnections.push_back(connections[iter]);
			}
		}

		return fromNodeConnections;
	}
};