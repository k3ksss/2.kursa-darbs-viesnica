#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "Header.h"
#include "json.hpp"

using json = nlohmann::json;

json jj2;
json jj3;
json jj4;

std::string::size_type izmers;
extern std::string epasts;

struct Date
{
	int d, m, y;
};

const int monthDays[12] = { 31, 28, 31, 30, 31, 30,
						   31, 31, 30, 31, 30, 31 };
 
int countLeapYears(Date d)
{
	int years = d.y;

	if (d.m <= 2)
		years--;

	return years / 4 - years / 100 + years / 400;
}

int getDifference(Date dt1, Date dt2)
{
	long int n1 = dt1.y * 365 + dt1.d;

	for (int i = 0; i < dt1.m - 1; i++)
		n1 += monthDays[i];

	n1 += countLeapYears(dt1);

	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);
 
	return (n2 - n1);
}

int maksat(std::string sakums, std::string beigas, int cenaparnr) {
	int summa;

	int day1, day2;
	int month1, month2;
	int year1, year2;

	int daystogether;

	day1 = std::stoi(beigas.substr(0, 2), &izmers);
	day2 = std::stoi(sakums.substr(0, 2), &izmers);
	month1 = std::stoi(beigas.substr(3, 2), &izmers);
	month2 = std::stoi(sakums.substr(3, 2), &izmers);
	year1 = std::stoi(beigas.substr(6, 4), &izmers);
	year2 = std::stoi(sakums.substr(6, 4), &izmers);

	Date sakumsdate = { day2, month2, year2 };
	Date beigasdate = { day1, month1, year1 };

	daystogether = getDifference(sakumsdate, beigasdate);

	summa = daystogether * cenaparnr;

	return summa;
}

bool isDateInRange(int day, int month, int year, int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear) {
	int entryDate = (year * 10000) + (month * 100) + day;
	int startDate = (startYear * 10000) + (startMonth * 100) + startDay;
	int endDate = (endYear * 10000) + (endMonth * 100) + endDay;

	if (entryDate >= startDate && entryDate <= endDate) {
		return true;
	}
	else {
		return false;
	}
}

