#include <iostream>
#include <vector>
#include<time.h>
#include<fstream>
#include<sstream>
#include <string>

using namespace std;

vector<vector<int>> prime;// ������ ��� �������� ������� 

class PSS {
private:
    vector<vector<uint16_t>> matrixPSS;
 
public:
    void convertSOK_PSS(vector<vector<vector<int>>> matrixInSOK, vector<int> basis) {
        uint64_t multBasis=1;
        // ������������� matrixPSS � ������ ��������
        matrixPSS.assign(matrixInSOK.size(), vector<uint16_t>(matrixInSOK[0].size(), 0));

        // ���������� ������������ ���������
        for (auto bas : basis) {
            multBasis *= bas;
        }

        vector<uint64_t> convertBasis(basis.size());
        for (int i = 0; i < convertBasis.size(); i++) {
            convertBasis[i] = multBasis / basis[i];
            convertBasis[i] *= convertBasis[i] % basis[i];
        }

        uint64_t convPSS ;

        // �������������� �������
        for (int row = 0; row < matrixInSOK.size(); row++) {
            for (int col = 0; col < matrixInSOK[row].size(); col++) {
                convPSS = 0;
                for (int i = 0; i < basis.size(); i++) {
                    convPSS += matrixInSOK[row][col][i] * convertBasis[i];
                }
                matrixPSS[row][col] = convPSS % multBasis;
            }
        }
        printMatrixPSS();
    }

    void printMatrixPSS() const {
        for (const auto& row : matrixPSS) {
            for (const auto& val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};


class SOK {
private:
    vector<vector<vector<int>>> matrixSOK;
    vector<int> basis;
public:
    void convertPSS_SOK(vector<vector<uint64_t>> z, int maxValue) {
         int mult = 1;

          bool br = false;
          for (auto row : prime) {
              for (auto val : row) {
                  mult *= val;
                  basis.push_back(val);
                  if (mult > maxValue) {
                      br = true;
                      break;
                  }
              }
              if (br) {
                  break;
              }
              else {
                  basis.resize(0);
                  mult = 1;
              }
          }

       // basis = prime[0];

        cout << "\n\n";

        for (auto g : basis) {
            cout << g << " ";
        }

        cout << "\n" << endl;


        matrixSOK.assign(z.size(), vector<vector<int>>(z.size(), vector<int>(basis.size())));

        for (int raw = 0; raw < z.size(); raw++) {
            for (int val = 0; val < z.size(); val++) {
                for (int i = 0; i < basis.size(); i++) {
                    matrixSOK[raw][val][i] = z[raw][val] % basis[i];
                    if ((matrixSOK[raw][val][i] / 10) == 0) {
                        cout << " " << matrixSOK[raw][val][i] << " ";
                    }
                    else {
                        cout << matrixSOK[raw][val][i] << " ";
                    }
                }
                cout << "    ";
            }
            cout << endl;
        }

        cout << "\n\n";

        PSS kk;
        kk.convertSOK_PSS(matrixSOK, basis);

        cout << "\n\n";
    }

    vector<vector<vector<int>>> ReturnSOK() { return matrixSOK; }
    vector<int>  ReturnBasis() { return basis; }
};
class MatrixOperation {
private:
    vector<vector<uint64_t>> matrix;
    SOK matrixInSok;
public:
    // ����� ��� �������� ���������� ������� � ���������� ����������
    MatrixOperation(uint64_t min, uint64_t max, int size) {
        // �������� �������
        matrix.assign(size, vector<uint64_t>(size));
        // ���������� ������� ���������� ����������
        for (auto& row : matrix) {
            for (auto& val : row) {
                val = rand() % (max - min + 1) + min;;
            }
        }

        for (const auto& row : matrix) {
            for (auto val : row) {
                cout << val << " ";
            }
            cout << endl;
        }

        cout << "\n��� �������" << endl;;


        matrixInSok.convertPSS_SOK(matrix, max);
        cout << endl;
    }
    // ����� ��� c������� ������
    vector<vector<uint64_t>> additionMatrix(vector<vector<uint64_t>>operator1, vector<vector<uint64_t>>operator2, int size) {
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
    vector<vector<uint64_t>> multiplicationMatrix(vector<vector<uint64_t>>operator1, vector<vector<uint64_t>>operator2, int size) {
        vector<vector<uint64_t>>matrixMultiplication(size, vector<uint64_t>(size));
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
    SOK SokMatrix1;
    SOK SokMatrix2;
    SOK SokMatrix3;

   

    //vector<vector<uint64_t>> matrix1;
    vector<vector<uint64_t>> matrix2;

    vector<vector<uint64_t>> ResultAdd;
    vector<vector<uint64_t>> ResultMultiplication;

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



    uint64_t size, RandomRangeMin, RandomRangeMax;
    int choose = 0;

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

            cout << "������� 1\n"<<endl;
            MatrixOperation matrix1(RandomRangeMin, RandomRangeMax, size);
          
            //M������ 2
            cout << "������� 2\n"<<endl;
            MatrixOperation matrix2(RandomRangeMin, RandomRangeMax, size);

         /*   cout << "\n ��� ������ �������";
            SokMatrix1.convertPPS_SOK(matrix1, RandomRangeMax);
            cout << "\n ��� ������ �������";
            SokMatrix2.convertPPS_SOK(matrix2, RandomRangeMax);*/

            break;
        }
        case(2): {
           /* ResultAdd = generator.additionMatrix(matrix1, matrix2, size);*/
            break;
        }
        case(3):
            /*ResultMultiplication = generator.multiplicationMatrix(matrix1, matrix2, size);
            SokMatrix2.convertPPS_SOK(ResultMultiplication, RandomRangeMax);*/

            break;
        }
    }



    return 0;
}

