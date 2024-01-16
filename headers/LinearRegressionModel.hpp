
#ifndef LINEAR_REGRESSION_MODEL_H
#define LINEAR_REGRESSION_MODEL_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <cmath>
#include <algorithm>


struct CarData {
    int km;
    int price;
};

class LinearRegressionModel {
private:
    double a0;
    double a1;
    double kmStdDev;
    double kmMean;
    double priceStdDev;
    double priceMean;
    std::vector<CarData> carData;

public:
    // Constructor
    LinearRegressionModel(const std::vector<CarData>& carData)
        : a0(0.00), a1(0.00), carData(carData)
        {}

    LinearRegressionModel(const std::vector<CarData>& carData, double a0, double a1) : 
        a0(a0), a1(a1),
        kmStdDev(0),
        kmMean(0),
        priceStdDev(0),
        priceMean(0),
        carData(carData)
    {}
    // Function to update coefficients based on gradient descent
    void update(double learning_rate);

    // Function to calculate the predicted values
    std::vector<double> predict() const;

    // Function to train the model
    void train(int max_iteration, double learning_rate);

    // Function to make predictions for a given kilometer value
    double predict(int km) ;
    void normalizeData();
};

#endif