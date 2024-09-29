#include <iostream>
#include <vector>
#include<time.h>
#include<fstream>
#include<sstream>
#include <string>

using namespace std;

vector<vector<int>> prime;// ������ ��� �������� ������� 


class SOK {
private:
    vector<vector<vector<int>>> matrixsok;
    vector<int> basis;
public:
    void convertPPS_SOK(vector<vector<int>> z ) {


    }
};
class MatrixOperation {
public:
    // ����� ��� �������� ���������� ������� � ���������� ����������

    void createMatrix(vector<vector<int>>& matrix, int min, int max, int size) {
        // �������� �������
        matrix.assign(size, vector<int>(size));
        // ���������� ������� ���������� ����������
        for (auto& row : matrix) {
            for (auto& val : row) {
                val = rand() % (max - min + 1) + min;;
            }
        }
    }
    // ����� ��� c������� ������
    vector<vector<int>> additionMatrix(vector<vector<int>>operator1, vector<vector<int>>operator2, int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                operator1[i][j] = operator1[i][j] + operator2[i][j];
                cout << operator1[i][j] << " ";
            }
            cout << endl;
        }
        return operator1;
    }
    // ����� ��� ��������� ������
    vector<vector<int>> multiplicationMatrix(vector<vector<int>>operator1, vector<vector<int>>operator2, int size) {
        vector<vector<int>>matrixMultiplication(size, vector<int>(size));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrixMultiplication[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    matrixMultiplication[i][j] += operator1[i][k] * operator2[k][j];
                }
                cout << matrixMultiplication[i][j] << " ";
            }
            cout << endl;
        }
        return matrixMultiplication;
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    MatrixOperation generator;

    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;

    vector<vector<int>> ResultAdd;
    vector<vector<int>> ResultMultiplication;

    ifstream file("BASIS.txt");
    if (!file) { cout << "ERROR open file\n"; }

    string str;
    string number;
    vector<int> num;
 
    while (getline(file, str)) {
        istringstream iss(str);
        while (iss >> number) {
            num.push_back(stoi(number));
        }
        prime.push_back(num);
        num.resize(0);
    };

   /* for (auto j : prime) {
        for (auto t : j) {
            cout << t << " ";
        }
        cout << endl;
    }*/


    int size, RandomRangeMin, RandomRangeMax, choose = 0;
    while (choose != 4)
    {
        cout << "�������� ��������:\n1)������������� �������\n2)������� �������\n3)����������� �������\n4)��������� ���������� ���������\n";
        cin >> choose;
        while (choose < 1 || choose > 4) {
            cout << "�������� ��������. ��������� �����.";
            cin >> choose;
        }
        switch (choose)
        {
        case(1): {
            cout << "������� ������ ������ �� 0 �� 100: ";
            cin >> size;
            while (size < 0 && size > 100) {
                cout << "������� ������ ������� �� 0 �� 100: ";
                cin >> size;
            }
            //M������ 1
            cout << "������� �������� �������� ��������� ��������� ����� ��� ������ �������\nmin: ";
            cin >> RandomRangeMin;
            cout << "max: ";
            cin >> RandomRangeMax;
            generator.createMatrix(matrix1, RandomRangeMin, RandomRangeMax, size);


            cout << "������� 1\n";
            for (const auto& row : matrix1) {
                for (int val : row) {
                    cout << val << " ";
                }
                cout << endl;
            }
            //M������ 2
            cout << "������� �������� �������� ��������� ��������� ����� ��� ������ �������\nmin: ";
            cin >> RandomRangeMin;
            cout << "max: ";
            cin >> RandomRangeMax;
            generator.createMatrix(matrix2, RandomRangeMin, RandomRangeMax, size);

            cout << "������� 2\n";
            for (const auto& row : matrix2) {
                for (int val : row) {
                    cout << val << " ";
                }
                cout << endl;
            }
            break;
        }
        case(2): {
            ResultAdd = generator.additionMatrix(matrix1, matrix2, size);
            break;
        }
        case(3):
            ResultMultiplication = generator.multiplicationMatrix(matrix1, matrix2, size);
   
            break;
        }
    }



    return 0;
}

