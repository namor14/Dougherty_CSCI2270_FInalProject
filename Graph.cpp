//#include "stdafx.h"
#include "Graph.hpp"

vertex * Graph::getRoute(Airport *start, Airport *end)
{
	vertex *startV = search(start->name);
	vertex *endV = search(end->name);
	startV->solved = true;
	startV->distance = 0;
	vertex *parent = new vertex;
	std::vector <vertex*> solved = { startV };
	while (!endV->solved)
	{
		int minDistance = INT_MAX;
		vertex *solvedV = nullptr;
		for (int i = 0; i < solved.size(); i++)
		{
			vertex *s = solved[i];
			for (int j = 0; j < s->adjacent.size(); i++)
			{
				if (!s->adjacent[j].v->solved)
				{
					int dist = s->distance + s->adjacent[j].weight;
					if (dist < minDistance)
					{
						solvedV = s->adjacent[j].v;
						minDistance = dist;
						parent = s;
					}
				}
			}
		}
		solvedV->distance = minDistance;
		solvedV->parent = parent;
		solvedV->solved = true;
		solved.push_back(solvedV);
	}
	return endV;
}

vertex * Graph::getRoute(Airport *start, Airport * end, std::string name)
{
	Airline *a = new Airline;
	for (int i = 0; i < airlines.size(); i++)
	{
		if (airlines[i]->name == name)
		{
			a = airlines[i];
		}
	}
	return a->flightMap->getRoute(start, end);
}

void Graph::insertVertex(Airport *key)
{
	bool found = false;
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].key == key)
		{
			found = true;
			break;
		}
	}
	if (found == false)
	{
		vertex v;
		v.key = key;
		vertices.push_back(v);
	}
}

void Graph::insertEdge(vertex *v1, vertex *v2, int weight)
{
	for (int i = 0; i < v1->adjacent.size(); i++)
	{
		if (v2->key == v1->adjacent[i].v->key)
		{
			return;
		}
	}
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].key == v1->key)
		{
			for (int j = 0; j < vertices.size(); j++)
			{
				if (vertices[j].key == v2->key && i != j)
				{
					adjVertex a;
					a.v = &vertices[j];
					a.weight = weight;
					vertices[i].adjacent.push_back(a);
				}
			}
		}
	}
}

void Graph::printGraph()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		std::cout << vertices[i].key->name << " has flights to:" << std::endl;
		for (int j = 0; j < vertices.size(); j++)
		{
			std::cout << vertices[i].adjacent[j].v->key->name << std::endl;
		}
	}
}

void Graph::printAirlines()
{
	for (int i = 0; i < airlines.size(); i++)
	{
		std::cout << airlines[i]->name << std::endl;
	}
}

void Graph::printAirlineGraph(std::string name)
{
	for (int i = 0; i < airlines.size(); i++)
	{
		if (airlines[i]->name == name)
		{
			airlines[i]->flightMap->printGraph();
			break;
		}
	}
}

bool Graph::airline(std::string name)
{
	bool ret = false;
	for (int i = 0; i < airlines.size(); i++)
	{
		if (airlines[i]->name == name) ret = true;
	}
	return ret;
}

vertex * Graph::search(std::string name)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].key->name == name)
		{
			return &vertices[i];
		}
	}
	return nullptr;
}

void Graph::buildGraph(std::string filename)
{
	std::fstream file;
	file.open(filename);
	std::string input;
	int mode = 1;
	while (file >> input)
	{
		//mode1 adds airports to overall graph
		if (input == "mode1")
		{
		mode = 1;
		}
		//mode2 adds airlines to airports/creates airline specific graphs
		else if (input == "mode2")
		{
			mode = 2;
		}
		//mode3 adds flights (connections between airports on airline graphs)
		else if (input == "mode3")
		{
			mode = 3;
		}
		else if (mode == 1)
		{
			Airport *b = new Airport;
			b->name = input;
			b->airlines = nullptr;
			insertVertex(b);
		}
		else if (mode == 2)
		{
			Airline *a = new Airline;
			vertex* v = search(input);
			file >> input;
			for (int i = 0; i < airlines.size(); i++)
			{
				if (airlines[i]->name == input)
				{
					a->next = nullptr;
					a = airlines[i];
					break;
				}
			}
			if (a->name == input)
			{
				a->flightMap->insertVertex(v->key);
			}
			else
			{
				a->name = input;
				a->next = nullptr;
				a->flightMap = new Graph;
				a->flightMap->insertVertex(v->key);
				airlines.push_back(a);
			}
			Airline *temp = v->key->airlines;
			if (temp == nullptr)
			{
				v->key->airlines = a;
				v->key->airlines->next = nullptr;
			}
			else
			{
				while (temp->next != nullptr)
				{
					temp = temp->next;
				}
				temp->next = a;
				temp->next->next = nullptr;
			}
		}
		else if (mode == 3)
		{
			vertex* v1 = search(input);
			file >> input;
			vertex* v2 = search(input);
			file >> input;
			bool flag1 = false;
			bool flag2 = false;
			Airline *temp = v1->key->airlines;
			while (temp != nullptr)
			{
				if (temp->name == input)
				{
					flag1 = true;
					break;
				}
				temp = temp->next;
			}
			temp = v2->key->airlines;
			while (temp != nullptr)
			{
				if (temp->name == input)
				{
					flag2 = true;
					break;
				}
				temp = temp->next;
			}
			file >> input;
			int weight = stoi(input);
			if (flag1 && flag2)
			{
				insertEdge(v1, v2, weight);
				insertEdge(v2, v1, weight);
			}
			else std::cout << "Connection not made" << std::endl;
		}
	}
	//build main graph connections using connections of airline graphs
	for (int i = 0; i < airlines.size(); i++)
	{
		Graph *g = airlines[i]->flightMap;
		for (int j = 0; j < g->vertices.size(); j++)
		{
			vertex v1 = g->vertices[j];
			for (int k = 0; k < g->vertices.size(); k++)
			{
				vertex v2 = g->vertices[k];
				if (k != j)
				{
					for (int l = 0; l < v2.adjacent.size(); l++)
					{
						if (v2.key->name == v1.adjacent[k].v->key->name)
						{
							insertEdge(&v1, &v2, v1.adjacent[k].weight);
						}
					}
				}
			}
		}
	}
}
