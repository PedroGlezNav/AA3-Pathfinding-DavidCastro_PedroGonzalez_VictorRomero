#include "BFS_Alg.h"

std::vector<Vector2D> BFS_Alg::CalculatePathNodes(Vector2D agentPos, Vector2D goalPos, Graph* graph)
{
	nodesInFrontier = 0;

	std::vector<Vector2D> frontier;
	frontier.push_back(agentPos);
	std::vector<Connection*> cameFrom;
	cameFrom.push_back(new Connection(0, NULL, agentPos));

	while (!frontier.empty())
	{
		if (frontier[0] == goalPos) {
			return CalculatePath(agentPos, goalPos, cameFrom);
		}

		std::vector<Connection*> connections= graph->GetConnectionsFromNode(frontier[0]);
		frontier.erase(frontier.begin());
		Vector2D neighbour;

		for each (Connection* frontierConnection in connections)
		{
			neighbour = frontierConnection->GetToNode();

			bool hasFoundIt = false;

			for (int iter = 0; iter < cameFrom.size() && !hasFoundIt; iter++)
			{
				if (neighbour.x == cameFrom[iter]->GetToNode().x && neighbour.y == cameFrom[iter]->GetToNode().y)
				{
					hasFoundIt = true;
				}
			}

			if (!hasFoundIt) {
				cameFrom.push_back(frontierConnection);
				frontier.push_back(neighbour);
				printf_s("New Frontier Point: (%f,%f)\n", neighbour.x, neighbour.y);
				nodesInFrontier++;
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