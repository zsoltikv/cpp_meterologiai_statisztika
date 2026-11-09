#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Weather
{
	string cityName;
	double maxTemp;
	int precipitation;
};

const int MAX_DAYS = 31;

int readWeather(Weather data[], int maxDays);
void printWeather(const Weather data[], int count);
int totalPrecipitation(const Weather data[], int count);
string coldestCityName(const Weather data[], int count);
int countHotDays(const Weather data[], int count);
int leastPrecipitationCityIndex(const Weather data[], int count);
bool measuredInBudapest(const Weather data[], int count);
int countNoPrecipitationDays(const Weather data[], int count);

int main()
{
	Weather data[MAX_DAYS];
	const int count = readWeather(data, MAX_DAYS);
	if (count == -1)
	{
		cerr << "Nem sikerult megnyitni az idojaras_08.txt fajlt.\n";
		return 1;
	}

	printWeather(data, count);
	cout << "\na. Osszesen " << count << " meresi nap (sor) adatait olvastuk be.\n";

	cout << "b. A honapban az osszes csapadek: " << totalPrecipitation(data, count) << " mm volt.\n";

	if (count > 0)
	{
		cout << "c. A leghidegebb telepules: " << coldestCityName(data, count) << '\n';
	}

	cout << "d. " << countHotDays(data, count) << " olyan nap volt, amikor a maximum homerseklet legalabb 33 fok volt.\n";

	const int leastPrecip = leastPrecipitationCityIndex(data, count);
	if (leastPrecip != -1)
	{
		cout << "e. Legkevesebb, de valamennyi csapadek " << data[leastPrecip].cityName
			<< " varosban volt, " << data[leastPrecip].precipitation << " mm.\n";
	}
	else
	{
		cout << "e. Nem volt olyan varos, ahol 0-nal nagyobb csapadek esett volna.\n";
	}

	if (measuredInBudapest(data, count))
	{
		cout << "f. Igen, tortent Budapesten is meres.\n";
	}
	else
	{
		cout << "f. Nem tortent Budapesten meres.\n";
	}

	cout << "g. " << countNoPrecipitationDays(data, count) << " olyan nap volt, amikor nem volt csapadek.\n";

	return 0;
}

int readWeather(Weather data[], int maxDays)
{
	ifstream input("idojaras_08.txt");
	if (!input)
	{
		return -1;
	}

	int count = 0;
	while (count < maxDays && input >> data[count].cityName >> data[count].maxTemp >> data[count].precipitation)
	{
		++count;
	}

	return count;
}

void printWeather(const Weather data[], int count)
{
	for (int i = 0; i < count; ++i)
	{
		cout << data[i].cityName << " " << data[i].maxTemp << " " << data[i].precipitation << '\n';
	}
}

int totalPrecipitation(const Weather data[], int count)
{
	int total = 0;
	for (int i = 0; i < count; ++i)
	{
		total += data[i].precipitation;
	}
	return total;
}

string coldestCityName(const Weather data[], int count)
{
	if (count == 0)
	{
		return "";
	}

	int coldest = 0;
	for (int i = 1; i < count; ++i)
	{
		if (data[i].maxTemp < data[coldest].maxTemp)
		{
			coldest = i;
		}
	}
	return data[coldest].cityName;
}

int countHotDays(const Weather data[], int count)
{
	int hotDays = 0;
	for (int i = 0; i < count; ++i)
	{
		if (data[i].maxTemp >= 33.0)
		{
			++hotDays;
		}
	}
	return hotDays;
}

int leastPrecipitationCityIndex(const Weather data[], int count)
{
	int least = -1;
	for (int i = 0; i < count; ++i)
	{
		if (data[i].precipitation > 0)
		{
			if (least == -1 || data[i].precipitation < data[least].precipitation)
			{
				least = i;
			}
		}
	}
	return least;
}

bool measuredInBudapest(const Weather data[], int count)
{
	for (int i = 0; i < count; ++i)
	{
		if (data[i].cityName == "Budapest")
		{
			return true;
		}
	}
	return false;
}

int countNoPrecipitationDays(const Weather data[], int count)
{
	int noPrecip = 0;
	for (int i = 0; i < count; ++i)
	{
		if (data[i].precipitation == 0)
		{
			++noPrecip;
		}
	}
	return noPrecip;
}