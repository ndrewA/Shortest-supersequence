#include "BST.h"

#include <unordered_set>
#include <unordered_map>

void printVec(std::vector<std::queue<size_t>> v)
{
    for(auto i :v)
    {
        while(!i.empty())
        {
            std::cout << i.front() << ' ';
            i.pop();
        }
        std::cout << '\n';
    }
    std::cout << "==========\n";
}

std::pair<size_t, size_t> findSeq(const std::vector<int>& allSequence, const std::vector<int>& allNumbers)
{
    const std::unordered_set<int> setNumbers(allNumbers.begin(), allNumbers.end());

    std::unordered_map<int, size_t> indexMap;
    for(size_t i = 0; i < allNumbers.size(); i++)
        indexMap.insert({allNumbers[i], i});

    std::vector<std::queue<size_t>> numberIndexes(allNumbers.size());

    size_t cnt = 0;

    for(size_t i = 0; i < allSequence.size(); i++) {
        if(setNumbers.find(allSequence[i]) != setNumbers.end()) {
            numberIndexes[indexMap[allSequence[i]]].push(i);
        } else ++cnt;
    }
    if(cnt <= allNumbers.size()) return {0, 0};

    BST tree(numberIndexes);
    std::pair<size_t, size_t> curSequence = {0, INT_MAX};

    while(true)
    {
        size_t curLen = tree.getBiggest()-tree.getSmallest();
        if(curLen < curSequence.second - curSequence.first)
            curSequence = {tree.getSmallest(), tree.getBiggest()};

        if(curLen == allNumbers.size()-1) return curSequence;

        size_t index = tree.removeSmallest();

        numberIndexes[index].pop();

        tree.addNumber(numberIndexes[index].front(), index);

        if(numberIndexes[index].empty()) break;
    }

    return curSequence;
}

int main()
{
    auto res = findSeq({7, 5, 9, 13, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7, 1, 5, 9}, {1, 2, 5});
    std::cout << "==========\n" << res.first << ' ' << res.second << '\n';
    return 0;
}
