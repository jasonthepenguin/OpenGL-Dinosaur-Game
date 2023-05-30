#pragma once

#include "TerrainNode.h"

class NPC_AI
{
	public:
		std::vector<TerrainNode> path;
		Terrain terrain;

		NPC_AI() {}
		NPC_AI(Terrain* terrain);


		void wander();
		void setStartNode(int x, int y);
		void setEndNode(int x, int y);
		std::vector<TerrainNode> calculatePath();
		float calculateH(TerrainNode& a, TerrainNode& b);
		std::vector<Node> getNeighbours(TerrainNode& node);
		bool checkCollision(TerrainNode& a, TerrainNode& b);


	private:

		Terrain* m_WorldEnvironment;
		std::vector<TerrainNode> m_TerrainNodes;
};


/**
AI_PathFinding::AI_PathFinding(Terrain* terrain) : terrain(terrain)
{
	// Constructor implementation.
}

AI_PathFinding::~AI_PathFinding()
{
	// Destructor implementation.
}

int AI_PathFinding::calculateH(const glm::ivec2& pos, const glm::ivec2& end)
{
	// Use Manhattan distance as heuristic
	return abs(end.x - pos.x) + abs(end.y - pos.y);
}

std::vector<Node*> AI_PathFinding::getNeighbours(Node* current)
{
	std::vector<Node*> neighbours;
	// Implement the logic to get neighbours
	return neighbours;
}

Node* AI_PathFinding::findPath()
{
	while (!openList.empty())
	{
		// Sort open list based on score (F = G + H)
		std::sort(openList.begin(), openList.end(), [](const Node* lhs, const Node* rhs)
			{
				return lhs->getScore() < rhs->getScore();
			});

		currentNode = openList.front();
		openList.erase(openList.begin());

		closedList.push_back(currentNode);

		if (currentNode->position == endNode->position)
		{
			// Found the destination
			return currentNode;
		}

		for (Node* neighbour : getNeighbours(currentNode))
		{
			// Ignore if neighbour is on closed list
			if (std::find(closedList.begin(), closedList.end(), neighbour) != closedList.end())
				continue;

			// Calculate scores
			int tentativeG = currentNode->G + 1; // Assuming cost to move is 1

			auto inOpenList = std::find_if(openList.begin(), openList.end(), [&neighbour](const Node* node)
				{
					return node->position == neighbour->position;
				});

			if (inOpenList == openList.end())
			{
				// Add neighbour to open list
				neighbour->G = tentativeG;
				neighbour->H = calculateH(neighbour->position, endNode->position);
				neighbour->parent = currentNode;
				openList.push_back(neighbour);
			}
			else if (tentativeG < (*inOpenList)->G)
			{
				// Update node in open list
				(*inOpenList)->G = tentativeG;
				(*inOpenList)->parent = currentNode;
			}
		}
	}

	return nullptr; // Path not found
}

std::list<glm::ivec2> AI_PathFinding::findPath(const glm::ivec2& start, const glm::ivec2& end)
{
	// Reset nodes
	openList.clear();
	closedList.clear();
	path.clear();

	startNode = new Node(start);
	endNode = new Node(end);

	// Start by adding the original position to the open list
	openList.push_back(startNode);

	pathNode = findPath();

	// Build path
	while (pathNode != nullptr)
	{
		path.push_front(pathNode->position);
		pathNode = pathNode->parent;
	}

	return path;
}





#include <list>
#include <vector>
#include <glm/glm.hpp>
#include "Terrain.h"

// A structure to hold the necessary parameters
struct Node
{
	glm::ivec2 position;
	int G, H;
	Node* parent;

	Node(glm::ivec2 pos, Node* p = nullptr) : position(pos), G(0), H(0), parent(p) {}
	int getScore() { return G + H; }
};

*/

