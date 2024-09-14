#include <iostream>
#include <vector>
#include<time.h>

using namespace std;
vector<vector<int>> matrix1;
vector<vector<int>> matrix2;

vector<vector<int>> ResultAdd;
vector<vector<int>> ResultMultiplication;

class MatrixOperation {
public:
    // Метод для создания квадратной матрицы с рандомными значениями

    void createMatrix(vector<vector<int>>& matrix, int min, int max, int size) {
        // Создание матрицы
        matrix.assign(size, vector<int>(size));
        // Заполнение матрицы случайными значениями
        for (auto& row : matrix) {
            for (auto& val : row) {
                val = rand() % (max - min + 1) + min;;
            }
        }
    }
    // Метод для cложения матриц
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
    // Метод для умножения матриц
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

    int size, RandomRangeMin, RandomRangeMax, choose = 0;
    while (choose != 4)
    {
        cout << "Выберите действие:\n1)Сгенерировать матрицы\n2)Сложить матрицы\n3)Перемножить матрицы\n4)Закончить выполнение программы\n";
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
            generator.createMatrix(matrix1, RandomRangeMin, RandomRangeMax, size);


            cout << "Матрица 1\n";
            for (const auto& row : matrix1) {
                for (int val : row) {
                    cout << val << " ";
                }
                cout << endl;
            }
            //Mатрица 2
            cout << "Введите диапазон значений генерации случайных чисел для второй матрицы\nmin: ";
            cin >> RandomRangeMin;
            cout << "max: ";
            cin >> RandomRangeMax;
            generator.createMatrix(matrix2, RandomRangeMin, RandomRangeMax, size);

            cout << "Матрица 2\n";
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

