#pragma once
#include <iomanip>
#include <string>
#include <iostream>
#include <vector>
#include "Korisnik.h"
#include "NaplatnePostaje.h"
#include "Vozilo.h"
#include "Skupine.h"
#include "tinyxml2.h"
#include <cmath>
#include "conio.h"
#include<fstream>
#define PI 4.0*atan(1.0)
using namespace std;
using namespace tinyxml2;

class Autocesta
{
public:
	Autocesta();
	~Autocesta();

	void UcitajPostaje();
	void IspisiPostajeAdmin();
	void IspisiPostajeKorisnik();
	void DajIzbornik();
	void LogIn();
	void UcitajKorisnike();
	void DodajPostaju();
	void ZapisiPromjeneXML();
	void Putovanje();
	void UcitajVozila();
	void ZapisiPromjeneVozila();
	void DodajVozilo();
	void UcitajSkupine();
	void IspisiVozila();
	void Povratak();
	double Haversine(double lat1, double lon1, double lat2, double lon2);

	XMLDocument m_oPostajeXmlDocument;
	XMLElement *m_pPostajeNaplatnaPostaja;

	XMLDocument m_oKorisnikXmlDocument;
	XMLElement *m_pKorisniciKorisnik;

	XMLDocument m_oVozilaXmlDocument;
	XMLElement *m_pVozilaVozilo;

	XMLDocument m_oSkupineXmlDocument;
	XMLElement *m_pSkupine;

	vector<Korisnik*>m_vKorisnik;
	vector<NaplatnePostaje*>m_vPostaje;
	vector<Vozilo*>m_vVozila;
	vector<Skupine*>m_vSkupine;
	

	
};

