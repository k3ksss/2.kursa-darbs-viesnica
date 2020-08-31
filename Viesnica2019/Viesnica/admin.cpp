#include <iostream>
#include "Header.h"
#include "json.hpp"
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>

using json = nlohmann::json;
json jj;

void pievienotvalsti() {
	std::string nosaukums, saisinajums, viesnicasnosaukums, zvaigznes, numurinuSkaits;
	int maxviesnicas, cenaparnumurinu;

	std::string::size_type izmers;

	std::ifstream dati("viesnicuData.json");
	if (dati.is_open()) {
		dati >> jj;
	}

	bool nepareizi = false;

	system("cls");

	do {
		std::cout << "Ievadiet valsts nosaukumu:";
		std::getline(std::cin >> std::ws, nosaukums);
		std::transform(nosaukums.begin(), nosaukums.end(), nosaukums.begin(), ::tolower);
	} while (kluda_valsts(nosaukums));

	do {
		std::cout << "Ievadiet valsts saisinajumu:";
		std::getline(std::cin >> std::ws, saisinajums);
	} while (kluda_valsts(saisinajums));

	do {
		std::cout << "Ievadiet maksimalo viesnicu skaitu:";
		std::cin >> maxviesnicas;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			nepareizi = true;
		}
		else {
			nepareizi = false;
		}
	} while (nepareizi);

	for (int x = 1; x <= maxviesnicas; x++) {
		system("cls");
		do {
			std::cout << "Ievadiet viesnicas nosaukumu:";
			std::getline(std::cin >> std::ws, viesnicasnosaukums);
			std::transform(viesnicasnosaukums.begin(), viesnicasnosaukums.end(), viesnicasnosaukums.begin(), ::tolower);
		} while (kluda_valsts(viesnicasnosaukums));

		do {
			std::cout << "Ievadiet viesnicas zvaigznu skaitu:";
			std::cin >> zvaigznes;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				nepareizi = true;
			}
			else {
				nepareizi = false;
			}
		} while (nepareizi);

		do {
			std::cout << "Ievadiet numurinu skaitu[MAX: 50]:";
			std::cin >> numurinuSkaits;
			if (std::stoi(numurinuSkaits, &izmers) <= 50 && std::stoi(numurinuSkaits, &izmers) >= 1) {
				nepareizi = false;
			}
			else {
				nepareizi = true;
			}
		} while (nepareizi);

		do {	
			std::cout << "Ievadiet cenu par numurinu:";
			std::cin >> cenaparnumurinu;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				nepareizi = true;
			}
			else {
				nepareizi = false;
			}
		} while (nepareizi);

		jj[nosaukums]["Saisinajums"] = saisinajums;
		jj[nosaukums]["Max-Viesnicas"] = maxviesnicas;
		jj[nosaukums]["Viesnicas"][viesnicasnosaukums]["Viesnicas-nosaukums"] = viesnicasnosaukums;
		jj[nosaukums]["Viesnicas"][viesnicasnosaukums]["Viesnicas-zvaigznes"] = zvaigznes;
		jj[nosaukums]["Viesnicas"][viesnicasnosaukums]["Viesnicas-cena-par-numurinu"] = cenaparnumurinu;
		jj[nosaukums]["Viesnicas"][viesnicasnosaukums]["Viesnicas-numurinu-skaits"] = numurinuSkaits;

		for (int x = 1; x <= std::stoi(numurinuSkaits,&izmers); x++) {
			std::string numurins = std::to_string(x);
			jj[nosaukums]["Viesnicas"][viesnicasnosaukums]["Viesnicas-numurini"][numurins]["Rezervets"] = false;
			jj[nosaukums]["Viesnicas"][viesnicasnosaukums]["Viesnicas-numurini"][numurins]["Rezervets-NO"] = "";
			jj[nosaukums]["Viesnicas"][viesnicasnosaukums]["Viesnicas-numurini"][numurins]["Rezervets-LIDZ"] = "";
		}
	}

	std::ofstream x("viesnicuData.json");
	x << std::setw(4) << jj << std::endl;

	std::cout << "Darits!";
	system("pause");
	return;
}

void mainit_key(json &jj, std::string& labojamais, std::string& labojums)
{
	auto itr = jj.find(labojamais);
	std::swap(jj[labojums], itr.value());
	jj.erase(itr);
}

void labosana_test(std::string labojamais, std::string nosaukums)
{
	std::ifstream i("viesnicuData.json");
	if (i.is_open()) {
		i >> jj;
	}

	mainit_key(jj, labojamais, nosaukums);

	std::ofstream o("viesnicuData.json");
	o << std::setw(4) << jj << '\n';
}

