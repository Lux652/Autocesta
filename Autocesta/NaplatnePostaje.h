#pragma once
#include <string>
#include <iostream>

using namespace std;
class NaplatnePostaje
{
public:
	NaplatnePostaje(int id, string naziv, float lat, float lng);
	~NaplatnePostaje();
	int m_nID;
	string m_sNaziv;
	float m_fLat;
	float m_fLng;
	void PrikaziSve();
};

