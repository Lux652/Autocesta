#include "stdafx.h"
#include "Vozilo.h"


Vozilo::Vozilo(int id,string naziv, int skupina)
{
	m_sNaziv = naziv;
	m_nSkupina = skupina;
	m_nID = id;
}


Vozilo::~Vozilo()
{
}
