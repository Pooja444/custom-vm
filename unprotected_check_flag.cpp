#include <bits/stdc++.h>

using namespace std;

int main() {
    char* input = (char *)malloc(100);
    cout << endl << "************************************************** Welcome to my flag checker program! **************************************************" << endl;
    cout << endl;
    cout << "All you need to do is enter a flag. If it is a valid flag, I will be very happy!!! :)" << endl;
    cout << endl << "Please enter your flag now: ";
    cin >> input;

    vector<int> flagValues({100, 50, 0, 190, 20, 210, 90, 60, 190, 0, 30, 60, 0, 210, 190, 20, 230, 60, 130, 100, 150, 80});
    int i;

    for(i = 0; i < 22; i++) {
        int flagValue = (int)input[i];
        flagValue -= 95;
        flagValue *= 10;
        if(flagValue != flagValues[i]) {
            cout << endl << "Hmmm, sorry, that's an invalid flag. Please try again!";
            break;
        }
    }
    
    if(i == 22) {
        cout << endl << "Congratulations, that's a valid flag!!!";
    }
}