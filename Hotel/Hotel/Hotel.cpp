#include <iostream>
#include <vector>//  folosim vectori
#include <algorithm>// folosim la functia push_back
using namespace std;
class Apartament// definirea unui apartament
{
	int numar_apartament;// variabile private( pot fi folosite doar in clasa asta
	static int inc;// variabila static, apartine clasei nu instantei. de ex , faci un  apartament si faci inc++; inc devine 1, faci alt apartament si faci din nou inc++ , inc devine 2. Daca inc apartinea unui obiect si nu  clasei atunci inc reincepea de la 0.
	bool disponibilitate[365]; // bool = adevarat sau fals, vector pentru fiecare zi in an. 
	string tip_apartament;// la cumm l-am definit poate primi un singur cuvant, nu citeste spatiile. Daca vrei sa scrii ceva din mai multe cuvinte foloseste -.!/_ sau ce mai vrei tu, de ex Camera-dubla, Dormitor-artificial,etc
	int pret_apartament;
public:// variabile si functii( noi avem doar functii) publice, pot fi folosite oriunde in cod( adica si in Hotel sau in int main)
	Apartament() :pret_apartament(100), numar_apartament(++inc) // constructorul
	{//  de fiecare data cand creez o camera valoarea lui pret se initializeaza cu 100 , iar numar camera ia valoarea lui ++inc( adica facem inc= inc+1 si dupa facem numar_apartament= inc, in ordinea aia)
		tip_apartament = "Duplex "; // valoarea de baza, oricum la cum am scris eu programul mereu o sa ii dai tu o descriere
		for (int i = 0;i < 365;i++)// setam camera in toate zilele ca disponibila
			disponibilitate[i] = true;
	}
	// pentru a putea folosi variabilele private in afara clasei facem functii publice care le pot accesa
	// conventie: le numim functii set si functii get
	// functiile get  returneaza valoarea, gen cand vrem sa comparam valoarea folosim get_variabila() ca sa folosim valoarea
	//  functiile set modifica valoaorea, cand vrem sa modificam pretul unei camere, sa ii schimbam descrierea,etc
	int get_nr()
	{
		return numar_apartament;
	}
	int get_pret()
	{
		return pret_apartament;
	}
	void set_disp(bool x, int y)// are doi parametrii, un bool cand vrem sa o eliberam sau sa o ocupam, si o zi( y ) cand vrem sa specificam ziua 
	{
		disponibilitate[y-1] = x;//vectorul incepe de la 0 nu de la 1, deci daca introduci ziua 1 de la tastatura, ea e stocata pe pozitia 0.
	}
	bool get_disp(int x)
	{
		return disponibilitate[x-1];
	}

	
	friend istream& operator >>(istream& is, Apartament& a) // suprascrierea citirii pentru Apartament
	{
		cout << "Apartamentul: " << a.numar_apartament << endl;
		cout << "Tip apartament: ";
		is >> a.tip_apartament;
		cout << "Pret pe zi: ";
		is >> a.pret_apartament;
		return is;
	}

	friend ostream& operator <<(ostream& os, Apartament& a)//  suprascrierea afisarii pentru apaprtament
	{
		os << endl;
		os << "Apartamentul: " << a.numar_apartament << endl;
		os << "Tip: " << a.tip_apartament << endl;
		os << "Pret pe zi: " << a.pret_apartament << endl;
		return os;
	}

};
int Apartament::inc = 0;// initializarea variabilei statice cu valoarea 0

