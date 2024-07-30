#include"Node.hpp"

float Node::s_rad = 50;

bool Node::handle(SDL_Event* e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	bool mouseInNode = (x > _x - s_rad && x < _x + s_rad) && (y > _y - s_rad && y < _y + s_rad);
	if (!mouseInNode) return false;
	else {
		if (e->type == SDL_MOUSEBUTTONDOWN) {
			_isActive = !_isActive;
			std::cout << "clicked " << _name << std::endl;
			if (!_isActive)
				return false;
		}
	}

	return true;
}

void Node::render(SDL_Renderer* renderer) {
	aacircleColor(renderer, (int)_x, (int)_y, s_rad, _isActive ? m_aColor : m_color);
	stringColor(renderer, (int)_x - 4*strlen(_name.c_str()), (int)(_y) - 3, _name.c_str(), _isActive ? m_aColor : m_color);
}

void Node::print(std::ostream& out = std::cout) {
	out << "Node: " << _name << '\n';
	out << "Position: (" << _x << ", " << _y << ")\n";
	out << "Neighbors:\n";
	for (auto neighbor : m_neighbors) {
		out << '\t' << neighbor->_name << std::endl;
	}
}