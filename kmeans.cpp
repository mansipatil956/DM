#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <bits/stdc++.h>

using namespace std;

// Function to calculate Euclidean distance between two vectors
float euclideanDistance(const vector<float>& a, const vector<float>& b) {
    float distance = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        distance += pow(a[i] - b[i], 2);
    }
    return sqrt(distance);
}

// Function to perform K-means clustering
vector<int> kMeansClustering(const vector<vector<float>>& data, int k, int maxIterations) {
    size_t numSamples = data.size();
    size_t numFeatures = data[0].size();

    // Initialize centroids randomly
    vector<vector<float>> centroids(k, vector<float>(numFeatures));
    for (int i = 0; i < k; ++i) {
        centroids[i] = data[i];
    }

    // Vector to store cluster assignments
    vector<int> clusterAssignments(numSamples);

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        // Assign each sample to the nearest centroid
        for (size_t i = 0; i < numSamples; ++i) {
            float minDistance = numeric_limits<float>::max();
            int closestCentroid = 0;
            for (int j = 0; j < k; ++j) {
                float distance = euclideanDistance(data[i], centroids[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestCentroid = j;
                }
            }
            clusterAssignments[i] = closestCentroid;
        }

        // Update centroids based on mean of assigned samples
        for (int j = 0; j < k; ++j) {
            vector<float> clusterSum(numFeatures, 0.0);
            int clusterSize = 0;
            for (size_t i = 0; i < numSamples; ++i) {
                if (clusterAssignments[i] == j) {
                    for (size_t f = 0; f < numFeatures; ++f) {
                        clusterSum[f] += data[i][f];
                    }
                    clusterSize++;
                }
            }
            for (size_t f = 0; f < numFeatures; ++f) {
                centroids[j][f] = clusterSum[f] / clusterSize;
            }
        }
    }

    return clusterAssignments;
}

int main() {
    // Read input data from CSV file
    CSVReader<2> in("input.csv");
    in.read_header(io::ignore_extra_column, "x", "y");

    vector<float> feature1, feature2;
    float f1, f2;
    while (in.read_row(f1, f2)) {
        feature1.push_back(f1);
        feature2.push_back(f2);
    }

    size_t numSamples = feature1.size();
    size_t numFeatures = 2;

    // Populate data vector
    vector<vector<float>> data(numSamples, vector<float>(numFeatures));
    for (size_t i = 0; i < numSamples; ++i) {
        data[i][0] = feature1[i];
        data[i][1] = feature2[i];
    }

    // Perform K-means clustering with k=3 and maxIterations=100
    int k = 3;
    int maxIterations = 100;
    vector<int> clusterAssignments = kMeansClustering(data, k, maxIterations);

    // Write results to CSV file
    ofstream outFile("output.csv");
    outFile << "Feature1,Feature2,Cluster\n";

    for (size_t i = 0; i < numSamples; ++i) {
        outFile << data[i][0] << "," << data[i][1] << "," << clusterAssignments[i] << "\n";
    }

    cout << "K-means clustering completed. Results written to output.csv." << endl;

    return 0;
}
