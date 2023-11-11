#include "SceneExercise3.h"

using namespace std;

SceneExercise3::SceneExercise3()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setPathCircleColor(255, 255, 0, 255);
	agent->setTarget(Vector2D(-20,-20));
	agents.push_back(agent);

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1,-1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[0]->setPosition(maze->cell2pix(rand_cell));
	initialAgent0Pos = maze->cell2pix(rand_cell);

	// set the coin in a random cell (but at least 3 cells far from the agent)
	for (int i = 0; i < 7; i++) {
		Vector2D newCoinPosition = Vector2D(-1, -1);
		coinPositions.push_back(newCoinPosition);
		while ((!maze->isValidCell(coinPositions[i])) || (Vector2D::Distance(coinPositions[i], rand_cell) < 3))
			coinPositions[i] = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}
	for each (Vector2D coinPosition in coinPositions)
	{
		coinPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
			coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}

	graph = new Graph(maze->GetTerrain());
	nav_Algorithm = new BFS_Alg();
	printf_s("Breadth-First Search--------------------------------------\n\n");
}

SceneExercise3::~SceneExercise3()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneExercise3::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
			draw_grid = !draw_grid;
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_E && agents[0]->getPathSize() == 0) {
			Vector2D rand_cell(-1, -1);
			for each (Vector2D coinPosition in coinPositions)
			{
				coinPosition = Vector2D(-1, -1);
				while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
					coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
			}
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_S && agents[0]->getPathSize() == 0) {

			int moreNearCoin = 0;
			coinPositions.push_back(agents[0]->getPosition());
			std::vector
			std::vector<Vector2D> toCoinPathPoints = nav_Algorithm->CalculatePathNodes(maze->pix2cell(agents[0]->getPosition()), coinPositions[moreNearCoin], graph, std::vector<Vector2D>());

			for (int iter = 1; iter < coinPositions.size(); iter++) {
				std::vector<Vector2D> pathPoints = nav_Algorithm->CalculatePathNodes(maze->pix2cell(agents[0]->getPosition()), coinPositions[iter], graph, std::vector<Vector2D>());
				if (toCoinPathPoints.size() > pathPoints.size()) {
					moreNearCoin = iter;
					toCoinPathPoints = pathPoints;
				}
				printf_s("Number of nodes in frontier: %d ----------------------------------\n\n", nav_Algorithm->GetNodesInFrontier());
			}

			std::priority_queue<std::pair<int, std::vector<Vector2D>>, std::vector<std::pair<int, std::vector<Vector2D>>>, std::greater<std::pair<int, std::vector<Vector2D>>>> orderedCoins;
			orderedCoins.push(std::make_pair(toCoinPathPoints.size(), toCoinPathPoints));
			for (int iter = 1; iter < coinPositions.size(); iter++) {

			}

			
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_R && agents[0]->getPathSize() == 0) {
			agents[0]->setPosition(initialAgent0Pos);
		}
		break;
	default:
		break;
	}

	agents[0]->update(dtime, event);
}

void SceneExercise3::draw()
{
	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	agents[0]->draw();
}

const char* SceneExercise3::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void SceneExercise3::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{		
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			} else {
				// Do not draw if it is not necessary (bg is already black)
			}
					
			
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void SceneExercise3::drawCoin()
{
	for each (Vector2D coinPosition in coinPositions)
	{
		Vector2D coin_coords = maze->cell2pix(coinPosition);
		int offset = CELL_SIZE / 2;
		SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
	}
}


bool SceneExercise3::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}
