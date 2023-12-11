#include<bits/stdc++.h>
using namespace std;

// Equal Frequency Binning
vector<vector<int>> equalFrequency(vector<int> arr, int m)
{
    int n = arr.size();
    int binSize = n / m;
    vector<vector<int>> bins;

    sort(arr.begin(), arr.end());
    int rem = n % m;  // Remaining elements

    int start = 0;
    for (int i = 0; i < m; i++)
    {
        int end = start + binSize;
        if (rem > 0)
        {
            end++;  // Add one element to this bin to distribute remaining elements
            rem--;
        }

        vector<int> bin;
        for (int j = start; j < end; j++)
        {
            bin.push_back(arr[j]);
        }
        bins.push_back(bin);

        start = end;
    }

    return bins;
}

// Equal Width Binning
vector<vector<int>> equalWidth(vector<int> arr, int m)
{
    int n = arr.size();

    int max_val = *max_element(arr.begin(), arr.end());
    int min_val = *min_element(arr.begin(), arr.end());
    int binWidth = (max_val - min_val) / m;

    vector<vector<int>> bins(m);

    for (int i : arr)
    {
        int binIndex = min((i - min_val) / binWidth, m - 1);
        bins[binIndex].push_back(i);
    }

    return bins;
}

// Read data from CSV
vector<int> readCSV(string filename)
{
    ifstream inputFile(filename);
    vector<int> data;
    string line, value;
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        while (getline(ss, value, ','))
        {
            data.push_back(stoi(value));
        }
    }
    inputFile.close();
    return data;
}

// Write binning outputs to CSV
void writeCSV(string filename, vector<vector<int>> bins)
{
    ofstream outputFile(filename);
    for (int i = 0; i < bins.size(); i++)
    {
        outputFile << "Bin " << i + 1 << ",";
        for (int num : bins[i])
        {
            outputFile << num << ",";
        }
        outputFile << "\n";
    }
    outputFile.close();
}

int main()
{
    vector<int> data = readCSV("input.csv");
    int m;

    int method;
    cout << "Choose binning method: " << endl;
    cout << "1. Equal Frequency Binning" << endl;
    cout << "2. Equal Width Binning" << endl;
    cout << "\nEnter method number: ";
    cin >> method;
    cout << "\nEnter number of bins: ";
    cin >> m;

    if (method == 1)
    {
        vector<vector<int>> freqBins = equalFrequency(data, m);
        writeCSV("output_equal_frequency.csv", freqBins);
    }
    else if (method == 2)
    {
        vector<vector<int>> widthBins = equalWidth(data, m);
        writeCSV("output_equal_width.csv", widthBins);
    }
    else
    {
        cout << "Invalid method choice." << endl;
    }

    return 0;
}
