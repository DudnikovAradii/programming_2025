#include <iostream>
#include <cmath> //����������� math ��� ������������� ������� pow
using namespace std;


int main() {
    int A, B, C; // ������ ���������� A, B, C
    cin >> A; // ��� input � ������
    cin >> B; // ��� input � ������
    cin >> C; // ��� input � ������
    float P; //��������� ����� � ��������� ������ � ������� float
    P = (A + B + C) / 2.0; // ���� ������������ ������������
    float S; //��������� ����� � ��������� ������ � ������� float
    S = pow((P * (P - A) * (P - B) * (P - C)), 0.5); // ������� ������

    setlocale(LC_ALL, "Russian"); // ������� ��� ����������� ������������� ������� ���� 
    cout << "������� ������������: " << S << " float" << endl; // ����� ����������
    cout << "int " << sizeof(int) * 8<< " ����, " << "�� " << numeric_limits<int>::min() << " �� " << numeric_limits<int>::max() << endl;
    cout << "float " << sizeof(int) * 8 << " ����, " << "�� " << numeric_limits<float>::lowest() << " �� " << numeric_limits<float>::max() << endl;


    return 0;
}
/*kaskdfkfa
osdfgpsgdp*/