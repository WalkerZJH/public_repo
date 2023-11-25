//
// Created by Walker on 2023/10/30.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <stack>
#include <string>

using namespace std;

// ��������
class Calculator {
public:
    int Calculator::getnums();                      //��ȡ�Ϸ�����
    bool Valid(const string &exp);                  //�����ж�getstr�ĺ�׺���ʽ�Ƿ�Ϸ�(Ŀǰ��ʵ���жϷǷ��ַ�)
    string getstr();                                //��ȡһ���ַ���
    bool isOperator(char c);                        //�ж��Ƿ��������������ת����׺���ʽ����Ҫ�߼�
    int precedence(char c);                         //�������ȼ�
    string format(const std::string &infix);        //��ʽ���ַ��������ո�ɾ������������Ӹ��ţ��滻��Ԫ����
    string Postfix(const std::string &infix);       //ת��Ϊ��׺���ʽ
    double calPostfix(const std::string &postfix);  //�����׺���ʽ
    void menu();                                    //���˵�
    void menu1();                                   //�����������˵�
private:
};

#endif //CALCULATOR_CALCULATOR_H