template <typename x>class Hotel// template ne permite sa facem vectori ce pot contine variabile de tipul "x", orice tip ar fi, tipul il specificam in int main
{
	vector<x> camere; // declararea vectorului
	int total_inchirieri;// mi se parea prea scurt proiectul asa ca am mai adaugat o variabila 
	// ea tine totalul vanzarilor/inchirilor, 
public:
	
	void creaza_camera(Apartament a)
	{
		camere.push_back(a);// adaugam apartamentul a la vectorul de apartamente, adica la hotelul nostru
	}
	int get_total()
	{
		return total_inchirieri;
	}

	void rezervare_camera(int nr,int zi_rezervare) //  rezerva o camera dupa nr ei si ziua specificata
	{
		for (auto i = camere.begin();i != camere.end();++i)// asa se parcurge vectorul dupa pozitii
		{
			if ((*i).get_nr() == nr )// un *i, un pointer, el retine adresa obiectului, deci cand il apelezi asa e de parca ai apela obiectul(apartamentul) si poti folosi functiile publice
			{
				if ((*i).get_disp(zi_rezervare) == false)// exemplu, functia get_disp returneaza disponibilitatea dintr-o zi si o comparat. Daca e falsa atunci
				{
					cout << "Camera este deja rezervata in ziua " << zi_rezervare<<endl;
					return;
				}
				(*i).set_disp(false, zi_rezervare);// aici ajunge doar daca  e dispoonibillasi o seteaaza ca rezervata
				total_inchirieri += (*i).get_pret();// adunam pretul camerei la total 
				break;// pentru ca am gasit camera si am inchiriat-o  putem sa ne oprim, nu trebuie sa mai parcurgem restul forului asa ca folosim break pentru a ne opri
			}
		}
	}
	void disponibilitate_camera(int nr, int zi) // verifica daca camera este disponibila intr-o zi 
	{
		for (auto i = camere.begin();i != camere.end();++i)
		{
			if ((*i).get_nr() == nr) // daca camera la care ne aflam are nr  ala specificat atunci. Pentru ca el parcurge de la camera 1, dupa camera 2, si verifica. Daca camera 2 are nr 2 atunci face alea
			{
				if ((*i).get_disp(zi) == true)
				{
					cout << "Camera este disponibila in ziua " << zi << endl;
					break;
				}
				else
				{
					cout << "Camera nu este disponibila in ziua " << zi << endl;
					break;
				}
			}
		}
	}
	void eliberare_camera(int nr, int zi_rezervare) // functie ce elibereaza o camera intr-o zi rezervata
	{//  pentru ca nu ii vedeam un rost anume, am pus sa scada 10% din pretul zilei respective, adica nu ii dai toti banii inapoi. Daca camera are pretul 100 si a inchiriat-o, daca o anuleaza primeste doar 10 lei inapoi
		for (auto i = camere.begin();i != camere.end();++i)
		{
			if ((*i).get_nr() == nr)
			{
				if ((*i).get_disp(zi_rezervare) == true)
				{
					cout << "Camera nu este rezervata in ziua " << zi_rezervare << endl;
					return;
				}
				(*i).set_disp(true, zi_rezervare);
				total_inchirieri -= (*i).get_pret()/10;
				break;
			}
		}
	}
	friend ostream& operator <<(ostream& os, Hotel& h)// suprascrierea afisarii hotelului
	{// programul stie pe care s-o aleaga in functie de ce urmeaza dupa <<, de ex daca dupa << urmeaza un apartament foloseste ostreamul de sus, daca urmeaza un hotel foloseste ostreamul de aici
		for (auto i = h.camere.begin();i != h.camere.end();++i)
		{
			os << (*i);// aici apelam ostream-ul de sus pentru fiecare camera din vectorul de apartamente
		}
		return os;
	}
};
int main()
{
	Hotel<Apartament> apartamente; //  declararea vectorului cu obiecte de tip apartament
	bool option = true;
	while (option)
	{
		int option2;
		cout << "1) Adauga camera" << endl;
		cout << "2) Afisare camere" << endl;
		cout << "3) Inchiriaza camera" << endl;
		cout << "4) Eliberare camera" << endl;
		cout << "5) Afisare profit total" << endl;
		cout << "6) Disponibilitate camera" << endl;
		cout << "7)Iesire" << endl;
		cin >> option2;
		switch (option2)
		{
		case 1:
		{
			Apartament a;
			cin >> a;
			apartamente.creaza_camera(a);
			break;
		}
		case 2:
		{
			cout << apartamente;
			break;
		}
		case 3:
		{
			cout << "Nr camera: ";
			int nr;
			cin >> nr;
			cout << "Prima zi a inchirierii: ";
			int prima;
			cin >> prima;
			cout << "Totalul de zile inchiriate: ";
			int total;
			cin >> total;
			for (int i = 0;i < total;i++)
			{
				apartamente.rezervare_camera(nr, prima);
				prima++;
			}
			break;
		}
		case 4:
		{
			cout << "Nr camera: ";
			int nr;
			cin >> nr;
			cout << "Ziua: ";
			int zi;
			cin >> zi;
			apartamente.eliberare_camera(nr, zi);
			break;
		}
		case 5:
		{
			cout << "Totalul chiriilor camerelor rezervate este in valoare de: " << apartamente.get_total() << endl;
			break;
		}
		case 6:
		{
			cout << "Nr camera: ";
			int nr;
			cin >> nr;
			cout << "Ziua: ";
			int zi;
			cin >> zi;
			apartamente.disponibilitate_camera(nr, zi);
			break;
		}
		case 7:
			option = false;
			break;
		}
	}
	return 0;
}

