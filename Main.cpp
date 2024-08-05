#include <iostream>
#include <cmath>
#include <vector>

// Function to calculate the spot rate using the Svensson model
double calculateSpotRate(double t, double beta0, double beta1, double beta2, double beta3, double tau1, double tau2) {
    double term1 = beta0;
    double term2 = beta1 * (1 - exp(-t / tau1)) / (t / tau1);
    double term3 = beta2 * ((1 - exp(-t / tau1)) / (t / tau1) - exp(-t / tau1));
    double term4 = beta3 * ((1 - exp(-t / tau2)) / (t / tau2) - exp(-t / tau2));
    return term1 + term2 + term3 + term4;
}

// Function to calculate the discount factor
double calculateDiscountFactor(double spotRate, double t) {
    return exp(-spotRate * t);
}

// Function to price a bond
double priceBond(double faceValue, double couponRate, int maturity, double beta0, double beta1, double beta2, double beta3, double tau1, double tau2) {
    double bondPrice = 0.0;
    double coupon = couponRate * faceValue;

    for (int t = 1; t <= maturity; ++t) {
        double spotRate = calculateSpotRate(t, beta0, beta1, beta2, beta3, tau1, tau2);
        double discountFactor = calculateDiscountFactor(spotRate, t);
        bondPrice += coupon * discountFactor;

        if (t == maturity) {
            bondPrice += faceValue * discountFactor;
        }
    }

    return bondPrice;
}

int main() {
    // Bond details
    double faceValue = 1000.0; // Face value of the bond
    double couponRate = 0.05; // Annual coupon rate
    int maturity = 5; // Maturity in years

    // Svensson model parameters
    double beta0 = 0.02;
    double beta1 = -0.01;
    double beta2 = 0.03;
    double beta3 = -0.02;
    double tau1 = 2.0;
    double tau2 = 10.0;

    double bondPrice = priceBond(faceValue, couponRate, maturity, beta0, beta1, beta2, beta3, tau1, tau2);

    std::cout << "The price of the bond is: $" << bondPrice << std::endl;

    return 0;
}
