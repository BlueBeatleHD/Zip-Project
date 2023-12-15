#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
struct Node {
	std::string gender;
	int pop, min_age, max_age, zip;
};
static void readData(ifstream& file, vector<Node*>& nodes) {
	string line;
	file.open("population_by_zip_2010.csv");
	if (!file.is_open())
	{
		cout << "Not open";
		return;
	}
	string buffer;
	getline(file, buffer);
	int lines = 0;
	while (getline(file, line, ',')) {
		Node* newNode = new Node;
		newNode->pop = stoi(line);
		getline(file, line, ',');
		if (line != "") {
			newNode->min_age = stoi(line);
		}
		else {
			newNode->min_age = 101;
		}
		getline(file, line, ',');
		if (line != "") {
			newNode->max_age = stoi(line);
		}
		else {
			newNode->max_age = 101;
		}
		getline(file, line, ',');
		if (line != "") {
			newNode->gender = line;
		}
		else {
			newNode->gender = "both";
		}
		getline(file, line, ',');
		newNode->zip = stoi(line);
		getline(file, line);
		//skip geoid
		if (newNode->min_age == 101 && newNode->max_age == 101 && newNode->gender == "both")
		{
			nodes.push_back(newNode);
		}
		else
		{
			delete newNode;
		}
		lines++;
	}
	cout << "Parsed through " << lines << " lines!\n";
	file.close();
}
static void print(vector<Node*>& nodes) {
	for (auto iter = nodes.begin(); iter != nodes.end(); iter++) {
		cout << "Population: " << (*iter)->pop << "  Minimum age: " << (*iter)->min_age << "   Maximum age: " << (*iter)->max_age << "   Gender: " << (*iter)->gender << "   Zipcode: " << (*iter)->zip << endl;
	}
}