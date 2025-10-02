#include <iostream>
#include <bitset>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    short A;
    cout << "����� �: ";
    cin >> A;
    short i;
    cout << "������� ����� ���� i (0-7): ";
    cin >> i;
    if (i < 0 || i > 7) {
        cout << "������: ����� ���� ������ ���� �� 0 �� 7" << endl;
        return 1;
    }
    bitset<8> b2 = A;
    cout << "�������� ������������� ����� A: " << b2.to_string() << endl;
    int bitI = (A >> i) & 1;
    cout << "i �������: " << bitI << endl;
    if (bitI == 0) {
        int result = A * A;
        result = result & ~(1 << i);
        bitset<32> result2 = result;
        cout << "��������� A^2 � ������������� � 0 ����� i � 10-�� ��: " << result<< "," << " � 2-�� ��: " << result2.to_string() << endl;
    }
    else {
        short number = 125;
        bitset<8> number2 = number;
        int chet = 170; // � �������� ���� �������� ��� 10101010 (��� ���������� � ������ �������� ��� ������ ���� �� ����)
        short result = number & chet;
        bitset<8> result2 = result;
        cout << "�������� �����: " << number << ", � �������� ����: " << number2.to_string() << endl;
        cout << "����� ������ ������ ����� �� 0: " << result << ", � �������� ����: " << result2.to_string() << endl;
    }

}
// Number 2
/*
int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "������� ����� ��������� �������� ";
    cin >> n;
    switch (n)
    {
    case 113:
        cout << "����������� � �������" << endl;
        break;
    case 114:
        cout << "����������� - ������������" << endl;
        break;
    case 117:
        cout << "����������� - ��������" << endl;
        break;
    case 118:
        cout << "����������� - �����������" << endl;
        break;
    case 119:
        cout << "����������� - ����������" << endl;
        break;
    case 125:
        cout << "����������� - �������" << endl;
        break;
    case 139:
        cout << "����������� - ������������" << endl;
        break;
    case 141:
        cout << "����������� - ������������" << endl;
        break;
    case 148:
        cout << "����������� - �������������" << endl;
        break;
    case 161:
        cout << "����������� - �������" << endl;
        break;
    case 191:
        cout << "����������� - �������������" << endl;
        break;
    case 593:
        cout << "����������� - �������" << endl;
        break;
    case 802:
        cout << "����������� - �������" << endl;
        break;
    default:
        cout << "������ �������� ���!" << endl;
        break;
    }
}
*/