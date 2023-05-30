#pragma once

#include <vector>
#include <cmath>
#include <limits>
#include <queue>
#include <functional>

class NPC_PathFinding
{
};






/**

class AI {
public:
	AI(Terrain* terrain) : terrain_(terrain) {}

	std::vector<Position> findPath(Position start, Position end) const {
		// Use A* algorithm to find path.
		auto compare = [](Node* a, Node* b) { return a->cost > b->cost; };
		std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openSet(compare);
		openSet.push(new Node(start, 0, nullptr));

		while (!openSet.empty()) {
			Node* current = openSet.top();
			openSet.pop();

			if (current->position.x == end.x && current->position.y == end.y) {
				std::vector<Position> path;
				while (current != nullptr) {
					path.push_back(current->position);
					current = current->parent;
				}
				return path;
			}

			std::vector<Position> neighbors = terrain_->getNeighbors(current->position);
			for (Position neighbor : neighbors) {
				if (terrain_->isWalkableAt(neighbor)) {
					double newCost = current->cost + std::hypot(neighbor.x - current->position.x, neighbor.y - current->position.y);
					openSet.push(new Node(neighbor, newCost, current));
				}
			}
		}

		return std::vector<Position>();
	}

private:
	Terrain* terrain_;
};



std::vector<TerrainNode*> getNeighbours(TerrainNode* node) {
	std::vector<TerrainNode*> neighbours;
	// Assume terrainNodes is a 2D grid stored in 1D format.
	for (int x = -1; x <= 1; ++x) {
		for (int z = -1; z <= 1; ++z) {
			if (x == 0 && z == 0) continue;  // Skip the current node itself.
			int newX = node->position.x + x;
			int newZ = node->position.z + z;
			if (newX >= 0 && newX < terrainSize && newZ >= 0 && newZ < terrainSize) {
				neighbours.push_back(&mTerrainNodes[newX * terrainSize + newZ]);
			}
		}
	}
	return neighbours;
}

float CalculateH(TerrainNode* node, TerrainNode* endNode) {
	return glm::distance(node->position, endNode->position);
}


bool AABB(const glm::vec3& minBox1, const glm::vec3& maxBox1, const glm::vec3& minBox2, const glm::vec3& maxBox2) {
	return (minBox1.x <= maxBox2.x && maxBox1.x >= minBox2.x) &&
		(minBox1.y <= maxBox2.y && maxBox1.y >= minBox2.y) &&
		(minBox1.z <= maxBox2.z && maxBox1.z >= minBox2.z);
}

**/

/*
class Node {
public:
	Position position;
	double cost;
	Node* parent;

	Node(Position pos, double cost, Node* parent) : position(pos), cost(cost), parent(parent) {}
};

class Terrain {
public:
	virtual bool isWalkableAt(Position pos) const = 0;
	virtual std::vector<Position> getNeighbors(Position pos) const = 0;
};

class AI_PathFinding
{
public:
	AI_PathFinding(Terrain* terrain);
	~AI_PathFinding();

	std::list<glm::ivec2> findPath(const glm::ivec2& start, const glm::ivec2& end);

private:
	Terrain* terrain;
	std::vector<Node*> openList, closedList;
	std::list<glm::ivec2> path;
	Node* startNode, * endNode, * currentNode, * pathNode;

	int calculateH(const glm::ivec2& pos, const glm::ivec2& end);
	std::vector<Node*> getNeighbours(Node* current);
	Node* findPath();
};


class Terrain {
public:
	virtual bool isWalkableAt(Position pos) const = 0;
	virtual std::vector<Position> getNeighbors(Position pos) const = 0;
};



std::vector<Position> findPath(Position start, Position end) const {
	// Use A* algorithm to find path.
	auto compare = [](Node* a, Node* b) { return a->cost > b->cost; };
	std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openSet(compare);
	openSet.push(new Node(start, 0, nullptr));

	while (!openSet.empty()) {
		Node* current = openSet.top();
		openSet.pop();

		if (current->position.x == end.x && current->position.y == end.y) {
			std::vector<Position> path;
			while (current != nullptr) {
				path.push_back(current->position);
				current = current->parent;
			}
			return path;
		}

		std::vector<Position> neighbors = terrain_->getNeighbors(current->position);
		for (Position neighbor : neighbors) {
			if (terrain_->isWalkableAt(neighbor)) {
				double newCost = current->cost + std::hypot(neighbor.x - current->position.x, neighbor.y - current->position.y);
				openSet.push(new Node(neighbor, newCost, current));
			}
		}
	}

	return std::vector<Position>();
}**/