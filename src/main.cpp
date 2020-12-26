
#include "statistic.h"
int main()
{
    vector<int> arrary; 
    for (int i = 0; i < 100; i++)
    {
        arrary.push_back(i);
    }

    int nums = 100;
    int K = 10; 

    vector<int> topk; 
    //topk = s.getLeastNumbers(arrary, K);
    Statistic s(K);
 
    topk = s.Top_k(arrary, K);

    for (int i = 0; i < K; i++)
    {
        cout << topk[i] << "   ";
    }

    cout << endl;

    vector<int> bottomk = s.Bottom_k(arrary, K);

    for (int i = 0; i < K; i++)
    {
        cout << bottomk[i] << "   ";
    }

    cout << endl;


    

    return 0;
}
