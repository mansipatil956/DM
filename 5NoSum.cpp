#include<bits/stdc++.h>
using namespace std;

// Function to calculate the median of a vector
float calculateMedian(vector<int> a)
{
    int size = a.size();
    if (size % 2 == 1)
        return a[size / 2];
    else
        return (a[size / 2 - 1] + a[size / 2]) / 2.0;
}

// Function to calculate the first quartile (Q1)
float calculateQuartile1(vector<int> v)
{
    int n = v.size();
    int mid = n / 2;
    if (n % 2 == 0)
    {
        return calculateMedian(vector<int>(v.begin(), v.begin() + mid));
    }
    else
    {
        return calculateMedian(vector<int>(v.begin(), v.begin() + mid + 1));
    }
}

// Function to calculate the third quartile (Q3)
float calculateQuartile3(vector<int> v)
{
    int n = v.size();
    int mid = n / 2;
    if (n % 2 == 0)
    {
        return calculateMedian(vector<int>(v.begin() + mid, v.end()));
    }
    else
    {
        return calculateMedian(vector<int>(v.begin() + mid + 1, v.end()));
    }
}

int main()
{
    ifstream in("input.csv");
    if (!in.is_open())
    {
        cout << "Error: Unable to open the input file." << endl;
        return 1;
    }

    vector<int> arr;
    int value;

    // Read data from the input file
    string line;
    while (getline(in, line))
    {
        if (line.empty())
            continue;
        value = stoi(line);
        arr.push_back(value);
    }

    int n = arr.size();
    if (n == 0)
    {
        cout << "Error: No data found in the input file." << endl;
        return 1;
    }

    sort(arr.begin(), arr.end());

    // Calculate quartiles and statistics
    float minVal = arr[0];
    float q1 = calculateQuartile1(arr);
    float median = calculateMedian(arr);
    float q3 = calculateQuartile3(arr);
    float maxVal = arr[n - 1];

    // Write results to the output file and console
    ofstream out("output.csv");
    out << "Minimum value: " << minVal << endl;
    out << "First Quartile (Q1) value: " << q1 << endl;
    out << "Median value: " << median << endl;
    out << "Third Quartile (Q3) value: " << q3 << endl;
    out << "Maximum value: " << maxVal << endl;

    cout << "The minimum value is " << minVal << endl;
    cout << "The First Quartile (Q1) is " << q1 << endl;
    cout << "The median is " << median << endl;
    cout << "The Third Quartile (Q3) is " << q3 << endl;
    cout << "The maximum value is " << maxVal << endl;

    return 0;
}
