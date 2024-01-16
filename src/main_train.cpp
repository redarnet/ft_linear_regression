#include "../headers/LinearRegressionModel.hpp"

std::vector<CarData> readCSVFile(const std::string& filename) {
    std::vector<CarData> data; 

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return data;
    }

    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        getline(iss, token, ',');
        int km = std::stoi(token);

        getline(iss, token, ',');
        int price = std::stoi(token);

        data.push_back({km, price});
    }
    file.close();
    return data;
}

int main() {
    // Variable Initialization
    std::string filename = "./data/data.csv";
    std::vector<CarData> carData = readCSVFile(filename);

    for (const auto& car : carData) {
        std::cout << "KM: " << car.km << ", Prix: " << car.price << std::endl;
    }

    // Training
    std::cout << "Making LinearRegressionModel \n";
    LinearRegressionModel linear_reg(carData);
    std::cout << "Training \n";
    linear_reg.normalizeData();
    linear_reg.train(1000000, 0.0001);
    // mettre a1 et a0 dans un file ?

    std::cout << "Testing \n";
    double X_test = 42000;
    double y = linear_reg.predict(X_test);
    std::cout << "Predicted price for " << X_test << " km: " << y << "\n";

    return 0;
}
