#pragma once
#include <ostream>
#include <sstream>
template <class Derived>
class BinaryIntBaseSequence
{
public:
    //Copy constructor
    BinaryIntBaseSequence(const BinaryIntBaseSequence& other)
    {
        this->sequenceInt = other.sequenceInt;
    }

    //Assignment operator 
    Derived& operator=(const Derived& other)
    {
        this->sequenceInt = other.sequenceInt;
        return static_cast<Derived&>(*this);
    }

    //Strong total ordering for set and map usage
    bool operator<(const Derived& other) const {
        return sequenceInt < other.sequenceInt;
    }

    // Overloads the << operator for BinaryIntBaseSequence objects
    // This allows the binary representation of sequenceInt to be easily printed
    // to an output stream, such as std::cout or a file stream.
    friend std::ostream& operator<<(std::ostream& os, const BinaryIntBaseSequence<Derived>& binaryIntBaseSequence)
    {
        uint64_t sequenceInt = binaryIntBaseSequence.sequenceInt;
        std::ostringstream oss;
        std::string resultToPrint;
        do
        {
            oss << (sequenceInt & 1); // last bit
            sequenceInt >>= 1;
        } while (sequenceInt);
        resultToPrint = oss.str();

        //revert to MSB to be in the left
        std::reverse(resultToPrint.begin(), resultToPrint.end());
        os << resultToPrint;
        return os;
    }

protected:
    uint64_t sequenceInt;
    BinaryIntBaseSequence(uint64_t sequenceInt)
    {
        this->sequenceInt = sequenceInt;
    }
};
