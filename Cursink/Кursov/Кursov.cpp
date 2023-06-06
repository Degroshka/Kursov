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
struct Prov {
    char elem;
    Prov* next;
};
int provfin(Fdol* f,Fdol *ff, Sdol* s, Sdol* ss) {
    while (f->next != nullptr) {
        while (s->next != nullptr) {
            cout << f->elem << " && " << s->elem << endl;
            if (f->elem == s->elem) {
                return 0;}
            s = s->next;}
        s = ss;
        f = f->next;}
    return 1;
}
int proverF(Fdol *pf, Sdol *ps,Sdol* ss, Fdol* ff,  char fch, char sch) {   //// 3 и 4   /// 4 и 
    cout << "ProverF" << endl;
    while (ff->elem != NULL or ss->elem != NULL) {
        cout << fch << " и " << sch << " И ТАБЛ 1.... " << ff->elem << " " << ss->elem << endl;
        if (fch == ff->elem or sch==ss->elem ) {
            ss = ps;
            while (ss->elem != NULL) {
                cout << fch << " и " << sch << " И ТАБЛ 1.5.... " << ff->elem << " " << ss->elem << endl;
                if (sch == ss->elem and fch==ff->elem) {
                    cout << fch << sch << " Не берем"<<endl;
                    return 2;
                }
                else if(sch==ss->elem){
                    return 4;
                }
                ss = ss->next;
            }
            return 1;
        }
        else if (fch == ss->elem or sch == ff->elem) {
            cout << fch << " и " << sch << " И ТАБЛ 2.... " << ff->elem << " " << ss->elem << endl;
            ss = ps;
            while (ss->elem != NULL) {
                cout << fch << " и " << sch << " И ТАБЛ 2.5... " << ff->elem << " " << ss->elem << endl;
                if (fch == ss->elem or sch==ss->elem) {
                    return 2;
                }
                else if (sch == ss->elem) {
                    return 4;
                }
               
                ss = ss->next;
            }
                return 1;
            }
            if (ff->elem != NULL)ff = ff->next;
            if (ss->elem != NULL)ss = ss->next;
        }
        return 0;
    }

int provnaSv() {
    ifstream fin("sym.txt");
    Prov* pr,*pE,*pF,*an;
    char som;
    if (fin.is_open()) {
    pr = pE = pF = an = new Prov;
    do {
        fin >> som; 
            pr->next = new Prov;
            pr->next->elem = NULL; 
            if (fin.eof()) {
                break;
            } pr->elem = som;
            pr = pr->next;
        
    } while (!fin.eof());
    pr->next = nullptr;
    fin.close();
}

    else {
        cout << "Ошибка открытия файла." << endl;
        return 3;
    }
    while (an!= nullptr) {
        an = an->next;
    }
    pr = pE;
    Prov* current = pE;
    while (pE->elem != NULL) {

        cout << pE->elem<<endl;

        while (pr->elem != NULL) {
            cout << pr->elem<<" and "<<pr->next->elem << endl;
            if ((pr->elem == pE->elem || pr->elem == pE->next->elem || pr->next->elem == pE->elem || pr->next->elem == pE->next->elem) && (pr != pE && pr->next != pE->next && pr!=pE->next && pr->next!=pE))
            {
                cout << "одинаково" << endl;
                break;
            }             
            pr = pr->next->next;
            if (pr->elem == NULL) {
                return 0;
            }
        }
        pr = pF;    
        pE = pE->next->next;
    } 
    while (current != nullptr) {
        Prov* next = current->next;
        delete current;
        current = next;
    }
    return 1;
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
    if (provnaSv() == 0) {
        cout << "Граф не связан";
        return 0;
    }
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
            if (proverF(pf,ps,ss, ff, fch, sch) == 1) {
                s->elem = sch;
            }
            else if (proverF(pf, ps,ss, ff, fch, sch) == 3) {
                f->elem = sch;               
            }
            else if(proverF(pf,ps,ss, ff, fch, sch) == 0)
            {
                f->elem = fch;
                s->elem = sch;
            }
            else if (proverF(pf, ps, ss, ff, fch, sch) == 4) {
                f->elem = fch;
            }
        }
        if (f->elem!= NULL)f = f->next;
        if(s->elem!=NULL)s = s->next;
    }while (true);
    f->next = nullptr;
    s->next = nullptr;
    s = ss;
    f = ff;
    print(f, s);
    if (provfin(f,ff, s, ss) == 1) {
        cout << "Двудольный";
    }
    else {
        cout << "Не двудольный";
    }
    fin.close(); // закрываем файл
    return 0;
}
