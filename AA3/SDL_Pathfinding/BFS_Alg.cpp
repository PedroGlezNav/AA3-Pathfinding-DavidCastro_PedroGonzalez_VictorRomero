#include "BFS_Alg.h"

std::vector<Vector2D> BFS_Alg::CalculatePathNodes(Vector2D agentPos, Vector2D goalPos, Graph* graph)
{
	std::vector<Vector2D> frontier;
	frontier.push_back(agentPos);
	std::vector<Connection*> cameFrom;
	cameFrom.push_back(new Connection(0, NULL, agentPos));

	for each (Vector2D nodeInFrontier in frontier)
	{
		if (nodeInFrontier == goalPos) {
			return CalculatePath(agentPos, goalPos, cameFrom);
		}

		std::vector<Connection*> connections= graph->GetConnectionsFromNode(nodeInFrontier);
		Vector2D neighbour;

		for each (Connection* connection1 in connections)
		{
			neighbour = connection1->GetToNode();

			for each (Connection * connection2 in cameFrom) 
			{
				if (neighbour != connection2->GetToNode()) 
				{
					cameFrom.push_back(connection1);
					frontier.push_back(neighbour);
					printf_s("New Frontier Point: (%f,%f)\n", neighbour.x, neighbour.y);
				}
			}
		}
	}
}

std::vector<Vector2D> BFS_Alg::CalculatePath(Vector2D agentPos, Vector2D goalPos, std::vector<Connection*> cameFrom)
{
	Vector2D current = goalPos;
	std::vector<Vector2D> path;
	path.push_back(current);

	while (current != agentPos) {
		for each (Connection* connection in cameFrom)
		{
			if (connection->GetToNode() == current) {
				current = connection->GetFromNode();
				path.push_back(current);
			}
		}
	}

	std::reverse(path.begin(), path.end());
	return path;
}