void rezerverNr(std::string valsts, std::string viesnica) {
	std::string izvele, cenaparnr;
	std::string numurini[250];
	std::string rezervacijasDatums, rezervacijasDatumsend;
	std::string vards, uzvards;

	bool p = false, exists = false;
	int i = 1, izvele2, izvele3, izvele4, INTcenaparnr;

	std::ifstream dati2("viesnicuData.json");
	if (dati2.is_open()) {
		dati2 >> jj2;
	}

	std::ifstream dati3("rezervacijuData.json");
	if (dati3.is_open()) {
		dati3 >> jj3;
		exists = true;
	}

	std::ifstream dati4("userData.json");
	if(dati4.is_open()){
		dati4 >> jj4;
	}

	system("cls");

	std::cout << "Jus izvelejaties viesnicu " << viesnica << "\n";
	std::cout << "Vai tiesam velaties rezervet numurinu viesnica?(1-ja, 0-ne)";
	std::cin >> izvele;

	if (izvele == "1") {
		system("cls");
		do {
			std::cout << "Jums jaievda datums, kura velaties rezervet(01-12-2019): ";
			std::getline(std::cin >> std::ws, rezervacijasDatums);
			std::cout << "Jums jaievda datums, lidz kuram velaties rezervet(05-12-2019): ";
			std::getline(std::cin >> std::ws, rezervacijasDatumsend);
			if (rezervacijasDatums[2] == '-' && rezervacijasDatums[5] == '-' && rezervacijasDatumsend[2] == '-' && rezervacijasDatumsend[5] == '-') {
				if (rezervacijasDatums.find_first_of("0123456789/") == std::string::npos && rezervacijasDatumsend.find_first_of("0123456789/") == std::string::npos) {
					p = true;
				}
			}
			else {
				p = false;
			}
		} while (p);

		system("cls");

		std::cout << "Jums ir dota iespeja izveleties kadu no brivajiem numurinjiem!\n";

		for (auto& el : jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-numurini").items()) {
			std::string num = el.key();
			if (jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-numurini").at(num).at("Rezervets") == false) {
				std::cout << i << "." << num << "\n";
				numurini[i - 1] = num;
				i++;
			}
		}

		std::cout << i << ".atpakal\n";
		std::cout << "Izvele: \n";
		std::cin >> izvele2;

		INTcenaparnr = jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-cena-par-numurinu");

		if (izvele2 == i) {
			return;
		}
		else if (izvele2 >= 1 && izvele2 < i) {
			system("cls");
			std::cout << "Vai tiesam velies rezervet so numurinu? (1-ja, 0-ne)\n";
			std::cin >> izvele3;

			if (izvele3 == 1) {
				system("cls");
				int maksa = maksat(rezervacijasDatums, rezervacijasDatumsend, INTcenaparnr);

				std::cout << "Kopa tas izmaksas " << maksa << "Euro\n";
				std::cout << "Apstiprinat? (1-ja, 0-ne)\n";
				std::cin >> izvele4;

				if (izvele4 == 1) {
					bool wrong = false;
					std::string b;
					std::string saisinajums, zvaigznes;
					std::string vardsunuzvards;

					system("cls");
					std::cout << "Saglabajam datubaze!\n";
					
					vards = jj4.at(epasts).at("Vards");
					uzvards = jj4.at(epasts).at("Uzvards");
					saisinajums = jj2.at(valsts).at("Saisinajums");
					zvaigznes = jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-zvaigznes");

					vardsunuzvards = vards + "-" + uzvards;

					int nr = rand() % 100000 + 1;
					b = std::to_string(nr);

					if (exists) {
						do {
							nr = rand() % 100000 + 1;
							b = std::to_string(nr);
							for (auto& el : jj3.at(vardsunuzvards).at("Rezervacijas").items()) {
									std::string item = el.key();
									int itemINT = std::stoi(item, &izmers);
									if (itemINT == nr) {
										wrong = true;
									}
									else {
										wrong = false;
									}
							}
						} while (wrong);
					}//nestrada pareizi

					jj3[vardsunuzvards]["Rezervacijas"][b]["valsts"] = valsts;
					jj3[vardsunuzvards]["Rezervacijas"][b]["saisinajums"] = saisinajums;
					jj3[vardsunuzvards]["Rezervacijas"][b]["numurins"] = numurini[izvele2 - 1];
					jj3[vardsunuzvards]["Rezervacijas"][b]["viesnica"] = viesnica;
					jj3[vardsunuzvards]["Rezervacijas"][b]["zvaigznes"] = zvaigznes;
					jj3[vardsunuzvards]["Rezervacijas"][b]["nr"] = b;
					jj3[vardsunuzvards]["Rezervacijas"][b]["sakums"] = rezervacijasDatums;
					jj3[vardsunuzvards]["Rezervacijas"][b]["beigas"] = rezervacijasDatumsend;
					jj3[vardsunuzvards]["Rezervacijas"][b]["kopsumma"] = maksa;

					jj2[valsts]["Viesnicas"][viesnica]["Viesnicas-numurini"][numurini[izvele2 - 1]]["Rezervets"] = true;
					jj2[valsts]["Viesnicas"][viesnica]["Viesnicas-numurini"][numurini[izvele2 - 1]]["Rezervets-LIDZ"] = rezervacijasDatumsend;
					jj2[valsts]["Viesnicas"][viesnica]["Viesnicas-numurini"][numurini[izvele2 - 1]]["Rezervets-NO"] = rezervacijasDatums;

					std::ofstream c("rezervacijuData.json");
					c << std::setw(4) << jj3 << '\n';

					std::ofstream c1("viesnicuData.json");
					c1 << std::setw(4) << jj2 << '\n';
				}
				else {
					return;
				}
			}
			else {
				rezerverNr(valsts, viesnica);
			}
		}
		else {
			rezerverNr(valsts, viesnica);
		}

		system("pause");

	}
	else {
		return;
	}
}

