#include"Graph.hpp"

edge_type Graph::et = DIRECTED;

void Graph::addNode(vec2 pos, std::string name) {
	if (name == "") name += 'A' + m_nodes.size();
	m_nodes.emplace_back(std::make_unique<Node>(pos, name));
}
void Graph::addNode(Node& node) {
	m_nodes.emplace_back(std::make_unique<Node>(std::move(node)));
}

void Graph::addEdge(Node& a, Node& b, float value) {
	m_adjList[&a][&b] = { value, et };
	if(et == UNDIRECTED)
		m_adjList[&b][&a] = { value, et };
}
void Graph::addEdge(int a, int b, float value) {
	addEdge(*m_nodes[a], *m_nodes[b], et);
}

void Graph::handleEvent(SDL_Event* e) {
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		for (auto& node : m_nodes) {
			if (node->handle(e)) {
				if (!_activeNode) {
					_activeNode = node.get();
				}
				else {
					if (!m_adjList[_activeNode].count(node.get()))
						addEdge(*_activeNode, *node.get());
					_activeNode = nullptr;
				}
			}
		}
	}
}

void Graph::render(SDL_Renderer* renderer) {
	for (auto& node : m_nodes) {
		node->render(renderer);
	}
	for (auto [node, edgeList] : m_adjList) {
		for (auto [neighbor, n_edge] : edgeList) {
			if (n_edge.type == DIRECTED) {
				ddrawEdge(renderer, *node, *neighbor);
			}
			else {
				udrawEdge(renderer, *node, *neighbor);
			}
		}
	}
}

//int Graph::udrawLine(SDL_Renderer* renderer, Node& a, Node& b, Uint32 color = 0xFF000000){}
//void Graph::ddrawLine(SDL_Renderer* renderer, Node& a, Node& b, Uint32 color = 0xFF000000, Uint32 arrowCol = 0xFF000000){}