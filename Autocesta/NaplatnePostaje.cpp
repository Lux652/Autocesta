#include "stdafx.h"
#include "NaplatnePostaje.h"


NaplatnePostaje::NaplatnePostaje(int id, string naziv, float lat, float lng)
{
	m_nID = id;
	m_sNaziv = naziv;
	m_fLat = lat;
	m_fLng = lng;
}


NaplatnePostaje::~NaplatnePostaje()
{
}

void NaplatnePostaje::PrikaziSve()
{

}