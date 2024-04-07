//
// Created by Davide Teixeira on 07/03/2024.
//

#include "GraphConstructor.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <unordered_map>


GraphConstructor::GraphConstructor(std::string citiesFile, std::string reservoirsFile, std::string stationsFile, std::string pipesFile, bool isSmallDataSet) :
    citiesFile(citiesFile), reservoirsFile(reservoirsFile), stationsFile(stationsFile), pipesFile(pipesFile), isSmallDataSet(isSmallDataSet) {};

GraphConstructor::GraphConstructor() : citiesFile("../Project1DataSetSmall/Cities_Madeira.csv"),
                                        reservoirsFile("../Project1DataSetSmall/Reservoirs_Madeira.csv"),
                                        stationsFile("../Project1DataSetSmall/Stations_Madeira.csv"),
                                        pipesFile("../Project1DataSetSmall/Pipes_Madeira.csv") {};

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
    long cityPopulation;
    if (isSmallDataSet) {
        std::string cityPopulationComplete = lineParsed[4] + lineParsed[5];
        cityPopulationComplete = cityPopulationComplete.substr(1, cityPopulationComplete.size()-2);
        if (cityPopulationComplete[cityPopulationComplete.size()-1] == '\"')
            cityPopulationComplete = cityPopulationComplete.substr(0, cityPopulationComplete.size()-1);
        cityPopulation = std::stol(cityPopulationComplete);
    }
    else{
        cityPopulation = 0;
    }

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
    std::string stationCode;
    if (lineParsed[1][lineParsed[1].size() - 1] == '\r')
        stationCode = lineParsed[1].substr(0, lineParsed[1].size()-1);

    else stationCode = lineParsed[1];


    return Station(stationCode, stationId);

}


void GraphConstructor::parsePipe(std::string line, std::string& sourc, std::string& dest, double& weight, int& direction) {
    std::vector<std::string> lineParsed;
    std::string word;
    std::istringstream iss(line);
    while(getline(iss, word, ',')){
        lineParsed.push_back(word);
    }

    sourc = lineParsed[0];
    dest = lineParsed[1];
    weight = std::stod(lineParsed[2]);
    direction = std::stoi(lineParsed[3]);
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
        if (line == ",,,") continue;
        Station station = parseStation(line);
        res.addVertex(station.getCode());
    }

    std::ifstream inPipes(pipesFile);
    getline(inPipes, line); // for jumping headers
    while(getline(inPipes, line)){
        std::string source, dest;
        double weight;
        int direction;
        parsePipe(line, source, dest, weight, direction);
        //std::cout << "Added edge " << source << ", " << dest << ", " << weight << std::endl;
        if (direction){
            if (!res.addEdge(source, dest, weight)) std::cout << "Error Creating the graph\n";
        }
        else{
            if (!res.addBidirectionalEdge(source, dest, weight)) std::cout << "Error Creating the graph\n";
        }
    }

    return res;
}



std::unordered_map<std::string, City> GraphConstructor::getCityMap() {
    std::unordered_map<std::string, City> cityMap = std::unordered_map<std::string, City>();
    std::string line;

    std::ifstream inCities(citiesFile);
    getline(inCities, line); // for jumping header
    while(getline(inCities, line)){
        City city = parseCity(line);
        cityMap.insert(std::make_pair(city.getCode(), city));
    }

    return cityMap;
}


std::unordered_map<std::string, Reservoir> GraphConstructor::getReservoirMap() {
    std::unordered_map<std::string, Reservoir> reservoirMap;
    std::string line;

    std::ifstream inReservoir(reservoirsFile);
    getline(inReservoir, line); // for jumping header
    while(getline(inReservoir, line)){
        Reservoir reservoir = parseReservoir(line);
        reservoirMap.insert(std::make_pair(reservoir.getCode(), reservoir));
    }

    return reservoirMap;
}


std::unordered_map<std::string, Station> GraphConstructor::getStationMap() {
    std::unordered_map<std::string, Station> stationMap;
    std::string line;

    std::ifstream inStations(stationsFile);
    getline(inStations, line); // for jumping headers
    while(getline(inStations, line)){
        if (line == ",,,") continue;
        Station station = parseStation(line);
        stationMap.insert(std::make_pair(station.getCode(), station));
    }

    return stationMap;
}


