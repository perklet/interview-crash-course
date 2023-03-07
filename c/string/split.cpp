#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> split(const char *str, char c = ' ')
{
    vector<string> result;

    do {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (*str++ != '\0');

    return result;
}

int main() {
    string s = "hello the world";
    vector<string> words = split(s.c_str());

    for (auto& word : words) {
        cout << word <<endl;
    }

    return 0;
}
