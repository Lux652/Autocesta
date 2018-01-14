#include "stdafx.h"
#include "Autocesta.h"


Autocesta::Autocesta()
{
	UcitajKorisnike();
	UcitajPostaje();
	UcitajSkupine();
	UcitajVozila();
}


Autocesta::~Autocesta()
{
}

void Autocesta::UcitajKorisnike()
{
	m_oKorisnikXmlDocument.LoadFile("Korisnici.xml");
	m_pKorisniciKorisnik = m_oKorisnikXmlDocument.FirstChildElement("Korisnici");
	XMLElement *pKorisnik;
	for (pKorisnik = m_pKorisniciKorisnik->FirstChildElement("Korisnik"); pKorisnik != NULL; pKorisnik = pKorisnik->NextSiblingElement())
	{
		string ime = pKorisnik->Attribute("ime");
		string prezime = pKorisnik->Attribute("prezime");
		string username = pKorisnik->Attribute("korisnicko_ime");
		string pass = pKorisnik->Attribute("lozinka");
		string tip = pKorisnik->Attribute("tip");
		m_vKorisnik.push_back(new Korisnik(ime, prezime, username, pass, stoi(tip)));
	}
}

void Autocesta::LogIn()
{

	string username, pass="";
	char ch;
	bool prihvatiKorisnika = false;	

	do 
	{		
		cout <<  "Username: ";
		cin >> username;
		cout << "Password: ";
		 ch = _getch();
		 while (ch != 13)
		 {
			 pass.push_back(ch);
			 cout << '*';
			 ch = _getch();
		 }	
		system("cls");
				
		for (int i = 0; i < m_vKorisnik.size(); i++) 
		{
		

			if (username == m_vKorisnik[i]->m_sUsername && pass == m_vKorisnik[i]->m_sPassword) 
			{
				prihvatiKorisnika = true;
				if (m_vKorisnik[i]->m_sTip == 0)
				{
					
					cout << "Uspjesna prijava " << m_vKorisnik[i]->m_sIme << " " << m_vKorisnik[i]->m_sPrezime << "!" << endl;
					cout << "" << endl;
					DajIzbornik();
				}
				if (m_vKorisnik[i]->m_sTip == 1)
				{
				
					cout << "Uspjesna prijava " << m_vKorisnik[i]->m_sIme << " " << m_vKorisnik[i]->m_sPrezime << "!" << endl;
					cout << "" << endl;
					Putovanje();					
				}			

			}
		}
		if (!prihvatiKorisnika)
		{
			system("cls");			
			cout <<  "Neispravno korisnicko ime ili lozinka!" << endl;
		}
	} 
	while (prihvatiKorisnika != true);

}

void Autocesta::DajIzbornik()
{
	int izbornik;


	cout << "1.Prikazi sve naplatne postaje" << endl;
	cout << "2.Dodaj naplatnu postaju" << endl;
	cout << "3.Dodaj vozilo u skupinu vozila" << endl;
	cout << "4.Novi korisnik" << endl;
	cin >> izbornik;
	system("cls");

	switch (izbornik)
	{
	case 1:
		
		IspisiPostajeAdmin();		
		break;
	case 2:
		
		DodajPostaju();
		break;
	case 3:
		
		DodajVozilo();		
		break;

	case 4:
		LogIn();
		break;

	default:
		cout << "Niste odabrali jednu od ponudenih  opcija, pokusajte ponovno" << "\n" << endl;
		DajIzbornik();

		break;
	}


}

void Autocesta::UcitajPostaje()
{
	m_oPostajeXmlDocument.LoadFile("NaplatnePostaje.xml");
	m_pPostajeNaplatnaPostaja = m_oPostajeXmlDocument.FirstChildElement("NaplatnaPostaja");
	XMLElement *pPostaja;
	for (pPostaja = m_pPostajeNaplatnaPostaja->FirstChildElement("Postaja"); pPostaja != NULL; pPostaja = pPostaja->NextSiblingElement())
	{
		string id = pPostaja->Attribute("ID");
		string naziv = pPostaja->Attribute("naziv");
		string lat = pPostaja->Attribute("lat");
		string lng = pPostaja->Attribute("lng");
		m_vPostaje.push_back(new NaplatnePostaje(stoi(id), naziv, stof(lat), stof(lng)));
	}

	}

