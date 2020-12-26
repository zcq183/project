/* 
 @brief:  get top K and bottom K
*代码采用STL中的最小优先队列实现，由于STL中自带最小优先队列，其底层就是二叉堆实现，
*所以就不再手写二叉堆了。最小优先队列顶层元素总是队列中最小的元素，也就是二叉堆堆顶。

 author:zhaoCQ 2020.12.26  
*/

#include <iostream>
#include <queue>
#include <vector>
#include <numeric> // std::accumulate
using namespace std;

class Solution
{
public:
    vector<int> get_bottomk(vector<int> array, int k)
    {
        priority_queue<int, vector<int>, greater<int>> small_heap;

        for (int i = 0; i < array.size(); i++)
        {
            small_heap.push(array[i]);
        }

        vector<int> res;
        int i = 0;

        while (!small_heap.empty() && i < k)
        {

            res.push_back(small_heap.top());

            small_heap.pop();
        }

        return res;
    }

    vector<int> get_topk(vector<int> array, int k)
    {
        priority_queue<int, vector<int>, less<int>> big_heap;

        for (int i = 0; i < array.size(); i++)
        {
            big_heap.push(array[i]);
        }

        vector<int> res;
        int i = 0;
        while (!big_heap.empty() && i < k)
        {

            res.push_back(big_heap.top());

            big_heap.pop();
            i++;
        }
        return res;
    }

    float get_mean(vector<int> array)
    {
        double sum = std::accumulate(std::begin(array), std::end(array), 0.0);
        double mean = sum / array.size(); //均值
    }

    vector<int> getLeastNumbers(vector<int> &arr, int k) // concrete implement
    {
        if (k == 0)
            return vector<int>();
        vector<int> max_heap_vec(arr.begin(), arr.begin() + k);
        buildMaxHeap(max_heap_vec);
        for (int i = k; i < arr.size(); ++i)
        {
            // 出现比堆顶元素小的值, 置换堆顶元素, 并调整堆
            if (arr[i] < max_heap_vec[0])
            {
                emplacePeek(max_heap_vec, arr[i]);
            }
        }
        return max_heap_vec;
    }

private:
    void buildMaxHeap(vector<int> &v)
    {
        // 所有非叶子节点从后往前依次下沉
        for (int i = (v.size() - 2) / 2; i >= 0; --i)
        {
            downAdjust(v, i);
        }
    }

    void downAdjust(vector<int> &v, int index)
    {
        int parent = v[index];
        // 左孩子节点索引
        int child_index = 2 * index + 1;
        while (child_index < v.size())
        {
            // 判断是否存在右孩子, 并选出较大的节点
            if (child_index + 1 < v.size() && v[child_index + 1] > v[child_index])
            {
                child_index += 1;
            }
            // 判断父节点和子节点的大小关系
            if (parent >= v[child_index])
                break;
            // 较大节点上浮
            v[index] = v[child_index];
            index = child_index;
            child_index = 2 * index + 1;
        }
        // 避免重复交换的无用工作
        v[index] = parent;
    }

    void emplacePeek(vector<int> &v, int val)
    {
        v[0] = val;
        downAdjust(v, 0);
    }
};

  

int test()
{
    vector<int> arrary; 
    for (int i = 0; i < 100; i++)
    {
        arrary.push_back(i);
    }

    int nums = 100;
    int K = 10;
    Solution s;

    vector<int> topk; 
    //topk = s.getLeastNumbers(arrary, K);

    topk = s.get_topk(arrary, K);

    for (int i = 0; i < K; i++)
    {
        cout << topk[i] << "   ";
    }

    cout << endl;

    vector<int> bottomk = s.get_bottomk(arrary, K);

    for (int i = 0; i < K; i++)
    {
        cout << bottomk[i] << "   ";
    }

    cout << endl;


    

    return 0;
}
