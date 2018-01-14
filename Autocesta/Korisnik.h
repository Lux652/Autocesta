#pragma once
#include <string>
#include <iostream>
using namespace std;

class Korisnik
{
public:
	Korisnik(string ime, string prezime, string username, string password, int tip);
	~Korisnik();
	string m_sIme;
	string m_sPrezime;
	string m_sUsername;
	string m_sPassword;
	int m_sTip;


};