void Autocesta::IspisiPostajeAdmin()
{
	int a = 0;
	cout << "R.br." << "\t" << "Naplatna postaja" << "\t" << "Lat" << setw(10) << "Lng" << "\t" << "\n";
	for (int i = 0; i < m_vPostaje.size(); i++)
	{

		cout << setw(2) << ++a << "." << setw(18) << m_vPostaje[i]->m_sNaziv << setw(15) << m_vPostaje[i]->m_fLat << setw(10) << m_vPostaje[i]->m_fLng << endl;;

	}
	Povratak();
}

void Autocesta::IspisiPostajeKorisnik()
{
	int a = 0;
	cout << "" << endl;
	cout << "R.br." << "\t" << "Naplatna postaja" << "\t" << "Lat" << setw(10) << "Lng" << "\t" << "\n";
	for (int i = 0; i < m_vPostaje.size(); i++)
	{

		cout << setw(2) << ++a << "." << setw(18) << m_vPostaje[i]->m_sNaziv << setw(15) << m_vPostaje[i]->m_fLat << setw(10) << m_vPostaje[i]->m_fLng << endl;;

	}
}

void Autocesta::ZapisiPromjeneXML()
{
	m_pPostajeNaplatnaPostaja->DeleteChildren();
	for (int i = 0; i < m_vPostaje.size(); i++)
	{
		XMLElement *newPostaja = m_oPostajeXmlDocument.NewElement("Postaja");
		newPostaja->SetAttribute("ID", m_vPostaje[i]->m_nID);
		newPostaja->SetAttribute("naziv", (m_vPostaje[i]->m_sNaziv).c_str());
		newPostaja->SetAttribute("lat", m_vPostaje[i]->m_fLat);
		newPostaja->SetAttribute("lng", m_vPostaje[i]->m_fLng);

		m_pPostajeNaplatnaPostaja->LinkEndChild(newPostaja);
	}
	m_oPostajeXmlDocument.SaveFile("NaplatnePostaje.xml");
}

void Autocesta::DodajPostaju()

{
	int id = 0;

	NaplatnePostaje* pointer = m_vPostaje[0];

	for (int i = 0; i < m_vPostaje.size(); i++)
	{
		if (pointer->m_nID < m_vPostaje[i]->m_nID)
		{
			pointer = m_vPostaje[i];
			id = m_vPostaje[i]->m_nID;
		}

	}
	cout << "Dodaj naplatnu postaju" << endl;
	
	string naziv;
	string lat;
	string lng;

	cout << "Unesite naziv: " << endl;
	cin >> naziv;

	cout << "Unesite Lat: " << endl;
	cin >> lat;

	cout << "Unesite Lng: " << endl;
	cin >> lng;


	m_vPostaje.push_back(new NaplatnePostaje(++id, naziv, stof(lat), stof(lng)));
	ZapisiPromjeneXML();

	Povratak();
}

