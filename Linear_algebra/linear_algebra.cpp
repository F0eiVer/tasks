#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void getMinor(double *arr, double *p, int i, int j, int n){
    int di, dj;
    di = 0;
    for(int ki=0; ki<n-1; ++ki){
        if(i == ki)
            di = 1;
        dj = 0;
        for(int kj=0; kj<n-1; ++kj){
            if(j == kj)
                dj = 1;
            p[ki*(n-1) + kj] = arr[(ki+di)*n + kj+dj];
        }
    }
}

double Determinate(double* arr, int n){
    int k=1, m;
    double d=0;
    m = n-1;
    if(n == 1){
        d = arr[0];
    }
    else if(n == 2){
        d = arr[0]*arr[3] - arr[1]*arr[2];
    }
    else{
        double* tmp = new double[m*m];
        for(int i=0; i<n; ++i){
            getMinor(arr, tmp, i, 0, n);
            d += k * arr[i*n] * Determinate(tmp, m);
            k = -k;
        }
        delete[]tmp;
    }
    return d;
}

class Matrix{
private:
    double* arr;
    int lines, columns;
    double det;

public:

    Matrix(int lines, int columns){
        if(lines < 0 || columns < 0){
            this->lines = 0;
            this->columns = 0;
            cout << "you entered incorrect data, so a null matrix was created";
        }
        else{
            if(lines == 0 || columns == 0){
                this->lines = 0;
                this->columns = 0;
            }
            else{
                this->lines = lines;
                this->columns = columns;
                arr = new double[lines*columns];
            }
        }
    }
    Matrix(){
        columns = 0;
        lines = 0;
        det = 0;
        arr = new double[0];
    }
    Matrix(const Matrix &obj){
        columns = obj.columns;
        lines = obj.lines;
        det = obj.det;

        arr = new double[lines*columns];
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                arr[i*columns + j] = obj.arr[i*columns + j];
            }
        }
    }
    ~Matrix(){
        delete[]arr;
    }

    int lines_g(){
        return lines;
    }
    int columns_g(){
        return columns;
    }
    double arr_g(int i, int j){
        if(i*columns + j < lines*columns && i*columns + j >= 0)
            return arr[i*columns + j];
        else{
            cerr << "index out of range";
            return 1./-0;
        }
    }
    void arr_set(double x, int i, int j){
        if(i*columns + j < lines*columns && i*columns + j >= 0)
            arr[i*columns + j] = x;
        else{
            cerr << "index out of range";
        }
    }

    void fill_m(){
        cout << "fill the matrix" << "\n";
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                cin >> arr[i*columns + j];
            }
        }
    }
    void print_m(){
        if(lines == 0 || columns == 0)
            cout << 0;
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                cout << arr[i*columns + j] << " ";
            }
            cout << "\n";
        }
    }

    double det_g(){
        if(lines == columns)
            det = Determinate(arr, lines);
        else{
            det = 1./-0;
        }
        return det;
    }

    void transposition(){
        int tmp;
        tmp = columns;
        columns = lines;
        lines = tmp;
        double* tmp_arr = new double[lines*columns];
        for(int i=0; i<lines*columns; ++i){
            tmp_arr[i] = arr[i];
        }
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                arr[i*columns + j] = tmp_arr[j*tmp + i];
            }
        }
        delete[]tmp_arr;
    }

    Matrix operator = (Matrix m){
        columns = m.columns_g();
        lines = m.lines_g();
        det = m.det_g();
        delete[]arr;

        arr = new double[lines*columns];
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                arr[i*columns + j] = m.arr_g(i, j);
            }
        }
        return *this;
    }

    bool operator == (Matrix m){
        if(this->columns != m.columns_g() || this->lines != m.lines_g())
            return false;
        else{
            for(int i=0; i<this->lines; ++i){
                for(int j=0; j<this->columns; ++j){
                    if(this->arr[i*columns + j] != m.arr_g(i, j))
                        return false;
                }
            }
            return true;
        }
    }

    bool operator != (Matrix m){
        if(this->columns != m.columns_g() || this->lines != m.lines_g())
            return true;
        else{
            for(int i=0; i<this->lines; ++i){
                for(int j=0; j<this->columns; ++j){
                    if(this->arr[i*columns + j] != m.arr_g(i, j))
                        return true;
                }
            }
            return false;
        }
    }

    Matrix operator + (Matrix m){
        if(columns == m.columns_g() && lines == m.lines_g()){
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    m.arr_set(m.arr_g(i, j) + arr[i*columns + j], i, j);
                }
            }
            return m;
        }
        else{
            cerr << "matrix sizes do not match, so you can't sum them";
            return Matrix();
        }
    }

    Matrix operator += (Matrix m){
        if(columns == m.columns_g() && lines == m.lines_g()){
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    arr[i*columns + j] += m.arr_g(i, j);
                }
            }
        }
        else{
            cerr << "matrix sizes do not match, so you can't sum them";
        }
        return *this;
    }

    Matrix operator -= (Matrix m){
        if(columns == m.columns_g() && lines == m.lines_g()){
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    arr[i*columns + j] -= m.arr_g(i, j);
                }
            }
        }
        else{
            cerr << "matrix sizes do not match, so you can't subtract them";
        }
        return *this;
    }

    Matrix operator - (Matrix m){
        if(columns == m.columns_g() && lines == m.lines_g()){
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    m.arr_set(arr[i*columns + j] - m.arr_g(i, j), i, j);
                }
            }
            return m;
        }
        else{
            cerr << "matrix sizes do not match, so you can't sum them";
            return Matrix();
        }
    }

    Matrix operator * (Matrix m){
        if(columns == m.lines_g()){
            Matrix tmp_m(lines, m.columns_g());
            double tmp;
            for(int i=0; i<lines; ++i){
                for(int j=0; j<m.columns_g(); ++j){
                    tmp = 0;
                    for(int k=0; k<columns; ++k){
                        tmp += arr[i*columns + k] * m.arr_g(k, j);
                    }
                    tmp_m.arr_set(tmp, i, j);
                }
            }
            return tmp_m;
        }
        else{
            cerr << "you can't multiply those matrices Because the number" << "\n";
            cerr << "of columns of the first matrix is not equal to the number of lines of the second";
            return Matrix();
        }
    }
    Matrix operator * (double x){
        Matrix tmp_m(lines, columns);
        double tmp;
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                tmp = arr[i*columns + j]*x;
                tmp_m.arr_set(tmp, i,j);
            }
        }
        return tmp_m;
    }

    Matrix operator / (double x){
        Matrix tmp_m(lines, columns);
        double tmp;
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                tmp = arr[i*columns + j]/x;
                tmp_m.arr_set(tmp, i,j);
            }
        }
        return tmp_m;
    }

    Matrix operator *= (Matrix m){
        if(columns == m.lines_g()){
            Matrix tmp_m(lines, m.columns_g());
            double tmp;
            for(int i=0; i<lines; ++i){
                for(int j=0; j<m.columns_g(); ++j){
                    tmp = 0;
                    for(int k=0; k<columns; ++k){
                        tmp += arr[i*columns + k] * m.arr_g(k, j);
                    }
                    tmp_m.arr_set(tmp, i, j);
                }
            }
            lines = tmp_m.lines_g();
            columns = tmp_m.columns_g();
            det = tmp_m.det_g();
            delete[]arr;
            arr = new double[lines*columns];
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    arr[i*columns + j] = tmp_m.arr_g(i, j);
                }
            }
        }
        else{
            cerr << "you can't multiply those matrices Because the number" << "\n";
            cerr << "of columns of the first matrix is not equal to the number of lines of the second ";
        }
        return *this;
    }
    Matrix operator *= (double x){
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                arr[i*columns + j] *= x;
            }
        }
        return *this;
    }
    Matrix operator /= (double x){
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                arr[i*columns + j] /= x;
            }
        }
        return *this;
    }

    Matrix operator ^ (int degree){
        if(columns == lines && degree > 1){
            Matrix m(lines, columns);
            Matrix ans;
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    m.arr_set(arr[i*columns + j], i, j);
                }
            }
            ans = m;
            for(int i=0; i<degree-1; ++i){
                ans = ans*m;
            }
            return ans;
        }
        else{
            cerr << "you can't exponentiate a matrix because it's not a square";
            return Matrix();
        }
    }

};

int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    Matrix A(2, 2);
    Matrix C(2, 2);
    Matrix B;

    fin.close();
    fout.close();
    return 0;
}
