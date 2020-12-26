/*

 @brief:  get top K and bottom K
*代码采用STL中的最小优先队列实现，由于STL中自带最小优先队列，其底层就是二叉堆实现，
*所以就不再手写二叉堆了。最小优先队列顶层元素总是队列中最小的元素，也就是二叉堆堆顶。

 author:zhaoCQ 2020.12.26  
*/
 

#include "statistic.h"

 
   vector<int>Statistic:: Bottom_k(vector<int> array, int k)
    {
        priority_queue<int, vector<int>, greater<int>> small_heap;

        for (int i = 0; i < array.size(); i++)
        {
            small_heap.push(array[i]);
        }

       
        int i = 0;
        m_bottomk.clear();

        while (!small_heap.empty() && i < m_k)
        {

            m_bottomk.push_back(small_heap.top());

            small_heap.pop();
        }

        return m_bottomk;
    }
 

    vector<int> Statistic::Top_k(vector<int> array, int k)
    {
        if(k>array.size())
        {
 
            cout << " k is biger than array size  "<<endl;
          
           exit (0);
        }
        priority_queue<int, vector<int>, less<int>> big_heap;

        for (int i = 0; i < array.size(); i++)
        {
            big_heap.push(array[i]);
        }

        int i = 0;
        while (!big_heap.empty() && i < m_k)
        {

            m_topk.push_back(big_heap.top());
            //m_topk_index.push_back

            big_heap.pop();
            i++;
        }
 
        



        //double sum = std::accumulate(std::begin(big_heap), std::end(big_heap), 0.0); // sum of exclude top k
        //m_mean_remove_topk = sum / big_heap.size();

        return m_topk;
    }

    int  Statistic::Mean_variance(vector<int> array,double &mean,double &variance,double &standard_deviation)
    {
        double sum = std::accumulate(std::begin(array), std::end(array), 0.0);
        mean = sum / array.size();

        // 求方差
        variance = 0.0;
        for (int i = 0; i < array.size(); i++)
        {
            variance = variance + pow(array[i] - mean, 2);
        }
        variance = variance / array.size();    // 方差
        standard_deviation = sqrt(variance);  //标准差


 
    }
  


  ////repeat data  did not process
   int Statistic::Mean_remove_maxmin_k(vector<int> array,double &mean,double &variance,double &standard_deviation)
   {

       double sum = std::accumulate(std::begin(array), std::end(array), 0.0);
      

         m_topk=Top_k(array,m_k);
         m_bottomk=Bottom_k(array,m_k);

         // auto min_topk= min_element(m_topk.begin(), m_topk.end());

         // auto max_bottomk=max_element(m_bottomk.begin(),m_bottomk.end());

         int min_topk;
         int max_bottomk;

         sum = 0;
         int size_remove=0;

         bool same_data_first=0;
        for(int i=0;i<array.size();i++)
        {
            if(array[i]<min_topk && array[i]>max_bottomk)
        {
            size_remove++;
            sum+=array[i];                                 ///overflow 

        } 

        }

          mean = sum / size_remove;
          variance = 0;
        for (int i = 0; i < array.size(); i++)
        {
            if((array[i] < min_topk) && (array[i]>max_bottomk))
                {

                    variance += (array[i] - mean) * (array[i] - mean);     ///overflow  catch do not process 
                }
        }

        // double sum_topK = std::accumulate(std::begin(m_topk), std::end(m_topk), 0.0);
        
        variance = 0.0;
        for (int i = 0; i < array.size(); i++)
        {

            variance = variance + pow(array[i] - mean, 2);
        }
       
        standard_deviation = sqrt(variance);  //标准差




   }