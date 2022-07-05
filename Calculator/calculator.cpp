#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#define ull unsigned long long

using namespace std;

struct Op{
    char op;
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


int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string exp, tmp_str;
    int f = 0, p = 0;
    Op tmpOp;
    char tmpC;
    double tmp = 0., tmp1, tmp2, tmpDif = 10., sign = 1;
    Stack_nums nums;
    Stack_op oper;
    fin >> tmp_str;
    exp = tmp_str;
    while(fin >> tmp_str){
        exp += tmp_str;
    }
    //cout << exp << "\n";

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
        else if(exp[i] == '.'){
            f = 1;
        }
        else{
            if(!p){
                nums.push(tmp*sign);
                p = 1;
            }
            sign = 1.;
            tmp = 0.;
            f = 0;
            tmpDif = 10.;

            if(exp[i] == '-'){
                if(!nums.siz || (i>0 && (exp[i-1] == '(')))
                    sign = -sign;
            }

            tmpOp.op = exp[i];
            if(exp[i] == '+' || exp[i] == '-')
                tmpOp.priority = 1;
            else if(exp[i] == '*' || exp[i] == '/')
                tmpOp.priority = 2;
            else if(exp[i] == '^')
                tmpOp.priority = 3;
            else if(exp[i] == '(' || exp[i] == 'c' || exp[i] == 't'){
                if(exp[i] == 'c')
                    i += 2;
                else if(exp[i] == 't')
                    i++;
                tmpOp.priority = 100;
            }
            else if(exp[i] == 's' && exp[i+1] == 'i'){
                i += 2;
                tmpOp.priority = 100;
                tmpOp.op = 'S';
            }
            else if(exp[i] == 's'){
                i += 3;
                tmpOp.priority = 100;
            }

            if(exp[i] == ')'){
                while(1){
                    tmpC = oper.top().op; oper.pop();
                    if(tmpC == '(' && (oper.top().op == 's' || oper.top().op == 'S' || oper.top().op == 'c' || oper.top().op == 't')){
                        if(oper.top().op == 'S'){
                            tmp1 = nums.top(); nums.pop();
                            nums.push(sin(tmp1));
                        }
                        else if(oper.top().op == 'c'){
                            tmp1 = nums.top(); nums.pop();
                            nums.push(cos(tmp1));
                        }
                        else if(oper.top().op == 't'){
                            tmp1 = nums.top(); nums.pop();
                            nums.push(tan(tmp1));
                        }
                        else{
                            tmp2 = nums.top(); nums.pop();
                            tmp1 = nums.top(); nums.pop();
                            nums.push(pow(tmp1, 1/tmp2));
                        }
                        oper.pop();
                        break;
                    }
                    else if(tmpC == '(')
                        break;
                    tmp2 = nums.top(); nums.pop();
                    tmp1 = nums.top(); nums.pop();
                    if(tmpC == '*'){
                        nums.push(tmp1*tmp2);
                    }
                    else if(tmpC == '/'){
                        nums.push(tmp1/tmp2);
                    }
                    else if(tmpC == '^'){
                        nums.push(pow(tmp1, tmp2));
                    }
                    else if(tmpC == '-'){
                        nums.push(tmp1-tmp2);
                    }
                    else{
                        nums.push(tmp1+tmp2);
                    }
                }
            }
            else if(sign > 0 && (!oper.siz || tmpOp.priority > oper.top().priority || oper.top().op == '(' \
                                 || oper.top().op == 's' || oper.top().op == 'S' || oper.top().op == 'c' || oper.top().op == 't')){
                oper.push(tmpOp);
            }
            else if(sign > 0){
                tmpC = oper.top().op; oper.pop();
                tmp2 = nums.top(); nums.pop();
                tmp1 = nums.top(); nums.pop();
                if(tmpC == '*'){
                    nums.push(tmp1*tmp2);
                }
                else if(tmpC == '/'){
                    nums.push(tmp1/tmp2);
                }
                else if(tmpC == '^'){
                    nums.push(pow(tmp1, tmp2));
                }
                else if(tmpC == '-'){
                    nums.push(tmp1-tmp2);
                }
                else{
                    nums.push(tmp1+tmp2);
                }
                i--;
            }
        }
        cout << nums.top() << "\n";
    }

    if(tmp){
        nums.push(tmp*sign);
    }
    while(oper.siz){
        tmpC = oper.top().op; oper.pop();
        if(tmpC == 'S' || tmpC == 'c' || tmpC == 't'){
            tmp1 = nums.top(); nums.pop();
        }
        else{
            tmp2 = nums.top(); nums.pop();
            tmp1 = nums.top(); nums.pop();
        }
        if(tmpC == 'S'){
            nums.push(sin(tmp1));
        }
        else if(tmpC == 'c'){
            nums.push(cos(tmp1));
        }
        else if(tmpC == 't'){
            nums.push(tan(tmp1));
        }
        else if(tmpC == '*'){
            nums.push(tmp1*tmp2);
        }
        else if(tmpC == '/'){
            nums.push(tmp1/tmp2);
        }
        else if(tmpC == '^'){
            nums.push(pow(tmp1, tmp2));
        }
        else if(tmpC == '-'){
            nums.push(tmp1-tmp2);
        }
        else if(tmpC == '+'){
            nums.push(tmp1+tmp2);
        }
        else{
            nums.push(pow(tmp1, 1/tmp2));
        }
    }

    cout << nums.top() << " ";


    fin.close();
    fout.close();
    return 0;
}
