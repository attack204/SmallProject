#include <algorithm>
#include <ctime>
#include <iostream>

int main()
{
    // 随机产生整数，用分区函数填充，以避免出现分桶不均
    const unsigned arraySize = 32768;
    int data[arraySize];

    for (unsigned c = 0; c < arraySize; ++c)
        data[c] = std::rand() % 256;

    // !!! 排序后下面的Loop运行将更快
    //std::sort(data, data + arraySize);

    // 测试部分
    clock_t start = clock();
    long long sum = 0;

    for (unsigned i = 0; i < 100000; ++i)
    {
        // 主要计算部分，选一半元素参与计算
        for (unsigned c = 0; c < arraySize; ++c)
        {
            if (data[c] >= 128)
                sum += data[c];
        }
    }

    double elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;

    std::cout << elapsedTime << std::endl;
    std::cout << "sum = " << sum << std::endl;
}