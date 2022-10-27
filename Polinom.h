#pragma once

class Polinom{
    private: 
        int n;
        int **a;
    public:
        Polinom(void);
        Polinom(int, int**);
        void sort();
        void same();
        Polinom operator+(Polinom);
        Polinom operator-(Polinom);
        Polinom operator*(Polinom);
        Polinom operator*(int);
        Polinom operator=(Polinom);
        bool operator==(Polinom);
        void reset();
        void show();
        ~Polinom(void);
};