//
// Created by Walker on 2023/10/30.
//
#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>          // atof   ���ַ���ת��Ϊ������
#include <sstream>
#include <regex>            //������ʽ
#include <bitset>
#include "Calculator.h"

double NaN = nan("NaN");

bool Calculator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == 'z' || c == 'y' || c == 'x' || c == 'w' || c == 'v' ||
           c == 'u' || c == 't' || c == 's' || c == 'r';
}

int Calculator::precedence(char c) {
    if (c == 'z' || c == 'y' || c == 'x' || c == 'w' || c == 'v' || c == 'u' || c == 't' || c == 's' || c == 'r')
        return 3;
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;                               //�˳����ȼ�����
    }
    return 0;
}

int Calculator::getnums() {
    int input;
    if (scanf("%d", &input) != 1) {
        printf("%s\n", "Invalid input, please re-enter.\n");
        while (getchar() != '\n');              // ������뻺����
        return getnums();                       // �ݹ�����������»�ȡ����
    }
    return input;
}

string Calculator::getstr() {
//    cout<<"begin"<<endl;                       //��Ҫ����
    string str;
    getline(cin, str);
//    cout << "���ǵõ����ַ���:" << str << endl;      //��Ҫ����
//    cout<<"������Valid�ķ���ֵ"<<endl;            //��Ҫ����
//    cout<<Valid(str)<<endl;                    //��Ҫ����
    if (!Valid(str)) {
        cout << "Invalid characters, please re-enter.\n" << endl;
//        cout<<2<<endl;                         //��Ҫ����
        return getstr();                         // �ݹ�����������»�ȡ����
    }
//    cout<<"end"<<endl;                         //��Ҫ����
    return str;
}

bool Calculator::Valid(const string &exp) {
    // ���ַ������ǺϷ����룬ֱ�ӷ��� false
    if (exp.empty()) {
        return false;
    }
    bool Valid = true;
//      �ж��ַ��Ƿ���
//      �����ַ�����
    char charArray[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '*', '/', '(', ')', '.', ' ', 's',
                        'i', 'n', 'c', 'o', 'a', 't', 'l', 'q', 'r', 'g'};
    // ����һ��λ���������ڴ洢�ַ������е��ַ�
    bitset<256> charVector;
    // ����λ�����е�λ����ʾ�ַ������е��ַ�����
    for (char c: charArray) { charVector.set(static_cast<unsigned char>(c)); }
    // �����ַ����е�ÿ���ַ��������λ�����е���Ӧλ
    for (char c: exp) {
        if (!charVector.test(static_cast<unsigned char>(c))) {
            Valid = false;
            break;
        }

    }
    return Valid;
}


string Calculator::format(const string &ori_infix) {
    string ori_infix_0 = ori_infix;
    // ȥ���ո�
    regex reg_0("\\s+");                // ƥ��һ�����������Ŀո�
    ori_infix_0 = regex_replace(ori_infix_0, reg_0, "");

    // �����滻�߼�
    string Funcs[9] = {"sin", "cos", "tan", "asin", "acos", "atan", "ln", "lg", "sqrt"};
    char Replacements[9] = {'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r'};
    for (size_t i = 0; i < 9; i++) {
        string temp = Funcs[i];
        regex regex(temp);
        ori_infix_0 = regex_replace(ori_infix_0, regex, string(1, Replacements[i]));
    }

//    �����Ĵ���
    if (ori_infix_0[0] == '-') { ori_infix_0 = ori_infix_0.insert(0, 1, '0'); }//������λ�Ǹ���
    regex reg("\\((-[0-9]+([.][0-9]+)?)");                  //���������ź��Ǹ���
    string ori_infix_1 = regex_replace(ori_infix_0, reg, "((0$1)");
    string infix = ori_infix_1;

    return infix;   //�ȴ�����ʵ��
}

string Calculator::Postfix(const string &ori_infix) {
    string infix = format(ori_infix);
    stack<char> s;                  // ������ջ
    string postfix;                 // ��׺���ʽ���
    for (char c: infix) {
        if (isdigit(c) || c == '.') {                  // ��ȡ��ĸ������
            postfix += c;
            continue;
        }
        postfix += ' ';                                // ��ӿո���ں��ڼ���
        if (isOperator(c)) {
            // ջ�ǿն���ջ�����������ȼ��ߣ����ж�ջ�Ƿ�գ����򲻴���ջ����
            while (!s.empty() && s.top() != '(' && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
                postfix += ' ';                         // ��ӿո���ں��ڼ���
            }
            s.push(c);

        } else if (c == '(') {                          // ������ֱ��ѹ��ջ��
            s.push(c);
//            flag2 = -1;
        } else if (c == ')') {                          // ��ȡ�м����в�����
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
                postfix += ' ';                         // ��ӿո���ں��ڼ���
            }
            if (!s.empty()) s.pop();                    // ����������
        }
    }
    postfix += ' ';                                     // ��ӿո���ں��ڼ���
    // ����ʣ�����ȼ��͵Ĳ�����
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
        if (!s.empty()) {                               // ����ջ�л���Ԫ�ص�ʱ����ӿո�
            postfix += ' ';
        }
    }
    return postfix;
}

