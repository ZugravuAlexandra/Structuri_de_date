#include <iostream>
#include <fstream>

using namespace std;

ifstream f("abce.in");
ofstream g("abce.out");

/// functia pentru noduri, care va avea valoare, parinte si copiii din stanga si dreapta ai nodului
struct SplayN
{
    int valoare;
    SplayN *par,*st,*dr;

    /// constructor fara parametri
    SplayN() : valoare(), par(nullptr), st(nullptr), dr(nullptr) {}

    /// constructor cu parametri
    SplayN(int valoare, SplayN *par = nullptr, SplayN *st = nullptr, SplayN *dr = nullptr ): valoare(valoare), par(par), st(st), dr(dr) {}


    /// constructor de copiere
    SplayN(SplayN *nod)
    {
        valoare = nod->valoare;
        par = nod->par;
        st = nod->st;
        dr = nod->dr;

    }
};


class SplayTree
{
private:
    SplayN *radacina;
    int size_a; /// numarul de noduri din arbore

    /// primeste o val si returneaza pointerul cu acea val sau nullptr daca nu exista
    SplayN *gasire_nod(const int &val)
    {
        SplayN *el_curent = radacina;
        SplayN *el_ant = nullptr;

        while(el_curent != NULL)
        {
            el_ant = el_curent;
            if(el_curent->valoare > val)
                el_curent = el_curent->st; /// ne ducem pe subarb. stang
            else if (el_curent->valoare < val)
                el_curent = el_curent->dr; /// ne ducem pe subarb. drept
            else
                return el_curent;
        }

        if(el_ant !=NULL)
            splay(el_ant);

        return nullptr;
    }

    /// splay
    /// o sa primeasca un nod pe care va trebui sa il puna ca radacina prin aplicarea de rotatii
    void splay(SplayN *nod)
    {
        while(nod->par != NULL)
        {
            /// daca parintele este radacina arborelui se aplica o rotatie (zig sau zag)
            if (nod->par == radacina)
            {
                if (nod == nod->par->st)  /// rotatia zig = se face rotatia spre dreapta
                    rotDreapta(nod->par);
                else                    /// rotatia zag = se fac  e rotatia spre stanga
                    rotStanga(nod->par);
            }
            else
            {
                /// in caz contrar facem o combinatie intre cele doua rotatii unde o sa avem nevoie de parinte si bunic
                SplayN *parinte = nod->par;
                SplayN *bunic = parinte->par;

                /// rotatia zig-zig

                if (nod==nod->par->st && parinte==parinte->par->st)
                {
                    rotDreapta(bunic);
                    rotDreapta(parinte);
                }

                /// rotatia zag-zag

                else if (nod == nod->par->dr && parinte == parinte->par->dr)
                {
                    rotStanga(bunic);
                    rotStanga(parinte);
                }

                /// rotatia zag-zig

                else if (nod == nod->par->dr && parinte == parinte->par->st)
                {
                    rotStanga(parinte);
                    rotDreapta(bunic);
                }

                /// rotatia zig-zag

                else
                {
                    rotDreapta(parinte);
                    rotStanga(bunic);
                }
            }

        }
        radacina=nod;
    }


    /// rotatii ajutatoare pentru zig si zag

    void rotDreapta(SplayN *nod)
    {
        SplayN *copil = nod->st;
        nod->st = copil->dr;

        if(nod->st)
        {
            nod->st->par=nod;
        }


        copil->dr=nod;
        copil->par=nod->par;

        if (nod->par)
        {
            if(nod->valoare < nod->par->valoare)
                nod->par->st = copil;
            else
                nod->par->dr = copil;
        }

        nod->par = copil;
    }

    void rotStanga(SplayN *nod)
    {
        SplayN *copil = nod->dr;
        nod->dr = copil->st;

        if(nod->dr)
            nod->dr->par = nod;
        copil->st = nod;
        copil->par = nod->par;

        if (nod->par)
        {
            if(nod->valoare < nod->par->valoare)
                nod->par->st = copil;
            else
                nod->par->dr =copil;

        }
        nod->par = copil;
    }

    /// maxim pentru a se duce in dreapta (pt. predecesor)

    SplayN *maxi(SplayN *nod)
    {
        SplayN *aux = nod;

        /// parcurgem subarborele pana ajungem la un nod fara copil drept si aplicam splay apoi
        /// pt a muta acel nod in radacina si sa il returneze
        while(aux->dr != NULL)
            aux=aux->dr;
        splay(aux);
        return aux;
    }

    /// minim pentru a se duce in stanga (pt. succesor)

    SplayN *mini(SplayN *nod)
    {
        SplayN *aux=nod;

         while(aux->dr !=NULL)
            aux=aux->st;
        splay(aux);
        return aux;
    }

    /// succesor

    SplayN *succesor(SplayN *nod)
    {
        /// daca nodul are un fiu drept atunci succesorul o sa fie minimul din subarborele din dreapta
        if(nod->dr)
            return mini(nod->dr);
        /// daca nodul nu are fiu drept atunci succ. o sa il cautam in sus, astfel luam parintele nodului
        SplayN *parinte=nod->par;

        /// daca nodul are un parinte (nu este radacina) se face while si se opreste cand nodul nu mai este fiul drept al parintelui sau
        if(parinte != NULL)
            while(parinte->dr == nod)
            {
                nod=parinte;
                parinte=parinte->par;

                if(parinte==nullptr)
                    break;
            }
        /// aducem succesorul in radacina
        splay(parinte);
        return parinte;
    }

