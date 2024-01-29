#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

inline void devideArrayOnHalfMaximum(std::vector<double>& vArr)
{
    double dMaximum = 0;
    dMaximum = *std::max_element(vArr.begin(), vArr.end());
    for (double& dNumber : vArr)
        dNumber = dNumber / (dMaximum / 2);
}

inline void outputArray(const std::vector<double>& c_vArr)
{
    for (const double& c_dNumber : c_vArr)
        std::cout << std::fixed << std::setprecision(3) << c_dNumber << " ";
    std::cout << std::endl;
}

inline void addArithmeticAverage(std::vector<double>& vArr)
{
    double dSumArithmeticAverage = 0;
    for (double& dNumber : vArr)
        dSumArithmeticAverage += dNumber;
    vArr.push_back(dSumArithmeticAverage);
    vArr.push_back(dSumArithmeticAverage / (vArr.size() - 1));
}

inline void proccesingArray(std::vector<double>& vArr)
{
    outputArray(vArr);
    addArithmeticAverage(vArr);
    outputArray(vArr);
    devideArrayOnHalfMaximum(vArr);
    outputArray(vArr);
}

int main()
{
    int iStartArraySize = 0;
    std::cin >> iStartArraySize;
    std::vector<double> vArr(iStartArraySize);
    for (int i = 0; i < iStartArraySize; i++)
        std::cin >> vArr[i];
    std::cout << vArr.size() << std::endl;
    proccesingArray(vArr);

    int iChoiceAction = 0;
    std::cin >> iChoiceAction;
    while (iChoiceAction != 0)
    {
        if (iChoiceAction == 1)
        {
            double dNewElement = 0;
            std::cin >> dNewElement;
            vArr.push_back(dNewElement);
            std::cout << "+: " << vArr.size() << std::endl;
        }
        if (iChoiceAction == 2)
            if (!vArr.empty())
            {
                vArr.pop_back();
                std::cout << "-: " << vArr.size() << std::endl;
            }
        proccesingArray(vArr);
        std::cin >> iChoiceAction;
    }
    return 0;
}
