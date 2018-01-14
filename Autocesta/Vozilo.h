#pragma once
#include <string>
#include <iostream>

using namespace std;
class Vozilo
{
public:
	Vozilo(int id,string naziv, int skupina);
	~Vozilo();
	string m_sNaziv;
	int m_nSkupina;
	int m_nID;
	
};

