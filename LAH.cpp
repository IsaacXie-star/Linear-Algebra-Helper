#include <iostream>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

const int N = 110;
const double eps = 1e-6;
int n;
double b[N][N];
double a[N][N];

int gauss(void)
{
    int r, c;
    for(c = 0, r = 0; c < n; c ++) {
        int t = r;
        for(int i = r; i < n; i++) {
            if(fabs(a[i][c]) > fabs(a[t][c])) t = i;
        }
        
        if(fabs(a[t][c]) < eps) {
            continue;
        }
        
        for(int i = c; i <= n; i ++) {
            swap(a[r][i], a[t][i]);
        }
        for(int i = n; i >= c; i --) {
            a[r][i] /= a[r][c];
        }
        for(int i = r + 1; i < n; i ++) {
            if(fabs(a[i][c]) > eps) {
                for(int j = n; j >= c; j --) {
                    a[i][j] -= a[r][j] * a[i][c];
                }
            }
        }
        r++;
    }
    
   if(r < n) {
       for(int i = r; i < n; i++) {
           if(fabs(a[i][n]) > eps) return 2;
       }
       return 1;
   }
   
   for(int i = n - 1; i >= 0; i --) {
       for(int j = i + 1; j < n; j ++) {
           a[i][n] -= a[i][j] * a[j][n];
       }
   }
   return 0;
}

void outputMatrix(void) {
    
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j <= n; j ++) {
            cout << b[i][j] << ' ';
        }
        cout << endl;
    }
}

void outputRREF(void) {
    
    gauss();
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j <= n; j ++) {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

int getRank(bool indicator) {
    
    int ans = 0;
    gauss();
    int r = n - 1;
    while (r) {
        if (a[n][r] != 0) {
            break;
        }
        r --;
    }
    ans = r + 1;
    
    if (!indicator) {
        cout << ans << endl;
        return 0;
    }
    
    return ans;
}

void getNullity(void) {
    
    int ans = 0;
    int k = getRank(1);
    cout << n - k << endl;
}

void getTrace(void) {
    
    int x = 0, y = 0;
    int trace = 0;
    
    while (x < n) {
        trace += b[x][y];
        x ++, y ++;
    }
    
    cout << trace << endl; 
}

void outputSolution(void) {
    
    int t = gauss();
    
    if(t == 0) {
        for(int i = 0; i < n; i ++) cout<< a[i][n] <<endl;
    }
    else if(t == 1) {
        cout << "Infinite group solutions" << endl;
    }
    else {
        cout << "No solution" << endl;
    }
}

void isDiagonal(void) {
    
    bool flag = true;
    for (int i = 0; i < n && flag; i ++) {
        for (int j = 0; j < n && flag; j ++) {
            if (b[i][j] != 0) {
                if (i != j) {
                    flag = false;
                }
            }
        }
    }
    
    if (flag) {
        cout << "The input matrix is diagonal" << endl;
    } else {
        cout << "The input matrix is not diagonal" << endl;
    }
}

void seeOperations(void) {
    
    cout << "Operations: " << endl;
    cout << "q: quit" << endl;
    cout << "gsol: Get Solution" << endl;
    cout << "gRREF: Get the RREF form of the matrix" << endl;
    cout << "grank: Get the rank of the matrix" << endl;
    cout << "gnull: Get the nullity of the matrix" << endl;
    cout << "gmatrix: See the input original matrix" << endl;
    cout << "gtrace: Get the trace of the matrix" << endl;
    cout << "isdiagonal: Determine if the input matrix is a diagonal matrix" << endl;
    
    return;
}

int main(void) {
    
    cout << fixed << setprecision(3);
    cout << "Please input the size of your matrix: ";
    cin>>n;
    cout << endl;
    cout << "Please input your matrix:" << endl;
    
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j <= n; j ++) {
            cin >> a[i][j];
            b[i][j] = a[i][j];
        }
    }
    
    while (true) {
        
        cout << "Type man to see all operations" << endl;
        cout << "Enter your command: ";
        string op;
        cin >> op;
        cout << endl;
        if (op == "man") {
            seeOperations();
        } else if (op == "q") {
            
            cout << "Are you sure you want to quit?" << endl;
            cout << "Enter Yes to quit, No to continue" << endl;
            string quitCommand;
            
            cin >> quitCommand;
            if (quitCommand == "Yes") {
                cout << "Quit successfully" << endl;
                break;
            } else {
                continue;
            }
            
        } else if (op == "gsol") {
            outputSolution();
        } else if (op == "gRREF") {
            outputRREF();
        } else if (op == "gmatrix") {
            outputMatrix();
        } else if (op == "gnull") {
            getNullity();
        } else if (op == "grank") {
            getRank(0);
        } else if (op == "gtrace") {
            getTrace();
        } else if (op == "isdiagonal") {
            isDiagonal();
        }
        cout << endl;
    }
    
    return 0;
}
