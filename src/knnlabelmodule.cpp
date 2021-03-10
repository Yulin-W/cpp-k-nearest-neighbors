#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
#include <tuple>
#include "./fast-cpp-csv-parser-master/csv.h"

#define K 500

typedef struct {
    long double x, y;
    long long label;
    long double distanceSquared;
} Point;

double euclideanSquaredDistance(Point a, Point b) {
    return pow(a.x-b.x, 2) + pow(a.y-b.y, 2);
}

bool compareDistance(Point a, Point b) {
    return (a.distanceSquared < b.distanceSquared);
}

bool compareLabel(Point a, Point b) {
    return (a.label < b.label);
}

// k-nearest neighbours algorithm, if there are labels with equal number of points, then take the label with the smallest value
// Argument expectations
// k < nTrain
// trainingSet has nTrain points
int predictPointLabel(std::vector<Point> trainingSet, int nTrain, int k, Point p) {
    // Compute distances
    for (int i=0; i<nTrain; i++) {
        trainingSet[i].distanceSquared = euclideanSquaredDistance(p, trainingSet[i]);
    }

    // Sort points by distance from p
    std::sort(trainingSet.begin(), trainingSet.begin()+nTrain, compareDistance);

    // Sort the k closest points by label
    std::sort(trainingSet.begin(), trainingSet.begin()+k, compareLabel);

    // Pickout the most common label
    int maxCount = 1;
    int currCount = 1;
    int mostCommonLabel = trainingSet[0].label;
    for (int i=1; i<k; i++) {
        if (trainingSet[i].label == trainingSet[i-1].label) {
            currCount++;
        } else {
            if (currCount > maxCount) {
                maxCount = currCount;
                mostCommonLabel = trainingSet[i-1].label;
            }
            currCount = 1;
        }
    }

    // Return the most common label found
    return mostCommonLabel;
}

std::vector<int> predictMultiplePointLabel(std::vector<Point> trainingSet, int nTrain, int k, std::vector<Point> input, int nInput) {
    std::vector<int> predictions;
    for (int i=0; i<nInput; i++) {
        predictions.push_back(predictPointLabel(trainingSet, nTrain, k, input[i]));
    }
    return predictions;
}

// Reads a Point array from a csv file
std::tuple<std::vector<Point>, int> readPointsFromCsv(std::string filename) {
    // Initialise the vector
    std::vector<Point> points;

    // Use csv parser library to read input data
    io::CSVReader<3> in(filename);
    double x, y;
    int label, nPoints=0;
    while(in.read_row(x, y, label)) {
        Point p = {x, y, label};
        points.push_back(p);
        nPoints++;
    }
    return std::make_tuple(points, nPoints);
}

// Reads a Point array without label from a csv file
std::tuple<std::vector<Point>, int> readUnlabelledPointsFromCsv(std::string filename) {
    // Initialise the vector
    std::vector<Point> points;

    // Use csv parser library to read input data
    io::CSVReader<2> in(filename);
    double x, y;
    int nPoints=0;
    while(in.read_row(x, y)) {
        Point p = {x, y};
        points.push_back(p);
        nPoints++;
    }
    return std::make_tuple(points, nPoints);
}

int main() {
    // Read training and input data from respective files
    auto [training, nTraining] = readPointsFromCsv("training.csv");
    auto [input, nInput] = readUnlabelledPointsFromCsv("input.csv");

    // Predict output for input
    std::vector<int> predictions = predictMultiplePointLabel(training, training.size(), K, input, input.size());

    // Write output to output.csv
    std::ofstream outputFile("output.csv");
    for (int i=0; i<nInput; i++) {
        outputFile << predictions[i] << std::endl;
    }
    outputFile.close();

    // Testing end
    return 0;
}