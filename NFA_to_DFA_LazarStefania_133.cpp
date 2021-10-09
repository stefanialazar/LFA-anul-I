#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

ifstream f("tema2b.in");
ofstream g("tema2b.out");

int N, M, nrF, i, j, d;
string z, S;
set <int> numere;

struct tranz
{
	string x, y;
	int l;
};

set <string> st_finaleDFA;
vector <string> st_finaleNFA;
vector <string> stariDFA;
vector <string> stariNFA;
vector <tranz> tranzitiiDFA;
vector <tranz> tranzitiiNFA;

void adaug_prima_tranz_DFA(string z)
{
	stariDFA.push_back(z);
	for (auto k : numere)
	{
		tranzitiiDFA.push_back(tranz());
		j = tranzitiiDFA.size();
		tranzitiiDFA[j - 1].x = z;
		tranzitiiDFA[j - 1].y = "";
		tranzitiiDFA[j - 1].l = k;
		for(i = 0; i < tranzitiiNFA.size(); i++)
			if (tranzitiiNFA[i].l == k && tranzitiiNFA[i].x == z)
				tranzitiiDFA[j - 1].y += tranzitiiNFA[i].y;
	
		if (tranzitiiDFA[j - 1].y.compare("") == 0)
		{
			tranzitiiDFA[j - 1].y += "DEAD"; //se duce in dead state
			string stare = tranzitiiDFA[j - 1].y;
			std::vector<string>::iterator it;
			it = find(stariDFA.begin(), stariDFA.end(), stare);
			if (it == stariDFA.end())
				stariDFA.push_back(stare);
		}
		else
		{
			sort(tranzitiiDFA[j - 1].y.begin(), tranzitiiDFA[j - 1].y.end());
			string stare = tranzitiiDFA[j - 1].y;
			std::vector<string>::iterator it;
			it = find(stariDFA.begin(), stariDFA.end(), stare);
			if (it == stariDFA.end())
				stariDFA.push_back(stare);
		}
	}
}
void adaug_tranz_DFA(string z) 
{
	for (auto k : numere)
	{
		tranzitiiDFA.push_back(tranz());
		j = tranzitiiDFA.size();

		if (z.compare("DEAD") == 0)
		{
			tranzitiiDFA[j - 1].x = z;
			tranzitiiDFA[j - 1].y = z;
			tranzitiiDFA[j - 1].l = k;
		}
		else
		{
			tranzitiiDFA[j - 1].x = z;
			tranzitiiDFA[j - 1].l = k;
			for (d = 0; d < z.size(); d++)
			{
				string s = "";
				s.push_back(z[d]);
				for (i = 0; i < tranzitiiNFA.size(); i++)
					if (tranzitiiNFA[i].x == s && tranzitiiNFA[i].l == k)
						if (tranzitiiDFA[j - 1].y.find(tranzitiiNFA[i].y) == std::string::npos)
							tranzitiiDFA[j - 1].y += tranzitiiNFA[i].y;
			}
			if (tranzitiiDFA[j - 1].y.compare("") == 0)
			{
				tranzitiiDFA[j - 1].y += "DEAD";
				string stare = tranzitiiDFA[j - 1].y;
				std::vector<string>::iterator it;
				it = find(stariDFA.begin(), stariDFA.end(), stare);
				if (it == stariDFA.end())
					stariDFA.push_back(stare);
			}
			else
			{
				sort(tranzitiiDFA[j - 1].y.begin(), tranzitiiDFA[j - 1].y.end());
				string stare = tranzitiiDFA[j - 1].y;
				std::vector<string>::iterator it;
				it = find(stariDFA.begin(), stariDFA.end(), stare);
				if (it == stariDFA.end())
					stariDFA.push_back(stare);
			}
		}
	}
}
void stari_finale_DFA()
{
	for (i = 0; i < st_finaleNFA.size(); i++)
		for (j = 0; j < stariDFA.size(); j++)
			if (stariDFA[j].find(st_finaleNFA[i]) != std::string::npos)
				st_finaleDFA.insert(stariDFA[j]);
	for (i = 0; i < stariDFA.size(); i++)
		if (stariDFA[i].compare("DEAD") == 0) //daca avem dead state , este stare finala !
			st_finaleDFA.insert("DEAD");
}

int main()
{
	f >> N; //numarul de stari ale automatului (NFA = DFA)
	for (i = 0; i < N; i++) //starile automatului (NFA)
	{
		f >> z;
		stariNFA.push_back(z);
	}

	f >> M; //numarul de tranzitii (NFA)

	for (i = 0; i < M; i++)
	{
		tranzitiiNFA.push_back(tranz());
		f >> z;
		tranzitiiNFA[i].x = z; //starea (nodul) din care pleaca tranzitia
		f >> z;
		tranzitiiNFA[i].y = z; //starea in care ajunge tranzitia
		f >> d;
		tranzitiiNFA[i].l = d; //numarul tranzitiei
		numere.insert(d);
	}

	f >> S; //starea initiala (NFA = DFA)

	f >> nrF; //numarul de stari finale (NFA)
	for (i = 0; i < nrF; i++)//starile finale (NFA)
	{
		f >> z;
		st_finaleNFA.push_back(z);
	}

	//adaugam tranz care pornesc din prima stare in DFA

	adaug_prima_tranz_DFA(stariNFA[0]);
	
	//adaugam restul tranz
	for (int idx = 1; idx < stariDFA.size(); idx++)
		adaug_tranz_DFA(stariDFA[idx]);
	
	//vedem care sunt starile finale in DFA
	stari_finale_DFA();
	
	//afisam in fisier DFA-ul
	 
	g << stariDFA.size() << endl; // numarul de stari finale (DFA)
	for (i = 0; i < stariDFA.size(); i++)//starile (DFA)
		g << stariDFA[i] << " ";
	g << endl;
	g << tranzitiiDFA.size() << endl; //numarul de tranzitii (DFA)
	for (i = 0; i < tranzitiiDFA.size(); i++) //tranz (DFA)
	{
		g << tranzitiiDFA[i].x << " " << tranzitiiDFA[i].y << " " << tranzitiiDFA[i].l << endl;
	}
	g << S << endl; //starea initiala (NFA = DFA)
	g << st_finaleDFA.size() << endl; //nr de stari finale DFA
	for (auto it = st_finaleDFA.begin(); it != st_finaleDFA.end(); it++) //starile finale DFA
	{
		g << *it << " ";
	}
	g << endl;
}