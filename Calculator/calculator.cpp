#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#define ull unsigned long long

using namespace std;

struct Op{
    string op;
    char priority;
};

struct Stack_op{
    ull siz=0;
    vector<Op> arr;

    void push(Op x){
        arr.push_back(x);
        siz++;
    }

    void pop(){
        siz--;
        arr.pop_back();
    }

    Op top(){
        return arr[siz-1];
    }
};

struct Stack_nums{
    ull siz=0;
    vector<double> arr;

    void push(double x){
        arr.push_back(x);
        siz++;
    }

    void pop(){
        siz--;
        arr.pop_back();
    }

    double top(){
        return arr[siz-1];
    }
};

struct Stack{
    ull siz=0;
    vector<char> arr;

    void push(char x){
        arr.push_back(x);
        siz++;
    }

    void pop(){
        siz--;
        arr.pop_back();
    }

    char top(){
        return arr[siz-1];
    }
};

//Correct bracket sequence
bool CBS(string str){
    Stack st;
    for(ull i=0; i<(ull)str.size(); ++i){
        if(str[i] == '(')
            st.push(str[i]);
        else if(str[i] == ')'){
            if(!st.siz)
                return false;
            st.pop();
        }
    }
    if(!st.siz)
        return true;
    return false;
}

bool Correctness(string str){
    int f=0;
    if((int)str[0] > 47 && (int)str[0] < 58 && (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '^' || str[0] == '/'))
        f = 1;
    for(ull i=1; i<(ull)str.size(); ++i){
        if((int)str[i] > 47 && (int)str[i] < 58 && (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '^' || str[i] == '/'))
            f = 1;
        if((((int)str[i-1] > 47 && (int)str[i-1] < 58) || (str[i-1] == ')')) && (((int)str[i] > 64 && (int)str[i] < 91) || ((int)str[i] > 96 && (int)str[i] < 123)))
            return false;
        if((str[i-1] == ')') && ((int)str[i] > 47 && (int)str[i] < 58))
            return false;
        if((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '^' || str[i] == '/') && (str[i-1] == '+' || str[i-1] == '-' || str[i-1] == '*' || str[i-1] == '^' || str[i-1] == '/'))
            return false;
        if((str[i-1] == '(') && (str[i] == ')'))
            return false;

    }
    if(f)
        return true;
    return false;
}


