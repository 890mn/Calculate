
/*��ʼ��д�����Ŀʱ�����԰������²����𽥹������һԪϡ�����ʽ��������

1. **������ݽṹ**��
   - ��ʼʱ������������һ������ʽ�����ݽṹ������Դ���һ������ʽ��Ľṹ����࣬����ϵ����ָ����Ϣ��
   - �����������һ����ʾ����ʽ�����ݽṹ������ʹ������ÿ���ڵ�洢һ������ʽ�

2. **ʵ�ֶ���ʽ����**��
   - ��д�����������û����룬��������Ķ���ʽ�Ȼ��������ӵ�����ʽ�������С�������δ���ͬ�������ʽ��

3. **ʵ�ֶ���ʽ���**��
   - ��д��������������ʽ��������ָ�����������������ʽ��

4. **ʵ�ֶ���ʽ�ļӷ��ͼ���**��
   - ��д������ִ�ж���ʽ�ļӷ��ͼ�������������Ҫ������������ʽ����������ָ��������Ӧ�Ĳ�����

5. **��չ����**����ѡ����
   - �����ϣ��ʵ��ѡ�������е��κι��ܣ���������ʽ��X����ֵ�����㵼����������ʽ��˵ȣ��������ڴ˽׶ν��С�

6. **�û�����**����ѡ����
   - �������㴴������������Ľ��棬����ʹ��C++���û������������н����������û����档

7. **����**��
   - �ڱ�дÿ������ģ��󣬽��в�����ȷ������ȷ�ԡ�ʹ����ĿҪ�����ṩ�Ĳ������ݽ��в��ԡ�

8. **�ĵ���ע��**��
   - ��ӱ�Ҫ��ע�������ʹ���Ĺ��ܺ��߼���
   - ��д�ĵ���˵�����ʹ����ļ��������书�ܡ�

9. **�Ż��͸Ľ�**��
   - ��ɻ������ܺ󣬿��Կ����Ż����롢������ܻ���Ӷ���Ĺ��ܡ�

10. **�ܽ������**��
    - ���������룬ȷ�����й��ܶ�����Ҫ���������������ղ��ԡ�

��������ݽṹ��ʵ�ֶ���ʽ���뿪ʼ��һ���������㡣һ�����ܹ��ɹ���������������ʽ��Ȼ������Ӽӷ��ͼ����������㽫��һ����ȫ���õļ򵥶���ʽ�������ĺ��Ĺ��ܡ�Ȼ�����������Ӹ���Ĺ��ܺͽ��棬��������ĿҪ�����չ���ܡ��ǵ��ڿ��������б��ִ���Ŀ�ά���Ժ������ԣ��⽫������������ɵ���չ�͸Ľ���ļ�������*/

#include <iostream>
#include <cmath>
// �ṹ�����ڱ�ʾ����ʽ��
struct PolyTerm {
    double coefficient; // ϵ��
    int exponent;      // ָ��
    PolyTerm* next; // ָ����һ������ʽ���ָ��

    // ���캯��
    PolyTerm(double coef, int exp) : coefficient(coef), exponent(exp), next(nullptr) {}
};

// ����ʽ�࣬����һ��ָ�����ʽ�����ָ��
class Polynomial {
private:
    PolyTerm* head; // ����ʽ�����ָ��

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


    // ����ʽ�ӷ�
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

    // �������ʽa��b�ĳ˻��������س˻�����ʽab
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

    std::cout << "�������һ������ʽ��������";
    int termCount1;
    std::cin >> termCount1;

    std::cout << "�������һ������ʽ��ÿһ�ϵ�� ָ������" << std::endl;
    for (int i = 0; i < termCount1; ++i) {
        double coef;
        int exp;
        std::cin >> coef >> exp;
        polynomial1.addTerm(coef, exp);
    }

    std::cout << "������ڶ�������ʽ��������";
    int termCount2;
    std::cin >> termCount2;

    std::cout << "������ڶ�������ʽ��ÿһ�ϵ�� ָ������" << std::endl;
    for (int i = 0; i < termCount2; ++i) {
        double coef;
        int exp;
        std::cin >> coef >> exp;
        polynomial2.addTerm(coef, exp);
    }

    std::cout << "����ʽ1��" << std::endl;
    polynomial1.print();

    std::cout << "����ʽ2��" << std::endl;
    polynomial2.print();

    // ִ�мӷ�����
    result = polynomial1 + polynomial2;
    std::cout << "����ʽ1 + ����ʽ2��" << std::endl;
    result.print();

    // ִ�м�������
    result = polynomial1 - polynomial2;
    std::cout << "����ʽ1 - ����ʽ2��" << std::endl;
    result.print();

    // �������ʽ1��X=2����ֵ
    double xValue = 2.0;
    double resultValue = polynomial1.evaluate(xValue);
    std::cout << "����ʽ1��X=" << xValue << "����ֵΪ��" << resultValue << std::endl;

    // �������ʽ1�ĵ�����
    Polynomial derivativeResult = polynomial1.derivative();
    std::cout << "����ʽ1�ĵ�������" << std::endl;
    derivativeResult.print();

    // �������ʽ1�Ͷ���ʽ2�ĳ˻�
    Polynomial productResult = polynomial1.multiply(polynomial2);
    std::cout << "����ʽ1�Ͷ���ʽ2�ĳ˻���" << std::endl;
    productResult.print();

    system("Pause");
}

/*����ʽ1��2x + 5x^3 - 3.1x^11
����ʽ2��7 - 5x^8 + 11x^9
Ԥ�ڼӷ������-3.1x^11 + 11x^9 + 2x + 7

����ʽ1��6x - 3 - x + 4.4x^2 - 1.2x^9
����ʽ2��-6x - 3 + 5.4x^2 - x^2 + 7.8x^15
Ԥ�ڼ��������-7.8x^15 - 1.2x^9 + 12x - 3 - x

����ʽ1��1 + x + x^2 + x^3 + x^4 + x^5
����ʽ2��-x^3 - x^4
Ԥ�ڼӷ������1 + x + x^2 + x^5

����ʽ1��x + x^3
����ʽ2��-x - x^3
Ԥ�ڼ��������0

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