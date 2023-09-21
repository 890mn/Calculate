#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>

// ����ʽ�ṹ��
struct PolyTerm {
    double coefficient; // ϵ��
    int exponent;      // ָ��
    PolyTerm* next; // ָ����һ������ʽ���ָ��

    // ���캯��
    PolyTerm(double coef, int exp) : coefficient(coef), exponent(exp), next(nullptr) {}
};

// ��ʷ��¼��Ľṹ��
struct HistoryItem {
    std::string operation;  // �������
    std::string polynomial1; // ��һ������ʽ
    std::string polynomial2; // �ڶ�������ʽ
    std::string result;     // ������

    HistoryItem(const std::string& op, const std::string& poly1, const std::string& poly2, const std::string& res)
            : operation(op), polynomial1(poly1), polynomial2(poly2), result(res) {}
};

// ���������ͬ����ʷ��¼�б��ֱ��Ӧ�����ͬ�ļ�����Ŀ
std::vector<HistoryItem> addHistory;
std::vector<HistoryItem> subHistory;
std::vector<HistoryItem> xValueHistory;
std::vector<HistoryItem> derivativeHistory;
std::vector<HistoryItem> multiplyHistory;

// ����ʽ�࣬����һ��ָ�����ʽ�����ָ��
class Polynomial {
private:
    PolyTerm* head; // ����ʽ�����ָ��
    std::vector<HistoryItem> history; // ��ʷ��¼

public:
    // ���캯��
    Polynomial() : head(nullptr) {}

    // ��Ӷ���ʽ��
    void addTerm(double coef, int exp) {
        auto newTerm = new PolyTerm(coef, exp);
        if (!head) {
            head = newTerm;
        } else {
            // ���������ҵ����һ������������ӵ����һ��ĺ���
            PolyTerm* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newTerm;
        }
    }

    // �������ʽ
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

                // ���ϵ�����������1���ǳ����
                if (current->exponent == 0 || (current->exponent != 0 && std::abs(current->coefficient) != 1)) {
                    std::cout << std::abs(current->coefficient);
                }

