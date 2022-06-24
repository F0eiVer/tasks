#include <iostream>
#include <fstream>
#include <vector>
#pragma pack(1)
#define uc unsigned char
#define ull unsigned long long

using namespace std;

struct Node{
    uc help_b;
    uc value;
};

int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    //input
    vector<uc> in = {0, 0, 0, 0, 0, 0, 4, 2, 0, 4, 4, 4, 4, 4, 4, 4, 80, 80, 80, 80, 0, 2, 2, 2, 2, 255, 255, 255, 255, 255, 0};
    vector<Node> arr;
    vector<uc> ans; // Для декодирования
    Node tmp_n;
    uc tmp;
    tmp_n.help_b = 0;
    // Сжатие
    for(ull i=1; i<(ull)in.size(); ++i){
        tmp = in[i];
        if(in[i-1] == tmp && tmp_n.help_b == 0){
            tmp_n.help_b = 128;
            tmp_n.value = tmp;
        }
        else if(in[i-1] == tmp && tmp_n.help_b < 255){
            tmp_n.help_b++;
        }
        else if(tmp_n.help_b == 255){
            arr.push_back(tmp_n);
            tmp_n.help_b = 0;
        }
        else{
            arr.push_back(tmp_n);
            tmp_n.value = tmp;
            tmp_n.help_b = 0;
        }
    }
    arr.push_back(tmp_n);

    // Результат
    for(ull i=0; i<(ull)arr.size(); ++i){
        if(arr[i].help_b/128)
            cout << (int)arr[i].help_b%128 + 2 << " " << (int)arr[i].value << "\n";
        else
            cout << (int)arr[i].value << "\n";
    }
    cout << "\n" << "----------------------------------------" << "\n\n";

    // Декодирование
    for(ull i=0; i<(ull)arr.size(); ++i){
        if(arr[i].help_b/128){
            for(uc j=0; j<arr[i].help_b%128 + 2; ++j){
                ans.push_back(arr[i].value);
            }
        }
        else{
            ans.push_back(arr[i].value);
        }
    }

    // Вывод ответа
    for(ull i=0; i<(ull)ans.size(); ++i){
        cout << (int)ans[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
