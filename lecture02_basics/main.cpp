#include <iostream>
#include <cmath> //����������� math ��� ������������� ������� pow
using namespace std;


int main() {
    int A, B, C;
    cin >> A; // ��� input � ������
    cin >> B; // ��� input � ������
    cin >> C; // ��� input � ������
    float P; //��������� ����� � ��������� ������ � ������� float
    P = (A + B + C) / 2.0; // ���� ������������ ������������
    float S; //��������� ����� � ��������� ������ � ������� float
    S= P * (P - A) * (P - B) * (P - C); // ������� ������ ��� �����
    float ROOT; //��������� ����� � ��������� ������ � ������� float
    ROOT = pow(S, 0.5); // � ������� pow ���� ������� 0.5 ����� (���������� ������)

    cout << ROOT << endl;
    cout << "int " << "32 bits, " << -2147483648 << 2147483647 << endl;
    cout << "float " << "32 bits, " << -3.4E-38 << 3.4E+38 << endl;


    return 0;
}