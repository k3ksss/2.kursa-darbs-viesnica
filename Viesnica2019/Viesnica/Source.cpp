#include "Header.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

std::string epasts;

using json = nlohmann::json;

json j;

void registration() {
	std::string vards, uzvards, parole, atkartotaparole, epasts, valsts;

	system("cls");

	std::ifstream i("userData.json");
	if (i.is_open()) {
		i >> j;
	}
	
	do {
		std::cout << "Vards: ";
		std::getline(std::cin >> std::ws, vards);
	} while (kluda_vards_uzvards(vards));
	do {
		std::cout << "Uzvards: ";
		std::getline(std::cin >> std::ws, uzvards);
	} while (kluda_vards_uzvards(uzvards));
	do {
		std::cout << "Parole: ";
		std::getline(std::cin >> std::ws, parole);
		std::cout << "Atkartota parole: ";
		std::getline(std::cin >> std::ws, atkartotaparole);
	} while (kluda_parole(parole,atkartotaparole));
	do {
		std::cout << "E-pasts: ";
		std::getline(std::cin >> std::ws, epasts);
	} while (kluda_epasts(epasts));
	do {
		std::cout << "Valsts: ";
		std::getline(std::cin >> std::ws, valsts);
	} while (kluda_valsts(valsts));
	
	j[epasts]["Vards"] = vards;
	j[epasts]["Uzvards"] = uzvards;
	j[epasts]["Parole"] = parole;
	j[epasts]["E-Pasts"] = epasts;
	j[epasts]["Valsts"] = valsts;
	j[epasts]["admin"] = false;

	std::ofstream x("userData.json");
	x << std::setw(4) << j << std::endl;

	x.close();

	return;
}

void login() {
	std::string parole;

	system("cls");

	std::ifstream dati("userData.json");
	dati >> j;
	
	std::cout << "Ievadiet epastu: ";
	std::getline(std::cin >> std::ws, epasts);
	std::cout << "Ievadiet parole: ";
	std::getline(std::cin >> std::ws, parole);

	if (parole == j[epasts]["Parole"]) {
		if (j[epasts]["admin"] == true) {
			adminMain();
		}
		else {
			userMain();
		}
	}
	else {
		login();
	}
}

int main() {
	int izvele;

	system("cls");

	std::cout << "Sveicinati\n";
	std::cout << "1.Registreties\n";
	std::cout << "2.Ielogoties sistema\n";
	std::cout << "3.Iziet\n";
	std::cout << "Izvele: ";
	std::cin >> izvele;

	switch (izvele) {
	case 1: registration(); main(); break;
	case 2: login(); main(); break;
	case 3: return 0;
	default: main();
	}
}