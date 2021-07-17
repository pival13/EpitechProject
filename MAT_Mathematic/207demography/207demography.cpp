/*
** EPITECH PROJECT, 2020
** 207demography_2019 [WSL: Ubuntu]
** File description:
** 207demography
*/

#include <algorithm>
#include <map>
#include <list>
#include <deque>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

map<size_t,double> getValues(list<string> &coutryCode)
{
    map<size_t,double> values;
    deque<size_t> years;
    ifstream f("./207demography_data.csv");
    if (!f.is_open())
        return values;
    string s;
    getline(f, s);
    if (s.length()) {
        s = s.substr(s.find(';')+1);
        s = s.substr(s.find(';')+1);
        while (s.find(';') != s.npos) {
            years.push_back(stoul(s));
            s = s.substr(s.find(';')+1);
        }
        years.push_back(stoul(s));
    }

    list<string> countrys;
    while (!f.eof() && !coutryCode.empty()) {
        getline(f, s);
        if (!s.length())
            break;
        if (count(s.begin(), s.end(), ';') != years.size()+1) {
            std::cerr << "invalid number of values" << std::endl;
            return map<size_t,double>(); }
        
        string name = s.substr(0,s.find(';'));
        s = s.substr(s.find(';')+1);
        if (count(coutryCode.begin(), coutryCode.end(), s.substr(0,s.find(';')))) {
            countrys.push_back(name);
            coutryCode.remove(s.substr(0,s.find(';')));
        
            s = s.substr(s.find(';')+1);
            for (int i = 0; s.find(';') != s.npos; i++) {
                values[years[i]] += double(stoul(s)) / 1000000;
                s = s.substr(s.find(';')+1);
            }
            values[years.back()] += double(stoul(s)) / 1000000;
        }
    }
    if (!coutryCode.empty()) {
        std::cerr << "Unknow country '" << coutryCode.front() << "'" << std::endl; return map<size_t,double>(); }
    f.close();
    countrys.sort();
    std::cout << "Country: ";
    for (auto c : countrys)
        if (c == countrys.front()) std::cout << c;
        else std::cout << ", " << c;
    std::cout << std::endl;
    return values;
}

void linearEquation(const map<size_t,double> &values)
{
    double aX, bX, aY, bY = 0;
    double Ex, Ey, Exy, Ex2, Ey2 = 0;
    double Sy, Sx, Sxy = 0;

    for (auto p : values) {
        Ex += p.first;
        Ey += p.second;
        Ex2 += p.first * p.first;
        Ey2 += p.second * p.second;
        Exy += p.first * p.second;
    }

    aX = ((values.size() * Exy) - (Ex*Ey)) / ((values.size()*Ex2) - (Ex*Ex));
    bX = ((Ey*Ex2) - (Ex*Exy)) / ((values.size()*Ex2) - (Ex*Ex));
    aY = ((values.size() * Exy) - (Ex*Ey)) / ((values.size()*Ey2) - (Ey*Ey));
    bY = ((Ex*Ey2) - (Ey*Exy)) / ((values.size()*Ey2) - (Ey*Ey));
    
    for (auto p: values) {
        Sx += pow(p.second - (aX*p.first + bX), 2);
        Sy += pow(p.second - (p.first - bY)/aY, 2);
        Sxy += (p.second - (aX*p.first + bX)) * (p.second - (p.first - bY)/aY);
    }
    Sx = sqrt(Sx/values.size());
    Sy = sqrt(Sy/values.size());
    Sxy /= values.size();
    printf("Fit1\n");
    printf("    Y = %.2f X %c %.2f\n", aX, (bX < 0? '-': '+'), abs(bX));
    printf("    Root-mean-square deviation: %.02f\n", Sx);
    printf("    Population in 2050: %.02f\n", aX*2050+bX);
    printf("Fit2\n");
    printf("    X = %.2f Y %c %.2f\n", aY, (bY < 0? '-': '+'), abs(bY));
    printf("    Root-mean-square deviation: %.02f\n", Sy);
    printf("    Population in 2050: %.02f\n", (2050-bY)/aY);
    printf("Correlation: %.4f\n", Sxy/(Sx*Sy));
}

int main(int n, char **arg)
{
    if (n < 2)
        return 84;
    
    list<string> code;
    for (size_t i = 1; i != n; i++)
        code.push_back(arg[i]);
    map<size_t,double> values = getValues(code);
    if (values.size() == 0)
        return 84;
    linearEquation(values);
    return 0;
}