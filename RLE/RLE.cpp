#include <iostream>
#include <fstream>
#include <string>
#define ull unsigned long long

using namespace std;

int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string str, ans;
    ull num = 1;
    char tmp;
    fin >> str;
    ans.push_back(str[0]);
    tmp = str[0];

    // Кодирование
    for(ull i=1; i<(ull)str.size(); ++i){

        if(tmp == str[i]){
            num++;
        }
        else{
            ans = ans + to_string(num);
            num = 1;
            ans.push_back(str[i]);
            tmp = str[i];
        }
    }
    if(num > 1){
        ans += to_string(num);
    }
    num = 0;
    str = string("");
    // Вывод ответа
    cout << ans << "\n";


    //Декодирование
    for(ull i=0; i<(ull)ans.size(); ++i){
        if((int)ans[i] < 48 || (int)ans[i] > 57){
            while(num){
                str.push_back(tmp);
                num--;
            }
            tmp = ans[i];
        }
        else{
            if(!num)
                num = (int)ans[i] - 48;
            else{
                num *= 10;
                num += (int)ans[i] - 48;
            }
        }
    }

    if(num){
        while(num){
            str.push_back(tmp);
            num--;
        }
    }

    //Изначальные данные
    cout << str;

    fin.close();
    fout.close();
    return 0;
}
