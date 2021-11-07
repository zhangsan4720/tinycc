#include"TokenAnaly.h"
#include <iostream>

TokenAnaly::TokenAnaly()
{
    create_symbol_map({
        {[](char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }, 0},
        {[](char c) { return c >= '0' && c <= '9'; },                             1},
        {[](char c) { return c == '.'; },                                         2},
        {[](char c) { return c == '+'; },                                         3},
        {[](char c) { return c == '-'; },                                         4},
        {[](char c) { return c == ' ' || c== '\n' || c=='\r'||c == 0; },          5},
    });
}

void TokenAnaly::create_symbol_map(vector<pair<function<bool(char)>, int>> conditions)
{
    memset((void *)m_SymbolMap, 0xff, 256);
    for (size_t i = 0; i < conditions.size(); i++)
    {
        for (int j = 0; j < 256; j++)
        {
            if (conditions[i].first((char)j))
            {
                m_SymbolMap[j] = conditions[i].second;
            }
        }
    }
}

void TokenAnaly::construct_symbol_command_table(const char * tableBuffer,const size_t bufferSize,size_t height, size_t width)
{
    m_Height = height;
    m_Width = width;
    size_t i = 0;
    while (i < bufferSize)
    {
        string command;
        if (!(tableBuffer[i] == ' ' || tableBuffer[i] == '\n'|| tableBuffer[i] == '\r'|| tableBuffer[i] == '\t'))
        {
            while (!(tableBuffer[i] == ' ' || tableBuffer[i] == '\n'|| tableBuffer[i] == '\r'|| tableBuffer[i] == '\t'))
            {
                command += tableBuffer[i++];
            }
            m_SymbolCommands.push_back(command);
        }
        else
        {
            i++;
        }
    }
}

vector<string> TokenAnaly::analy(char * codeBuffer,const size_t codeSize)
{
    vector<string> result;
    //分析代码
    auto jump = [&](int nextState){ state = nextState; };
    auto next = [&](){ end++; };
    auto save = [&]()
    {
        string word;
        char tempChar = 0;
        swap(tempChar, codeBuffer[end]);
        word.insert(0, &codeBuffer[start]);
        swap(tempChar, codeBuffer[end]);
        start = end;
        if(state != 8)
        {
            cout << word << endl;
            result.push_back(word);
        }
    };
    while (end < codeSize + 1)
    {
        if (m_SymbolMap[codeBuffer[end]] == -1)
        {
            cout << "unknow symbol" << endl;
            end++;
            continue;
        }
        string command = m_SymbolCommands[state * m_Width + m_SymbolMap[codeBuffer[end]]];
        size_t k = 0;
        while (k < command.size())
        {
            if (command[k] == 'j')
            {
                k++;
                string num;
                while (command[k] >= '0' && command[k] <= '9')
                {
                    num += command[k++];
                }
                jump(atoi(num.c_str())); //状态跳转
            }
            else if (command[k] == 'n')
            {
                k++;
                next(); //下一个字符
            }
            else if (command[k] == 's')
            {
                k++;
                save(); //获取单词
            }
        }
    }
    return result;
}