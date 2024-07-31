#pragma once

#include<vector>
#include<iostream>
#include<string>

#include"SDL2/SDL.h"
#include"SDL2/SDL2_gfxPrimitives.h"

#include"node_internal.hpp"

struct Node {
	int _x, _y;
	std::string _name;
	std::vector<Node*> m_neighbors;
    bool _isActive   = false;
    bool _isDragging = false;
    bool _canDrag    = false;

    Uint32 m_color;
    Uint32 m_aColor;

	static float s_rad;

    Node() : _x(0), _y(0), m_color(0xFF000000) { _name = "Node"; m_aColor = 0xFFFF0000; }
	Node(vec2 vec) : _x(vec.x), _y(vec.y), m_color(0xFF000000) { _name = "Node"; m_aColor = 0xFFFF0000; }
	Node(const std::string name) : _x(0), _y(0), _name(name), m_color(0xFF000000) { m_aColor = 0xFFFF0000; }
	Node(vec2 vec, const std::string name) : _x(vec.x), _y(vec.y), _name(name), m_color(0xFF000000) { m_aColor = 0xFFFF0000; }

    bool handle(SDL_Event*);
	void render(SDL_Renderer*);
	void print(std::ostream&);
};

inline int udrawEdge(SDL_Renderer* renderer, Node& a, Node& b, Uint32 color = 0xFF000000) {
    int x1, x2;
    int y1, y2;
    double angle = atan2(b._y - a._y, b._x - a._x);

    x1 = a._x + Node::s_rad * cos(angle);
    y1 = a._y + Node::s_rad * sin(angle);
    x2 = b._x - Node::s_rad * cos(angle);
    y2 = b._y - Node::s_rad * sin(angle);

    return aalineColor(renderer, x1, y1, x2, y2, color);
}
inline void ddrawEdge(SDL_Renderer* renderer, Node& a, Node& b, Uint32 color = 0xFF000000, Uint32 arrowCol = 0xFF000000) {
    int x1, x2;
    int y1, y2;
    int arrowhead_size = 10;
    double angle = atan2(b._y - a._y, b._x - a._x);

    x1 = a._x + Node::s_rad * cos(angle);
    y1 = a._y + Node::s_rad * sin(angle);
    x2 = b._x - Node::s_rad * cos(angle);
    y2 = b._y - Node::s_rad * sin(angle);

    aalineColor(renderer, x1, y1, x2, y2, color);

    int x3 = x2 - arrowhead_size * cos(angle - M_PI / 6);
    int y3 = y2 - arrowhead_size * sin(angle - M_PI / 6);
    int x4 = x2 - arrowhead_size * cos(angle + M_PI / 6);
    int y4 = y2 - arrowhead_size * sin(angle + M_PI / 6);

    // Draw the arrowhead
    aatrigonColor(renderer, x2, y2, x3, y3, x4, y4, arrowCol);
    filledTrigonColor(renderer, x2, y2, x3, y3, x4, y4, arrowCol);
}