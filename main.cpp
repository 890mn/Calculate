
/*开始编写这个项目时，可以按照以下步骤逐渐构建你的一元稀疏多项式计算器：

1. **设计数据结构**：
   - 开始时，考虑如何设计一个多项式的数据结构。你可以创建一个多项式项的结构体或类，包含系数和指数信息。
   - 接下来，设计一个表示多项式的数据结构，可以使用链表，每个节点存储一个多项式项。

2. **实现多项式输入**：
   - 编写函数来接受用户输入，解析输入的多项式项，然后将它们添加到多项式的链表中。考虑如何处理不同的输入格式。

3. **实现多项式输出**：
   - 编写函数来遍历多项式链表并按照指数降序排列输出多项式。

4. **实现多项式的加法和减法**：
   - 编写函数来执行多项式的加法和减法操作。这需要遍历两个多项式链表，并根据指数进行相应的操作。

5. **扩展功能**（可选）：
   - 如果你希望实现选作内容中的任何功能（如计算多项式在X处的值、计算导函数、多项式相乘等），可以在此阶段进行。

6. **用户界面**（可选）：
   - 如果你打算创建仿真计算器的界面，可以使用C++的用户界面库或命令行界面库来设计用户界面。

7. **测试**：
   - 在编写每个功能模块后，进行测试以确保其正确性。使用项目要求中提供的测试数据进行测试。

8. **文档和注释**：
   - 添加必要的注释来解释代码的功能和逻辑。
   - 编写文档，说明如何使用你的计算器和其功能。

9. **优化和改进**：
   - 完成基本功能后，可以考虑优化代码、提高性能或添加额外的功能。

10. **总结和整理**：
    - 最后，整理代码，确保所有功能都按照要求工作，并进行最终测试。

从设计数据结构和实现多项式输入开始是一个不错的起点。一旦你能够成功地输入和输出多项式，然后再添加加法和减法操作，你将有一个完全可用的简单多项式计算器的核心功能。然后，你可以逐步添加更多的功能和界面，以满足项目要求和扩展功能。记得在开发过程中保持代码的可维护性和清晰性，这将有助于你更轻松地扩展和改进你的计算器。*/

#include <iostream>
#include <cmath>
// 结构体用于表示多项式项
struct PolyTerm {
    double coefficient; // 系数
    int exponent;      // 指数
    PolyTerm* next; // 指向下一个多项式项的指针

    // 构造函数
    PolyTerm(double coef, int exp) : coefficient(coef), exponent(exp), next(nullptr) {}
};

// 多项式类，包含一个指向多项式首项的指针
class Polynomial {
private:
    PolyTerm* head; // 多项式首项的指针

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


    // 多项式加法
    Polynomial operator+(const Polynomial& other) const {
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
                result.addTerm(coef2, exp2);
                current2 = (current2) ? current2->next : nullptr;
            } else {
                result.addTerm(coef1 + coef2, exp1);
                current1 = (current1) ? current1->next : nullptr;
                current2 = (current2) ? current2->next : nullptr;
            }
        }
        return result;
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
        Polynomial result;
        PolyTerm* current = head;

        while (current) {
            double coef = current->coefficient * current->exponent;
            int exp = (current->exponent > 0) ? current->exponent - 1 : 0;
            result.addTerm(coef, exp);
            current = current->next;
        }

        return result;
    }

    // 计算多项式a和b的乘积，并返回乘积多项式ab
    Polynomial multiply(const Polynomial& other) const {
        Polynomial result;

        PolyTerm* current1 = head;
        while (current1) {
            PolyTerm* current2 = other.head;
            while (current2) {
                double coef1 = current1->coefficient;
                double coef2 = current2->coefficient;
                int exp1 = current1->exponent;
                int exp2 = current2->exponent;

                double productCoef = coef1 * coef2;
                int productExp = exp1 + exp2;

                result.addTerm(productCoef, productExp);

                current2 = current2->next;
            }
            current1 = current1->next;
        }

        return result;
    }

};


int main(int argc, char *argv[]) {
    Polynomial polynomial1, polynomial2, result;

    std::cout << "请输入第一个多项式的项数：";
    int termCount1;
    std::cin >> termCount1;

    std::cout << "请输入第一个多项式的每一项（系数 指数）：" << std::endl;
    for (int i = 0; i < termCount1; ++i) {
        double coef;
        int exp;
        std::cin >> coef >> exp;
        polynomial1.addTerm(coef, exp);
    }

    std::cout << "请输入第二个多项式的项数：";
    int termCount2;
    std::cin >> termCount2;

    std::cout << "请输入第二个多项式的每一项（系数 指数）：" << std::endl;
    for (int i = 0; i < termCount2; ++i) {
        double coef;
        int exp;
        std::cin >> coef >> exp;
        polynomial2.addTerm(coef, exp);
    }

    std::cout << "多项式1：" << std::endl;
    polynomial1.print();

    std::cout << "多项式2：" << std::endl;
    polynomial2.print();

    // 执行加法操作
    result = polynomial1 + polynomial2;
    std::cout << "多项式1 + 多项式2：" << std::endl;
    result.print();

    // 执行减法操作
    result = polynomial1 - polynomial2;
    std::cout << "多项式1 - 多项式2：" << std::endl;
    result.print();

    // 计算多项式1在X=2处的值
    double xValue = 2.0;
    double resultValue = polynomial1.evaluate(xValue);
    std::cout << "多项式1在X=" << xValue << "处的值为：" << resultValue << std::endl;

    // 计算多项式1的导函数
    Polynomial derivativeResult = polynomial1.derivative();
    std::cout << "多项式1的导函数：" << std::endl;
    derivativeResult.print();

    // 计算多项式1和多项式2的乘积
    Polynomial productResult = polynomial1.multiply(polynomial2);
    std::cout << "多项式1和多项式2的乘积：" << std::endl;
    productResult.print();

    system("Pause");
}

/*多项式1：2x + 5x^3 - 3.1x^11
多项式2：7 - 5x^8 + 11x^9
预期加法结果：-3.1x^11 + 11x^9 + 2x + 7

多项式1：6x - 3 - x + 4.4x^2 - 1.2x^9
多项式2：-6x - 3 + 5.4x^2 - x^2 + 7.8x^15
预期减法结果：-7.8x^15 - 1.2x^9 + 12x - 3 - x

多项式1：1 + x + x^2 + x^3 + x^4 + x^5
多项式2：-x^3 - x^4
预期加法结果：1 + x + x^2 + x^5

多项式1：x + x^3
多项式2：-x - x^3
预期减法结果：0

 exp1:
 3
2 1
5 3
-3.1 11

 3
7 0
-5 8
11 9

 exp2:
 6
1 0
1 1
1 2
1 3
1 4
1 5

 2
-1 3
-1 4

 exp3:
 2
1 1
1 3

 2
-1 1
-1 3
 */