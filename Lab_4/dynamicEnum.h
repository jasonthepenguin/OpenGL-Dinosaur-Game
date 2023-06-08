#pragma once

#include <vector>
#include <iostream>
#include <string>

/**
 * @brief A class that represents a dynamic enumeration.
 *
 * This class allows adding values to an enumeration dynamically and provides methods to retrieve the value based on its description or index.
 */
class dynamicEnum
{
private:
    std::vector<std::string> values; /**< The vector to store the enumeration values. */
public:
    /**
     * @brief Adds a new value to the enumeration.
     *
     * @param description The description of the value to be added.
     */
    void addValue(std::string description) {
        values.push_back(description);
    }

    /**
     * @brief Gets the index of the value in the enumeration based on its description.
     *
     * @param description The description of the value.
     * @return The index of the value in the enumeration, or -1 if the value is not found.
     */
    int getValue(std::string description) {
        if (values.size() == 0)
            return -1;
        std::vector<std::string>::iterator iterate;
        int count = 0;
        for (iterate = values.begin(); iterate != values.end(); iterate++) {
            if (description == *iterate)
                return count;
            count++;
        }
        return -1;
    }

    /**
     * @brief Gets the description of the value in the enumeration based on its index.
     *
     * @param value The index of the value.
     * @return The description of the value, or "INVALID_MESSAGE" if the index is invalid or the enumeration is empty.
     */
    std::string getDescription(int value) {
        if (value > values.size() - 1 || value < 0 || values.size() == 0)
            return "INVALID_MESSAGE";
        else
            return values[value];
    }

    /**
     * @brief Overloaded stream insertion operator to print the enumeration values.
     *
     * @param os The output stream.
     * @param dn The dynamicEnum object.
     * @return The output stream after printing the values.
     */
    friend std::ostream& operator<<(std::ostream& os, dynamicEnum& dn) {
        std::string out = "";
        int count = 0;
        std::vector<std::string>::iterator iterate;
        for (iterate = dn.values.begin(); iterate != dn.values.end(); iterate++) {
            os << count << " " << *iterate << std::endl;
            count++;
        }
        return os;
    }
};