void mekletNrValsts() {
	std::string search;
	std::string searchResults[250], viesnicas[250];
	int i = 1, res = 0, izvele, izvele2;
	system("cls");

	std::cout << "Ievadiet valsts nosaukumu, kuru velaties meklet: ";
	std::cin >> search;

	std::ifstream dati("viesnicuData.json");
	if (dati.is_open()) {
		dati >> jj2;
	}

	for (auto& el : jj2.items()) {
		std::string nosauk = el.key();
		res = isSubstring(search, nosauk);

		if(res != -1) {
			std::cout << i << "." << nosauk << "\n";
			searchResults[i - 1] = nosauk;
			i++;
		}
		
	}

	if(i > 1){
		std::cout << i << ".atpakal\n";
		std::cout << "Izvele: ";
		std::cin >> izvele;

		if (izvele == i) {
			return;
		}
		else if (izvele != i && izvele >= 1) {
			int x = 1;
			system("cls");
			std::cout << "Izvelieties viesnicu:\n";
			for (auto& el : jj2.at(searchResults[izvele - 1]).at("Viesnicas").items()) {
				std::cout << x << "." << el.key() << "\n";
				viesnicas[x - 1] = el.key();
				x++;
			}
			std::cout << x << ".atpakal\n";
			std::cout << "Izvele: ";
			std::cin >> izvele2;

			std::string iValsts = searchResults[izvele - 1];
			std::string iViesnica = viesnicas[izvele2 - 1];
			rezerverNr(iValsts, iViesnica);
			return;
		}
		system("pause");

	}
	else
	{
		std::cout << "res:" << res << "\nNav atrasts neviens rezultats!\n";
		system("pause");
	}
}

void mekletNrViesnica() {
	std::string search;
	std::string searchResults[250],valstis[250];
	int i = 1, res = 0, izvele;
	system("cls");

	std::cout << "Ievadiet viesnicas nosaukumu, kuru velaties meklet: ";
	std::cin >> search;

	std::ifstream dati("viesnicuData.json");
	if (dati.is_open()) {
		dati >> jj2;
	}

	for (auto& el : jj2.items()) {
		std::string valsts = el.key();
		for (auto& gl : jj2.at(valsts).at("Viesnicas").items()) {
			std::string viesnica = gl.key();
			res = isSubstring(search, viesnica);

			if (res != -1) {
				std::cout << i << "." << viesnica << "\n";
				searchResults[i - 1] = viesnica;
				valstis[i - 1] = valsts;
				i++;
			}
		}
	}

	if (i > 1) {
		std::cout << i << ".atpakal\n";
		std::cout << "Izvele: ";
		std::cin >> izvele;

		if (izvele == i) {
			return;
		}
		else if (izvele != i && izvele >= 1) {
			std::string iValsts = valstis[izvele - 1];
			std::string iViesnica = searchResults[izvele - 1];
			rezerverNr(iValsts, iViesnica);
			return;
		}
		system("pause");

	}
	else
	{
		std::cout << "res:" << res << "\nNav atrasts neviens rezultats!\n";
		system("pause");
	}
}

void mekletNrZvaigznem() {
	std::string search;
	std::string searchResults[250], valstis[250];
	int i = 1, res = 0, izvele;
	system("cls");

	std::cout << "Ievadiet viesnicas zvaigznes, kuras velaties meklet: ";
	std::cin >> search;

	std::ifstream dati("viesnicuData.json");
	if (dati.is_open()) {
		dati >> jj2;
	}

	for (auto& el : jj2.items()) {
		std::string valsts = el.key();
		for (auto& gl : jj2.at(valsts).at("Viesnicas").items()) {
			std::string viesnica = gl.key();
			if(search == jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-zvaigznes")) {
					std::cout << i << "." << viesnica << "\n";
					searchResults[i - 1] = viesnica;
					valstis[i - 1] = valsts;
					i++;
			}
		}
	}

	if (i > 1) {
		std::cout << i << ".atpakal\n";
		std::cout << "Izvele: ";
		std::cin >> izvele;

		if (izvele == i) {
			return;
		}
		else if (izvele != i && izvele >= 1) {
			std::string iValsts = valstis[izvele - 1];
			std::string iViesnica = searchResults[izvele - 1];
			rezerverNr(iValsts, iViesnica);
			return;
		}
		system("pause");

	}
	else
	{
		std::cout << "res:" << res << "\nNav atrasts neviens rezultats!\n";
		system("pause");
	}
}

