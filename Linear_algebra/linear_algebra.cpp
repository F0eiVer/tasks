#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class Matrix{
private:
    vector<double> arr;
    int lines, columns;
    double det;

    void getMinor(vector<double> &arr, vector<double> &p, int i, int j, int n){
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

    double Determinate(vector<double>& arr, int n){
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
            vector<double> tmp (m*m);
            for(int i=0; i<n; ++i){
                getMinor(arr, tmp, i, 0, n);
                d += k * arr[i*n] * Determinate(tmp, m);
                k = -k;
            }
            tmp.clear();
        }
        return d;
    }

public:

    Matrix(int lines, int columns){
        if(lines < 0 || columns < 0){
            this->lines = 0;
            this->columns = 0;
            cerr << "you entered incorrect data, so a null matrix was created";
        }
        else{
            if(lines == 0 || columns == 0){
                this->lines = 0;
                this->columns = 0;
            }
            else{
                this->lines = lines;
                this->columns = columns;
                arr = vector<double> (lines*columns);
            }
        }

    }
    Matrix(vector<vector<double>> &a){
        if(a.size()>0){
            lines = (int)a.size();
            columns = (int)a[0].size();
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    arr[i*columns + j] =a[i][j];
                }
            }
            countDet();
        }
        else{
            lines = columns = det = 0;
            arr = vector<double> (0);
        }
    }

    Matrix(vector<double> &a, int lines, int columns){
        if(lines < 0 || columns < 0){
            this->lines = 0;
            this->columns = 0;
            cerr << "you entered incorrect data, so a null matrix was created";
        }
        else{
            if(lines == 0 || columns == 0){
                this->lines = 0;
                this->columns = 0;
            }
            else{
                this->lines = lines;
                this->columns = columns;
                arr = vector<double> (lines*columns);
            }
        }
        for(int i=0; i<lines*columns; ++i){
            arr[i] = a[i];
        }
    }

    Matrix(){
        columns = lines = det = 0;
        arr = vector<double> (0);
    }
    Matrix(const Matrix &obj){
        columns = obj.columns;
        lines = obj.lines;
        det = obj.det;

        arr = vector<double> (lines*columns);
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                arr[i*columns + j] = obj.arr[i*columns + j];
            }
        }
    }
    Matrix(Matrix&& obj){
        columns = obj.columnsGet();
        lines = obj.linesGet();
        det = detGet();
        arr = obj.arrGetAll();
        obj.clearM();
    }

    ~Matrix(){
        arr.clear();
    }

    void clearM(){
        lines = 0;
        columns = 0;
        det = 0;
        arr.clear();
    }

    int linesGet() const{
        return lines;
    }
    int columnsGet() const{
        return columns;
    }
    double arrGet(int i, int j) const{
        if(i*columns + j < lines*columns && i*columns + j >= 0)
            return arr[i*columns + j];
        else{
            cerr << "index out of range";
            return 1./-0;
        }
    }
    vector<double> arrGetAll(){
        return arr;
    }
    void arrSet(double x, int i, int j){
        if(i*columns + j < lines*columns && i*columns + j >= 0)
            arr[i*columns + j] = x;
        else{
            cerr << "index out of range";
        }
    }

    void fillM(){
        cout << "fill the matrix" << "\n";
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                cin >> arr[i*columns + j];
            }
        }
    }
    void countDet(){
        if(lines == columns)
            det = this->Determinate(arr, lines);
        else{
            det = 1./-0;
        }
    }
    void printM(){
        if(lines == 0 || columns == 0)
            cout << 0;
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                cout << arr[i*columns + j] << " ";
            }
            cout << "\n";
        }
    }

    double detGet() const{
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

    Matrix operator = (const Matrix& m){
        columns = m.columnsGet();
        lines = m.linesGet();
        det = m.detGet();
        arr.clear();

        arr = vector<double> (lines*columns);
        for(int i=0; i<lines; ++i){
            for(int j=0; j<columns; ++j){
                arr[i*columns + j] = m.arrGet(i, j);
            }
        }
        return *this;
    }

    Matrix operator = (Matrix&& m){
        if(this != &m){
            arr.clear();
            arr = m.arrGetAll();
            lines = m.linesGet();
            columns = m.columnsGet();
            det = m.detGet();
            m.clearM();
        }

        return *this;
    }

    bool operator == (const Matrix& m){
        if(this->columns != m.columnsGet() || this->lines != m.linesGet())
            return false;
        else{
            for(int i=0; i<this->lines; ++i){
                for(int j=0; j<this->columns; ++j){
                    if(this->arr[i*columns + j] != m.arrGet(i, j))
                        return false;
                }
            }
            return true;
        }
    }

    bool operator != (const Matrix& m){
        if(this->columns != m.columnsGet() || this->lines != m.linesGet())
            return true;
        else{
            for(int i=0; i<this->lines; ++i){
                for(int j=0; j<this->columns; ++j){
                    if(this->arr[i*columns + j] != m.arrGet(i, j))
                        return true;
                }
            }
            return false;
        }
    }

    Matrix operator + (Matrix& m){
        if(columns == m.columnsGet() && lines == m.linesGet()){
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    m.arrSet(m.arrGet(i, j) + arr[i*columns + j], i, j);
                }
            }
            return m;
        }
        else{
            cerr << "matrix sizes do not match, so you can't sum them";
            return Matrix();
        }
    }

    Matrix operator += (const Matrix& m){
        if(columns == m.columnsGet() && lines == m.linesGet()){
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    arr[i*columns + j] += m.arrGet(i, j);
                }
            }
        }
        else{
            cerr << "matrix sizes do not match, so you can't sum them";
        }
        return *this;
    }

    Matrix operator -= (const Matrix& m){
        if(columns == m.columnsGet() && lines == m.linesGet()){
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    arr[i*columns + j] -= m.arrGet(i, j);
                }
            }
        }
        else{
            cerr << "matrix sizes do not match, so you can't subtract them";
        }
        return *this;
    }

    Matrix operator - (Matrix& m){
        if(columns == m.columnsGet() && lines == m.linesGet()){
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    m.arrSet(arr[i*columns + j] - m.arrGet(i, j), i, j);
                }
            }
            return m;
        }
        else{
            cerr << "matrix sizes do not match, so you can't sum them";
            return Matrix();
        }
    }

    Matrix operator * (const Matrix& m){
        if(columns == m.linesGet()){
            Matrix tmp_m(lines, m.columnsGet());
            double tmp;
            for(int i=0; i<lines; ++i){
                for(int j=0; j<m.columnsGet(); ++j){
                    tmp = 0;
                    for(int k=0; k<columns; ++k){
                        tmp += arr[i*columns + k] * m.arrGet(k, j);
                    }
                    tmp_m.arrSet(tmp, i, j);
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
                tmp_m.arrSet(tmp, i,j);
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
                tmp_m.arrSet(tmp, i,j);
            }
        }
        return tmp_m;
    }

    Matrix operator *= (const Matrix& m){
        if(columns == m.linesGet()){
            Matrix tmp_m(lines, m.columnsGet());
            double tmp;
            for(int i=0; i<lines; ++i){
                for(int j=0; j<m.columnsGet(); ++j){
                    tmp = 0;
                    for(int k=0; k<columns; ++k){
                        tmp += arr[i*columns + k] * m.arrGet(k, j);
                    }
                    tmp_m.arrSet(tmp, i, j);
                }
            }
            lines = tmp_m.linesGet();
            columns = tmp_m.columnsGet();
            det = tmp_m.detGet();
            arr.clear();
            arr = vector<double> (lines*columns);
            for(int i=0; i<lines; ++i){
                for(int j=0; j<columns; ++j){
                    arr[i*columns + j] = tmp_m.arrGet(i, j);
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
                    m.arrSet(arr[i*columns + j], i, j);
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

ostream& operator << (ostream &os, Matrix &m){
    if(m.linesGet() == 0 || m.columnsGet() == 0)
        os << 0;
    for(int i=0; i<m.linesGet(); ++i){
        for(int j=0; j<m.columnsGet(); ++j){
            os << m.arrGet(i, j)<< " ";
        }
        os << "\n";
        }
    return os;
}

istream& operator >> (istream &is, Matrix &m){
    double tmp;
    for(int i=0; i<m.linesGet(); ++i){
        for(int j=0; j<m.columnsGet(); ++j){
            is >> tmp;
            m.arrSet(tmp, i, j);
        }
    }
    return is;
}


int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");


    fin.close();
    fout.close();
    return 0;
}
