#include "Wayspace.hpp"

Wayspace::Wayspace() : active(false), scale_set(false) {}

Wayspace::~Wayspace()
{
	for(auto& point : waypoint_vec)
	{
		delete point;
	}
}

void Wayspace::pullFeature(std::string point, std::string type)
{
	waypoint_map.find(point)->removeFeature(type);
}

void Wayspace::pushFeature(std::string point, std::string type, double metric)
{
	waypoint_map.find(point)->addFeature(type, metric);
}

void Wayspace::undoAdd()
{
	if(waypoint_stack.size() == 0){std::cout << std::endl << "no additions to undo" << std::endl; return;}
	Waypoint* popped = waypoint_stack.top();
	waypoint_stack.pop();
	for(auto& point : waypoint_vec)
	{
		if(point == popped)
		{
			std::swap(point, waypoint_vec.back());
			waypoint_vec.pop_back();
		}
	}
	waypoint_map.remove(popped->getName());
	std::cout << std::endl << "'" << popped->getName() << "' successfully removed" << std::endl;
	delete popped;
}

void Wayspace::listPoints()
{
	std::cout << std::endl;
	if(waypoint_vec.empty()){std::cout << "no waypoints in map" << std::endl; return;}
	for(auto& point : waypoint_vec){std::cout << point->getName() << " : <" <<  point->getY() << "," << point->getX() << ">" << std::endl;}
}

void Wayspace::rankFeatures(std::string type)
{
	std::vector<Waypoint*> temp_vec;
	if(waypoint_vec.empty()){std::cout << std::endl << "no waypoints in map" << std::endl; return;}
	for(auto& point : waypoint_vec)
	{
		if(point->checkFeature(type))
		{
			temp_vec.push_back(point);
		}
	}
	Quicksort::quicksort(temp_vec, type);
	
	std::cout << std::endl << "waypoints ranked by '" << type << "'" << std::endl;
	for(auto& point : temp_vec)
	{
		std::cout << point->getName() << " : <" << point->getX() << "," << point->getY() << "> : "  << point->getFeature(type) << std::endl;
	}
}

void Wayspace::viewPoint(std::string name)
{
	waypoint_map.find(name)->viewPoint();	
}

void Wayspace::plotPoints(){for(auto& point : waypoint_vec){plotRight(point->getY(), point->getX(), "@"+point->getName());}}

void Wayspace::addPoint(int y, int x, std::string name)
{
	Waypoint* new_point = new Waypoint(y, x, name);
	waypoint_vec.push_back(new_point);
	waypoint_stack.push(new_point);
	waypoint_map.insert(new_point);
}

bool Wayspace::checkExistName(std::string name){return waypoint_map.count(name);}
void Wayspace::setScale(int scale){this->scale = scale;scale_set = true;}
bool Wayspace::getScaleSet(){return this->scale_set;}
void Wayspace::setUnit(std::string unit){this->unit = unit;}
std::string Wayspace::getUnit(){return this->unit;}
int Wayspace::getScale(){return this->scale;}


void Wayspace::plotElements()
{
	plotRight(2, 75, "<W+E>");
	plotDown(0, 77, "^N+Sv");
	plotRight(1, 0, "<-+-> " + std::to_string(scale*5) + " " + unit + "(s)");
	plotRight(0, 0, "(viewing '" + name  + "')");
	plotRight(21, 0, "('exitmap' to return)");
}

void Wayspace::plotRight(int y, int x, std::string input)
{
	for(int i = 0; i < input.length(); i++){ascii_grid[y][x+i] = input[i];}
}

void Wayspace::plotDown(int y, int x, std::string input)
{
	for(int i = 0; i < input.length(); i++){ascii_grid[y+i][x] = input[i];}
}

void Wayspace::fillSpace(const char c)
{
	for(auto& row : ascii_grid)
	{
		for(char& point : row)
		{
			point = c;
		}
	}
}

bool Wayspace::getActive(){return this->active;}
void Wayspace::printSpace()
{
	system("clear");
	for(auto& row : ascii_grid)
	{
		for(char& point : row)
		{
			std::cout << point;
		}
		std::cout << std::endl;
	}
}

void Wayspace::setName(std::string name){this->name = name;}
void Wayspace::activate(){this->active = true;}
std::string Wayspace::getName(){return this->name;}

void Wayspace::deactivate()
{
	//	waypoint_vec.clear();
	name.clear();
	active = false;
	fillSpace(char(' '));
	scale = 0;
	scale_set = false;
}

