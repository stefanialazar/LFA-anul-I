#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <stack>
#include <string>

using namespace std;

ifstream f("tema2a.in");
ofstream g("tema2a.out");

int N, M, nrF, i, j, d, nrCuv;
string S, x, y, l, cuvant;

vector <vector <string>> tranzitiiL_NFA;
vector <string> aux;
vector <string> st_finaleL_NFA;

string DFS(string start, string cuvant, vector <vector <string>> tranzitii, vector <string> st_finale)
{
	string x, idx_cuvant, ind;
	int i, j, idx;
	idx_cuvant = "0";
	stack <string> dfs;
	dfs.push(start);
	dfs.push(idx_cuvant);
	while (!dfs.empty())
	{
		ind = dfs.top();
		dfs.pop();
		x = dfs.top();
		dfs.pop();

		for (i = 0; i < tranzitii.size(); i++)
		{
			if (tranzitii[i][0] == x)
				idx = i;
		}

		for (i = 1; i < tranzitii[idx].size(); i += 2)
		{
			string d = "";
			d += cuvant[stoi(ind)];
			if ( d == tranzitii[idx][i + 1])
			{
				if (stoi(ind) == cuvant.size() - 1)
				{
					for (j = 0; j < st_finale.size(); j++)
					{
						if (tranzitii[idx][i] == st_finale[j])
						{
							return "DA";
						}
					}
				}
				else
				{
					dfs.push(tranzitii[idx][i]);
					int ind0 = stoi(ind);
					ind0 += 1;
					ind = to_string(ind0);
					dfs.push(ind);
				}
			}
			else if (tranzitii[idx][i + 1] == "e")
			{
				if (stoi(ind) == cuvant.size() - 1)
				{
					for (j = 0; j < st_finale.size(); j++)
					{
						if (tranzitii[idx][i] == st_finale[j])
						{
							return "DA";
						}
					}
				}
				else
				{
					dfs.push(tranzitii[idx][i]);
					int ind0 = stoi(ind);
					ind0 += 1;
					ind = to_string(ind0);
					dfs.push(ind);
				}
			}
		}
	}
	return "NU";
}

int main()
{	//vom construi listele de adiacenta in felul urmator : pe pozitia 0 va fi nodul iar in rest perechi de (vecin,litera)

	f >> N; //numarul de stari ale automatului
	for (i = 0; i < N; i++)//starile automatului
	{
		f >> x;
		tranzitiiL_NFA.push_back(aux);
		tranzitiiL_NFA[i].push_back(x);
	}
	f >> M;//numarul de tranzitii
	for (i = 0; i < M; i++)
	{
		f >> x >> y >> l;
		for (j = 0; j < N; j++)
		{
			if (tranzitiiL_NFA[j][0] == x)
			{
				tranzitiiL_NFA[j].push_back(y);  //vecin
				tranzitiiL_NFA[j].push_back(l); //tranzitie
			}
		}
	}
	f >> S;//starea initiala
	f >> nrF;//starea finala
	for (i = 0; i < nrF; i++)//starile finale
	{
		f >> x;
		st_finaleL_NFA.push_back(x);
	}
	f >> nrCuv;//numarul de cuvinte ce urmeaza a fi verificate

	for (i = 0; i < nrCuv; i++)
	{
		f >> cuvant;
		g << DFS(S, cuvant, tranzitiiL_NFA, st_finaleL_NFA) << endl;
	}
}