int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string exp, tmp_str, tmpC;
    int f = 0, p = 1, k = 1, b = 0;
    Op tmpOp;
    vector<string> functions = {"sin", "cos", "tan", "sqrt"};
    double tmp = 0., tmp1, tmp2, tmpDif = 10., sign = 1;
    Stack_nums nums;
    Stack_op oper;
    cout << " Enter the expression\n";
    cout << " Write 'stop' to calculate it\n";
    cout << " Write 'end' to finish working\n";
    while(1){
        do{
            cin >> tmp_str;
            if(tmp_str == "end")
                break;
            exp += tmp_str;
        }
        while(cin.get() != '\n');

        if(!CBS(exp)){
            cerr << "incorrect input. Wrong bracket sequence\n";
            cout << "----------------------------------------" << "\n";
            tmp_str = exp = "";
            continue;
        }

        if(!Correctness(exp)){
            cerr << "incorrect input\n";
            cout << "----------------------------------------" << "\n";
            tmp_str = exp = "";
            continue;
        }

        for(int i=0; i<(int)exp.size(); ++i){

            if((int)exp[i] > 47 && (int)exp[i] < 58){
                p = 0;
                if(!f){
                    tmp *= 10;
                    tmp += (double)((int)exp[i] - 48);
                }
                else{
                    tmp += ((double)((int)exp[i] - 48))/tmpDif;
                    tmpDif *= 10;
                }
            }
            else if(f == 1 && exp[i] == '.'){
                cerr << "You have written incorrect data\n";
                p = 1;
                while(nums.siz){
                    nums.pop();
                }
                while(oper.siz){
                    oper.pop();
                }
                break;

            }
            else if(exp[i] == '.'){
                f = 1;
            }
            else if(exp[i] == ','){
                if(!p){
                    nums.push(tmp);
                    p = 1;
                }
                tmp = 0.;
                f = 0;
                tmpDif = 10.;
                continue;
            }
            else if((!nums.siz || (i>0 && (exp[i-1] == '('))) && p && exp[i] == '-'){
                sign = -sign;
                b = abs(b-1);

            }
            else if((!nums.siz || (i>0 && (exp[i-1] == '('))) && p && exp[i] == '+'){
                cerr << "incorrect input\n";
                p = 1;
                while(nums.siz){
                    nums.pop();
                }
                while(oper.siz){
                    oper.pop();
                }
                sign = 1; p = 1; f = 0; tmpDif = 10.; k = 1;
                tmp_str = exp = "";
                break;
            }
            else{
                if(!p){
                    nums.push(tmp);
                    p = 1;
                }
                tmp = 0.;
                f = 0;
                tmpDif = 10.;

                tmpOp.op = "";
                tmpOp.op += exp[i];
                if(exp[i] == '+' || exp[i] == '-')
                    tmpOp.priority = 1;
                else if(exp[i] == '*' || exp[i] == '/')
                    tmpOp.priority = 2;
                else if(exp[i] == '^')
                    tmpOp.priority = 3;
                else if(exp[i] == '('){
                    tmpOp.priority = 4;
                }
                else if(((int)exp[i] > 64 && (int)exp[i] < 91) || ((int)exp[i] > 96 && (int)exp[i] < 123)){
                    tmpOp.priority = 5;
                    i++; k = 1;
                    while(exp[i] != '(' && i < (int)exp.size())
                        tmpOp.op += exp[i++];
                    i--;
                    for(int i=0; i<(int)functions.size(); ++i){
                        if(tmpOp.op == functions[i])
                            k = 0;
                    }
                    if(k){
                        cerr << "unknown function: " << tmpOp.op << "\n";
                        p = 1;
                        while(nums.siz){
                            nums.pop();
                        }
                        while(oper.siz){
                            oper.pop();
                        }
                        break;
                    }
                }

                if(exp[i] == ')'){
                    if(oper.siz){

                        while(1){
                            if(!oper.siz)
                                break;
                            tmpC = oper.top().op; oper.pop();
                            if(tmpC[0] == '(' && oper.siz && (oper.top().op == "sin" || oper.top().op == "sqrt" || oper.top().op == "cos" || oper.top().op == "tan")){
                                if(oper.top().op == "sin"){
                                    tmp1 = nums.top(); nums.pop();
                                    nums.push(sign * sin(tmp1));
                                }
                                else if(oper.top().op == "cos"){
                                    tmp1 = nums.top(); nums.pop();
                                    nums.push(sign * cos(tmp1));
                                }
                                else if(oper.top().op == "tan"){
                                    tmp1 = nums.top(); nums.pop();
                                    nums.push(sign * tan(tmp1));
                                }
                                else if(oper.top().op == "sqrt"){
                                    tmp2 = nums.top(); nums.pop();
                                    tmp1 = nums.top(); nums.pop();
                                    nums.push(sign * pow(tmp1, 1./tmp2));
                                }
                                oper.pop();
                                break;
                            }
                            else if(tmpC[0] == '('){
                                if(b){
                                    tmp1 = nums.top(); nums.pop();
                                    tmp1 *= sign;
                                    nums.push(tmp1);
                                    sign *= -1;
                                    b = abs(b-1);
                                }
                                break;
                            }
                            tmp2 = nums.top(); nums.pop();
                            tmp1 = nums.top(); nums.pop();
                            if(tmpC[0] == '*'){
                                nums.push(tmp1*tmp2);
                            }
                            else if(tmpC[0] == '/'){
                                nums.push(tmp1/tmp2);
                            }
                            else if(tmpC[0] == '^'){
                                nums.push(pow(tmp1, tmp2));
                            }
                            else if(tmpC[0] == '-'){
                                nums.push(tmp1-tmp2);
                            }
                            else{
                                nums.push(tmp1+tmp2);
                            }
                        }
                    }
                }
                else if((!oper.siz || (tmpOp.priority > oper.top().priority) || oper.top().op[0] == '(' || tmpOp.priority == 4)){
                    oper.push(tmpOp);
                }
                else{
                    tmpC = oper.top().op; oper.pop();
                    tmp2 = nums.top(); nums.pop();
                    tmp1 = nums.top(); nums.pop();
                    if(tmpC[0] == '*'){
                        nums.push(tmp1*tmp2);
                    }
                    else if(tmpC[0] == '/'){
                        nums.push(tmp1/tmp2);
                    }
                    else if(tmpC[0] == '^'){
                        nums.push(pow(tmp1, tmp2));
                    }
                    else if(tmpC[0] == '-'){
                        nums.push(tmp1-tmp2);
                    }
                    else{
                        nums.push(tmp1+tmp2);
                    }
                    i--;
                }
            }
        }
        if(!p){
            nums.push(tmp);
        }

        if((oper.siz || sign < 0) && !nums.siz){
            cerr << "incorrect input\n";
            cout << "----------------------------------------" << "\n";
            while(nums.siz){
                nums.pop();
            }
            while(oper.siz){
                oper.pop();
            }
            tmp_str = exp = "";
            sign = 1; p = 1; f = 0; tmpDif = 10.; k = 1; b = 0;
            continue;
        }

        while(oper.siz){
            tmpC = oper.top().op; oper.pop();
            if(tmpC == "sin" || tmpC == "cos" || tmpC == "tan" ){
                tmp1 = nums.top(); nums.pop();
            }
            else{
                tmp2 = nums.top(); nums.pop();
                tmp1 = nums.top(); nums.pop();
            }
            if(tmpC == "sin"){
                nums.push(sign * sin(tmp1));
            }
            else if(tmpC == "cos"){
                nums.push(sign * cos(tmp1));
            }
            else if(tmpC == "tan"){
                nums.push(sign * tan(tmp1));
            }
            else if(tmpC == "sqrt"){
                nums.push(sign * pow(tmp1, 1./tmp2));
            }
            else if(tmpC[0] == '*'){
                nums.push(tmp1*tmp2);
            }
            else if(tmpC[0] == '/'){
                nums.push(tmp1/tmp2);
            }
            else if(tmpC[0] == '^'){
                nums.push(pow(tmp1, tmp2));
            }
            else if(tmpC[0] == '-'){
                nums.push(tmp1-tmp2);
            }
            else if(tmpC[0] == '+'){
                nums.push(tmp1+tmp2);
            }

        }
        if(nums.siz)
            cout << nums.top() << "\n";
        cout << "----------------------------------------" << "\n";
        while(nums.siz){
            nums.pop();
        }
        while(oper.siz){
            oper.pop();
        }
        tmp_str = exp = "";
        sign = 1; p = 1; f = 0; tmpDif = 10.; k = 1; tmp = 0.; b = 0;

    }

    fin.close();
    fout.close();
    return 0;
}
