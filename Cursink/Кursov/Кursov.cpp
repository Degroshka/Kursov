#include <iostream>
using namespace std;
struct Fdol {
	char elem;
	Fdol* next, * prev;
};
struct Sdol {
	char elem;
	Sdol* next, * prev;
};
void prov(Fdol *f,Sdol *s,Fdol *pf,Sdol *ps) {
	while (s != NULL and f!=NULL) {
		while (pf!=NULL) {
			
			if (s->elem == pf->elem and f->elem == ps->elem) {
				if(ps->next==NULL and pf->next==NULL) {
					ps = NULL;
					pf = NULL;
					return;
				}else{
					pf->prev->next = pf->next;
					ps->prev->next = ps->next;
					if (pf->elem == NULL) {
						return;
					}		
					delete pf;
					delete ps;
					
				}

			}
			ps = ps->next;
			pf = pf->next;
		}
		pf = f;
		ps = s;
		s = s->next;
		f = f->next;
	}
	cout << " -------- " << endl;

}


int main() {
	setlocale(LC_ALL, "Russian");
	Fdol* f, * ff,*pf;
	Sdol* s, * ss,*ps;
	f = ff=pf = new Fdol;
	s = ss = ps = new Sdol;
	char fch, sch;
	cout << "Введите номера вершин между которыми есть связи" << endl;
	cout << "Вершина x связана с вершиной y " << endl;
	for (;;) {
		cout << "x=";
		cin >> fch;
		if (fch == '.') {
			break;
		}
		cout << "y=";
		cin >> sch;
		if (sch == '.') {
			break;
		}
		if (fch != sch) {
			f->elem = fch;
			s->elem = sch;
			f->next = new Fdol;
			f->next->prev = f;
			s->next = new Sdol;
			s->next->prev = s;
			f = f->next;
			s = s->next;
		}
	}
	f->next = new Fdol;
	f->next = NULL;
	s->next = new Sdol;
	s->next = NULL;
	s = ss;
	f = ff;
	prov(f,s,pf,ps);
	while (f->next != NULL) {
		while (s->next != NULL) {
			cout << f->elem << " and " << s->elem << endl;
			if (f->elem == s->elem) {
				cout << " Не двудольынй";
				return 0;
			}
			s = s->next;
		}
		s = ss;
		f = f->next;
	}
	if (!isdigit(f->elem)) {
		cout << " Двудольный";
	}
	else {
		cout << " Недостаточно информации";
	}
}