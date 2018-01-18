#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

bool belongsto(string * cuv, int length, string word, int * position) {
    for(int i = 0; i < length; i++) {
        if(cuv[i] == word) {
            (*position) = i;
            return true;
        }
    }
    return false;
}

int main() {
    ifstream t;
    int length;
    t.open("input.txt");
    t.seekg(0, ios::end);
    length = t.tellg();
    t.seekg(0, ios::beg);
    char * buffer = new char[length];
    t.read(buffer, length);
    t.close();
    string cuv[length];
    int nrcuv = 0, frecv[length];
    for(int i = 0; i < length; i++) {
        while(buffer[i] == ' ' && buffer[i] != NULL) i++;
        string word = "";
        while(buffer[i] != ' ' && buffer[i] != NULL) {
            word.append(1, buffer[i]);
            i++;
        }
        int pos;
        if(!belongsto(cuv, nrcuv, word, &pos)) {
            cuv[nrcuv] = word;
            frecv[nrcuv] = 1;
            nrcuv++;
        } else {
            frecv[pos]++;
        }
    }
    for(int i = 0; i < nrcuv - 1; i++) {
        if(frecv[i] < frecv[i+1]) {
            for(int j = i+1; j > 0; j--) {
                if(frecv[j] > frecv[j - 1]) {
                    swap(frecv[j], frecv[j - 1]);
                    swap(cuv[j], cuv[j - 1]);
                }
            }
        }
    }
    fstream f;
    f.open("output.txt", ios::out);
    for(int i = 0; i < nrcuv; i++) {
        f << cuv[i] << " " << frecv[i] << endl;
    }
    return 0;
}
