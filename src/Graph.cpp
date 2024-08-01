#include"Graph.hpp"

void Graph::addNode(vec2 pos, std::string name) {
	if (name == "") name += 'A' + m_nodes.size();
	m_nodes.emplace_back(std::make_unique<Node>(pos, name));
}
void Graph::addNode(Node& node) {
	m_nodes.emplace_back(std::make_unique<Node>(std::move(node)));
}

void Graph::addEdge(Node& a, Node& b, EdgeType et, float value) {
	m_adjList[&a][&b] = { &a, &b, value, et };
	if(et == EdgeType::UNDIRECTED)
		m_adjList[&b][&a] = { &a, &b, value, et };
}
void Graph::addEdge(int a, int b, EdgeType et, float value) {
	addEdge(*m_nodes[a], *m_nodes[b], et);
}

void Graph::removeEdge(Node& a, Node& b){
	if (m_adjList[&a][&b].type == EdgeType::UNDIRECTED)
		m_adjList[&b].erase(&a);
	m_adjList[&a].erase(&b);
}
void Graph::removeEdge(int a, int b){
	removeEdge(*m_nodes[a], *m_nodes[b]);
}

void Graph::handleEvent(SDL_Event* e) {
	bool newNode = true;

	switch (e->type) {
	case SDL_MOUSEBUTTONDOWN:
		for (auto& node : m_nodes) {
			bool isClicked = false;

			if (node->handle(e)) {
				isClicked = true;
				newNode = false;
			}

			if(isClicked) {
				if (!_activeNode) {
					_activeNode = node.get();
					break;
				}
				else {
					if (_activeNode == node.get()) {
						if (!isClicked) {
							continue;
						}
					}
					else if (!m_adjList[_activeNode].count(node.get())) {
						EdgeType et = e->button.button == SDL_BUTTON_LEFT ? EdgeType::DIRECTED : EdgeType::UNDIRECTED;
						addEdge(*_activeNode, *node.get(), et);
					}
					else {
						removeEdge(*_activeNode, *node.get());
					}

					node->_isActive = false;
					_activeNode->_isActive = false;
					_activeNode = nullptr;
				}
			}
		}

		if (newNode) {
			std::string name = "Node " + std::to_string(m_nodes.size());
			int x, y;
			SDL_GetMouseState(&x, &y);

			addNode(vec2(x, y), name);
		}

		break;

	default:
		for (auto& node : m_nodes) {
			node->handle(e);
		}
		break;
	}
}

void Graph::render(SDL_Renderer* renderer) {
	for (auto& node : m_nodes) {
		node->render(renderer);
	}
	for (auto [node, edgeList] : m_adjList) {
		for (auto [neighbor, n_edge] : edgeList) {
			if (n_edge.type == EdgeType::DIRECTED) {
				ddrawEdge(renderer, *node, *neighbor);
			}
			else {
				udrawEdge(renderer, *node, *neighbor);
			}
		}
	}
}