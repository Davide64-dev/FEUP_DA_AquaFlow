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

Reservoir GraphConstructor::parseReservoir(std::string line){
    std::vector<std::string> lineParsed;
    std::string word;
    std::istringstream iss(line);
    while(getline(iss, word, ',')){
        lineParsed.push_back(word);
    }

    std::string reservoirName = lineParsed[0];
    std::string reservoirMunicipaly = lineParsed[1];
    int reservoirId = std::stoi(lineParsed[2]);
    std::string reservoidCode = lineParsed[3];
    long reservoirMaxDelivery = std::stol(lineParsed[4]);

    return Reservoir(reservoirName, reservoirMunicipaly, reservoirId, reservoidCode, reservoirMaxDelivery);
}

Station GraphConstructor::parseStation(std::string line) {
    std::vector<std::string> lineParsed;
    std::string word;
    std::istringstream iss(line);
    while(getline(iss, word, ',')){
        lineParsed.push_back(word);
    }

    int stationId = std::stoi(lineParsed[0]);
    std::string stationCode = lineParsed[1].substr(0, lineParsed[1].size()-1);

    return Station(stationCode, stationId);

}

Graph<std::string> GraphConstructor::createGraph(){
    Graph<std::string> res = Graph<std::string>();
    std::string line;


    std::ifstream inCities(citiesFile);
    getline(inCities, line); // for jumping header
    while(getline(inCities, line)){
        City city = parseCity(line);
        res.addVertex(city.getCode());
    }

    std::ifstream inReservoir(reservoirsFile);
    getline(inReservoir, line); // for jumping header
    while(getline(inReservoir, line)){
        Reservoir reservoir = parseReservoir(line);
        res.addVertex(reservoir.getCode());
    }

    std::ifstream inStations(stationsFile);
    getline(inStations, line); // for jumping headers
    while(getline(inStations, line)){
        Station station = parseStation(line);
        res.addVertex(station.getCode());
    }

    return res;
}