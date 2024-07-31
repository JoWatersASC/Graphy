#pragma once

#include<memory>
#include<unordered_map>

#include"Node.hpp"

enum edge_type { DIRECTED, UNDIRECTED };
struct edge {
	float val;
	edge_type type = DIRECTED;
};

typedef std::unordered_map<Node*, std::unordered_map<Node*, edge>> AdjacencyList;
typedef std::unordered_map<std::pair<Node, Node>, float> EdgeList;
typedef std::vector<std::vector<float>> AdjacencyMatrix;

class Graph {
public:
	Graph() = default;

	void addNode(vec2 pos = vec2(50, 50), std::string name = "");
	void addNode(Node&);

	void addEdge(Node&, Node&, edge_type et = DIRECTED, float value = 1.0f);
	void addEdge(int, int, edge_type et = DIRECTED, float value = 1.0f);

	void removeEdge(Node&, Node&);
	void removeEdge(int, int);

	void handleEvent(SDL_Event*);
	void render(SDL_Renderer*);

private:
	std::vector<std::unique_ptr<Node>> m_nodes;
	AdjacencyList m_adjList;
	Node* _activeNode;
};