#pragma once

#include <vector>
#include <iostream>
#include <string>

class dynamicEnum
{
private:
    std::vector<std::string> values;
public:
    void addValue(std::string description) {
        values.push_back(description);
    }
    int getValue(std::string description) {
        if (values.size() == 0)
            return -1;
        std::vector<std::string>::iterator iterate;
        int count = 0;
        for (iterate = values.begin(); iterate
            != values.end(); iterate++) {
            if (description == *iterate)
                return count;
            count++;
        }
        return -1;
    }
    std::string getDescription(int value) {
        if (value > values.size() - 1 || value < 0
            || values.size() == 0)
            return "INVALID_MESSAGE";
        else
            return values[value];
    }
    friend std::ostream& operator<<(std::ostream& os,
        dynamicEnum& dn) {
        std::string out = "";
        int count = 0;
        std::vector<std::string>::iterator iterate;
        for (iterate = dn.values.begin(); iterate
            != dn.values.end(); iterate++) {
            os << count << " " << *iterate << std::endl;
            count++;
        }
        return os;
    }
};