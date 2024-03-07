//
// Created by Davide Teixeira on 07/03/2024.
//

#include "GraphConstructor.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

GraphConstructor::GraphConstructor(std::string citiesFile, std::string reservoirsFile, std::string stationsFile, std::string pipesFile) :
    citiesFile(citiesFile), reservoirsFile(reservoirsFile), stationsFile(stationsFile), pipesFile(pipesFile) {};

City GraphConstructor::parseCity(std::string line) {
    std::vector<std::string> lineParsed;
    std::string word;
    std::istringstream iss(line);
    while(getline(iss, word, ',')){
        lineParsed.push_back(word);
    }

    std::string cityName = lineParsed[0];
    int cityId = std::stoi(lineParsed[1]);
    std::string cityCode = lineParsed[2];
    float cityDemand = std::stof(lineParsed[3]);
    long cityPopulation = std::stol(lineParsed[4]);

    return City(cityName, cityId, cityCode, cityDemand, cityPopulation);
}

Graph<Element> GraphConstructor::createGraph(){
    Graph<Element> res = Graph<Element>();

    std::ifstream in(citiesFile);

    std::string line;

    getline(in, line); // for jumping header

    while(getline(in, line)){
        City city = parseCity(line);

        res.addVertex(city);
    }

    return res;
}