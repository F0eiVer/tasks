#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void print_state(vector< vector<int> >& arr){
    for(int i=0; i<3; ++i){
        for(int j=0; j<(int)arr[i].size(); ++j){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "------------------------" << "\n";
}

void hanoi(vector< vector<int> >& arr, int n, int s, int f){
    if(n == 1){
        arr[f-1].push_back(arr[s-1][arr[s-1].size()-1]);
        arr[s-1].pop_back();
        print_state(arr);
    }
    else{
        int tmp = 6-s-f;
        hanoi(arr, n-1, s, tmp);
        arr[f-1].push_back(arr[s-1][arr[s-1].size()-1]);
        arr[s-1].pop_back();
        print_state(arr);
        hanoi(arr, n-1, tmp, f);
    }

}

int main(){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, start, finish;
    fin >> n >> start >> finish;
    vector< vector<int> > arr (3);
    for(int i=n; i>0; --i){
        arr[start-1].push_back(i);
    }

    hanoi(arr, n, start, finish);

    fin.close();
    fout.close();
    return 0;
}
