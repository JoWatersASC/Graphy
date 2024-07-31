#include"Node.hpp"

float Node::s_rad = 50;

bool Node::handle(SDL_Event* e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	bool res = true;

	bool mouseInNode = (x > _x - s_rad && x < _x + s_rad) && (y > _y - s_rad && y < _y + s_rad);
	if (!mouseInNode) res = false;

	switch(e->type) {
	case SDL_MOUSEBUTTONUP:
		_isDragging = false;
		_canDrag = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (!mouseInNode) break;
		_isActive = !_isActive;
		_canDrag = true;
		break;

	case SDL_MOUSEMOTION:
		if(_canDrag){
			_x = x;
			_y = y;

			_isDragging = true;
			res = false;
		}

		break;

	default:
		break;
	}

	return res;
}

void Node::render(SDL_Renderer* renderer) {
	aacircleColor(renderer, (int)_x, (int)_y, s_rad, _isActive ? m_aColor : m_color);
	filledCircleColor(renderer, (int)_x, (int)_y, s_rad - 1, _isActive ? m_aColor : 0xFFFFFFFF);

	stringColor(renderer, (int)_x - 4*strlen(_name.c_str()), (int)(_y) - 3, _name.c_str(), _isActive ? 0xFFFFFFFF : 0xFF000000);
}

void Node::print(std::ostream& out = std::cout) {
	out << "Node: " << _name << '\n';
	out << "Position: (" << _x << ", " << _y << ")\n";
	out << "Neighbors:\n";
	for (auto neighbor : m_neighbors) {
		out << '\t' << neighbor->_name << std::endl;
	}
}