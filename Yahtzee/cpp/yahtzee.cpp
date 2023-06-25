#include "yahtzee.hpp"
#include <string.h>
#include <numeric>
#include <vector>
#include <functional>
#include <algorithm>
#include <map>

namespace
{
    using func = std::function<int(int, int)>;
    const func allOnes = [](int a, int b) -> int
    { return b == 1 ? a + b : a; };
    const func allTwos = [](int a, int b) -> int
    { return b == 2 ? a + b : a; };
    const func allThrees = [](int a, int b) -> int
    { return b == 3 ? a + b : a; };
    const func allFours = [](int a, int b) -> int
    { return b == 4 ? a + b : a; };
    const func allFives = [](int a, int b) -> int
    { return b == 5 ? a + b : a; };
    const func allSixes = [](int a, int b) -> int
    { return b == 6 ? a + b : a; };

    const std::map<int, func> mapping = {
        {1, allOnes},
        {2, allTwos},
        {3, allThrees},
        {4, allFours},
        {5, allSixes}};

};

int Yahtzee::Chance(int d1, int d2, int d3, int d4, int d5)
{
    return d1 + d2 + d3 + d4 + d5;
}

int Yahtzee::yahtzee(int dice[])
{
    for (int i = 1; i < 5; i++)
    {
        if (dice[0] != dice[i])
        {
            return 0;
        }
    }

    return 50;
}

int Yahtzee::Ones(int d1, int d2, int d3, int d4, int d5)
{
    std::vector<int> vec = {d1, d2, d3, d4, d5};
    return std::accumulate(vec.begin(), vec.end(), 0, allOnes);
}

int Yahtzee::Twos(int d1, int d2, int d3, int d4, int d5)
{
    std::vector<int> vec = {d1, d2, d3, d4, d5};
    return std::accumulate(vec.begin(), vec.end(), 0, allTwos);
}

int Yahtzee::Threes(int d1, int d2, int d3, int d4, int d5)
{
    std::vector<int> vec = {d1, d2, d3, d4, d5};
    return std::accumulate(vec.begin(), vec.end(), 0, allThrees);
}

Yahtzee::Yahtzee()
{
}

Yahtzee::Yahtzee(int d1, int d2, int d3, int d4, int _5)
{
    dice = new int[5];
    dice[0] = d1;
    dice[1] = d2;
    dice[2] = d3;
    dice[3] = d4;
    dice[4] = _5;
}

int Yahtzee::Fours()
{
    return std::accumulate(dice, dice + 5, 0, allFours);
}

int Yahtzee::Fives()
{
    return std::accumulate(dice, dice + 5, 0, allFives);
}

int Yahtzee::sixes()
{
    return std::accumulate(dice, dice + 5, 0, allSixes);
}

int Yahtzee::ScorePair(int d1, int d2, int d3, int d4, int d5)
{
    std::vector<int> vec = {d1, d2, d3, d4, d5};
    
    int max = 0;
    for(int i = 1; i < 7; i++) {
        auto count = std::count(vec.begin(), vec.end(), i);
        
        if(count == 2 && i > max) {
            max = i;
        }
    }

    return max*2;
}

int Yahtzee::TwoPair(int d1, int d2, int d3, int d4, int d5)
{
    std::vector<int> vec = {d1, d2, d3, d4, d5};
    int n = 0;
    int result = 0;
    for(int i = 1; i < 7; i++) {
        auto count = std::count(vec.begin(), vec.end(), i);
        if(count == 2) {
            n++;
            result += 2*i;
        }
    }    

    return n == 2 ? result : 0;
}

int Yahtzee::FourOfAKind(int _1, int _2, int d3, int d4, int d5)
{
    std::vector<int> vec = {_1, _2, d3, d4, d5};
    for(int i = 1; i < 7; i++) {
        auto count = std::count(vec.begin(), vec.end(), i);
        if(count == 4) {
            return 4*i;
        }
    }    
    return 0;
}

int Yahtzee::ThreeOfAKind(int d1, int d2, int d3, int d4, int d5)
{
    std::vector<int> vec = {d1, d2, d3, d4, d5};
    for(int i = 1; i < 7; i++) {
        auto count = std::count(vec.begin(), vec.end(), i);
        if(count == 3) {
            return 3*i;
        }
    }    
    return 0;
}

int Yahtzee::SmallStraight(int d1, int d2, int d3, int d4, int d5)
{
    std::vector<int> vec = {d1, d2, d3, d4, d5};
    auto sum = std::accumulate(vec.begin(), vec.end(), 0);
    return sum == 15 ? 15 : 0;  
}

int Yahtzee::LargeStraight(int d1, int d2, int d3, int d4, int d5)
{
    std::vector<int> vec = {d1, d2, d3, d4, d5};
    auto sum = std::accumulate(vec.begin(), vec.end(), 0);
    return sum == 20 ? 20 : 0;  
}

int Yahtzee::FullHouse(int d1, int d2, int d3, int d4, int d5)
{
    int result = 0;
    int num = 0;
    std::vector<int> vec = {d1, d2, d3, d4, d5};
    for(int i = 1; i < 7; i++) {
        auto count = std::count(vec.begin(), vec.end(), i);
        if(count == 2) {
            num += count;
            result += 2*i;
        }
        if(count == 3) {
            num += count;
            result += 3*i;
        }
    }    
    return num == 5 ? result : 0;
}