void labotvalsti() {
	bool nepareizi = false;

	std::string valstis[250], viesnicas[250];
	std::string jnosaukums, jsaisinajums, jviesnicasnosaukums, jzvaigznes, jnumurinuSK;
	int jmaxviesnicas, jcenaparnr;
	int izvele;
	int izvele2;

	std::string nosaukums, saisinajums, viesnicasnosaukums, zvaigznes, numurinuSK;
	int maxviesnicas, cenaparnr;

	std::ifstream dati("viesnicuData.json");
	if (dati.is_open()) {
		dati >> jj;
	}

	int x = 0;
	for (auto& el : jj.items()) {
		std::cout << x + 1 << "." << el.key() << std::endl;
		valstis[x] = el.key();
		x++;
	}

	std::cout << "Izvele: ";
	std::cin >> izvele;
	system("cls");
	std::string labojamais = valstis[izvele - 1];


	std::cout << "Izvelaties ko velaties veikt ar izveleto valsti\n";
	std::cout << "1.Labot valsts nosaukumu\n";
	std::cout << "2.Labot valsts saisinajumu\n";
	std::cout << "3.labot maximalo viesnicu skaitu valsti\n";
	std::cout << "4.labot viesnicu nosaukumus\n";
	std::cout << "5.labot viesnicu zvaigznu skaitu\n";
	std::cout << "6.labot numurina cenu\n";
	std::cout << "7.labot numurina skaitu\n";
	std::cout << "8.iziet\n";
	std::cout << "Izvele: ";
	std::cin >> izvele2;

	if (izvele2 == 1) {
		system("cls");
		std::cout << valstis[izvele - 1];
		std::cout << "\nievadiet jaunu valsti";
		std::cin >> jnosaukums;
		std::transform(jnosaukums.begin(), jnosaukums.end(), jnosaukums.begin(), ::tolower);
		labosana_test(labojamais, jnosaukums);
		adminMain();
	}
	else if (izvele2 == 2) {
		std::cout << "Esosais saisinajums: " << jj[valstis[izvele - 1]]["Saisinajums"] << "\n";
		std::cout << "Jauns saisinajums: ";
		std::cin >> jsaisinajums;
		jj[valstis[izvele - 1]]["Saisinajums"] = jsaisinajums;
		std::ofstream o("viesnicuData.json");
		o << std::setw(4) << jj << '\n';
	}
	else if (izvele2 == 3) {
		int esosaisviesnicuskaits = jj[valstis[izvele - 1]]["Max-Viesnicas"];

		std::cout << "Max viesnicu skaits: " << esosaisviesnicuskaits << "\n";
		std::cout << "Jauns max viesnicu skaits ";
		std::cin >> jmaxviesnicas;

		jj[valstis[izvele - 1]]["Max-Viesnicas"] = jmaxviesnicas;

		std::ofstream h("viesnicuData.json");
		h << std::setw(4) << jj << '\n';
		h.close();

		int i = 0;
		for (auto& el : jj.at(valstis[izvele - 1]).at("Viesnicas").items()) {
			viesnicas[i] = el.key();
			i++;
		}

		if (jmaxviesnicas < esosaisviesnicuskaits) {
			for (int j = esosaisviesnicuskaits; j > jmaxviesnicas; j--) {
				jj.at(valstis[izvele - 1]).at("Viesnicas").erase(viesnicas[j - 1]);
			}
		}
		else if (jmaxviesnicas == esosaisviesnicuskaits) {
			return;
		}
		else {
			for (int j = esosaisviesnicuskaits; j < jmaxviesnicas; j++) {
				system("cls");
				do {
					std::cout << "Ievadiet viesnicas nosaukumu:";
					std::getline(std::cin >> std::ws, viesnicasnosaukums);
					std::transform(viesnicasnosaukums.begin(), viesnicasnosaukums.end(), viesnicasnosaukums.begin(), ::tolower);
				} while (kluda_valsts(viesnicasnosaukums));

				do {
					std::cout << "Ievadiet viesnicas zvaigznu skaitu:";
					std::cin >> zvaigznes;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						nepareizi = true;
					}
					else {
						nepareizi = false;
					}
				} while (nepareizi);

				do {
					std::cout << "Ievadiet cenu par numurinu:";
					std::cin >> cenaparnr;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						nepareizi = true;
					}
					else {
						nepareizi = false;
					}
				} while (nepareizi);
				jj[valstis[izvele - 1]]["Viesnicas"][viesnicasnosaukums]["Viesnicas-nosaukums"] = viesnicasnosaukums;
				jj[valstis[izvele - 1]]["Viesnicas"][viesnicasnosaukums]["Viesnicas-zvaigznes"] = zvaigznes;
				jj[valstis[izvele - 1]]["Viesnicas"][viesnicasnosaukums]["Viesnicas-cena-par-numurinu"] = cenaparnr;

				jj[valstis[izvele - 1]]["Max-Viesnicas"] = jmaxviesnicas;
				std::ofstream o("viesnicuData.json");
				o << std::setw(4) << jj << '\n';
			}
		}
		std::ofstream c("viesnicuData.json");
		c << std::setw(4) << jj << '\n';
	}
	else if (izvele2 == 4) {
		int i = 0, viesnicasIzvele = 0;

		system("cls");
		std::cout << "Izvelieties viesnicu: " << std::endl;

		for (auto& el : jj.at(valstis[izvele - 1]).at("Viesnicas").items()) {
			std::cout << i + 1 << "." << el.key() << "\n";
			viesnicas[i] = el.key();
			i++;
		}

		std::cout << "Izvele: ";
		std::cin >> viesnicasIzvele;

		nosaukums = viesnicas[viesnicasIzvele - 1];
	
		system("cls");

		std::cout << "Nosaukums: " << nosaukums;
		std::cout << "Jaunais nosaukums: ";
		std::getline(std::cin >> std::ws, jnosaukums);
		std::transform(jnosaukums.begin(), jnosaukums.end(), jnosaukums.begin(), ::tolower);

		auto itr = jj.at(valstis[izvele-1]).at("Viesnicas").find(nosaukums);
		std::swap(jj[valstis[izvele-1]]["Viesnicas"][jnosaukums], itr.value());
		jj.erase(itr);

		std::ofstream h("viesnicuData.json");
		h << std::setw(4) << jj << '\n';
	}
	else if (izvele2 == 5) {
		int i = 0, viesnicasIzvele;
		for (auto& el : jj.at(valstis[izvele - 1]).at("Viesnicas").items()) {
			std::cout << i + 1 << "." << el.key() << "\n";
			viesnicas[i] = el.key();
			i++;
		}
		std::cout << "Izvele: ";
		std::cin >> viesnicasIzvele;

		system("pause");

		zvaigznes = jj.at(valstis[izvele - 1]).at("Viesnicas").at(viesnicas[viesnicasIzvele - 1]).at("Viesnicas-zvaigznes");

		system("cls");

		std::cout << "Zvaigznes: " << zvaigznes << std::endl;
		std::cout << "Jaunais zvaigznu skaits: ";
		std::cin >> jzvaigznes;

		jj[valstis[izvele - 1]]["Viesnicas"][viesnicas[viesnicasIzvele - 1]]["Viesnicas-zvaigznes"] = jzvaigznes;

		std::ofstream c("viesnicuData.json");
		c << std::setw(4) << jj << '\n';

	}
	else if (izvele2 == 6) {
		int i = 0, viesnicasIzvele;
		for (auto& el : jj.at(valstis[izvele - 1]).at("Viesnicas").items()) {
			std::cout << i + 1 << "." << el.key() << "\n";
			viesnicas[i] = el.key();
			i++;
		}
		std::cout << "Izvele: ";
		std::cin >> viesnicasIzvele;
	
		system("pause");

		cenaparnr = jj.at(valstis[izvele - 1]).at("Viesnicas").at(viesnicas[viesnicasIzvele - 1]).at("Viesnicas-cena-par-numurinu");
	
		system("cls");

		std::cout << "Cena par numurinu: " << cenaparnr << std::endl;
		std::cout << "Jauna cena par numurinu: ";
		std::cin >> jcenaparnr;

		jj[valstis[izvele - 1]]["Viesnicas"][viesnicas[viesnicasIzvele - 1]]["Viesnicas-cena-par-numurinu"] = jcenaparnr;

		std::ofstream c("viesnicuData.json");
		c << std::setw(4) << jj << '\n';
	}
	else if (izvele2 == 7) {
		int i = 0, viesnicasIzvele;
		std::string::size_type izmers;

		for (auto& el : jj.at(valstis[izvele - 1]).at("Viesnicas").items()) {
			std::cout << i + 1 << "." << el.key() << "\n";
			viesnicas[i] = el.key();
			i++;
		}
		std::cout << "Izvele: ";
		std::cin >> viesnicasIzvele;

		system("pause");

		numurinuSK = jj.at(valstis[izvele - 1]).at("Viesnicas").at(viesnicas[viesnicasIzvele - 1]).at("Viesnicas-numurinu-skaits");

		system("cls");

		std::cout << "Numurinu skaits: " << numurinuSK << std::endl;
		std::cout << "Jaunais numurinu skaits: ";
		std::cin >> jnumurinuSK;

		jj[valstis[izvele - 1]]["Viesnicas"][viesnicas[viesnicasIzvele - 1]]["Viesnicas-numurinu-skaits"] = jnumurinuSK;

		int INTnumSK = std::stoi(numurinuSK, &izmers);
		int INTjnumSK = std::stoi(jnumurinuSK, &izmers);

		if (INTnumSK < INTjnumSK) {
			for (int x = INTnumSK + 1; x <= INTjnumSK; x++) {
				std::string numurins = std::to_string(x);
				jj[valstis[izvele - 1]]["Viesnicas"][viesnicas[viesnicasIzvele - 1]]["Viesnicas-numurini"][numurins]["Rezervets"] = false;
				jj[valstis[izvele - 1]]["Viesnicas"][viesnicas[viesnicasIzvele - 1]]["Viesnicas-numurini"][numurins]["Rezervets-NO"] = "";
				jj[valstis[izvele - 1]]["Viesnicas"][viesnicas[viesnicasIzvele - 1]]["Viesnicas-numurini"][numurins]["Rezervets-LIDZ"] = "";
			}
		}
		else if (INTnumSK > INTjnumSK) {
			for (int x = INTnumSK; x > INTjnumSK; x--) {
				std::string numurins = std::to_string(x);
				jj.at(valstis[izvele - 1]).at("Viesnicas").at(viesnicas[viesnicasIzvele - 1]).at("Viesnicas-numurini").erase(numurins);
			}
		}


		std::ofstream c("viesnicuData.json");
		c << std::setw(4) << jj << '\n';
	}
	else if(izvele2 == 8) {
		return;
	}
	else {
		adminMain();
	}
	system("pause");
}

