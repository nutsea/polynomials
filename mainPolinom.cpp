#include "Polinom.h"
#include <iostream>
#include <cmath>
using namespace std;

int main(){
    Polinom Zero;
    int n, m;
    cout << "Размерность первого полинома: ";
    cin >> n;
    int **a = new int *[n];
    for (int i = 0; i < n; i++) a[i] = new int[2];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 2; j++){
            cin >> a[i][j];
            while (a[i][1] > 5){
                cout << "Максимальная степень 5. Введите другое значение: ";
                cin >> a[i][j];
            }
        }
    }
    cout << endl;
    Polinom First(n, a);
    First.same();

    cout << "Размерность второго полинома: ";
    cin >> m;
    int **b = new int *[m];
    for (int i = 0; i < m; i++) b[i] = new int[2];
    for (int i = 0; i < m; i++){
        for (int j = 0; j < 2; j++){
            cin >> b[i][j];
            while (b[i][1] > 5){
                cout << "Максимальная степень 5. Введите другое значение: ";
                cin >> b[i][j];
            }
        }
    }
    cout << endl;
    Polinom Second(m, b);
    Second.same();

    cout << "Первый полином: ";
    First.show();
    cout << "Второй полином: ";
    Second.show();
    if (First == Second) cout << "Эти полиномы равны\n\n";
    else cout << "Эти полиномы не равны\n\n";

    Polinom Result;

    int p, k;
    cout << "Номер полинома: ";
    cin >> p;
    cout << "На какое число умножить: ";
    cin >> k;
    while (p != 1 && p != 2){
        cout << "Выберите существующий полином: ";
        cin >> p;
    }

    Result = First + Second;
    cout << "\nСложение: ";
    Result.show();
    Result.reset();

    cout << "Вычитание: ";
    if (!(First == Second)){
        Result = First - Second;
        Result.show();
        Result.reset();
    }
    else cout << 0 << "\n\n1";

    Result = First * Second;
    cout << "Умножение двух полиномов: ";
    Result.show();
    Result.reset();

    switch (p){
    case 1:
        cout << "Умножение первого полинома на число " << k << ": ";
        if (k != 0){
            Result = First * k;
            Result.show();
        }
        else cout << 0 << "\n\n";
        break;
    case 2: 
        cout << "Умножение второго полинома на число " << k << ": ";
        if (k != 0){
            Result = Second * k;
            Result.show();
        }
        else cout << 0 << "\n\n";
        break;
    }
}