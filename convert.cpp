#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;




int main()
{
	setlocale(LC_ALL, "rus");

	const int SIZE = 12;

	ifstream file;

	string month, service;

	string  kalendar[SIZE] = { "январь", "февраль", "март", "апрель", "май", "июнь", "июль", "август", "сентябрь", "октябрь", "ноябрь", "декабрь" };

	map <string, set<string>> month_serv;

	set <string> lines, services, serv;



	file.open("чеки.txt");

	if (!file.is_open())
	{
		cout << "Ошибка открытия файла!\n";
		return 1;
	}

	else
	{
		cout << "Файл открыт!\n";
		string line;


		while (getline(file, line))

			lines.insert(line);

		if (lines.empty())
		{
			cout << "Файл пуст!\n\n";
			return -1;
		}


	}
	file.close(); // закрываю освобождая ресурс

	ofstream out;
	out.open("чеки_по_папкам.txt");

	for (int i = 0; i < SIZE; ++i)
	{
		for (string line : lines)
		{

			int pos = line.find("_"); // Первое подчеркивание разделяет услугу и месяц
			if (pos != string::npos)
			{
				service = line.substr(0, pos);

				month = line.substr(pos + 1, line.find(".") - pos - 1); // Извлекаем месяц из названия файла

				services.insert(service); //все сервисы


			}



			if (kalendar[i] == month)
			{
				out << month + '\\' + line << endl;



				if (month_serv.find(kalendar[i]) == month_serv.end())
				{

					serv.insert(service);
					month_serv.insert(make_pair(kalendar[i], serv));

				}

				else
				{
					month_serv[kalendar[i]].insert(service);

				}



			}

			else { continue; }


		}



		out << endl;
	}


	out << "Не оплачено:\n";

	for (int i = 0; i < SIZE; ++i)
	{
		if (month_serv[kalendar[i]] == services)
		{
			cout << "Все оплачено в " + kalendar[i] << endl;
		}

		else
		{
			out << kalendar[i] << endl;


			for (auto line : services)
			{

				if (month_serv[kalendar[i]].find(line) != month_serv[kalendar[i]].end())
					continue;

				else
					out << line << endl;
			}


			out << endl;

		}

	}


	out.close();

	return 0;
}
