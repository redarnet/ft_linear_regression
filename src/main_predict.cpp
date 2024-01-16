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

int main()
{
    std::string filename = "./data/data.csv";
    std::vector<CarData> carData = readCSVFile(filename);
    LinearRegressionModel linear_reg(carData, 0, 0);
    // mettre a1 et a0 dans un file ?

    double X_test;
    std::cout << "Enter predict: "; // no flush needed
    std::cin >> X_test;
    linear_reg.normalizeData();
    double y = linear_reg.predict(X_test);
    std::cout << "Predicted price for " << X_test << " km: " << y << "\n";
    return 0;
}