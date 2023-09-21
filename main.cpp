#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>

// 多项式结构体
struct PolyTerm {
    double coefficient; // 系数
    int exponent;      // 指数
    PolyTerm* next; // 指向下一个多项式项的指针

    // 构造函数
    PolyTerm(double coef, int exp) : coefficient(coef), exponent(exp), next(nullptr) {}
};

// 历史记录项的结构体
struct HistoryItem {
    std::string operation;  // 计算操作
    std::string polynomial1; // 第一个多项式
    std::string polynomial2; // 第二个多项式
    std::string result;     // 计算结果

    HistoryItem(const std::string& op, const std::string& poly1, const std::string& poly2, const std::string& res)
            : operation(op), polynomial1(poly1), polynomial2(poly2), result(res) {}
};

// 创建五个不同的历史记录列表，分别对应五个不同的计算项目
std::vector<HistoryItem> addHistory;
std::vector<HistoryItem> subHistory;
std::vector<HistoryItem> xValueHistory;
std::vector<HistoryItem> derivativeHistory;
std::vector<HistoryItem> multiplyHistory;

// 多项式类，包含一个指向多项式首项的指针
class Polynomial {
private:
    PolyTerm* head; // 多项式首项的指针
    std::vector<HistoryItem> history; // 历史记录

public:
    // 构造函数
    Polynomial() : head(nullptr) {}

    // 添加多项式项
    void addTerm(double coef, int exp) {
        auto newTerm = new PolyTerm(coef, exp);
        if (!head) {
            head = newTerm;
        } else {
            // 遍历链表找到最后一项，并将新项连接到最后一项的后面
            PolyTerm* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newTerm;
        }
    }

    // 输出多项式
    void print() {
        PolyTerm* current = head;
        bool isFirstTerm = true;

        while (current) {
            if (current->coefficient != 0) {
                if (!isFirstTerm) {
                    if (current->coefficient > 0) {
                        std::cout << " + ";
                    } else {
                        std::cout << " - ";
                    }
                } else {
                    isFirstTerm = false;
                }

                // 输出系数（如果不是1或是常数项）
                if (current->exponent == 0 || (current->exponent != 0 && std::abs(current->coefficient) != 1)) {
                    std::cout << std::abs(current->coefficient);
                }

                // 输出指数
                if (current->exponent > 0) {
                    std::cout << "x";
                    if (current->exponent != 1) {
                        std::cout << "^" << current->exponent;
                    }
                }
            }
            current = current->next;
        }

        // 多项式为0的情况
        if (isFirstTerm) {
            std::cout << "0";
        }

        std::cout << std::endl;
    }

    // 将多项式对象转换为字符串
    std::string toString() const {
        std::ostringstream oss; // 创建一个输出字符串流，用于构建多项式的字符串表示
        PolyTerm* current = head; // 从多项式的头部开始遍历
        bool isFirstTerm = true; // 用于标记是否是第一个项

        while (current) {
            double coef = current->coefficient; // 获取当前项的系数
            int exp = current->exponent; // 获取当前项的指数

            if (coef != 0) { // 如果系数不为零
                if (!isFirstTerm) {
                    if (coef > 0) {
                        oss << " + "; // 如果不是第一个项且系数为正数，添加加号
                    } else {
                        oss << " - "; // 如果不是第一个项且系数为负数，添加减号
                    }
                } else {
                    isFirstTerm = false; // 如果是第一个项，将 isFirstTerm 设置为 false
                }

                if (std::abs(coef) != 1 || exp == 0) {
                    oss << std::fixed << std::setprecision(2) << std::abs(coef); // 设置输出精度并添加系数的绝对值
                }

                if (exp > 0) {
                    oss << "x"; // 如果指数大于0，添加变量 x
                    if (exp != 1) {
                        oss << "^" << exp; // 如果指数不等于1，添加指数部分
                    }
                }
            }
            current = current->next; // 移动到下一个项
        }

        return oss.str(); // 将构建的字符串从字符串流中提取并返回
    }

