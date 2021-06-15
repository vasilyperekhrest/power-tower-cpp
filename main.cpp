//
// Created by Vasily Perekhrest on 15.06.2021.
//

#include <iostream>
#include <vector>

#include <flint/fmpzxx.h>
#include <flint/fmpz_factorxx.h>


int main() {
    flint::fmpzxx base("2017");
    unsigned int n = 2017;

    flint::fmpzxx power("1"), module;

    // module = module_base ^ module_exp
    flint::fmpzxx module_base("10");
    unsigned int module_exp = 50;

    if (n > module_exp) {
        n = module_exp;
    }

    if (module_base == 10) {
        fmpz_pow_ui(module._fmpz(), module_base._fmpz(), module_exp);

        flint::fmpzxx d;
        fmpz_gcd(d._fmpz(), base._fmpz(), module._fmpz());
        if (d != 1) {
            std::cout << base << " is not mutually simple with the module." << std::endl;
            return -1;
        }

        for (int i = 0; i < n; i++) {
            fmpz_powm(power._fmpz(), base._fmpz(), power._fmpz(), module._fmpz());
        }

    } else {
        fmpz_pow_ui(module._fmpz(), module_base._fmpz(), module_exp);

        flint::fmpzxx d, phi(module);
        std::vector<flint::fmpzxx> phi_list;

        if (d != 1) {
            std::cout << base << " is not mutually simple with the module." << std::endl;
            return -1;
        }

        phi_list.push_back(phi);
        for (int i = 0; i < n; i++) {
            fmpz_euler_phi(phi._fmpz(), phi._fmpz());
            fmpz_gcd(d._fmpz(), phi._fmpz(), base._fmpz());
            if (d != 1) {
                std::cout << base << " is not mutually simple with the module." << std::endl;
                return -1;
            }
            phi_list.push_back(phi);
        }

        for (int i = 0; i < n + 1; i++) {
            fmpz_powm(power._fmpz(), base._fmpz(), power._fmpz(), phi_list[n - i]._fmpz());
        }
    }

    std::cout << power << std::endl;

    return 0;
}