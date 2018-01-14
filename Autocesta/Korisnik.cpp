#include "stdafx.h"
#include "Korisnik.h"


Korisnik::Korisnik(string ime, string prezime, string username, string password, int tip)
{
	m_sIme = ime;
	m_sPrezime = prezime;
	m_sUsername = username;
	m_sPassword = password;
	m_sTip = tip;
}


Korisnik::~Korisnik()
{
}