    // 多项式加法 运算符重载
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result; // 创建一个用于存储结果的多项式对象

        PolyTerm* current1 = head; // 创建指向当前对象的第一个多项式项的指针
        PolyTerm* current2 = other.head; // 创建指向第二个多项式对象的第一个多项式项的指针

        while (current1 || current2) { // 循环直到两个多项式的所有项都被处理完
            double coef1 = (current1) ? current1->coefficient : 0; // 获取第一个多项式项的系数，如果当前项为空则默认为0
            double coef2 = (current2) ? current2->coefficient : 0; // 获取第二个多项式项的系数，如果当前项为空则默认为0
            int exp1 = (current1) ? current1->exponent : 0; // 获取第一个多项式项的指数，如果当前项为空则默认为0
            int exp2 = (current2) ? current2->exponent : 0; // 获取第二个多项式项的指数，如果当前项为空则默认为0

            if (exp1 > exp2) { // 如果第一个多项式项的指数大于第二个多项式项的指数
                result.addTerm(coef1, exp1); // 将第一个多项式项添加到结果多项式中
                current1 = (current1) ? current1->next : nullptr; // 移动到第一个多项式的下一个项，如果没有下一个项则将指针设置为nullptr
            } else if (exp1 < exp2) { // 如果第一个多项式项的指数小于第二个多项式项的指数
                result.addTerm(coef2, exp2); // 将第二个多项式项添加到结果多项式中
                current2 = (current2) ? current2->next : nullptr; // 移动到第二个多项式的下一个项，如果没有下一个项则将指针设置为nullptr
            } else { // 如果两个多项式项的指数相等
                result.addTerm(coef1 + coef2, exp1); // 将它们的系数相加后添加到结果多项式中
                current1 = (current1) ? current1->next : nullptr; // 移动到第一个多项式的下一个项
                current2 = (current2) ? current2->next : nullptr; // 移动到第二个多项式的下一个项
            }
        }

