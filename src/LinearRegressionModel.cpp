#include "../headers/LinearRegressionModel.hpp"

// Function definitions for LinearRegressionModel
void LinearRegressionModel::update(double learning_rate) {
    double sum_residual_a0 = 0.0;
    double sum_residual_a1 = 0.0;

    for (const auto& data : carData) {
        double prediction = a0 + a1 * data.km;
        sum_residual_a0 += prediction - data.price;
        sum_residual_a1 += (prediction - data.price) * data.km;
    }

    a0 -= (learning_rate / carData.size()) * sum_residual_a0;
    a1 -= (learning_rate / carData.size()) * sum_residual_a1;
}

std::vector<double> LinearRegressionModel::predict() const {
    std::vector<double> predictions;
    predictions.reserve(carData.size());

    for (const auto& data : carData) {
        double prediction = a0 + a1 * data.km;
        predictions.push_back(prediction);
    }

    return predictions;
}

void LinearRegressionModel::train(int max_iteration, double learning_rate) {
    while (max_iteration > 0) {
        update(learning_rate);
        max_iteration--;
        //  std::cout << "a0 = " << a0 << ", a1 = " << a1 << std::endl;
    }
}

void LinearRegressionModel::normalizeData() {
        std::vector<double> kmValues;
        std::vector<double> priceValues;

        // Collecter les valeurs de kilométrage et de prix
        for (const auto& data : carData) {
            kmValues.push_back(data.km);
            priceValues.push_back(data.price);
        }

        // Calculer la moyenne et l'écart type
        this->kmMean = std::accumulate(kmValues.begin(), kmValues.end(), 0.0) / kmValues.size();
        this->kmStdDev = sqrt(std::inner_product(kmValues.begin(), kmValues.end(), kmValues.begin(), 0.0) / kmValues.size() - kmMean * kmMean);

        this->priceMean = std::accumulate(priceValues.begin(), priceValues.end(), 0.0) / priceValues.size();
        this->priceStdDev = sqrt(std::inner_product(priceValues.begin(), priceValues.end(), priceValues.begin(), 0.0) / priceValues.size() - priceMean * priceMean);

        // Normaliser les données
        for (auto& data : carData) {
            data.km = (data.km - kmMean) / kmStdDev;
            data.price = (data.price - priceMean) / priceStdDev;
        }
    }

double LinearRegressionModel::predict(int km)  {

    std::cout << "a1 = " << a1 << " a0 = " << a0 << std::endl;
 
    // Normaliser la nouvelle donnée
    if (kmStdDev == 0)
        return 0;
    double normalized_km = (km - kmMean) / kmStdDev;

    // Utiliser la nouvelle donnée normalisée pour la prédiction
    double normalized_prediction = a0 + a1 * normalized_km;

    // Inverser le processus de normalisation pour obtenir la prédiction dans l'unité d'origine
    double prediction = normalized_prediction * priceStdDev + priceMean;

    a0 = a0 * priceStdDev + priceMean;
    a1 = a1 * priceStdDev / kmStdDev;
    std::cout << " a1 = " << a1 << "a0 =  " << a0 << std::endl;
    // prediction =  a0 + a1 * km;
    return prediction;
}
