/**
 * @file main.cpp
 * @brief 程序入口
 * @author srAm-dev
 * @version 0.1
 * @date 2025-12-12
 * @copyright Copyright (c) 2025 srAm-dev
 * SPDX-License-Identifier: WTFPL
 * Licensed under the WTFPL.
 */
#include <iostream>
#include <fstream>
#include "Parser.hpp"

/**
 * @brief 程序入口
 *
 * 该函数是语法分析器的主入口,
 * 接受命令行参数作为输入和输出文件路径,
 * 创建Parser对象并执行语法分析,
 * 最后将规约步骤输出到指定文件。
 *
 * @param argc 命令行参数数量
 * @param argv 命令行参数数组,第一个参数为输入文件路径(<input_file>)，第二个参数为输出文件路径(<output_file>)
 * @return int 返回程序执行状态码
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    Parser parser(argv[1]);
    if (parser.parse()) parser.printReduceStack(argv[2]);
    return 0;
}