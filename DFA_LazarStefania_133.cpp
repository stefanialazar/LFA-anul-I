#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");


int N, M, S, nrF, nrCuv, i, j, z, stareCurenta, lung;
char w;
struct tranz
{
	int x, y;
	char l;
};
vector <int> st_finale;
vector <int> stari;
vector <tranz> tranzitii;
string cuvant;
bool acceptat;


int main()
{
	f >> N; //numarul de stari ale automatului
	for (i = 0; i < N; i++) //starile automatului
	{
		f >> z;
		stari.push_back(z);
	}
	f >> M; //numarul de tranzitii
	
	for (i = 0; i < M; i++)
	{
		tranzitii.push_back(tranz());
		f >> z;
		tranzitii[i].x = z; //starea (nodul) din care pleaca tranzitia
		f >> z;
		tranzitii[i].y = z; //starea in care ajunge tranzitia
		f >> w;
		tranzitii[i].l = w; //litera tranzitiei
	}
	f >> S; //starea initiala
	f >> nrF; //numarul de stari finale
	for (i = 0; i < nrF; i++)//starile finale
	{
		f >> z;
		st_finale.push_back(z);
	}
	f >> nrCuv;//numarul de cuvinte ce urmeaza a fi verificate

	for (i = 0; i < nrCuv; i++)
	{
		stareCurenta = S;
		f >> cuvant;
		acceptat = 0;
		lung = cuvant.size();
		for (j = 0; j < lung; j++)
		{
			w = cuvant[j];
			for (z = 0; z < tranzitii.size(); z++)
			{
				if (stareCurenta == tranzitii[z].x && w == tranzitii[z].l)
				{
					stareCurenta = tranzitii[z].y;
					break;
				}
			}
		}
		
		for (j = 0; j < nrF; j++)//starile finale
		{
			
			if (stareCurenta == st_finale[j])
			{
				acceptat = 1;
				break;
			}
		}
		if (acceptat == 0)
			g << "NU" << endl;
		else
			g << "DA" << endl;
	}
}