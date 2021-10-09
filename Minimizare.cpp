#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

ifstream m("minimizare.in");
ofstream mout("minimizare.out");

int N, M, nrF, i, j, d, d1, mult;
string z, S, tranz1, tranz2;
set <int> numere;

struct tranz
{
	string x, y;
	int l;
};

set <string> st_finaleDFA;
vector <string> stariDFA;
vector <tranz> tranzitiiDFA;

//minimizare
int N_min, M_min, nrF_min;
string S_min;
set <string> aux, elimina_nefinale, elimina_finale;
vector <set <string>> st_finaleDFA_min;
vector <set <string>> st_nefinaleDFA_min;
vector <tranz> tranzitiiDFA_min;
vector <string> stariDFA_min;

int main()
{
	{
		m >> N; //numarul de stari ale automatului (NFA = DFA)
		for (i = 0; i < N; i++) //starile automatului (NFA)
		{
			m >> z;
			stariDFA.push_back(z);
		}
		m >> M; //numarul de tranzitii (NFA)
		for (i = 0; i < M; i++)
		{
			tranzitiiDFA.push_back(tranz());
			m >> z;
			tranzitiiDFA[i].x = z; //starea (nodul) din care pleaca tranzitia
			m >> z;
			tranzitiiDFA[i].y = z; //starea in care ajunge tranzitia
			m >> d;
			tranzitiiDFA[i].l = d; //numarul tranzitiei
			numere.insert(d);
		}
		m >> S; //starea initiala (NFA = DFA)
		m >> nrF; //numarul de stari finale (NFA)
		for (i = 0; i < nrF; i++)//starile finale (NFA)
		{
			m >> z;
			st_finaleDFA.insert(z);
		}
	}

	//minimizarea DFA-ului

	st_nefinaleDFA_min.push_back(aux);
	st_finaleDFA_min.push_back(aux);

	for (auto it = st_finaleDFA.begin(); it != st_finaleDFA.end(); it++)
	{
		st_finaleDFA_min[0].insert(*it);
	}
	
	for (i = 0; i < tranzitiiDFA.size(); i++)
	{
		st_nefinaleDFA_min[0].insert(tranzitiiDFA[i].y);
	}
	for (auto it = st_finaleDFA_min[0].begin(); it != st_finaleDFA_min[0].end(); it++)
	{
		st_nefinaleDFA_min[0].erase(*it);
	}
	// st_nefinaleDFA_min[0] = starile din DFA ce nu sunt finale, fara starile unreachable
	// st_finaleDFA_min[0] = starile din DFA ce sunt finale
	
	bool verifica = 1;
	while( verifica == 1 )
	{
		for( d = 0; d < st_nefinaleDFA_min.size(); d++)
		{
			if (st_nefinaleDFA_min[d].size() > 1)
			{
				auto it = st_nefinaleDFA_min[d].begin();
				for (auto it2 = st_nefinaleDFA_min[d].begin(); it2 != st_nefinaleDFA_min[d].end(); it2++)
				{
					bool bun1 = 0, bun2 = 0;
					if (*it != *it2)
					{
						for (auto n : numere)
						{
							for (i = 0; i < tranzitiiDFA.size(); i++)
							{
								if (tranzitiiDFA[i].x == *it && tranzitiiDFA[i].l == n)
									tranz1 = tranzitiiDFA[i].y;
								else if (tranzitiiDFA[i].x == *it2 && tranzitiiDFA[i].l == n)
									tranz2 = tranzitiiDFA[i].y;
							}

							//trebuie sa verificam daca tranzitiile se duc in aceeasi multime

							for (i = 0; i < st_nefinaleDFA_min.size(); i++)
							{
								//verificam in multimiile cu starile ce nu sunt finale
								const bool gasit1 = st_nefinaleDFA_min[i].find(tranz1) != st_nefinaleDFA_min[i].end();
								const bool gasit2 = st_nefinaleDFA_min[i].find(tranz2) != st_nefinaleDFA_min[i].end();
								if (gasit1 == 1 && gasit2 == 1)
								{
									if (bun1 == 1)
										bun2 = 1;
									else
										bun1 = 1;
								}
							}
							for (i = 0; i < st_finaleDFA_min.size(); i++)
							{
								//verificam in multimiile cu starile ce sunt finale
								const bool gasit1 = st_finaleDFA_min[i].find(tranz1) != st_finaleDFA_min[i].end();
								const bool gasit2 = st_finaleDFA_min[i].find(tranz2) != st_finaleDFA_min[i].end();
								if (gasit1 == 1 && gasit2 == 1)
								{
									if (bun2 == 1)
										bun1 = 1;
									else
										bun2 = 1;
								}
							}
						}
						if (bun1 == 1 && bun2 == 1)
							continue;
						else
							elimina_nefinale.insert(*it2);
					}
				}
			}
		}

		for (d = 0; d < st_finaleDFA_min.size(); d++)
		{
			if (st_finaleDFA_min[d].size() > 1)
			{
				auto it = st_finaleDFA_min[d].begin();

				for (auto it2 = st_finaleDFA_min[d].begin(); it2 != st_finaleDFA_min[d].end(); it2++)
				{
					bool bun1 = 0, bun2 = 0;
					if (*it != *it2)
					{
						for (auto n : numere)
						{
							for (i = 0; i < tranzitiiDFA.size(); i++)
							{
								if (tranzitiiDFA[i].x == *it && tranzitiiDFA[i].l == n)
									tranz1 = tranzitiiDFA[i].y;
								else if (tranzitiiDFA[i].x == *it2 && tranzitiiDFA[i].l == n)
									tranz2 = tranzitiiDFA[i].y;
							}
							//trebuie sa verificam daca tranzitiile se duc in aceeasi multime

							for (i = 0; i < st_nefinaleDFA_min.size(); i++)
							{
								//verificam in multimiile cu starile ce nu sunt finale
								const bool gasit1 = st_nefinaleDFA_min[i].find(tranz1) != st_nefinaleDFA_min[i].end();
								const bool gasit2 = st_nefinaleDFA_min[i].find(tranz2) != st_nefinaleDFA_min[i].end();
								if (gasit1 == 1 && gasit2 == 1)
								{
									if (bun1 == 1)
										bun2 = 1;
									else
										bun1 = 1;
								}
							}
							for (i = 0; i < st_finaleDFA_min.size(); i++)
							{
								//verificam in multimiile cu starile ce sunt finale
								const bool gasit1 = st_finaleDFA_min[i].find(tranz1) != st_finaleDFA_min[i].end();
								const bool gasit2 = st_finaleDFA_min[i].find(tranz2) != st_finaleDFA_min[i].end();;
								if (gasit1 == 1 && gasit2 == 1)
								{
									if (bun2 == 1)
										bun1 = 1;
									else
										bun2 = 1;
								}
							}
						}
						if (bun1 == 1 && bun2 == 1)
							continue;
						else
							elimina_finale.insert(*it2);
					}
				}
			}
		}

		if (elimina_nefinale.size() == 0 && elimina_finale.size() == 0)
			verifica = 0;

		if (elimina_nefinale.size() != 0)
		{
			i = st_nefinaleDFA_min.size();
			st_nefinaleDFA_min.push_back(aux);
			for (auto it = elimina_nefinale.begin(); it != elimina_nefinale.end(); it++)
			{
				for (j = 0; j < st_nefinaleDFA_min.size(); j++)
				{
					const bool gasit = st_nefinaleDFA_min[j].find(*it) != st_nefinaleDFA_min[j].end();
					if (gasit == 1)
					{
						st_nefinaleDFA_min[i].insert(*it);
						st_nefinaleDFA_min[j].erase(*it);
						break;
					}
						
				}
				
			}
			elimina_nefinale.clear();
		}

		if (elimina_finale.size() != 0)
		{
			i = st_finaleDFA_min.size();
			st_finaleDFA_min.push_back(aux);
			for (auto it = elimina_finale.begin(); it != elimina_finale.end(); it++)
			{
				for (j = 0; j < st_finaleDFA_min.size(); j++)
				{
					const bool gasit = st_finaleDFA_min[j].find(*it) != st_finaleDFA_min[j].end();
					if (gasit == 1)
					{
						st_finaleDFA_min[i].insert(*it);
						st_finaleDFA_min[j].erase(*it);
						break;
					}
				}
			}
			elimina_finale.clear();
		}
	}

	for (i = 0; i < st_nefinaleDFA_min.size(); i++)
	{
		if (st_nefinaleDFA_min[i].size() > 1)
		{
			string s;
			auto it = st_nefinaleDFA_min[i].begin();
			s += *it;
			for (auto it2 = it; it2 != st_nefinaleDFA_min[i].end(); it2++)
				if (*it != *it2)
					s += *it2;
			st_nefinaleDFA_min[i].clear();
			st_nefinaleDFA_min[i].insert(s);
			stariDFA_min.push_back(s);
		}
		else
		{
			string s;
			auto it = st_nefinaleDFA_min[i].begin();
			s += *it;
			stariDFA_min.push_back(s);
		}
	}

	for (i = 0; i < st_finaleDFA_min.size(); i++)
	{
		if (st_finaleDFA_min[i].size() > 1)
		{
			string s;
			auto it = st_finaleDFA_min[i].begin();
			s += *it;
			for (auto it2 = it; it2 != st_finaleDFA_min[i].end(); it2++)
				if (*it != *it2)
					s += *it2;
			st_finaleDFA_min[i].clear();
			st_finaleDFA_min[i].insert(s);
			stariDFA_min.push_back(s);
		}
		else
		{
			string s;
			auto it = st_finaleDFA_min[i].begin();
			s += *it;
			stariDFA_min.push_back(s);
		}
	}

	N_min += st_nefinaleDFA_min.size();
	N_min += st_finaleDFA_min.size();
	nrF_min += st_finaleDFA_min.size();
	mout << N_min << endl;

	for (i = 0; i < stariDFA_min.size(); i++)
	{
		mout << stariDFA_min[i] << " ";
	}
	mout << endl;

	for (i = 0; i < stariDFA_min.size(); i++)
	{
		string it = stariDFA_min[i];
		for (auto n : numere)
		{
			tranzitiiDFA_min.push_back(tranz());
			j = tranzitiiDFA_min.size();
			tranzitiiDFA_min[j - 1].x = it;
			tranzitiiDFA_min[j - 1].y = "";
			tranzitiiDFA_min[j - 1].l = n;
			for (d = 0; d < tranzitiiDFA.size(); d++)
			{
				string s = "";
				s.push_back(tranzitiiDFA_min[j - 1].x[0]);
				if (tranzitiiDFA[d].l == n && tranzitiiDFA[d].x == s)
				{
					string s1 = tranzitiiDFA[d].y;
					for (d1 = 0; d1 < stariDFA_min.size(); d1++)
						if (stariDFA_min[d1].find(s1) != std::string::npos)
							tranzitiiDFA_min[j - 1].y = stariDFA_min[d1];
				}
			}
		}
	}
	mout << tranzitiiDFA_min.size() << endl;

	for (i = 0; i < tranzitiiDFA_min.size(); i++)
	{
		mout << tranzitiiDFA_min[i].x << " " << tranzitiiDFA_min[i].y << " " << tranzitiiDFA_min[i].l << endl;
	}

	for (i = 0; i < stariDFA_min.size(); i++) //caut starea initiala in dfa minimizat
		if (stariDFA_min[i].find(S) != std::string::npos)
		{
			S_min = stariDFA_min[i];
			break;
		}
	mout << S_min << endl << nrF_min << endl;

	for (i = 0; i < st_finaleDFA_min.size(); i++)
	{
		for (auto it = st_finaleDFA_min[i].begin(); it != st_finaleDFA_min[i].end(); it++)
		{
			mout << *it << " ";
		}
	}
}