void Autocesta::Putovanje()
{

	string s_Polaziste;
	int n_PolazisteOdabir;
	int n_OdredisteOdabir;
	string s_Odrediste;
	int n_vozilo;
	int n_tip;
	float f_skupina=0;
	static double d_Udaljenost;
	static double d_Cijena;
	float f_Trajanje;
	double lat1, lon1, lat2, lon2;


	IspisiPostajeKorisnik();
	cout << "" << endl;
	cout << "Odaberite polaziste" << endl;
	cin >> n_PolazisteOdabir;
	cout << "Odaberite odrediste" << endl;
	cin >> n_OdredisteOdabir;
	cout << "" << endl;

	


	for (int i = 0; i < m_vPostaje.size(); i++)
	{
		if (n_PolazisteOdabir == m_vPostaje[i]->m_nID)
		{
			s_Polaziste = m_vPostaje[i]->m_sNaziv;
			lat1 = m_vPostaje[i]->m_fLat;
			lon1 = m_vPostaje[i]->m_fLng;
		}
		if (n_OdredisteOdabir == m_vPostaje[i]->m_nID)
		{
			s_Odrediste = m_vPostaje[i]->m_sNaziv;
			lat2 = m_vPostaje[i]->m_fLat;
			lon2 = m_vPostaje[i]->m_fLng;
		}
	}
	cout << "" << endl;
	cout << "Odaberite vrstu vozila" << endl;
	cout << "" << endl;
	IspisiVozila();
	cin >> n_vozilo;

	for (int i = 0; i < m_vVozila.size(); i++)
	{
		for (int j = 0; j < m_vSkupine.size(); j++)
		{
			if (n_vozilo = m_vVozila[i]->m_nID && m_vVozila[i]->m_nSkupina == 1 && m_vSkupine[j]->m_nID==1)
			{
				f_skupina = m_vSkupine[j]->m_fCijena;
			}
			if (n_vozilo = m_vVozila[i]->m_nID && m_vVozila[i]->m_nSkupina == 2 && m_vSkupine[j]->m_nID == 2)
			{
				f_skupina = m_vSkupine[j]->m_fCijena;
			}
			if (n_vozilo = m_vVozila[i]->m_nID && m_vVozila[i]->m_nSkupina == 3 && m_vSkupine[j]->m_nID == 3)
			{
				f_skupina = m_vSkupine[j]->m_fCijena;
			}
			if (n_vozilo = m_vVozila[i]->m_nID && m_vVozila[i]->m_nSkupina == 4 && m_vSkupine[j]->m_nID == 4)
			{
				f_skupina = m_vSkupine[j]->m_fCijena;
			}
		}	
	}

	d_Cijena = (Haversine(lat1, lon1, lat2, lon2)*f_skupina);
	d_Udaljenost = Haversine(lat1, lon1, lat2, lon2);
	f_Trajanje = (Haversine(lat1, lon1, lat2, lon2) / 120);
	
	
	system("cls");
	cout << "Od " << s_Polaziste << " " << "do " << s_Odrediste << endl;
	cout << "Ukupno kilometara: " << d_Udaljenost << "km" << endl;
	cout << "Cestarina: " << d_Cijena << "kn" << endl;
	cout << "Trajanje puta: " << f_Trajanje << "h"<<endl;
	
	ofstream outputFile;
	outputFile.open("Report.txt");
	outputFile<< "Od " << s_Polaziste << " " << "do " << s_Odrediste << endl;
	outputFile<< "Ukupno kilometara: " << d_Udaljenost << "km" << endl;
	outputFile<< "Cestarina: " << d_Cijena << "kn" << endl;
	outputFile<< "Trajanje puta: " << f_Trajanje << "h" << endl;
	outputFile << " " << endl;
	outputFile.close();

	
}

void Autocesta::UcitajVozila()
{
	m_oVozilaXmlDocument.LoadFile("Vozila.xml");
	m_pVozilaVozilo = m_oVozilaXmlDocument.FirstChildElement("Vozila");
	XMLElement *pVozilo;
	for (pVozilo = m_pVozilaVozilo->FirstChildElement("Vozilo"); pVozilo != NULL; pVozilo = pVozilo->NextSiblingElement())
	{	
		string id = pVozilo->Attribute("id");
		string naziv = pVozilo->Attribute("naziv");
		string skupina = pVozilo->Attribute("skupina");
		m_vVozila.push_back(new Vozilo(stoi(id),naziv, stoi(skupina)));
	}
}