        return result; // 返回包含相加结果的多项式对象
    }

    //多项式减法
    Polynomial operator-(const Polynomial& other) const {
        Polynomial result;
        PolyTerm* current1 = head;
        PolyTerm* current2 = other.head;

        while (current1 || current2) {
            double coef1 = (current1) ? current1->coefficient : 0;
            double coef2 = (current2) ? current2->coefficient : 0;
            int exp1 = (current1) ? current1->exponent : 0;
            int exp2 = (current2) ? current2->exponent : 0;

            if (exp1 > exp2) {
                result.addTerm(coef1, exp1);
                current1 = (current1) ? current1->next : nullptr;
            } else if (exp1 < exp2) {
                result.addTerm(-coef2, exp2); // Subtracting term
                current2 = (current2) ? current2->next : nullptr;
            } else {
                result.addTerm(coef1 - coef2, exp1);
                current1 = (current1) ? current1->next : nullptr;
                current2 = (current2) ? current2->next : nullptr;
            }
        }
        return result;
    }

    // 计算多项式在X处的值
    double evaluate(double x) const {
        double result = 0.0;
        PolyTerm* current = head;
        while (current) {
            result += current->coefficient * pow(x, current->exponent);
            current = current->next;
        }
        return result;
    }

    // 计算多项式的导函数
    Polynomial derivative() const {
        Polynomial result; // 创建一个用于存储导函数结果的多项式对象

        PolyTerm* current = head; // 创建指向当前多项式对象的第一个多项式项的指针

        while (current) { // 遍历多项式的每一项
            double coef = current->coefficient * current->exponent; // 计算导函数项的系数，即原系数乘以指数
            int exp = (current->exponent > 0) ? current->exponent - 1 : 0; // 计算导函数项的指数，如果原指数大于0则减1，否则为0
            result.addTerm(coef, exp); // 将导函数项添加到结果多项式中
            current = current->next; // 移动到多项式的下一个项
        }

        return result; // 返回包含导函数结果的多项式对象
    }

    // 计算多项式a和b的乘积，并返回乘积多项式ab
    Polynomial multiply(const Polynomial& other) const {
        Polynomial result; // 创建一个用于存储乘积多项式结果的多项式对象
        PolyTerm* current1 = head; // 创建指向当前多项式对象的第一个多项式项的指针

        while (current1) { // 遍历第一个多项式的每一项
            PolyTerm* current2 = other.head; // 创建指向第二个多项式对象的第一个多项式项的指针

            while (current2) { // 遍历第二个多项式的每一项
                double coef1 = current1->coefficient; // 获取第一个多项式项的系数
                double coef2 = current2->coefficient; // 获取第二个多项式项的系数
                int exp1 = current1->exponent; // 获取第一个多项式项的指数
                int exp2 = current2->exponent; // 获取第二个多项式项的指数

                double productCoef = coef1 * coef2; // 计算两个项的系数相乘，得到新的系数
                int productExp = exp1 + exp2; // 计算两个项的指数相加，得到新的指数

                // 检查结果多项式中是否已存在具有相同指数的项
                bool termExists = false;
                PolyTerm* currentResult = result.head;
                while (currentResult) {
                    if (currentResult->exponent == productExp) {
                        currentResult->coefficient += productCoef; // 如果存在，将系数相加
                        termExists = true;
                        break;
                    }
                    currentResult = currentResult->next;
                }
                // 如果结果多项式中不存在具有相同指数的项，将新的项添加到结果中
                if (!termExists) {
                    result.addTerm(productCoef, productExp);
                }
                current2 = current2->next; // 移动到第二个多项式的下一个项
            }
            current1 = current1->next; // 移动到第一个多项式的下一个项
        }
        return result; // 返回包含乘积结果的多项式对象
    }

    void createPolynomial(Polynomial& polynomial1, Polynomial& polynomial2){
        std::cout << "[Save] Enter 2 Polynomial follow the hints given by" << std::endl;
        std::cout << "[Tips] 3x^2 + 6x + 1 -> 3 3 2 6 1 1 0\n" << std::endl;
        std::cout << "[Poly1] 请输入第一个多项式的项数「3」:";
        int termCount1;
        std::cin >> termCount1;

        std::cout << "[Poly1] 请输入第一个多项式的每一项(系数 指数)「3 2 6 1 1 0」" << std::endl;
        for (int i = 0; i < termCount1; ++i) {
            double coef;
            int exp;
            std::cin >> coef >> exp;
            polynomial1.addTerm(coef, exp);
        }

        std::cout << "\n[Poly2] 请输入第二个多项式的项数「3」:";
        int termCount2;
        std::cin >> termCount2;

        std::cout << "[Poly2] 请输入第二个多项式的每一项(系数 指数)「3 2 6 1 1 0」" << std::endl;
        for (int i = 0; i < termCount2; ++i) {
            double coef;
            int exp;
            std::cin >> coef >> exp;
            polynomial2.addTerm(coef, exp);
        }

        std::cout << "\n[Save] Polynomial saved success & Review\n" << std::endl;
        std::cout << "[Save] Polynomial 1: ";
        polynomial1.print();

        std::cout << "[Save] Polynomial 2: ";
        polynomial2.print();
        std::cout << std::endl;
    }

    void addHistoryItem(const std::string& op, const std::string& poly1, const std::string& poly2, const std::string& res) {
        history.emplace_back(op, poly1, poly2, res);
    }

    void performCalculation(const Polynomial& poly1, const Polynomial& poly2, char operation) {
        Polynomial result;
        std::string opStr;
        if(operation == '+'){
            opStr = "Add";
            result = poly1 + poly2;
            std::cout << "[Result] ";
            result.print();
            addHistoryItem(opStr, poly1.toString(), poly2.toString(), result.toString());
            addHistory.emplace_back(opStr, poly1.toString(), poly2.toString(), result.toString());
        }
        else if(operation == '-'){
            opStr = "Sub";
            result = poly1 - poly2;
            std::cout << "[Result] ";
            result.print();
            addHistoryItem(opStr, poly1.toString(), poly2.toString(), result.toString());
            subHistory.emplace_back(opStr, poly1.toString(), poly2.toString(), result.toString());
        }
        else if(operation == 'x'){
            opStr = "Value at X";
            double xValue;
            std::cout << "[Input] Please enter the X value:";
            std::cin >> xValue;
            double resultValue = poly1.evaluate(xValue);
            std::cout << "[Result] Polynomial 1 at X = " << xValue << " 's value is " << resultValue << std::endl;
            history.emplace_back(opStr, poly1.toString(), " ", std::to_string(resultValue));
            xValueHistory.emplace_back(opStr, poly1.toString(), " ", std::to_string(resultValue));
            resultValue = poly2.evaluate(xValue);
            std::cout << "[Result] Polynomial 2 at X = " << xValue << " 's value is " << resultValue << std::endl;
            history.emplace_back(opStr, " ", poly2.toString(), std::to_string(resultValue));
            xValueHistory.emplace_back(opStr, " ", poly2.toString(), std::to_string(resultValue));
        }
        else if(operation == '\''){
            opStr = "Derivative";
            Polynomial derivativeResult = poly1.derivative();
            std::cout << "[Result] Polynomial 1 's Derivative Function: " << std::endl;
            derivativeResult.print();
            history.emplace_back(opStr, poly1.toString(), " ", derivativeResult.toString());
            derivativeHistory.emplace_back(opStr, poly1.toString(), " ", derivativeResult.toString());
            derivativeResult = poly2.derivative();
            std::cout << "[Result] Polynomial 2 's Derivative Function: " << std::endl;
            derivativeResult.print();
            history.emplace_back(opStr, " ", poly2.toString(), derivativeResult.toString());
            derivativeHistory.emplace_back(opStr, " ", poly2.toString(), derivativeResult.toString());
        }
        else if(operation == '*'){
            opStr = "Product";
            Polynomial productResult = poly1.multiply(poly2);
            std::cout << "[Result] The Product Polynomial of 1 & 2: " << std::endl;
            productResult.print();
            history.emplace_back(opStr, poly1.toString(), poly2.toString(), productResult.toString());
            multiplyHistory.emplace_back(opStr, poly1.toString(), poly2.toString(), productResult.toString());
        }
    }

    void displayHistory(const std::vector<HistoryItem>& history, const std::string& operation) {
        std::cout << operation << std::endl;
        std::cout << "  Operation  |          Polynomial 1            |         Polynomial 2             |              Result" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

        for (const HistoryItem& item : history) {
            std::cout << std::setw(11) << std::left << item.operation << "  |  "
                << std::setw(30) << std::left << item.polynomial1 << "  |  "
                << std::setw(30) << std::left << item.polynomial2 << "  |  "
                << std::setw(10) << std::left << item.result << std::endl;
        }
        std::cout << std::endl;
    }

    std::string modeSwitch(bool mode){
        return mode ? "[Multiple]    " : "[Simple]      ";
    }
};

