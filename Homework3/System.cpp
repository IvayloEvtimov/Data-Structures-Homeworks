#include "System.h"

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

System::System():map(),zones()
{
}

void System::load(std::ifstream &input)
{
	bool hasKeys = false;
	std::string str;
	char ch = 0;
	std::getline(input, str, '\n');
	if (str != "[zones]")
		return;

	// Cycle for reading the egdes for traversing from zone to zone
	while (true)
	{
		vertex startZone;
		vertex endZone;
		key keyName;

		input >> startZone;

		if (input.eof())
			break;

		//It means that the there are no more edges and the reading of keys for each zone has to begin
		if (startZone == "[keys]")
		{
			input.ignore(256,'\n');
			hasKeys = true;
			break;
		}

		//Used for reading the "->" symbol between each zone
		input >> str;
		input >> endZone;

		// If there is no opening bracket
		// then no key is required for traversing from these zones
		if (!lookForChar('[', input))
			addEdge(map, startZone, endZone); // And the zones are added to the map
		else
		{	// Else the key is extracted 
			std::getline(input, keyName, ']');
			if (input.eof())
				break;

			// And the edge if added with an additional key
			addEdge(map, startZone, endZone, keyName);

			input.ignore(256, '\n');
		}

	}

	// If there are no keys in some zones 
	// the reading will stop
	if (!hasKeys)
		return;

	// Cycle used for reading the keys in each zone
	while (true)
	{
		key keyName;
		std::string str;
		vertex zone;

		getline(input , keyName,'-');
		if (input.eof())
			break;
		while (keyName.back() == ' ')
			keyName.erase(keyName.size() - 1);

		input >> str;
		input>> zone;

		input.ignore(256, '\n');

		zones.insert(zone, keyName);
	}

}

// Finds unreachable zones by givin a starting zone
void System::findUnreachable(const vertex& start)
{
	// Used for storring each collected key throughout the traversing
	std::unordered_set<key> foundKeys;
	// unordered_set used for storing each passed zone
	std::unordered_set<vertex> reached=dfsWrapper(start,foundKeys);


	// Opens the export file for writing
	std::ofstream output("unreachable.dot");
	if (!output.is_open())
		return;

	// Exports the graph to the file
	exportGraph(output, reached);
	output.close();
}

bool System::lookForChar(const char delim, std::ifstream& input)
{
	char ch = input.peek();
	while (true)
	{
		if (ch == delim)
			return true;
		if (ch == '\n' || ch == 0)
			return false;
		input.get(ch);
	}
	return false;
}


void System::dfsSearch(const vertex &currentZone, std::unordered_set<vertex>&reached, std::unordered_set<key>foundKeys, bool newKey)
{
	// Checks if the current zone has any key
	if (zones.hasKeys(currentZone))
	{
		for (const vertex& zone : zones.find(currentZone))
		{
			if (!foundKeys.count(zone))
				newKey = true;

			foundKeys.insert(zone);
		}
	}

	reached.insert(currentZone);

	// Tries to reach any of the current zone's neighbours
	for (edge& currEdge : map.map[currentZone])
	{
		// If a new Keys has been added to the collection
		// and the neighbour has already been visited
		// tries again to reach any new zones with the newly added keys
		if (newKey && reached.count(currEdge.first))
		{	
			// The new search returns its reached zones
			// and they are combined with the current reached zones
			std::unordered_set<vertex> newReached = dfsWrapper(currEdge.first, foundKeys);

			if (newReached != reached)
				for (const vertex& zone : newReached)
					reached.insert(zone);

			newKey = false;
		}

		// If the neighbour hasn't been reached
		// and if the path isn't blocked
		// goes into the the neighbour
		if (!reached.count(currEdge.first))
			if (currEdge.second == "no key" || foundKeys.count(currEdge.second))
				dfsSearch(currEdge.first, reached, foundKeys, newKey);
	}
}
// Method for outputing the map into a .dot file
void System::exportGraph(std::ofstream &output, std::unordered_set<vertex> reached)
{
	output << "digraph {\n";

	// Outputs all the zones with keys in them
	// And all the zones which aren't reachable
	outputZones(output, reached);

	output << std::endl << std::endl;

	//Outputs all the edges of the map and puts a label if 
	// A key is required in order to pass through

	for (const std::pair<const vertex, std::vector<edge>>& itr : map.map)
	{
		for (const edge& currEdge : itr.second)
		{
			output << itr.first;
			output << " -> ";
			output << (currEdge).first;

			if ((currEdge).second != "no key")
				output << "[label=\"" << (currEdge).second << "\"]";
			output << ';' << std::endl;
		}
	}

	output << "}\n";
}

// Adds label to a zone depending on whether it is reachable or there is a key in it
void System::addLabel(std::ofstream & output,const vertex& zone, const bool reached,  std::vector<key> keys)
{
	// If there is no key inside and the zone if reached
	// Then there is no need to add a label
	if (reached==true && keys.empty())
		return;

	output << zone << "[";

	if (!keys.empty())
	{	// Cycle for all the keys located in the zone
		for (const key& currKey : keys)
		{
			output << "label=\"";
			output << zone;
			output << "\\l";
			output << currKey;
			output << "\"";
			if (!reached)
				output << ", ";
		}
	}

	// If the zone isn't reachable
	if (!reached)
		output << "color = red, style = filled, fillcolor = \"#ffefef\"";

	output << "];\n";
}

void System::outputZones(std::ofstream &output, const std::unordered_set<vertex>& reached)
{
	std::unordered_set<vertex> outputedZones;

	// Outputs all the edges in the map
	// By first checking if it has alreaby been outputed
	// In order to reduce repetition

	for (const std::pair<const vertex, std::vector<edge>>& itr : map.map)
	{
		if (!outputedZones.count(itr.first))
		{
			addLabel(output, itr.first, reached.count(itr.first), zones.find(itr.first));
			outputedZones.insert(itr.first);
		}

		for (const edge& currEdge : itr.second)
		{
			if (!outputedZones.count((currEdge).first))
			{
				addLabel(output, (currEdge).first, reached.count((currEdge).first), zones.find((currEdge).first));
				outputedZones.insert((currEdge).first);
			}
		}
	}
}

std::unordered_set<key> System::dfsWrapper(const vertex &zone,std::unordered_set<key>& foundKeys)
{
	std::unordered_set<vertex> reached;
	dfsSearch(zone, reached, foundKeys);
	return reached;
}
