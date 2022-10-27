#include "Polinom.h"
#include <iostream>
#include <cmath>
using namespace std;

Polinom::Polinom(void){

}

Polinom::Polinom(int n, int **a){
    this -> n = n;
    this -> a = new int *[n];
    for (int i = 0; i < n; i++) 
        this -> a[i] = new int[2];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 2; j++)
            this -> a[i][j] = a[i][j];
    }
}

Polinom::~Polinom(void){

}

void Polinom::sort(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (a[i][1] > a[j][1]){
                swap(a[i][1], a[j][1]);
                swap(a[i][0], a[j][0]);
            }
        }
    }
}

void Polinom::same(){
    sort();
    int t = 1; //счетчик размерности результата
    for (int i = 0; i < n - 1; i++){ //количество разных степеней
        if (a[i][1] != a[i + 1][1])
        t++;
    }
    int* index = new int[t]; //создание массива размерности количества степеней
    int h = 0; //переменная, хранащая индекс
    int k = 0; //переменная, хранящая индекс
    for (int i = 0; i < t - 1; i++){ //прохождение по полиному до (t - 1) элемента
        while (a[h][1] == a[h + 1][1]){ //пока есть подобные слагаемые
            a[k][0] += a[h + 1][0]; //сложение подобных слагаемых
            h++; //переход к следующему индексу
        }
        index[i] = k; //индекс элемента, который возьмем
        k = h + 1; //переход к следующей строке
        h = k; //индекс следующей строки
    }
    if (h != (n - 1)){ //если индекс не принадлежит последнему элементу
        for (int i = h; i < n - 1; i++){ //прохождение по полиному, начиная с этого индекса
            a[k][0] += a[i + 1][0]; //сложение всех элементы после этого индекса
            index[t - 1] = k; //индекс в последний элемент массива
        }
    }
    else{
        index[t - 1] = k; //индекс в последний элемент массива
    }
    for (int i = 0; i < t; i++){
        for (int j = 0; j < 2; j++)
            a[i][j] = a[index[i]][j]; //запись нужных элементов
    }
    for (int i = t; i < n; i++){
        delete a[i]; //удаление элементов, равных 0
    }
    n = t; //новая размерность полинома
}

Polinom Polinom::operator+(Polinom P){
    int **res = new int *[n + P.n];
    for (int i = 0; i < n + P.n; i++) res[i] = new int[2];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 2; j++)
            res[i][j] = a[i][j]; //добавление первого полинома
    }
    for (int i = n; i < n + P.n; i++){
        for (int j = 0; j < 2; j++)
            res[i][j] = P.a[i - n][j]; //добавление второго полинома
    }
    Polinom temp(n + P.n, res);
    temp.same();
    return temp;
}

Polinom Polinom::operator-(Polinom P){
    int **res = new int *[n + P.n];
    for (int i = 0; i < n + P.n; i++) res[i] = new int[2];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 2; j++)
            res[i][j] = a[i][j]; //добавление первого полинома
    }
    for (int i = n; i < n + P.n; i++){
        res[i][0] = -P.a[i - n][0]; //добавление элементов второго полинома с противоположным знаком
        res[i][1] = P.a[i - n][1]; //добавление степеней
    }
    Polinom temp(n + P.n, res);
    temp.same();
    return temp;
}

Polinom Polinom::operator*(Polinom P){
    int t = n * P.n;
    int **res = new int *[t];
    for (int i = 0; i < t; i++) res[i] = new int[1];
    int k = 0; //индекс строки матрицы результата
    for (int i = 0; i < n; i++){
        for (int j = 0; j < P.n; j++){
            res[k][0] = a[i][0] * P.a[j][0]; //умножение коэффициентов
            res[k][1] = a[i][1] + P.a[j][1]; //сложение степеней
            k++;
        }
    }
    Polinom temp(t, res);
    temp.same();
    return temp;
}

Polinom Polinom::operator*(int k){ //умножение полинома на число
    int **res = new int *[n];
    for (int i = 0; i < n; i++) res[i] = new int[2];
    for (int i = 0; i < n; i++){
        res[i][0] = k * a[i][0]; //умножаем коэффициент на число
        res[i][1] = a[i][1]; //записываем степень
    }
    Polinom temp(n, res);
    temp.same();
    return temp;
}

Polinom Polinom::operator=(Polinom P){
    n = P.n;
    a = P.a;
    return *this;
}

bool Polinom::operator==(Polinom P){
    bool t = true;
    if (n == P.n){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < 2; j++){
                if (a[i][j] != P.a[i][j]) t = false; //если элементы не равны, полиномы не равны
            }
        }
    }
    else t = false;
    return t;
}

void Polinom::reset(){
    for (int i = 0; i < n; i++)
    delete[] a[i];
}

void Polinom::show(){
    bool t = false;
    if (a[0][0] != 0){ //элемент = 0 не выводим
        t = true; //полином не нулевой
        if (a[0][0] > 0){
            if (a[0][0] != 1) cout << a[0][0]; //коэффициент = 1 не выводим
            cout << "x";
            if (a[0][1] != 1) cout << "^" << a[0][1]; //степень = 1 не выводим
        }
        else{
            if (a[0][0] != -1) cout << "- " << abs(a[0][0]); //коэффициент = -1 не выводим
            cout << "x";
            if (a[0][1] != 1) cout << "^" << a[0][1]; //степень = 1 не выводим
        }
    }
    for (int i = 1; i < n; i++){
        if (a[i][0] != 0){
            t = true;
            if (a[i][0] > 0){
                if (t) cout << " + ";
                if (a[i][0] != 1) cout << a[i][0];
                cout << "x"; 
                if (a[i][1] != 1) cout << "^" << a[i][1];
            }
            else{
                cout << " - ";
                if (a[i][0] != -1) cout << abs(a[i][0]);
                cout << "x";
                if (a[i][1] != 1) cout << "^" << a[i][1];
            }
        }
    }
    if (!t) cout << 0; //если полином нулевой
    cout << "\n\n";
}