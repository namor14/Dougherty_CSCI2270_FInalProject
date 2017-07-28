# Dougherty_CSCI2270_FinalProject
My Project consists of a graph of Airports. Each of these airports has a linked list contained within that contains each Airline’s flight map. Each connection between airports will be weighted by the number of miles between the airports. The airline’s flight map will also be a graph which will necessarily be a subset of the primary graph. A user may select two destinations and receive fastest route, the fastest route an individual airline may offer, display the contents of the Airport map, the map of a specific airline. Each Airport will be a struct containing a linked list of airlines present and name of city, where each airline will be a struct containing their flight map. Data will be fed into the program using a text file wherein each city exists and has its available airlines contained within, which will be processed and read in to the vertices of the airport graph, and from there the airline maps will be subsequently constructed.

In order to run simply compile the provided files and interact through the command line, text.txt is the default text file containing airline information, but any data in the same form will also be processed. Editing the text.txt is the easiest way to do this.

Roman Dougherty

Open Issues/Bugs
The program breaks upon attempting to print Airports and their connections
The program will not find the correct route through the graph
The program does not properly display airlines in the Vector

Program was written in Visual Studio 2017 Community on a Windows system, however it should work just as well with g++.