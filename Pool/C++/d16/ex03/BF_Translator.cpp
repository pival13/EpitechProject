/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** BF_Translator
*/

#include "BF_Translator.hpp"

BF_Translator::BF_Translator() : bfChar()
{
    bfChar['+'] = "++*ptr;";
    bfChar['-'] = "--*ptr;";
    bfChar['>'] = "++ptr;";
    bfChar['<'] = "--ptr;";
    bfChar['.'] = "putchar(*ptr);";
    bfChar[','] = "*ptr=getchar();";
    bfChar['['] = "while(*ptr){";
    bfChar[']'] = "}";
    bfChar[' '] = "";
    bfChar['\r'] = "";
    bfChar['\n'] = "";
    bfChar['\t'] = "";
}

BF_Translator::~BF_Translator()
{
}

int BF_Translator::translate(const std::string &inname, const std::string &outname)
{
    std::ifstream in(inname);
    std::ofstream out(outname);

    if (!in.is_open() || !out.is_open())
        return 1;

    std::string str;
    std::getline(in, str, '\0');
    in.close();
    for (char c : str)
        if (!bfChar.count(c)) {
            out.close();
            return 1;
        }
    
    out << "#include<stdio.h>\nint main(){char array[30000]={0};char *ptr=array;";
    for (char c : str)
        out << bfChar[c];
    out << "}";

    out.close();
    return 0;
}