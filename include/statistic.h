#include <iostream>
#include <queue>
#include <vector>
#include <numeric> // std::accumulate
#include <cmath>
#include <algorithm>

using namespace std;

/*******************************************************************

 @brief:  get top K and bottom K ,mean ,variance,standard variance ,
           and variance and std_variance by remove max min  

 @author:zhaoCQ 2020.12.26  

 note:
*代码采用STL中的最小优先队列实现，由于STL中自带最小优先队列，其底层就是二叉堆实现，
*所以就不再手写二叉堆了。最小优先队列顶层元素总是队列中最小的元素，也就是二叉堆堆顶。
****************************************************************/

class Statistic
{
public:
    Statistic(int k) : m_k(k)
    {

    }

    ~Statistic()
    {
    }

    vector<int> Bottom_k(vector<int> array, int k);

    vector<int> Top_k(vector<int> array, int k);

    int Mean_variance(vector<int> array, double &mean, double &variance, double &standard_deviation);

    int Mean_remove_maxmin_k(vector<int> array, double &mean, double &variance, double &standard_deviation);

private:

    vector<int> m_topk;
    vector<int> m_bottomk;

     vector<int> m_remove_2k;   ///remove top k and bottom k array

    ///priority_queue<int, vector<int>, less<int>> m_heap;

    int m_k;
    double m_variance;
    double m_std_variance;

    double m_mean_remove_topk;
    double m_mean_remove_bottomk;

    double m_variance_remove_topk;
    double m_variance_remove_bottomk;
};
