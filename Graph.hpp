//#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct vertex;
struct adjVertex;
struct Airport;
struct Airline;

#ifndef GRAPH_HPP
#define GRAPH_HPP

class Graph
{
private:
	std::vector<Airline*> airlines;
	std::vector<vertex> vertices;
public:
	vertex* getRoute(Airport *start, Airport *destination);
	vertex* getRoute(Airport *start, Airport *destination, std::string name);
	void insertVertex(Airport *key);
	void insertEdge(vertex *v1, vertex *v2, int weight);
	void printGraph();
	void printAirlines();
	void printAirlineGraph(std::string name);
	bool airline(std::string name);
	vertex *search(std::string name);
	void buildGraph(std::string filename);
};

#endif

struct adjVertex
{
	vertex *v;
	int weight;
};

struct vertex
{
	Airport *key;
	std::vector<adjVertex> adjacent;
	bool solved;
	int distance;
	vertex *parent;
};

struct Airline
{
	std::string name;
	Graph *flightMap;
	Airline * next;
};

struct Airport
{
	std::string name;
	Airline* airlines = nullptr;
};