    /// la fel ca la succesor dar pe partea stanga
    SplayN *predecesor(SplayN *nod)
    {
        if(nod->st)
            return maxi(nod->st);
        SplayN *parinte=nod->par;

        if(parinte)
            while(parinte->st == nod)
            {
                nod=parinte;
                parinte=parinte->par;

                if(parinte==nullptr)
                    break;
            }

        splay(parinte);
        return parinte;
    }


public:
    /// constructor care imi initializeaza radacina cu nullptr si size_a cu 0
    SplayTree() : radacina(nullptr), size_a(0) {}

    /// inserare

    void inserare(const int &val)
    {
        /// verificam daca valoare exista deja in arbore
        if(gasire_nod(val) == NULL)
        {
            SplayN *el_curent = radacina;
            SplayN *parinte=nullptr;
            /// facem un nod nou
            auto *nod_nou = new SplayN(val);


            ++size_a; /// dimensiunea arborelui creste

            /// se parcurge arborele de la radacina la frunze
            while(el_curent != NULL)
            {
                parinte = el_curent;

                /// daca valoarea noului nod este mai mica decat a nodului curent se face cautarea in stanga, altfel in dreapta
                if(el_curent->valoare>val)
                    el_curent=el_curent->st;
                else
                    el_curent=el_curent->dr;

                nod_nou->par = parinte;
            }

            /// daca parintele nodului este null inseamna ca arborele este gol si noul nod o sa fie radacina
            if(parinte == NULL)
            {
                radacina=nod_nou;
            }
            else
            {
                if (nod_nou->valoare < parinte->valoare)
                    parinte->st=nod_nou;
                else
                    parinte->dr=nod_nou;

                splay(nod_nou); /// facem splay ca sa ducem nodul nou in radacina
            }
        }
    }

    /// stergere top-down

    void stergere(const int &val)
    {
        if(radacina != NULL)
        {
            /// cauta nodul care trebuie eliminat
            SplayN *gasit=gasire_nod(val);

            /// daca nodul este gasit devine radacina
            if (gasit!=NULL)
            {
                splay(gasit);

                /// verificam daca arborele din stanga este null, caz in care fiul din dreapt este radacina
                if (radacina->st == NULL)
                {
                    radacina=radacina->dr;
                    delete gasit;
                }
                else
                {
                    /// altfel se gaseste cel mai mare nod din subarborele stang al radacinii si facem splay
                    SplayN *arb_dr=radacina->dr;
                    radacina=radacina->st;

                    delete gasit;
                    radacina->par=nullptr;

                    SplayN *m_arb_st = maxi(radacina);
                    splay(m_arb_st);

                    if (arb_dr != NULL)
                    {
                        arb_dr->par = radacina;
                    }

                    radacina->dr = arb_dr;
                }

                --size_a; /// dimensiunea arborelui scade
            }
        }
    }

    /// succesor
    /// cea mai mica valoare mai mare decat val
    int succesor(const int &val)
    {
        SplayN *el_curent=radacina;
        SplayN *el_ant = nullptr;

        while(el_curent != NULL)
        {
            el_ant=el_curent;
            ///daca valoarea el_curent este mai mare ca val nodului atunci se duce spre stanga sau dreapta
            if(el_curent->valoare>val)
                el_curent=el_curent->st;
            else if (el_curent->valoare<val)
                el_curent=el_curent->dr;
            else
                /// sau daca val el_curent este egala cu val se returneaza valoarea lui
                return el_curent->valoare;
        }

        /// este returnata valoarea nodului anterior sau recursic este apelata functia succesor pentru el_ant
        if(el_ant->valoare>val)
            return el_ant->valoare;
        else
            return succesor(el_ant)->valoare;
    }

    /// predecesor
    int predecesor (const int &val)
    {
        SplayN *el_curent=radacina;
        SplayN *el_ant  = nullptr;

        while(el_curent != NULL)
        {
            el_ant=el_curent;
            if(el_curent->valoare > val)
                el_curent=el_curent->st;
            else if(el_curent->valoare < val)
                el_curent=el_curent->dr;
            else
                return el_curent->valoare;
        }

        if (el_ant->valoare<val)
            return el_ant->valoare;
        else
            return predecesor(el_ant)->valoare;
    }

    ///  search

    bool gasit(const int &val)
    {
        SplayN *g= gasire_nod(val);
        if(g != NULL)
        {
            splay(g);
            return true;
        }
        return false;
    }


    ///afisare

    void afisare(SplayN *nod, int inf, int sup)
    {
        if(nod->st != NULL)
            afisare(nod->st, inf, sup);
        if (nod->dr != NULL)
            afisare(nod->dr, inf, sup);
        if (nod->valoare >= inf && nod->valoare <= sup)
            g<<nod->valoare<<" ";
    }

    void afis_s(int inf, int sup)
    {
        afisare(radacina, inf, sup);

    }


};

int main()
{
    int n;
    int cer, x, y, i;
    SplayTree arbore;


    f>>n;


    for (i=0; i<n; ++i)
    {
        f>>cer>>x;

        if(cer==1)
            arbore.inserare(x);
        else if(cer==2)
            arbore.stergere(x);
        else if(cer==3)
            g<<arbore.gasit(x)<<'\n';
        else if(cer==4)
            g<<arbore.predecesor(x)<<'\n';
        else if(cer==5)
            g<<arbore.succesor(x)<<'\n';
        else
        {
            f>>y;
            arbore.afis_s(x,y);
            g<<'\n';
        }
    }

    return 0;
}