int main() {
    Polynomial polynomial1, polynomial2, result, calculator;
    char operation;

    while (true) {
        std::cout << "[Polynomial Calculator] -Powered by Huang Yixuan Ver1.0\n" << std::endl;
        std::cout << "[Calculate]   1. 多项式计算" << std::endl;
        std::cout << "[History]     2. 查看历史记录" << std::endl;
        std::cout << "[Exit]        0. 退出\n" << std::endl;

        int choice_main;
        std::cout << "[Choice_main] 请选择选项：";
        std::cin >> choice_main;
        std::cout << std::endl << std::endl;

        system("cls");
        if (choice_main == 1) {
            bool multi = false;
            while(true){
                std::cout << "[Calculate Menu] 2 Polynomial with 5 Calculate Mode\n" << std::endl;
                std::cout << "[Save]        1. 多项式暂存 「Multiple」" << std::endl;
                std::cout << "[Calculate]   2. 多项式计算 「Simple」" << std::endl;
                std::cout << "[Exit]        0. 退出\n" << std::endl;
                std::cout << "[Tips] You can choose「Function1」operation FIRST\n";
                std::cout << "       in order to Calculate MORE efficient\n";
                std::cout << "       When you're processing SAME POLYNOMIAL SEQUENCE.\n\n";

                int choice_cal_1;
                std::cout << "[Choice_cal_1] 请选择选项：";
                std::cin >> choice_cal_1;

                system("cls");
                if(choice_cal_1 == 1){
                    calculator.createPolynomial(polynomial1, polynomial2);
                    multi = true;
                    system("Pause");
                }
                else if(choice_cal_1 == 2){
                    while(true) {
                        std::cout << "[Calculate] 5 functions with [simple/multiple] operation\n" << std::endl;
                        std::cout << calculator.modeSwitch(multi) << "1. 多项式加法" << std::endl;
                        std::cout << calculator.modeSwitch(multi) << "2. 多项式减法" << std::endl;
                        std::cout << calculator.modeSwitch(multi) << "3. 多项式在X处的值" << std::endl;
                        std::cout << calculator.modeSwitch(multi) << "4. 多项式a的导函数a’" << std::endl;
                        std::cout << calculator.modeSwitch(multi) << "5. 多项式a和b相乘，建立乘积多项式ab" << std::endl;
                        std::cout << "[Exit]        0. 退出\n" << std::endl;

                        int choice_cal_2;
                        std::cout << "[Choice_cal_2] 请选择选项：";
                        std::cin >> choice_cal_2;

                        if(!multi && choice_cal_2){
                            calculator.createPolynomial(polynomial1, polynomial2);
                        }

                        if (choice_cal_2 == 1) {
                            std::cout << "\n[Calculate] Polynomial add:\n" << std::endl;
                            std::cout << "[Result] Polynomial 1 + Polynomial 2：" << std::endl;
                            operation = '+';
                            calculator.performCalculation(polynomial1, polynomial2, operation);
                        } else if (choice_cal_2 == 2) {
                            std::cout << "\n[Calculate] Polynomial sub:\n" << std::endl;
                            std::cout << "[Result] Polynomial 1 - Polynomial 2：" << std::endl;
                            operation = '-';
                            calculator.performCalculation(polynomial1, polynomial2, operation);
                        } else if (choice_cal_2 == 3) {
                            std::cout << "[Calculate] Polynomial with X -> Value:\n" << std::endl;
                            operation = 'x';
                            calculator.performCalculation(polynomial1, polynomial2, operation);
                        } else if (choice_cal_2 == 4) {
                            std::cout << "[Calculate] Polynomial Derivative Function:\n" << std::endl;
                            operation = '\'';
                            calculator.performCalculation(polynomial1, polynomial2, operation);
                        } else if (choice_cal_2 == 5) {
                            std::cout << "[Calculate] Product Polynomial:\n" << std::endl;
                            operation = '*';
                            calculator.performCalculation(polynomial1, polynomial2, operation);
                        } else if (choice_cal_2 == 0) {
                            system("cls");
                            break;
                        } else {
                            std::cout << "[Error] 无效选项，请重新选择。" << std::endl;
                        }
                        system("Pause");
                        system("cls");
                    }
                }else if(choice_cal_1 == 0){
                    system("cls");
                    break;
                }else{
                    std::cout << "[Error] 无效选项，请重新选择。" << std::endl;
                }
                system("cls");
            }
        } else if (choice_main== 2) {
            std::cout << "[History] Print if has\n" << std::endl;
            // 遍历并显示每个计算项目的历史记录
            calculator.displayHistory(addHistory, "[Add]");
            calculator.displayHistory(subHistory, "[Sub]");
            calculator.displayHistory(xValueHistory, "[Value at X]");
            calculator.displayHistory(derivativeHistory, "[Derivative Function]");
            calculator.displayHistory(multiplyHistory, "[Product Polynomial]");
            std::cout << std::endl;
            system("Pause");
            system("cls");
        } else if (choice_main == 0) {
            break;
        } else {
            std::cout << "[Error] 无效选项，请重新选择。" << std::endl;
        }
    }
    return 0;
}