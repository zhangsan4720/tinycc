#include <iostream>
#include "TokenAnaly.h"
#include <fstream>
using namespace std;
int main()
{
    TokenAnaly tokenAnaly;
    //读取文件
    ifstream binaryTableFile("symboltable.txt", ios::binary);
    ifstream binaryCodeFile("code.txt", ios::binary);
    if (binaryTableFile.is_open() && binaryCodeFile.is_open())
    {
        //获取符号表数据
        binaryTableFile.seekg(0, ios::end);
        size_t fileSize = (size_t)binaryTableFile.tellg();
        binaryTableFile.seekg(0, ios::beg);
        char *tableBuffer = new char[fileSize + 1];
        tableBuffer[fileSize] = 0;
        binaryTableFile.read(tableBuffer, fileSize);
        //构建指令符号表
        tokenAnaly.construct_symbol_command_table(tableBuffer,fileSize,9,6);
        //获取代码
        binaryCodeFile.seekg(0, ios::end);
        fileSize = (size_t)binaryCodeFile.tellg();
        binaryCodeFile.seekg(0, ios::beg);
        char *codeBuffer = new char[fileSize + 1];
        codeBuffer[fileSize] = 0;
        binaryCodeFile.read(codeBuffer, fileSize);
        //词法分析
        tokenAnaly.analy(codeBuffer,fileSize);
    }
    return 0;
}