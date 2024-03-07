//
// Created by Davide Teixeira on 07/03/2024.
//

#ifndef DA_PROJ1_ELEMENT_H
#define DA_PROJ1_ELEMENT_H

class Element{

protected:
    std::string code;
public:

    Element(std::string code) : code(code) {};

    bool operator==(const Element& other) const{
        return this->code == other.code;
    }
};

#endif //DA_PROJ1_ELEMENT_H
