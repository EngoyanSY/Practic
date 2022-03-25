#include "plant.h"

//#include <discpp.h>

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
using std::vector;

int
main() {
    // Инициализация ОУ.
    Plant plant;
    plant_init(plant);


    //Ввод исходных данных
    int K, L, N;

    cout << "Number of sensors: "; //Кол-во датчиков
    cin >> K;

    cout << "Nomber of surveys: "; //Число опросов каждого датчика в серии
    cin >> L;

    cout << "Nomber of series: "; //Число серий
    cin >> N;

    vector<int>M(K);              //Массив номеров датчиков
    vector<double>R(K);           //Массив граничных значений для датчиков

    cout << "\n\tSensors:\n";     
    for (size_t i = 0; i < K; i++)
    {
        cout << "M" << i+1 << " = ";
        cin >> M[i];
    }

    cout << "\n\tLimit value:\n";  
    for (size_t i = 0; i < K; i++)
    {
        cout << "R" << i+1 << " = ";
        cin >> R[i];
    }
    cout << "\n";

    //Вывод исходных данных
    for (size_t i = 0; i < K; i++)
    {
        cout << "Sensor M" << i+1 << ": " << M[i] << "\tLimit: " << R[i] << "\n";
    }
    cout << "\n";

    //Снятие измерений
    vector<double>X(L); //Массив измерений для датчика
    vector<int>Er(K);   //Массив кол-ва нарушений для каждого датчика

    for (size_t n = 1; n <= N; n++)
    {
        cout << "Series: " << n << "\n";
        for (size_t i = 0; i < K; i++)
        {
            
            for (size_t j = 0; j < L; j++)
            {
                X[j] = plant_measure(M[i], plant);
            }

            auto xmax = X[0];
            auto xmin = X[0];

            for (size_t j = 0; j < L; j++)
            {
                if (X[j] > xmax)
                    xmax = X[j];

                else if (X[j] < xmin)
                    xmin = X[j];
            }

            if (xmax - xmin >= R[i])
            {
                cout << "  Sensor: M" << i+1 << "\t" << xmax - xmin << "\n";
                Er[i]++;
            }
                
        }
        cout << "\n";
    }

    //Вывод кол-ва нарушений
    cout << "\nNumber of violations:\n";
    for (size_t i = 0; i < K; i++)
        cout << "  Sensor M" << i+1 << ": " << Er[i] << "\n";
}
