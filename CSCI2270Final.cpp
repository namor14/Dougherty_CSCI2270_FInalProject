// CSCI2270Final.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Graph.hpp"

int main()
{
	bool flag = true;
	Graph g;
	g.buildGraph("file.txt");
	while (flag)
	{
		std::cout << "1: Get flight(s) from Airport to Airport" << std::endl;
		std::cout << "2: Get flight(s) from Airport to Airport with one carrier" << std::endl;
		std::cout << "3: Print all available connections" << std::endl;
		std::cout << "4: Print all connections for a carrier" << std::endl;
		std::cout << "5: Print available carriers" << std::endl;
		std::cout << "6: Quit" << std::endl;
		std::string input;
		std::getline(std::cin, input);
		int choice = stoi(input);
		if (choice == 1)
		{
			std::cout << "From where will you depart?" << std::endl;
			std::getline(std::cin, input);
			vertex *v1 = g.search(input);
			if (v1 == nullptr)
			{
				std::cout << "City not found" << std::endl;
				continue;
			}
			std::cout << "Where will you arrive?" << std::endl;
			std::getline(std::cin, input);
			vertex *v2 = g.search(input);
			if (v2 == nullptr)
			{
				std::cout << "City not found" << std::endl;
				continue;
			}
			vertex *trip = g.getRoute(v1->key, v2->key);
			int distance = trip->distance;
			if (v2->parent = v1) std::cout << "You will have a direct route" << std::endl;
			else
			{
				std::cout << "Your route will take you through: " << std::endl;
				while (trip->parent != v1)
				{
					std::cout << " " << trip->parent->key->name << ", " << std::endl;
					trip = trip->parent;
				}
			}
			std::cout << "Your route will span: " << distance << " miles." << std::endl;
		}
		else if (choice == 2)
		{
			std::cout << "From where will you depart?" << std::endl;
			std::getline(std::cin, input);
			vertex *v1 = g.search(input);
			if (v1 == nullptr)
			{
				std::cout << "City not found" << std::endl;
				continue;
			}
			std::cout << "Where will you arrive?" << std::endl;
			std::getline(std::cin, input);
			vertex *v2 = g.search(input);
			if (v2 == nullptr)
			{
				std::cout << "City not found" << std::endl;
				continue;
			}
			std::cout << "Which carrier would you like?" << std::endl;
			std::getline(std::cin, input);
			if (!g.airline(input))
			{
				std::cout << "Carrier not found" << std::endl;
				continue;
			}
			vertex *trip = g.getRoute(v1->key, v2->key, input);
			int distance = trip->distance;
			if (v2->parent = v1) std::cout << "You will have a direct route" << std::endl;
			else
			{
				std::cout << "Your route will take you through: " << std::endl;
				while (trip->parent != v1)
				{
					std::cout << " " << trip->parent->key->name << ", " << std::endl;
					trip = trip->parent;
				}
			}
			std::cout << "Your route will span: " << distance << " miles." << std::endl;
		}
		else if (choice == 3)
		{
			g.printGraph();
		}
		else if (choice == 4)
		{
			std::cout << "Which carrier would you like?" << std::endl;
			std::getline(std::cin, input);
			if (!g.airline(input))
			{
				std::cout << "Carrier not found" << std::endl;
				continue;
			}
			g.printAirlineGraph(input);
		}
		else if (choice == 5)
		{
			g.printAirlines();
		}
		else if (choice == 6)
		{
			flag = false;
		}
	}
}

