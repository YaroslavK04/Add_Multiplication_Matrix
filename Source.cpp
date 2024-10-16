#include <iostream>
#include <vector>
#include<time.h>
#include<fstream>
#include<sstream>
#include <string>
#include<cmath>

using namespace std;

vector<vector<int>> prime;// вектор для хранения базисов 


uint64_t modInverse(uint64_t Mi, uint64_t basis) {
    uint64_t i = 0;
    uint64_t j;
    while (((Mi * i) % basis) != 1) {
        j = ((Mi * i) % basis);
        i++;
       
    }
    j = ((Mi * i) % basis);
    return i;
 
}




class PSS {
private:
    vector<vector<uint64_t>> matrixPSS;

public:
    void convertSOK_PSS(vector<vector<vector<int>>> matrixInSOK, vector<int> basis) {
        uint64_t multBasis = 1;
        uint64_t Mi;

        // Инициализация matrixPSS с нужным размером
        matrixPSS.assign(matrixInSOK.size(), vector<uint64_t>(matrixInSOK[0].size(), 0));

        // Вычисление произведения оснований
        for (auto bas : basis) {
            multBasis *= bas;
        }
        vector<uint64_t> convertBasis(basis.size());
        try {

            for (int i = 0; i < convertBasis.size(); i++) {
                Mi = multBasis / basis[i];
                convertBasis[i] = Mi;
                convertBasis[i] *= modInverse(Mi, basis[i]);
            }
        }
        catch (const runtime_error& e) {
            cout << e.what() << endl;
        }

        uint64_t convPSS;
     

        // Преобразование матрицы
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


public:
    vector<vector<vector<int>>> matrixSOK;
    vector<int> basis;
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

        cout << "\n";

        PSS kk;
        kk.convertSOK_PSS(matrixSOK, basis);

        cout << "\n";
    }

    
};
class MatrixOperation {
public:
    vector<vector<uint64_t>> matrix;
    SOK matrixInSok;

    // Метод для создания квадратной матрицы с рандомными значениями
    void GeneraitMatrix(uint64_t min, uint64_t max, int size) {
        // Создание матрицы
        matrix.assign(size, vector<uint64_t>(size));
        // Заполнение матрицы случайными значениями
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

        cout << "\nСОК матрицы" << endl;;


        matrixInSok.convertPSS_SOK(matrix, max);
      
    }
    // Метод для cложения матриц
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
    // Метод для умножения матриц
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

        cout << endl;
        return matrixMultiplication;
    }

    // Метод для cложения матриц
    vector<vector<vector<int>>> additionMatrixInSOK(vector<vector<vector<int>>> matriInSok2, int size) {
        int del;
        vector<vector<vector<int>>> AddMatrixSok(matriInSok2.size(), vector<vector<int>>(matriInSok2.size(), vector<int>(matriInSok2[0][0].size(), 0)));
        for (int row = 0; row < matriInSok2.size(); row++) {
            for (int col = 0; col < matriInSok2[row].size(); col++) {
                for (int i = 0; i < matriInSok2[row][col].size(); i++) {
                    AddMatrixSok[row][col][i] = matriInSok2[row][col][i] + matrixInSok.matrixSOK[row][col][i];
                    if (AddMatrixSok[row][col][i] >= matrixInSok.basis[i]) {
                        del = AddMatrixSok[row][col][i] / matrixInSok.basis[i];
                        AddMatrixSok[row][col][i] -= del * matrixInSok.basis[i];
                    }
                }
            }
        }
        for (const auto row : AddMatrixSok) {
            for (const auto col : row) {
                for (const auto i : col) {
                    cout << ((i / 10) == 0 ? " " : "") << i << " ";
                }
                cout << "   ";
            }
            cout << endl;
        }

        PSS psss;
        psss.convertSOK_PSS(AddMatrixSok, prime[0]);

        return AddMatrixSok;
    }

    vector<vector<vector<int>>> MultMatrixInSOK(vector<vector<vector<int>>> matriInSok2, int size) {
        vector<vector<vector<int>>> MultMatrixSok(matriInSok2.size(), vector<vector<int>>(matriInSok2.size(), vector<int>(matriInSok2[0][0].size(), 0)));
        
        int del;
        for (int row = 0; row < matriInSok2.size(); row++) {
            for (int col = 0; col < matriInSok2[row].size(); col++) {
                for (int k = 0; k < matriInSok2[row].size(); k++) {
                    for (int prime = 0; prime < MultMatrixSok[row][col].size(); prime++) {
                        MultMatrixSok[row][col][prime] += matriInSok2[k][col][prime] * matrixInSok.matrixSOK[row][k][prime]; 
                    }
                }
                for (int prime = 0; prime < MultMatrixSok[row][col].size(); prime++) {
                    if (MultMatrixSok[row][col][prime] >= matrixInSok.basis[prime]) {
                        del = MultMatrixSok[row][col][prime] / matrixInSok.basis[prime];
                        MultMatrixSok[row][col][prime] -= del * matrixInSok.basis[prime];
                        //MultMatrixSok[row][col][prime] -= matrixInSok.basis[prime];
                    }
                }
            }
        }

        for (const auto row : MultMatrixSok) {
            for (const auto col : row) {
                for (const auto i : col) {
                    cout << ((i / 10) == 0 ? " " : "") << i << " ";
                }
                cout << "   ";
            }
            cout << endl;
        }

        PSS psss;
        psss.convertSOK_PSS(MultMatrixSok, prime[0]);

        return MultMatrixSok;
    }


};

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    SOK SokMatrix1;
    SOK SokMatrix2;
    SOK SokMatrix3;
   
    MatrixOperation matrix1;
    MatrixOperation matrix2;

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
        cout << "\nВыберите действие:\n1)Сгенерировать матрицы\n2)Сложить матрицы\n3)Перемножить матрицы\n4)Закончить выполнение программы\n";
        cin >> choose;
        while (choose < 1 || choose > 4) {
            cout << "Неверное значение. Повторите выбор.";
            cin >> choose;
        }
        switch (choose)
        {
        case(1): {
            cout << "Введите размер матриц от 0 до 100: ";
            cin >> size;
            while (size < 0 && size > 100) {
                cout << "Введите размер матрицы от 0 до 100: ";
                cin >> size;
            }
            //Mатрица 1
            cout << "Введите диапазон значений генерации случайных чисел для первой матрицы\nmin: ";
            cin >> RandomRangeMin;
            cout << "max: ";
            cin >> RandomRangeMax;

            cout << "Матрица 1"<<endl;
            matrix1.GeneraitMatrix(RandomRangeMin, RandomRangeMax, size);
            
          
            //Mатрица 2
            cout << "Матрица 2"<<endl;
            matrix2.GeneraitMatrix(RandomRangeMin, RandomRangeMax, size);

        

            break;
        }
        case(2): {
            ResultAdd = matrix1.additionMatrix(matrix1.matrix, matrix2.matrix, size);
            matrix1.additionMatrixInSOK(matrix2.matrixInSok.matrixSOK, size);
            break;
        }
        case(3):
            ResultMultiplication = matrix1.multiplicationMatrix(matrix1.matrix,matrix2.matrix, size);
            /*SokMatrix2.convertPPS_SOK(ResultMultiplication, RandomRangeMax);*/
            matrix1.MultMatrixInSOK( matrix2.matrixInSok.matrixSOK, size);

           /* cout << endl;

            SOK yuyu;
            yuyu.convertPSS_SOK(ResultMultiplication, 9);*/

            

            break;
        }
    }



    return 0;
}

