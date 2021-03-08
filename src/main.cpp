#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
#include "./fast-cpp-csv-parser-master/csv.h"

typedef struct {
    double x, y;
    int label;
    double distanceSquared;
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

// Reads a Point array from a csv file
std::vector<Point> readPointsFromCsv(std::string filename) {
    // Initialise the vector
    std::vector<Point> points;

    // Use csv parser library to read input data
    io::CSVReader<3> in(filename);
    double x, y;
    int label;
    while(in.read_row(x, y, label)) {
        Point p = {x, y, label};
        points.push_back(p);
    }
    return points;
}

int main() {
    // Testing start
    Point p = {0, 0, 0};
    int k = 4;
    std::vector<Point> training = readPointsFromCsv("input.csv");
    std::cout << predictPointLabel(training, training.size(), k, p);
    // Testing end
    return 0;
}