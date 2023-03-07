#include <iostream>
#include <vector>
#include <string>

class BloomFilter {

    using std::vector;
    using std::string;

public:
    BloomFilter(int size, vector<Hasher*> hashers)
        : m_size(size), m_hashers(hashers), m_arr(new char[size]) {}
    ~BloomFilter() { if (m_arr) delete m_arr;}

    // TODO implement

private:
    const static int CHAR_BIT_SIZE = 8;
    int m_size;
    char* arr;
    vector<Hasher*> m_hashers;
    void set_bit(long pos);
    bool get_bit(long pos);
};

