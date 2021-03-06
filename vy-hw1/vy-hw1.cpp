#include <iostream>
using namespace std;

#define MAX 100

class Stack
{
	int top;
public:
	int a[MAX];

	Stack() { top = -1; }
	
	bool ekle(int x);
	int sil();
	bool bos_mu();
	void yazdir();
	void aktarma();
};

bool Stack::ekle(int x)
{
	if (top >= (MAX - 1))
	{
		cout << "Eleman Eklenemedi!! Yigit Dolu!!\n";
		return false;
	}
	else
	{
		a[++top] = x;
		cout << x << " yigita eklendi.\n";
		return true;
	}
}

int Stack::sil()
{
	if (top < 0)
	{
		cout << "Yigit Bos!!\n";
		return 0;
	}
	else
	{
		int x = a[top--];
		return x;
	}
}

bool Stack::bos_mu()
{
	return (top < 0);
}

void Stack::yazdir()
{
	cout << "\n*** STACK ***\n";
	for (int i=top; i > -1; i-- ) {
		cout << a[i] << endl;
	}
	cout << "*** ***** ***\n";
}

//ikili Agac

class agac
{
	struct dugum
	{
		int deger;
		dugum* sol;
		dugum* sag;
	};

	dugum* kok;

	dugum* bosalt(dugum* t)
	{
		if (t == NULL)
			return NULL;
		{
			bosalt(t->sol);
			bosalt(t->sag);
			delete t;
		}
		return NULL;
	}

	dugum* t_ekle(int x, dugum* t)
	{
		if (t == NULL)
		{
			t = new dugum;
			t->deger = x;
			t->sol = t->sag = NULL;
		}
		else if (x < t->deger)
			t->sol = t_ekle(x, t->sol);
		else if (x > t->deger)
			t->sag = t_ekle(x, t->sag);
		return t;
	}

	dugum* minbul(dugum* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->sol == NULL)
			return t;
		else
			return minbul(t->sol);
	}

	dugum* maxbul(dugum* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->sag == NULL)
			return t;
		else
			return maxbul(t->sag);
	}

	dugum* t_sil(int x, dugum* t)
	{
		dugum* temp;
		if (t == NULL)
			return NULL;
		else if (x < t->deger)
			t->sol = t_sil(x, t->sol);
		else if (x > t->deger)
			t->sag = t_sil(x, t->sag);
		else if (t->sol && t->sag)
		{
			temp = minbul(t->sag);
			t->deger = temp->deger;
			t->sag = t_sil(t->deger, t->sag);
		}
		else
		{
			temp = t;
			if (t->sol == NULL)
				t = t->sag;
			else if (t->sag == NULL)
				t = t->sol;
			delete temp;
		}

		return t;
	}

	void sirala(dugum* t)
	{
		if (t == NULL)
			return;
		sirala(t->sol);
		cout << t->deger << "    ";
		sirala(t->sag);
	}

public:
	agac()
	{
		kok = NULL;
	}

	~agac()
	{
		kok = bosalt(kok);
	}

	void t_ekle(int x)
	{
		kok = t_ekle(x, kok);
	}

	void t_sil(int x)
	{
		kok = t_sil(x, kok);
	}

	void goster()
	{
		sirala(kok);
		cout << endl;
	}
};

//ikili Agac sonu.

void Stack::aktarma()
{
	agac tr;
	cout << "Kok:" << a[top] << endl;
	for (int i = top; i > -1; i--) {
		tr.t_ekle(a[i]);
	}
	for (int i = top; i > -2; i--) {
		sil();
	}
	cout << "---LDR Formundaki Agac---\n";
	tr.goster();
}

int main() {
	int selection, eklenecek;
	class Stack s;

	while (1)
	{
		cout << "*** *** *** *** *** ***\n";
		cout << " 1 --> Yigita eleman Ekle \n";
		cout << " 2 --> Yigittan eleman Sil \n";
		cout << " 3 --> Yigittaki elemanlari yazdir \n";
		cout << " 4 --> Elemanlari ikili agaca tasi ve agaci yazdir \n";
		cout << " 5 --> Cikis \n";
		cout << "*** *** *** *** *** ***\n";

		cout << "Seciminizi girin: ";
		cin >> selection;

		switch (selection) {
		case 1:
			cout << "Eklenecek elemani giriniz:";
			cin >> eklenecek;
			s.ekle(eklenecek);
			break;
		case 2:
			cout << s.sil() << " silindi.\n";;
			break;
		case 3:
			if (s.bos_mu() == 1)
				cout << "Yigit bos!!\n";
			else
				s.yazdir();
			break;
		case 4:
			s.aktarma();
			break;
		case 5:
			exit(0);
		default:
			cout << "Yanlis Secim!!\n";
			continue;
		}
	}
	system("pause");
	return 0;
}