void Autocesta::DodajVozilo()
{
	int id = 0;

	Vozilo* pointer = m_vVozila[0];

	for (int i = 0; i < m_vVozila.size(); i++)
	{
		if (pointer->m_nID < m_vVozila[i]->m_nID)
		{
			pointer = m_vVozila[i];
			id = m_vVozila[i]->m_nID;
		}

	}
	
	cout << "Dodajte vozilo u jednu od 4 skupine vozila" << endl;
	cout << "1.) Skupina I" << endl;
	cout << "2.) Skupina II" << endl;
	cout << "3.) Skupina III" << endl;
	cout << "4.) Skupina IV" << endl;

	string naziv;
	int skupina;
	int odabir;
	cin >> odabir;
	switch (odabir)
	{
	case 1:
		skupina = 1;
		cout << "Unesite naziv vozila: " << endl;
		cin.ignore();
		getline(cin, naziv);
		break;
	case 2:
		skupina = 2;
		cout << "Unesite naziv vozila: " << endl;
		cin.ignore();
		getline(cin, naziv);
		break;
	case 3:
		skupina = 3;
		cout << "Unesite naziv vozila: " << endl;
		cin.ignore();
		getline(cin, naziv);
		break;
	case 4:
		skupina = 4;
		cout << "Unesite naziv vozila: " << endl;
		cin.ignore();
		getline(cin, naziv);
		break;
	default:
		cout << "Niste odabrali jednu od ponudenih skupina!" << endl;
			break;
	}

	m_vVozila.push_back(new Vozilo(++id,naziv, skupina));
	ZapisiPromjeneVozila();
	Povratak();
}

void Autocesta::ZapisiPromjeneVozila()
{
	m_pVozilaVozilo->DeleteChildren();
	for (int i = 0; i < m_vVozila.size(); i++)
	{
		XMLElement *newVozilo = m_oVozilaXmlDocument.NewElement("Vozilo");
		
		newVozilo->SetAttribute("id", (m_vVozila[i]->m_nID));
		newVozilo->SetAttribute("naziv", (m_vVozila[i]->m_sNaziv).c_str());
		newVozilo->SetAttribute("skupina", m_vVozila[i]->m_nSkupina);

		m_pVozilaVozilo->LinkEndChild(newVozilo);
	}
	m_oVozilaXmlDocument.SaveFile("Vozila.xml");
}

double Autocesta::Haversine(double lat1, double lon1, double lat2, double lon2)
{
	double dLat1 = lat1*(PI / 180);
	double dLon1 = lon1*(PI / 180);
	double dLat2 = lat2*(PI / 180);
	double dLon2 = lon2*(PI / 180);
	double dLat = dLat1 - dLat2;
	double dLon = dLon1 - dLon2;
	double aHarv = pow(sin(dLat / 2.0), 2.0) + cos(dLat1)*cos(dLat2)*pow(sin(dLon / 2), 2);
	double cHarv = 2 * atan2(sqrt(aHarv), sqrt(1.0 - aHarv));
	const double earth = 6356.750;
	double distance = earth*cHarv;
	return distance;

}

void Autocesta::UcitajSkupine()
{
	m_oSkupineXmlDocument.LoadFile("Skupine.xml");
	m_pSkupine = m_oSkupineXmlDocument.FirstChildElement("Skupine");
	XMLElement *pSkupine;
	for (pSkupine = m_pSkupine->FirstChildElement("Skupina"); pSkupine != NULL; pSkupine = pSkupine->NextSiblingElement())
	{	
		string cijena = pSkupine->Attribute("cijena");
		string id = pSkupine->Attribute("id");
	
		m_vSkupine.push_back(new Skupine(stoi(id),stof(cijena)));
		
	}


}

void Autocesta::IspisiVozila()
{
	int a = 0;
	cout << "R.br."<< '\t' << "Vrsta vozila" << endl;
	for (int i = 0; i < m_vVozila.size(); i++)
	{
		cout  <<setw(2) << ++a << setw(16) << m_vVozila[i]->m_sNaziv << endl;
	}
}

void Autocesta::Povratak()
{
	int a;
	cout << endl;
	cout << "Prisnite tipku ENTER za povratak na glavni izbornik ili tipku ESC za izlaz iz programa" << endl;
	cout << endl;
	a = _getch();
	if (a == 13)
	{
		system("cls");
		DajIzbornik();
	}
	else if (a == 27)
	{
		exit(0);
	}
}