void mekletNrBriviemDatumiem() {
	std::string search;
	std::string searchResults[250], valstis[250];
	int i = 1, res = 0, izvele;
	system("cls");
	std::string::size_type izmers;

	std::cout << "Ievadiet datumu, kura velaties rezervet viesnicu(31-01-2019): "; //parbaude nava
	std::cin >> search;

	std::ifstream dati("viesnicuData.json");
	if (dati.is_open()) {
		dati >> jj2;
	}

	for (auto& el : jj2.items()) {
		std::string valsts = el.key();
		for (auto& gl : jj2.at(valsts).at("Viesnicas").items()) {
			std::string viesnica = gl.key();
			for (auto& cl : jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-numurini").items()) {
				std::string numurins = cl.key();
				
				if (jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-numurini").at(numurins).at("Rezervets") == false) {
					std::cout << i << "." << viesnica << "\n";
					searchResults[i - 1] = viesnica;
					valstis[i - 1] = valsts;
					i++;
				}
				else if (jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-numurini").at(numurins).at("Rezervets") == true) {
					std::string rezervetsNO = jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-numurini").at(numurins).at("Rezervets-NO");
					std::string rezervetsLIDZ = jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-numurini").at(numurins).at("Rezervets-LIDZ");

					int day1 = std::stoi(rezervetsNO.substr(0, 2), &izmers);
					int day2 = std::stoi(rezervetsLIDZ.substr(0, 2), &izmers);
					int day3 = std::stoi(search.substr(0, 2), &izmers);
					int month1 = std::stoi(rezervetsNO.substr(3, 2), &izmers);
					int month2 = std::stoi(rezervetsLIDZ.substr(3, 2), &izmers);
					int month3 = std::stoi(search.substr(3, 2), &izmers);
					int year1 = std::stoi(rezervetsNO.substr(6, 4), &izmers);
					int year2 = std::stoi(rezervetsLIDZ.substr(6, 4), &izmers);
					int year3 = std::stoi(search.substr(6, 4), &izmers);

					if (!isDateInRange(day3, month3, year3, day1, month1, year1, day3, month3, year3)) {
						std::cout << i << "." << viesnica << "\n";
						searchResults[i - 1] = viesnica;
						valstis[i - 1] = valsts;
						i++;
					}
				}
			}
		}
	}

	if (i > 1) {
		std::cout << i << ".atpakal\n";
		std::cout << "Izvele: ";
		std::cin >> izvele;

		if (izvele == i) {
			return;
		}
		else if (izvele != i && izvele >= 1) {
			std::string iValsts = valstis[izvele - 1];
			std::string iViesnica = searchResults[izvele - 1];
			rezerverNr(iValsts, iViesnica);
		}
		system("pause");

	}
	else
	{
		std::cout << "res:" << res << "\nNav atrasts neviens rezultats!\n";
		system("pause");
	}
}

void mekletNr() {
	int izvele;
	system("cls");
	std::cout << "Meklet numurinju pec\n";
	std::cout << "1.valsts\n";
	std::cout << "2.viesnicas\n";
	std::cout << "3.zvaigznem\n";
	std::cout << "4.briviem datumiem\n";
	std::cout << "5.atpakal\n";
	std::cout << "izvele:";
	std::cin >> izvele;

	switch (izvele) {
	case 1: mekletNrValsts(); mekletNr();
		break;
	case 2: mekletNrViesnica(); mekletNr();
		break;
	case 3: mekletNrZvaigznem(); mekletNr();
		break;
	case 4: mekletNrBriviemDatumiem(); mekletNr();
		break;
	case 5: return;
		break;
	default:
		mekletNr();
		break;
	}
}

