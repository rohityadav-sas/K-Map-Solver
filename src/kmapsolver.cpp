#include "kmapsolver.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <string>

std::string toBinary(int number, int width)
{
    std::string binary = "";
    for (int i = width - 1; i >= 0; --i)
    {
        binary += (number & (1 << i)) ? '1' : '0';
    }
    return binary;
}

int countOnes(const std::string &s)
{
    return count(s.begin(), s.end(), '1');
}

bool combine(const std::string &a, const std::string &b, std::string &result)
{
    int differences = 0;
    result = a;
    for (size_t i = 0; i < a.size(); ++i)
    {
        if (a[i] != b[i])
        {
            if (++differences > 1)
                return false;
            result[i] = '-';
        }
    }
    return differences == 1;
}

std::vector<std::string> minimizeKMap(int numInputs, const std::vector<int> &minterms)
{
    int numCells = pow(2, numInputs);
    std::vector<std::string> kmap(numCells);

    for (int i = 0; i < numCells; ++i)
    {
        kmap[i] = "0";
    }
    for (int minterm : minterms)
    {
        kmap[minterm] = "1";
    }

    std::map<int, std::vector<std::string>> groups;
    for (int minterm : minterms)
    {
        std::string binary = toBinary(minterm, numInputs);
        groups[countOnes(binary)].push_back(binary);
    }

    std::set<std::string> primeImplicants;
    bool updated;

    do
    {
        updated = false;
        std::map<int, std::vector<std::string>> newGroups;
        std::set<std::string> combined;

        for (auto it = groups.begin(); it != prev(groups.end()); ++it)
        {
            const auto &group1 = it->second;
            const auto &group2 = next(it)->second;
            for (const auto &a : group1)
            {
                for (const auto &b : group2)
                {
                    std::string result;
                    if (combine(a, b, result))
                    {
                        newGroups[countOnes(result)].push_back(result);
                        combined.insert(a);
                        combined.insert(b);
                        updated = true;
                    }
                }
            }
        }

        for (const auto &group : groups)
        {
            for (const auto &minterm : group.second)
            {
                if (combined.find(minterm) == combined.end())
                {
                    primeImplicants.insert(minterm);
                }
            }
        }
        groups = std::move(newGroups);
    } while (updated);

    for (const auto &group : groups)
    {
        primeImplicants.insert(group.second.begin(), group.second.end());
    }

    return std::vector<std::string>(primeImplicants.begin(), primeImplicants.end());
}

std::string formatImplicant(const std::string &implicant, int numInputs)
{
    std::string result;
    for (int i = 0; i < numInputs; ++i)
    {
        char var = 'A' + i;
        if (implicant[i] == '1')
        {
            result += var;
        }
        else if (implicant[i] == '0')
        {
            result += var;
            result += "'";
        }
    }
    return result;
}