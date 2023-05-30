#include <iostream>
#include <fstream>
using namespace std;

struct Fdol {
    char elem;
    Fdol* next, * prev;
};

struct Sdol {
    char elem;
    Sdol* next, * prev;
};
int provfin(Fdol* f,Fdol *ff, Sdol* s, Sdol* ss) {
    while (f->next != nullptr) {
        while (s->next != nullptr) {
            cout << f->elem << " and " << s->elem << endl;
            if (f->elem == s->elem) {
                return 0;
            }
            s = s->next;
            
        }
        s = ss;
        f = f->next;
    }
    return 1;
}
int proverF(Sdol* s, Fdol* ff, Fdol* f, char fch, char sch) {   //// 3 и 4   /// 4 и 
    cout << "ProverF" << endl;
    while (f->elem != NULL) {
        cout<< "fch и f" << endl;
        cout << fch << " и " << f->elem <<endl;
        if (fch == f->elem) { 
                    return 1;
                }
                f = f->next;
        }
    return 0;
}

    
    
    
    
    //do {
        //cout << f->elem<< " проверка на "<<fch<<endl;
        //if (fch == f->elem) {
         ///   return 0;
       // }
     //   f = f->next;
  // }while (f->elem!=NULL);
    //return 1;
//
void prov(Fdol* f, Fdol* ff, Sdol* s, Sdol* ss, Fdol* pf, Sdol* ps) {
    while (s) {
        while (pf) {
            if (s->elem == pf->elem and f->elem == ps->elem) {
                if (!pf->next) {
                    ps = nullptr;
                    pf = nullptr;
                    return;
                }
                else {
                    pf->prev->next = pf->next;
                    ps->prev->next = ps->next;
                    pf->next->prev = pf->prev;
                    ps->next->prev = ps->prev;
                    ss = ps->prev;
                    ff = pf->prev;
                    delete pf;
                    delete ps;
                    ps = ss;
                    pf = ff;
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
}
void print(Fdol* f, Sdol* s) {
    
    while (f!=nullptr) {
        cout << f->elem;
        f = f->next;
    }
    cout << endl;
    while (s!=nullptr) {
        cout << s->elem;
        s = s->next;
    }
    cout << endl;

}

int main() {
    setlocale(LC_ALL, "Russian");
    ifstream fin("sym.txt"); // открываем файл для чтения
    if (!fin.is_open()) { // если файл не открыт
        cout << "Ошибка открытия файла!" << endl;
        return 0;
    }
    Fdol* f, * ff, * pf;
    Sdol* s, * ss, * ps;
    f = ff = pf = new Fdol;
    s = ss = ps = new Sdol;
    char fch, sch;
    do {
        fin >> fch >> sch;
        if (fin.eof()) {
            break;
        }
        if (fch != sch) {
            f->next = new Fdol;
            f->next->prev = f;
            s->next = new Sdol;
            s->next->prev = s;
            f->next->elem = NULL;
            s->next->elem = NULL;
            if (proverF(s, ff, f, fch, sch) == 1) {
                s->elem = sch;
            }
            else
            {
                f->elem = fch;
                s->elem = sch;
            }
        }
        f = f->next;
        s = s->next;

    }while (true);
    f->next = nullptr;
    s->next = nullptr;
    s = ss;
    f = ff;
    print(f, s);
    prov(f, ff, s, ss, pf, ps);
    
    if (provfin(f,ff, s, ss) == 1) {
        cout << "Двудольный";
    }
    else {
        cout << "Не двудольный";
    }
    fin.close(); // закрываем файл
    return 0;
}