double Calculator::calPostfix(const string &postfix) {
    istringstream input(postfix);                   //ʹ����������ȡ��׺���ʽ�������ַ�
    stack<double> s;
    string token;
    while (input >> token) {                            //����������ȡ�ַ�
        if (isOperator(token[0])) {//�ж϶�ȡ��������ַ��Ƿ�Ϊ������
            if (s.empty()) return NaN;
            double opn2 = s.top();
            s.pop();
            if (token == "+") {
                if (s.empty()) return NaN;
                double opn1 = s.top();
                s.pop();
                s.push(opn1 + opn2);
            } else if (token == "-") {
                if (s.empty()) return NaN;
                double opn1 = s.top();
                s.pop();
                s.push(opn1 - opn2);
            } else if (token == "*") {
                if (s.empty()) return NaN;
                double opn1 = s.top();
                s.pop();
                s.push(opn1 * opn2);
            } else if (token == "/") {
                if (s.empty()) return NaN;
                double opn1 = s.top();
                s.pop();
                s.push(opn1 / opn2);
            } else if (token == "z") {
                s.push(sin(opn2));
            } else if (token == "y") {
                s.push(cos(opn2));
            } else if (token == "x") {
                s.push(tan(opn2));
            } else if (token == "w") {
                s.push(asin(opn2));
            } else if (token == "v") {
                s.push(acos(opn2));
            } else if (token == "u") {
                s.push(atan(opn2));
            } else if (token == "t") {
                s.push(log(opn2));
            } else if (token == "s") {
                s.push(log10(opn2));
            } else if (token == "r") {
                s.push(sqrt(opn2));
            }
        } else {
            s.push(atof(token.c_str()));         //���ַ���ת��Ϊ����������ѹ��ջ�С�
        }
    }
    return s.top();
}

void Calculator::menu1() {

//    string exp;
    cout << "֧���������ͣ�������������С��\n��ʱ֧�ֶ�Ԫ������+-*/,\n"
            "��ʱ֧�ֵ�Ԫ������{\"sin\", \"cos\", \"tan\", \"asin\", \"acos\", \"atan\", \"ln\", \"lg\", \"sqrt\"}\n"
            "��Ԫ��������Ҫ��op()�ĸ�ʽ���룬����sin(1),��������sin1.(���Ǻ����Ի���������)\n"
            "��������֧�ַǷ��ַ���⣬�ո��Զ�ɾ��\n";
    cout << "������׺���ʽ: " << endl;
    cin.ignore();                                           // ��Ӵ�����������з�!!!!�ǳ���Ҫ���������ʿ�ָ�롣
    string exp = getstr();
    clock_t time_0 = clock();
    string postfixexp = Postfix(exp);
    clock_t time_1 = clock();
    cout << "��׺���ʽ��֧�ֵĵ�Ԫ��������ں�׺���ʽ�д���������ӳ���ϵ:\n"
            "{\"sin\t\", \"cos\t\", \"tan\t\", \"asin\", \"acos\", \"atan\", \"ln\t\", \"lg\t\", \"sqrt\"}\n"
            "{'z\t', 'y\t', 'x\t', 'w\t', 'v\t', 'u\t', 't\t', 's\t', 'r\t'}\n"
            "��׺���ʽ��: " << postfixexp << endl;
    system("pause");  //����

    clock_t time_2 = clock();
    double result = calPostfix(postfixexp);
    clock_t time_3 = clock();
    if (isnan(result))
        cout << "Input format error.\n";
    else {
        cout << "��������: " << result << endl;
        cout << "ת����׺���ʽ����ʱ��Ϊ: " << (double) (time_1 - time_0) / CLOCKS_PER_SEC << "\n��׺���ʽ���㻨��ʱ��Ϊ:"
             << (double) (time_3 - time_2) / CLOCKS_PER_SEC << "\n\n\n";
    }
    system("pause");
}

void Calculator::menu() {
    setbuf(stdout, NULL);
    int flag = 1;
    while (flag) {
        cout << "��ӭʹ�������ª�ļ�����!\n����Ӣ���ַ�����";
        cout << "�����ѡ��\n0.�˳�\n1.����������\n";
        cout << "���ѡ����(֧�ִ�����Ƿ����봦��):\n";
        int choice = getnums();
        switch (choice) {
            case 0 :
                flag = 0;
                cout << "��лʹ��.\n���˳�..." << endl;
                system("pause");
                break;
            case 1:
                menu1();
                break;
            default:
                cout << "Function not available.\n" << endl;
                break;
        }
    }

}