void labotRezervaciju(std::string vuu, std::string reznr, std::string valsts, std::string viesnica, std::string numurins) {
	int izvele, izvele2, izvele3, cenaparnr;
	std::string sakumadatums, beigudatums, jsakumadatums, jbeigudatums;

	system("cls");

	cenaparnr = jj2.at(valsts).at("Viesnicas").at(viesnica).at("Viesnicas-cena-par-numurinu");

	std::cout << "Vai velaties labot rezervacijas datumus? (1-ja, 0-ne)\n";
	std::cin >> izvele;

	if (izvele == 1) {
		system("cls");
		sakumadatums = jj3.at(vuu).at("Rezervacijas").at(reznr).at("sakums");
		beigudatums = jj3.at(vuu).at("Rezervacijas").at(reznr).at("beigas");

		std::cout << "sakuma datums " << sakumadatums << "\n";
		std::cout << "Vai velaties labot? (1-ja, 0-ne)\n";
		std::cin >> izvele2;

		if (izvele2 == 1) {
			std::cout << "Jaunais sakuma datums: ";
			std::cin >> jsakumadatums;

			jj3[vuu]["Rezervacijas"][reznr]["sakums"] = jsakumadatums;
			jj2[valsts]["Viesnicas"][viesnica]["Viesnicas-numurini"][numurins]["Rezervets-NO"] = jsakumadatums;
			jj3[vuu]["Rezervacijas"][reznr]["kopsumma"] = maksat(jsakumadatums, beigudatums, cenaparnr);

			std::ofstream c("viesnicuData.json");
			c << std::setw(4) << jj2 << '\n';

			std::ofstream c1("rezervacijuData.json");
			c1 << std::setw(4) << jj3 << '\n';
		}
		else if (izvele == 0) {
			//
		}
		else {
			labotRezervaciju(vuu, reznr,valsts,viesnica,numurins);
		}

		sakumadatums = jj3.at(vuu).at("Rezervacijas").at(reznr).at("sakums");
		beigudatums = jj3.at(vuu).at("Rezervacijas").at(reznr).at("beigas");

		std::cout << "beigu datums " << beigudatums << "\n";
		std::cout << "Vai velaties labot? (1-ja, 0-ne)\n";
		std::cin >> izvele3;

		if (izvele3 == 1) {
			std::cout << "Jaunais beigu datums: ";
			std::cin >> jbeigudatums;

			jj3[vuu]["Rezervacijas"][reznr]["beigas"] = jbeigudatums;
			jj2[valsts]["Viesnicas"][viesnica]["Viesnicas-numurini"][numurins]["Rezervets-LIDZ"] = jbeigudatums;
			jj3[vuu]["Rezervacijas"][reznr]["kopsumma"] = maksat(sakumadatums, jbeigudatums, cenaparnr);

			std::ofstream c("viesnicuData.json");
			c << std::setw(4) << jj2 << '\n';

			std::ofstream c1("rezervacijuData.json");
			c1 << std::setw(4) << jj3 << '\n';
		}
	}
	else {
		return;
	}
}

void drukatRezervaciju(std::string vards, std::string uzvards , std::string reznr) {
	std::string vuu, valsts, saisinajums, viesnica, sakums, beigas, numurins, zvaigznes;

	vuu = vards + "-" + uzvards;

	std::ifstream dati("rezervacijuData.json");
	if (dati.is_open()) {
		dati >> jj3;
	}

	system("cls");

	valsts = jj3.at(vuu).at("Rezervacijas").at(reznr).at("valsts");
	saisinajums = jj3.at(vuu).at("Rezervacijas").at(reznr).at("saisinajums");
	viesnica = jj3.at(vuu).at("Rezervacijas").at(reznr).at("viesnica");
	sakums = jj3.at(vuu).at("Rezervacijas").at(reznr).at("sakums");
	beigas = jj3.at(vuu).at("Rezervacijas").at(reznr).at("beigas");
	numurins = jj3.at(vuu).at("Rezervacijas").at(reznr).at("numurins");
	zvaigznes = jj3.at(vuu).at("Rezervacijas").at(reznr).at("zvaigznes");

	std::ofstream rezHTML(reznr + ".html");

	rezHTML << "<!DOCTYPE html><html><head><style>table, th, td{border: 1px solid black;}</style></head><body><table>" <<
		"<tr><th>" << vards << " " << uzvards << "</th><th>" << "Rez. Nr. " << reznr << "</th></tr>" <<
		"<tr><th>" << "Valsts" << "</th><th>" << valsts << " (" << saisinajums << ")" << "</th></tr>" <<
		"<tr><th>" << "Viesnica" << "</th><th>" << viesnica << "</th></tr>" <<
		"<tr><th>" << "Sakums" << "</th><th>" << sakums << "</th></tr>" <<
		"<tr><th>" << "Beigas" << "</th><th>" << beigas << "</th></tr>" <<
		"<tr><th>" << "Numurins" << "</th><th>" << numurins << "</th></tr>" <<
		"<tr><th>" << "Zvaigznes" << "</th><th>" << zvaigznes << "</th></tr>" <<
		"</table></body></html>";
	rezHTML.close();
	std::cout << "Rezervacija sagalbata programmas mape.\n";
	system("pause");
	return;

}

