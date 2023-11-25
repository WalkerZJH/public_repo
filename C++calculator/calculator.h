//
// Created by Walker on 2023/10/30.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <stack>
#include <string>

using namespace std;

// 计算器类
class Calculator {
public:
    int Calculator::getnums();                      //获取合法数字
    bool Valid(const string &exp);                  //用于判断getstr的后缀表达式是否合法(目前仅实现判断非法字符)
    string getstr();                                //获取一个字符串
    bool isOperator(char c);                        //判断是否是运算符，用于转换后缀表达式的重要逻辑
    int precedence(char c);                         //定义优先级
    string format(const std::string &infix);        //格式化字符串，将空格删除，将负数添加负号，替换单元函数
    string Postfix(const std::string &infix);       //转换为后缀表达式
    double calPostfix(const std::string &postfix);  //计算后缀表达式
    void menu();                                    //主菜单
    void menu1();                                   //基础计算器菜单
private:
};

#endif //CALCULATOR_CALCULATOR_H