                // ���ָ��
                if (current->exponent > 0) {
                    std::cout << "x";
                    if (current->exponent != 1) {
                        std::cout << "^" << current->exponent;
                    }
                }
            }
            current = current->next;
        }

        // ����ʽΪ0�����
        if (isFirstTerm) {
            std::cout << "0";
        }

        std::cout << std::endl;
    }

    // ������ʽ����ת��Ϊ�ַ���
    std::string toString() const {
        std::ostringstream oss; // ����һ������ַ����������ڹ�������ʽ���ַ�����ʾ
        PolyTerm* current = head; // �Ӷ���ʽ��ͷ����ʼ����
        bool isFirstTerm = true; // ���ڱ���Ƿ��ǵ�һ����

        while (current) {
            double coef = current->coefficient; // ��ȡ��ǰ���ϵ��
            int exp = current->exponent; // ��ȡ��ǰ���ָ��

            if (coef != 0) { // ���ϵ����Ϊ��
                if (!isFirstTerm) {
                    if (coef > 0) {
                        oss << " + "; // ������ǵ�һ������ϵ��Ϊ��������ӼӺ�
                    } else {
                        oss << " - "; // ������ǵ�һ������ϵ��Ϊ��������Ӽ���
                    }
                } else {
                    isFirstTerm = false; // ����ǵ�һ����� isFirstTerm ����Ϊ false
                }

                if (std::abs(coef) != 1 || exp == 0) {
                    oss << std::fixed << std::setprecision(2) << std::abs(coef); // ����������Ȳ����ϵ���ľ���ֵ
                }

                if (exp > 0) {
                    oss << "x"; // ���ָ������0����ӱ��� x
                    if (exp != 1) {
                        oss << "^" << exp; // ���ָ��������1�����ָ������
                    }
                }
            }
            current = current->next; // �ƶ�����һ����
        }

        return oss.str(); // ���������ַ������ַ���������ȡ������
    }

    // ����ʽ�ӷ� ���������
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result; // ����һ�����ڴ洢����Ķ���ʽ����

        PolyTerm* current1 = head; // ����ָ��ǰ����ĵ�һ������ʽ���ָ��
        PolyTerm* current2 = other.head; // ����ָ��ڶ�������ʽ����ĵ�һ������ʽ���ָ��

        while (current1 || current2) { // ѭ��ֱ����������ʽ���������������
            double coef1 = (current1) ? current1->coefficient : 0; // ��ȡ��һ������ʽ���ϵ���������ǰ��Ϊ����Ĭ��Ϊ0
            double coef2 = (current2) ? current2->coefficient : 0; // ��ȡ�ڶ�������ʽ���ϵ���������ǰ��Ϊ����Ĭ��Ϊ0
            int exp1 = (current1) ? current1->exponent : 0; // ��ȡ��һ������ʽ���ָ���������ǰ��Ϊ����Ĭ��Ϊ0
            int exp2 = (current2) ? current2->exponent : 0; // ��ȡ�ڶ�������ʽ���ָ���������ǰ��Ϊ����Ĭ��Ϊ0

            if (exp1 > exp2) { // �����һ������ʽ���ָ�����ڵڶ�������ʽ���ָ��
                result.addTerm(coef1, exp1); // ����һ������ʽ����ӵ��������ʽ��
                current1 = (current1) ? current1->next : nullptr; // �ƶ�����һ������ʽ����һ������û����һ������ָ������Ϊnullptr
            } else if (exp1 < exp2) { // �����һ������ʽ���ָ��С�ڵڶ�������ʽ���ָ��
                result.addTerm(coef2, exp2); // ���ڶ�������ʽ����ӵ��������ʽ��
                current2 = (current2) ? current2->next : nullptr; // �ƶ����ڶ�������ʽ����һ������û����һ������ָ������Ϊnullptr
            } else { // �����������ʽ���ָ�����
                result.addTerm(coef1 + coef2, exp1); // �����ǵ�ϵ����Ӻ���ӵ��������ʽ��
                current1 = (current1) ? current1->next : nullptr; // �ƶ�����һ������ʽ����һ����
                current2 = (current2) ? current2->next : nullptr; // �ƶ����ڶ�������ʽ����һ����
            }
        }

        return result; // ���ذ�����ӽ���Ķ���ʽ����
    }

    //����ʽ����
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

    // �������ʽ��X����ֵ
    double evaluate(double x) const {
        double result = 0.0;
        PolyTerm* current = head;
        while (current) {
            result += current->coefficient * pow(x, current->exponent);
            current = current->next;
        }
        return result;
    }

    // �������ʽ�ĵ�����
    Polynomial derivative() const {
        Polynomial result; // ����һ�����ڴ洢����������Ķ���ʽ����

        PolyTerm* current = head; // ����ָ��ǰ����ʽ����ĵ�һ������ʽ���ָ��

        while (current) { // ��������ʽ��ÿһ��
            double coef = current->coefficient * current->exponent; // ���㵼�������ϵ������ԭϵ������ָ��
            int exp = (current->exponent > 0) ? current->exponent - 1 : 0; // ���㵼�������ָ�������ԭָ������0���1������Ϊ0
            result.addTerm(coef, exp); // ������������ӵ��������ʽ��
            current = current->next; // �ƶ�������ʽ����һ����
        }

        return result; // ���ذ�������������Ķ���ʽ����
    }

    // �������ʽa��b�ĳ˻��������س˻�����ʽab
    Polynomial multiply(const Polynomial& other) const {
        Polynomial result; // ����һ�����ڴ洢�˻�����ʽ����Ķ���ʽ����
        PolyTerm* current1 = head; // ����ָ��ǰ����ʽ����ĵ�һ������ʽ���ָ��

        while (current1) { // ������һ������ʽ��ÿһ��
            PolyTerm* current2 = other.head; // ����ָ��ڶ�������ʽ����ĵ�һ������ʽ���ָ��

            while (current2) { // �����ڶ�������ʽ��ÿһ��
                double coef1 = current1->coefficient; // ��ȡ��һ������ʽ���ϵ��
                double coef2 = current2->coefficient; // ��ȡ�ڶ�������ʽ���ϵ��
                int exp1 = current1->exponent; // ��ȡ��һ������ʽ���ָ��
                int exp2 = current2->exponent; // ��ȡ�ڶ�������ʽ���ָ��

                double productCoef = coef1 * coef2; // �����������ϵ����ˣ��õ��µ�ϵ��
                int productExp = exp1 + exp2; // �����������ָ����ӣ��õ��µ�ָ��

                // ���������ʽ���Ƿ��Ѵ��ھ�����ָͬ������
                bool termExists = false;
                PolyTerm* currentResult = result.head;
                while (currentResult) {
                    if (currentResult->exponent == productExp) {
                        currentResult->coefficient += productCoef; // ������ڣ���ϵ�����
                        termExists = true;
                        break;
                    }
                    currentResult = currentResult->next;
                }
                // ����������ʽ�в����ھ�����ָͬ��������µ�����ӵ������
                if (!termExists) {
                    result.addTerm(productCoef, productExp);
                }
                current2 = current2->next; // �ƶ����ڶ�������ʽ����һ����
            }
            current1 = current1->next; // �ƶ�����һ������ʽ����һ����
        }
        return result; // ���ذ����˻�����Ķ���ʽ����
    }

    void createPolynomial(Polynomial& polynomial1, Polynomial& polynomial2){
        std::cout << "[Save] Enter 2 Polynomial follow the hints given by" << std::endl;
        std::cout << "[Tips] 3x^2 + 6x + 1 -> 3 3 2 6 1 1 0\n" << std::endl;
        std::cout << "[Poly1] �������һ������ʽ��������3��:";
        int termCount1;
        std::cin >> termCount1;

        std::cout << "[Poly1] �������һ������ʽ��ÿһ��(ϵ�� ָ��)��3 2 6 1 1 0��" << std::endl;
        for (int i = 0; i < termCount1; ++i) {
            double coef;
            int exp;
            std::cin >> coef >> exp;
            polynomial1.addTerm(coef, exp);
        }

        std::cout << "\n[Poly2] ������ڶ�������ʽ��������3��:";
        int termCount2;
        std::cin >> termCount2;

        std::cout << "[Poly2] ������ڶ�������ʽ��ÿһ��(ϵ�� ָ��)��3 2 6 1 1 0��" << std::endl;
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
        std::cout << "[Calculate]   1. ����ʽ����" << std::endl;
        std::cout << "[History]     2. �鿴��ʷ��¼" << std::endl;
        std::cout << "[Exit]        0. �˳�\n" << std::endl;

        int choice_main;
        std::cout << "[Choice_main] ��ѡ��ѡ�";
        std::cin >> choice_main;
        std::cout << std::endl << std::endl;

        system("cls");
        if (choice_main == 1) {
            bool multi = false;
            while(true){
                std::cout << "[Calculate Menu] 2 Polynomial with 5 Calculate Mode\n" << std::endl;
                std::cout << "[Save]        1. ����ʽ�ݴ� ��Multiple��" << std::endl;
                std::cout << "[Calculate]   2. ����ʽ���� ��Simple��" << std::endl;
                std::cout << "[Exit]        0. �˳�\n" << std::endl;
                std::cout << "[Tips] You can choose��Function1��operation FIRST\n";
                std::cout << "       in order to Calculate MORE efficient\n";
                std::cout << "       When you're processing SAME POLYNOMIAL SEQUENCE.\n\n";

                int choice_cal_1;
                std::cout << "[Choice_cal_1] ��ѡ��ѡ�";
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
                        std::cout << calculator.modeSwitch(multi) << "1. ����ʽ�ӷ�" << std::endl;
                        std::cout << calculator.modeSwitch(multi) << "2. ����ʽ����" << std::endl;
                        std::cout << calculator.modeSwitch(multi) << "3. ����ʽ��X����ֵ" << std::endl;
                        std::cout << calculator.modeSwitch(multi) << "4. ����ʽa�ĵ�����a��" << std::endl;
                        std::cout << calculator.modeSwitch(multi) << "5. ����ʽa��b��ˣ������˻�����ʽab" << std::endl;
                        std::cout << "[Exit]        0. �˳�\n" << std::endl;

                        int choice_cal_2;
                        std::cout << "[Choice_cal_2] ��ѡ��ѡ�";
                        std::cin >> choice_cal_2;

                        if(!multi && choice_cal_2){
                            calculator.createPolynomial(polynomial1, polynomial2);
                        }

                        if (choice_cal_2 == 1) {
                            std::cout << "\n[Calculate] Polynomial add:\n" << std::endl;
                            std::cout << "[Result] Polynomial 1 + Polynomial 2��" << std::endl;
                            operation = '+';
                            calculator.performCalculation(polynomial1, polynomial2, operation);
                        } else if (choice_cal_2 == 2) {
                            std::cout << "\n[Calculate] Polynomial sub:\n" << std::endl;
                            std::cout << "[Result] Polynomial 1 - Polynomial 2��" << std::endl;
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
                            std::cout << "[Error] ��Чѡ�������ѡ��" << std::endl;
                        }
                        system("Pause");
                        system("cls");
                    }
                }else if(choice_cal_1 == 0){
                    system("cls");
                    break;
                }else{
                    std::cout << "[Error] ��Чѡ�������ѡ��" << std::endl;
                }
                system("cls");
            }
        } else if (choice_main== 2) {
            std::cout << "[History] Print if has\n" << std::endl;
            // ��������ʾÿ��������Ŀ����ʷ��¼
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
            std::cout << "[Error] ��Чѡ�������ѡ��" << std::endl;
        }
    }
    return 0;
}