void mekletrezervacijas() {
	// ??????
}

void rezervacijas() {
	std::string vards, uzvards;
	std::string vuu, valsts, viesnica, numurins;

	std::string rezervacijasnr[250];

	int izvele, izvele2;

	bool exists = false;

	std::ifstream dati("rezervacijuData.json");
	if (dati.is_open()) {
		dati >> jj3;
		exists = true;
	}
	std::ifstream dati1("userData.json");
	if (dati1.is_open()) {
		dati1 >> jj4;
	}
	std::ifstream dati2("viesnicuData.json");
	if (dati2.is_open()) {
		dati2 >> jj2;
	}

	vards = jj4.at(epasts).at("Vards");
	uzvards = jj4.at(epasts).at("Uzvards");

	vuu = vards + "-" + uzvards;

	system("cls");
	std::cout << "Jusu rezervacijas:\n";
	
	int i = 1;
	if (exists) {
		for (auto& l : jj3.at(vuu).at("Rezervacijas").items()) {
			std::cout << i << "." << l.key() << "\n";
			rezervacijasnr[i - 1] = l.key();
			i++;
		}
	}

	std::cout << i << ".atpakal";
	std::cout << "izvele:";
	std::cin >> izvele;

	valsts = jj3.at(vuu).at("Rezervacijas").at(rezervacijasnr[izvele - 1]).at("valsts");
	viesnica = jj3.at(vuu).at("Rezervacijas").at(rezervacijasnr[izvele - 1]).at("viesnica");
	numurins = jj3.at(vuu).at("Rezervacijas").at(rezervacijasnr[izvele - 1]).at("numurins");

	if (izvele == i) {
		return;
	}
	else if (izvele > 0 && izvele < i) {
		system("cls");
		std::cout << "Ko tu velies darit ar izveleto rezervaciju? \n";
		std::cout << "1.labot datumus\n";
		std::cout << "2.atcelt rezervaciju(uzreiz)\n";
		std::cout << "3.drukat rezervaciju\n";
		std::cout << "4.atpakal\n";
		std::cout << "izvele:";
		std::cin >> izvele2;

		if (izvele2 == 1) {
			labotRezervaciju(vuu, rezervacijasnr[izvele - 1], valsts, viesnica, numurins);
		}
		else if (izvele2 == 2) {
			jj3[vuu]["History-Rezervacijas"][rezervacijasnr[izvele - 1]] = jj3.at(vuu).at("Rezervacijas").at(rezervacijasnr[izvele - 1]);

			jj3.at(vuu).at("Rezervacijas").erase(rezervacijasnr[izvele - 1]);

			jj2[valsts]["Viesnicas"][viesnica]["Viesnicas-numurini"][numurins]["Rezervets"] = false;
			jj2[valsts]["Viesnicas"][viesnica]["Viesnicas-numurini"][numurins]["Rezervets-LIDZ"] = "";
			jj2[valsts]["Viesnicas"][viesnica]["Viesnicas-numurini"][numurins]["Rezervets-NO"] = "";

			std::ofstream c("viesnicuData.json");
			c << std::setw(4) << jj2 << '\n';

			std::ofstream c1("rezervacijuData.json");
			c1 << std::setw(4) << jj3 << '\n';

			system("cls");
			std::cout << "Dzests!\n";
			system("pause");
			return;
		}
		else if (izvele2 == 3) {
			drukatRezervaciju(vards,uzvards,rezervacijasnr[izvele - 1]);
		}
		else if (izvele2 == 4) {
			return;
		}
		else {
			rezervacijas();
		}
	}
	else {
		rezervacijas();
	}
}

void userMain() {
	int izvele;
	system("cls");
	std::cout << "Sveicinats lietotaj\n" << std::endl;
	
	std::cout << "1.meklet un rezervet numurinu\n";
	std::cout << "2.rezervacijas\n";

	std::cout << "3.Iziet\n";
	std::cout << "Izvele: ";
	std::cin >> izvele;

	switch (izvele)
	{
	case 1: mekletNr(); userMain(); break;
	case 2: rezervacijas(); userMain(); break;

	case 3: return;
	break;
		default:
			userMain();
			break;
	}

	system("pause");
}

