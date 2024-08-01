#pragma once

#include<memory>
#include<unordered_map>

#include"Node.hpp"

enum class EdgeType { DIRECTED, UNDIRECTED };
struct Edge {
	Node* a;
	Node* b;
	float val;
	EdgeType type = EdgeType::DIRECTED;

	void draw(SDL_Renderer* renderer);
	
};

typedef std::unordered_map<Node*, std::unordered_map<Node*, Edge>> AdjacencyList;
typedef std::vector<std::vector<float>> AdjacencyMatrix;
typedef std::vector<Edge> EdgeList;

class Graph {
public:
	Graph() = default;

	void addNode(vec2 pos = vec2(50, 50), std::string name = "");
	void addNode(Node&);

	void addEdge(Node&, Node&, EdgeType et = EdgeType::DIRECTED, float value = 1.0f);
	void addEdge(int, int, EdgeType et = EdgeType::DIRECTED, float value = 1.0f);

	void removeEdge(Node&, Node&);
	void removeEdge(int, int);

	void handleEvent(SDL_Event*);
	void render(SDL_Renderer*);

private:
	std::vector<std::unique_ptr<Node>> m_nodes;
	AdjacencyList m_adjList;
	Node* _activeNode;
};