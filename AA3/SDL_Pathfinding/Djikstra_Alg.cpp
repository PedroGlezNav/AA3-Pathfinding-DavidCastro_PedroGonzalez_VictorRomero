#include "Djikstra_Alg.h"

std::vector<Vector2D> Djikstra_Alg::CalculatePathNodes(Vector2D agentPos, Vector2D goalPos, Graph* graph)
{
	nodesInFrontier = 0;

	std::priority_queue<std::pair<float, Vector2D>, std::vector<std::pair<float, Vector2D>>, std::greater<std::pair<float, Vector2D>>> frontier;
	frontier.push(std::make_pair(55.f, agentPos));

	std::vector<std::pair<Vector2D, float>> costSoFar;
	costSoFar.push_back(std::make_pair(agentPos, 0.f));

	std::vector<std::pair<Vector2D, Vector2D>> cameFrom;
	cameFrom.push_back(std::make_pair(NULL, agentPos));

	while (!frontier.empty())
	{
		if (frontier.top().second == goalPos) {
			return CalculatePath(agentPos, goalPos, cameFrom);
		}

		std::vector<Connection*> connections= graph->GetConnectionsFromNode(frontier.top().second);
		frontier.pop();
		Vector2D neighbour;

		for each (Connection* frontierConnection in connections)
		{

			neighbour = frontierConnection->GetToNode();

			bool hasFoundIt = false; 
			float newCost = 0;
			int foundIter = 0;

			for (int iter = 0; iter < costSoFar.size() && !hasFoundIt; iter++) {

				if (neighbour.x == costSoFar[iter].first.x && neighbour.y == costSoFar[iter].first.y) 
				{
					hasFoundIt = true; 
					newCost = costSoFar[iter].second;
					foundIter = iter;
				}
			}
			newCost += frontierConnection->GetCost();

			if (!hasFoundIt) 
			{
				costSoFar.push_back(std::make_pair(frontierConnection->GetToNode(), newCost));
				cameFrom.push_back(std::make_pair(frontierConnection->GetFromNode(), frontierConnection->GetToNode()));
				frontier.push(std::pair<int, Vector2D>(newCost, frontierConnection->GetToNode()));

				printf_s("New Frontier Point: (%f,%f)\n", neighbour.x, neighbour.y);
				nodesInFrontier++;
			}
			else if (newCost < costSoFar[foundIter].second) 
			{
				costSoFar[foundIter].second = newCost;
				cameFrom[foundIter].first = frontierConnection->GetFromNode();
				frontier.push(std::pair<int, Vector2D>(newCost, frontierConnection->GetToNode()));

				printf_s("New Frontier Point: (%f,%f)\n", neighbour.x, neighbour.y);
				nodesInFrontier++;
			}
		}
	}
}