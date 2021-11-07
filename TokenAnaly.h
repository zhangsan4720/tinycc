#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>

using namespace std;
class TokenAnaly
{
    char m_SymbolMap[256];
    size_t m_Height = 0, m_Width = 0;
    vector<string> m_SymbolCommands;
    void create_symbol_map(vector<pair<function<bool(char)>, int>> conditions);
    //指令
    int state = 0;
    size_t start = 0, end = 0;
public:
    TokenAnaly();
    void construct_symbol_command_table(const char *tableBuffer, const size_t bufferSize, size_t height, size_t width);
    vector<string> analy(char * codeBuffer,const size_t codeSize);
    ~TokenAnaly(){}
};