void dzestvalsti() {
	int izvele, izvele2, izvele3;
	std::string viesnicas[250], valstis[250];

	std::ifstream dati("viesnicuData.json");
	if (dati.is_open()) {
		dati >> jj;
	}
	system("cls");
	std::cout << "Izvelies ko velies dzest!\n";
	std::cout << "1.Valsts vai viesnica\n";
	std::cout << "2.Atpakal\n";
	std::cin >> izvele;

	if (izvele == 1) {
		int h = 0;
		system("cls");
		for (auto& el : jj.items()) {
			std::cout << h + 1 << "." << el.key() << "\n";
			valstis[h] = el.key();
			h++;
		}
		std::cout << h + 1<< ".atpakal\n";
		std::cout << "izvele: ";
		std::cin >> izvele2;

		if (izvele2 == h + 1) {
			dzestvalsti();
		}//parbauda vai nav ievadits random simbols lai nenobugojas

		system("cls");

		std::cout << "DZEST\n";
		std::cout << "1.viesnicu\n";
		std::cout << "2.valsti[NEATGRIEZENISKI UZREIZ]\n";
		std::cout << "3.atpakal\n";
		std::cout << "izvele: ";
		std::cin >> izvele3;
		
		if (izvele3 == 1) {
			int g = 0;
			system("cls");
			for (auto& el : jj.at(valstis[izvele2 - 1]).at("Viesnicas").items()) {
				std::cout << g + 1 << "." << el.key() << "\n";
				viesnicas[g] = el.key();
				g++;
			}
			std::cout << g + 1 << ".atpakal\n";
			std::cout << "izveleies viesnicu kur dzest[Neatgriezeniski]: ";
			std::cin >> izvele3;

			if (izvele3 == g + 1) {
				dzestvalsti();
			}//parbauda vai nav ievadits random simbols lai nenobugojas

			jj.at(valstis[izvele2 - 1]).at("Viesnicas").erase(viesnicas[izvele3 - 1]);

			std::ofstream c("viesnicuData.json");
			c << std::setw(4) << jj << '\n';
		}
		else if (izvele3 == 2) {
			jj.erase(valstis[izvele2 - 1]);
			std::ofstream c("viesnicuData.json");
			c << std::setw(4) << jj << '\n';
		}
		else if (izvele3 == 3) {
			dzestvalsti();
		}
		else {
			dzestvalsti();
		}

	}
	else if (izvele == 2) {
		return;
	}
	else {
		dzestvalsti();
	}
}

void adminMain() {
	int izvele;
	system("cls");

	std::cout << "Sveicinats administrator\n";
	std::cout << "1.Pievienot valsti\n";
	std::cout << "2.Labot valsti\n";
	std::cout << "3.Dzest valsti\n";
	std::cout << "4.Iziet\n";
	std::cout << "Izvele: ";
	std::cin >> izvele;

	switch (izvele)
	{
	case 1: pievienotvalsti(); adminMain(); break;
	case 2: labotvalsti(); adminMain(); break;
	case 3: dzestvalsti(); adminMain(); break;
	case 4: return; break;
	default:
		adminMain();
		break;
	}

	system("pause");
}