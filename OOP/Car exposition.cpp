#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream in("input.in");
ofstream out("output.out");

class Masina{
    protected:
        int an_fabricatie;
        string tip;
        double lungime;
        double litraj;
        int nr_persoane;
        string luna_primire;
        double pret;
        double reducere;
        int id;


    public:
        static int id_generator;
        void set_reducere(double red)
        {
            reducere=red;
        }
        double get_reducere()
        {
            return reducere;
        }
        virtual int get_sh() const
        {
            return 0;
        }
        void set_tip(string tipm)
        {
            tip=tipm;
        }
        Masina();
        Masina(int an,string tipm,double lung,double lit,int nr_pers,string luna,double pretm);
        ~Masina()=default;
        friend ifstream &operator >>(ifstream &in, Masina *M)
        {
            in>>(*M).an_fabricatie;
            in>>(*M).lungime;
            in>>(*M).litraj;
            in>>(*M).nr_persoane;
            in>>(*M).luna_primire;
            in>>(*M).pret;
        }
        friend ifstream &operator >>(ifstream &in, Masina M)
        {
            in>>(M).an_fabricatie;
            in>>(M).lungime;
            in>>(M).litraj;
            in>>(M).nr_persoane;
            in>>(M).luna_primire;
            in>>(M).pret;
        }
        Masina get_masina()
        {
            return *this;
        }
        void set_pret(double value)
        {
            pret=value;
        }
        int get_id() const
        {
           return id;
        }
        double get_lungime()
        {
            return lungime;
        }
        double get_litraj()
        {
            return litraj;
        }
        int get_nr_persoane()
        {
            return nr_persoane;
        }
        double get_pret()
        {
            return pret;
        }
        string get_luna_primire()
        {
            return luna_primire;
        }
        virtual void afis()
        {
            cout<<"Tip: "<<tip<<" ";
            cout<<"An: "<<an_fabricatie<<" ";
            cout<<"Lungime: "<<lungime<<" ";
            cout<<"Litraj: "<<litraj <<" ";
            cout<<"Capacitate: "<<nr_persoane <<" ";
            cout<<"Luna primire: "<<luna_primire <<" ";
            cout<<"Pret: "<<pret<<" ";
            cout<<endl;

        }
        void operator =(Masina &A)
        {
                tip=A.tip;
                an_fabricatie=A.an_fabricatie;
                lungime=A.lungime;
                litraj=A.litraj;
                nr_persoane=A.nr_persoane;
                luna_primire=A.luna_primire;
                pret=A.pret;

        }
        void operator =(Masina *A)
        {
            tip=A->tip;
            an_fabricatie=A->an_fabricatie;
            lungime=A->lungime;
            litraj=A->litraj;
            nr_persoane=A->nr_persoane;
            luna_primire=A->luna_primire;
            pret=A->pret;
        }
        string get_tip()
        {
            return tip;
        }
        int operator ==(Masina &A)
        {
            if(an_fabricatie!=A.an_fabricatie)
                return 0;
            if(tip!=A.tip)
                return 0;
            if(pret!=A.pret)
                return 0;
            if(luna_primire!=A.luna_primire)
                return 0;
            if(nr_persoane!=A.nr_persoane)
                return 0;
            if(litraj!=A.litraj)
                return 0;
            if(lungime!=A.lungime)
                return 0;
            return 1;
        }
        int get_an()
        {
            return an_fabricatie;
        }
};
Masina::Masina(int an,string tipm,double lung,double lit,int nr_pers,string luna,double pretm)
{
    tip=tipm;
    an_fabricatie=an;
    lungime=lung;
    litraj=lit;
    nr_persoane=nr_pers;
    luna_primire=luna;
    pret=pretm;
    id=id_generator;
    //id_generator++;
}
Masina::Masina()
{
    an_fabricatie=0;
    tip='tip';
    lungime=0;
    litraj=0;
    nr_persoane=0;
    luna_primire="luna";
    pret=0;
    id=id_generator;
    //id_generator++;
}
class Mini:public Masina{
    public:
        friend ifstream &operator >>(ifstream &in, Mini *M)
        {
            in>>(*M).an_fabricatie;
            in>>(*M).lungime;
            in>>(*M).litraj;
            in>>(*M).nr_persoane;
            in>>(*M).luna_primire;
            in>>(*M).pret;
        }
        Mini(int an,string tipm,double lung,double lit,int nr_pers,string luna,double pretm):
            Masina(an,tipm,lung,lit,nr_pers,luna,pretm){}
        Mini():Masina()
        {
        }
        ~Mini()=default;
        void afis()
        {
            cout<<"ID: "<<id<<" ";
            cout<<"Tip: "<<tip<<" ";
            cout<<"An: "<<an_fabricatie<<" ";
            cout<<"Lungime: "<<lungime<<" ";
            cout<<"Litraj: "<<litraj <<" ";
            cout<<"Capacitate: "<<nr_persoane <<" ";
            cout<<"Luna primire: "<<luna_primire <<" ";
            cout<<"Pret: "<<pret<<" ";
            cout<<endl;

        }
};
class Mica:public Masina{
    public:
        void afis()
        {
            cout<<"ID: "<<id<<" ";
            cout<<"Tip: "<<tip<<" ";
            cout<<"An: "<<an_fabricatie<<" ";
            cout<<"Lungime: "<<lungime<<" ";
            cout<<"Litraj: "<<litraj <<" ";
            cout<<"Capacitate: "<<nr_persoane <<" ";
            cout<<"Luna primire: "<<luna_primire <<" ";
            cout<<"Pret: "<<pret<<" ";
            cout<<endl;

        }
        friend ifstream &operator >>(ifstream &in, Mica *M)
        {
            in>>(*M).an_fabricatie;
            in>>(*M).lungime;
            in>>(*M).litraj;
            in>>(*M).nr_persoane;
            in>>(*M).luna_primire;
            in>>(*M).pret;
        }
        Mica(int an,string tipm,double lung,double lit,int nr_pers,string luna,double pretm):
            Masina(an,tipm,lung,lit,nr_pers,luna,pretm){}
        Mica():Masina(){}
        ~Mica()=default;
};
class Compacta:public Masina{
    string model;
    public:
        string get_model()
        {
            return model;
        }
        void set_model(string modelm)
        {
            model=modelm;
        }
        void afis()
        {
            cout<<"ID: "<<id<<" ";
            cout<<"Tip: "<<tip<<" ";
            cout<<"An: "<<an_fabricatie<<" ";
            cout<<"Model: "<<model<<" ";
            cout<<"Lungime: "<<lungime<<" ";
            cout<<"Litraj: "<<litraj <<" ";
            cout<<"Capacitate: "<<nr_persoane <<" ";
            cout<<"Luna primire: "<<luna_primire <<" ";
            cout<<"Pret: "<<pret<<" ";
            cout<<endl;

        }
        friend ifstream &operator >>(ifstream &in, Compacta *M)
        {
            in>>(*M).an_fabricatie;
            in>>(*M).model;
            in>>(*M).lungime;
            in>>(*M).litraj;
            in>>(*M).nr_persoane;
            in>>(*M).luna_primire;
            in>>(*M).pret;

        }
        Compacta(int an,string tipm,string modelm,double lung,double lit,int nr_pers,string luna,double pretm):
            Masina(an,tipm,lung,lit,nr_pers,luna,pretm){
                model=modelm;
            }
        Compacta():Masina(){}
        ~Compacta()=default;
};

class Monovolum:public Masina
{

    int second_hand;
public:
    void set_sh(bool sh)
    {
        second_hand=sh;
    }

    int get_sh()
    {
        return second_hand;
    }
    void afis()
    {
        cout<<"ID: "<<id<<" ";
        cout<<"Tip: "<<tip<<" ";
        cout<<"An: "<<an_fabricatie<<" ";
        cout<<"Lungime: "<<lungime<<" ";
        cout<<"Litraj: "<<litraj <<" ";
        cout<<"Capacitate: "<<nr_persoane <<" ";
        cout<<"Luna primire: "<<luna_primire <<" ";
        cout<<"Pret: "<<pret<<" ";
        cout<<"Second hand:";
        if(second_hand==1)
            cout<<"Da ";
        else
            cout<<"Nu ";
        cout<<endl;
    }

    Monovolum()
    {

        static string tip="MONOVOLUM1";
        an_fabricatie=0;
        second_hand=0;
        lungime=0;
        litraj=0;
        nr_persoane=0;
        luna_primire="luna";
        pret=0;
        reducere=0;
    }
    public:

    Monovolum(int an,double lung,double lit,int nr_pers,string luna,int pretm,bool sh):
        Masina(an,"MONOVOLUM",lung,lit,nr_pers,luna,pretm){
            static string tip="MONOVOLUM1";
        reducere=0;}
    void set_an(int an)
    {
        an_fabricatie=static_cast<int>(an);
    }
    void operator =(Masina &A)
    {
        tip="MONOVOLUM";
        an_fabricatie=A.get_an();
        litraj=A.get_litraj();
        lungime=A.get_lungime();
        pret=A.get_pret();
        id=A.get_id();
        nr_persoane=A.get_nr_persoane();
        luna_primire=A.get_luna_primire();
    }
    void operator =(Monovolum &A)
    {
        tip="MONOVOLUM";
        an_fabricatie=A.get_an();
        litraj=A.get_litraj();
        lungime=A.get_lungime();
        pret=A.get_pret();
        id=A.get_id();
        nr_persoane=A.get_nr_persoane();
        luna_primire=A.get_luna_primire();
        second_hand=A.get_sh();
    }
    void operator =(Masina *A)
    {
        tip="MONOVOLUM";
        an_fabricatie=(*A).get_an();
        litraj=(*A).get_litraj();
        lungime=(*A).get_lungime();
        pret=(*A).get_pret();
        id=(*A).get_id();
        nr_persoane=(*A).get_nr_persoane();
        luna_primire=(*A).get_luna_primire();
    }
    friend ifstream &operator >>(ifstream &in, Monovolum &M)
        {
            in>>(M).an_fabricatie;
            in>>(M).lungime;
            in>>(M).litraj;
            in>>(M).nr_persoane;
            in>>(M).luna_primire;
            in>>(M).pret;
            in>>M.second_hand;
        }
        friend ifstream &operator >>(ifstream &in, Monovolum *M)
        {
            in>>(*M).an_fabricatie;
            in>>(*M).lungime;
            in>>(*M).litraj;
            in>>(*M).nr_persoane;
            in>>(*M).luna_primire;
            in>>(*M).pret;
            in>>(*M).second_hand;
        }
};
void meniu_luna(int &luna)
{
    cout<<"Introduceti numarul lunii in care ne aflam:";
    cin>>luna;
    cout<<"\n";
    while(luna <1 || luna>12)
    {
        cout<<"Numarul lunii este gresit.Introduceti un numar intre 1 si 12:";
        cin>>luna;
        cout<<"\n";
    }
}

template <class T>class Vanzare
{
    int masini_stoc;
    int masini_vandute;
    vector <T*> Vandute;
    vector <T*>Stoc;
public:
    Masina* find_pret(int idm)
    {
         for(auto i: Stoc)
            if(idm==i->get_id())
                return i;
    }
    void add_stoc(T *A)
    {

        masini_stoc++;
        Stoc.push_back(A);
    }
    void add_vandute(T *A)
    {
        masini_vandute++;
        masini_stoc--;
        Vandute.push_back(A);

    }
    friend ofstream &operator <<(ofstream &out, Vanzare &V)
    {
        cout<<"\nNumarul de masini din stoc este: ";
        cout<<V.masini_stoc<<"\n";
        for(auto i: V.Stoc)
        {
            i->afis();
        }
        cout<<"Numarul de masini vandute este: ";
        cout<<V.masini_vandute<<"\n";
        for(auto i: V.Vandute)
        {
            i->afis();
        }
    }
    Vanzare()
    {
        masini_stoc=0;
        masini_vandute=0;
        Stoc.clear();
        Vandute.clear();

    }
    bool id_exist(int id)
    {
        for(auto i: Stoc)
        {
            if(i->get_id()==id)
                return 1;
        }
        return 0;
    }
    operator -= (int id_vandut)
    {
        cout<<"\n---ACTUALIZARE---\n";
        int ok=0;
        int i=0;
        for(i=0;i<masini_stoc && ok==0;i++)
        {
            if((Stoc[i])->get_id()==id_vandut)
            {
                if((Stoc[i])->get_tip()=="MONOVOLUM")
                {
                    ok=2;
                    break;
                }
                else
                {
                    ok=1;
                    break;
                }

            }
        }
        if(ok==0)
            cout<<"Masina nu exista in stoc \n";
        if(ok==1)
        {
            cout<<"Masina cu id-ul "<<id_vandut<<" a fost vanduta \n";
            add_vandute(Stoc[i]);
        }
        if(ok==2)
        {
            double reducere=0;
            bool sh=Stoc[i]->get_sh();
            reducere=Stoc[i]->get_reducere();
            if(sh)
                reducere=reducere+2019-Stoc[i]->get_an();
            Stoc[i]->set_pret(Stoc[i]->get_pret()*(100-reducere)/100);
            add_vandute(Stoc[i]);
            cout<<"Masina cu id-ul "<<id_vandut<<" a fost vanduta \n";

        }
        cout<<"Stocul a fost actualizat \n";
        Stoc.erase(Stoc.begin()+i);
    }
};
template <>class Vanzare<unsigned>
{
    int nr_monovolume_stoc;
    int nr_monovolume_vandute;
    vector<Monovolum *> Monovolume_Stoc;
    vector<Monovolum *> Monovolume_Vandute;
public:
    void set_Monovolume_stoc(int n)
    {
        nr_monovolume_stoc=n;
    }
    Vanzare()
    {
        nr_monovolume_stoc=0;
        nr_monovolume_vandute=0;
        Monovolume_Stoc.erase(Monovolume_Stoc.begin(),Monovolume_Stoc.end());
        Monovolume_Vandute.erase(Monovolume_Vandute.begin(),Monovolume_Vandute.end());
    }
    void operator -= (int id_vandut)
    {
        cout<<"\n---Actualizare Monovolum---\n";
        Monovolum *A=new Monovolum();
        int ok=0;
        for(int i=0;i<nr_monovolume_stoc && ok==0;i++)
        {
            if(Monovolume_Stoc[i]->get_id()==id_vandut)
            {
                A=Monovolume_Stoc[i];
                Monovolume_Stoc.erase(Monovolume_Stoc.begin()+i);
                ok=1;
            }
        }
        if(ok==0)
            cout<<"Monovolumul cautat nu exista in stoc \n";
        else
        {
            double reducere=0;
            cout<<"Monovolumul cu id-ul: "<<id_vandut<<" a fost vandut. \n";
            bool sh=A->get_sh();
            Monovolume_Vandute.push_back(A);
            nr_monovolume_vandute++;
            nr_monovolume_stoc--;
        }
    }
    friend ofstream &operator <<(ofstream &out, Vanzare &A)
    {
        cout<<"Numarul de monovolume din stoc este: "<<A.nr_monovolume_stoc<<"\n";
        for(int i=0;i<A.nr_monovolume_stoc;i++)
        {
            A.Monovolume_Stoc[i]->afis();
        }
        cout<<"Numarul de monovolume vandute este: ";
        cout<<A.nr_monovolume_vandute<<"\n";
        for(int i=0;i<A.nr_monovolume_vandute;i++)
        {
            A.Monovolume_Vandute[i]->afis();
        }
    }
    void add_stoc(Monovolum *A)
    {
        Monovolume_Stoc.push_back(A);
        nr_monovolume_stoc++;
    }

};
int Masina::id_generator=1;
int main()
{
    Vanzare <Masina> V;
    Vanzare <unsigned> M;
    int n;
    in>>n;
    for(int i=0;i<n;i++)
    {
        string tip;
        in>>tip;
        if(tip=="MONOVOLUM")
        {

            Monovolum *B=new Monovolum();
            B->set_tip(tip);

            in>>B;
            B->id_generator++;
            try
            {
                if(B->get_nr_persoane()<5 || B->get_nr_persoane()>7)
                    throw(1);
                else
                {
                    B->afis();
                    V.add_stoc(B);
                    M.add_stoc(B);
                }
            }
            catch(int d)
            {
                cout<<"Nu corespunde.. :";
                B->id_generator--;
                B->afis();
            }
        }
        else
        {
            if(tip=="MICA")
            {
                Mica *A=new Mica();
                in>>A;
                A->set_tip(tip);
                A->id_generator++;
                try
                {
                    double lg=A->get_lungime();
                    if(A->get_lungime()<3.85 || A->get_lungime()>4.1)
                    {
                         throw(1);
                    }
                    else
                    {
                         A->afis();
                         V.add_stoc(A);
                    }
                }
                catch(int d)
                {
                    cout<<"Nu corespunde:";
                    A->id_generator--;
                    A->afis();
                }
            }
            else if(tip=="MINI")
            {
                Mini *A=new Mini();
                in>>A;
                A->set_tip(tip);
                A->id_generator++;
                try
                {
                    if(A->get_lungime()>=4 || A->get_litraj()>=2)
                        throw(1);
                    else
                    {
                        V.add_stoc(A);
                        A->afis();
                    }
                }
                catch(int d)
                {
                    cout<<"Nu corespunde:";
                    A->id_generator--;
                    A->afis();
                }
            }
            else if(tip=="COMPACTA")
            {
                Compacta *A=new Compacta();
                in>>A;
                A->set_tip(tip);
                A->id_generator++;
                try{
                    if(A->get_model()!="SEDAN" && A->get_model()!="HATCHBACK" && A->get_model()!="COMBI")
                        throw(1);
                    else
                    {
                        V.add_stoc(A);
                        A->afis();
                    }
                }
                catch(int d)
                {
                    cout<<"Nu corespunde: ";
                    A->id_generator--;
                    A->afis();
                }
            }
        }
    }
    int op=0;
    while(op!=5)
    {
        cout<<"\nAlegeti una dintre variantele.\n";
        cout<<"1.Introduceti o masina in stoc.\n";
        cout<<"2.Vindeti o masina.\n";
        cout<<"3.Afisati stocul.\n";
        cout<<"4.Afisati stocul Monovolumelor.\n";
        cout<<"5.Stop\n";
        cout<<"Introduceti numarul operatiunii dorite:";
        cin>>op;
        switch(op)
        {
        case 1:
            {
            string tip;
            in>>tip;
            if(tip=="MONOVOLUM")
            {
                Monovolum *B=new Monovolum();
                B->set_tip(tip);
                in>>B;
                B->id_generator++;
                try
                {
                    if(B->get_nr_persoane()<5 || B->get_nr_persoane()>7)
                        throw (1);
                    else
                    {
                        V.add_stoc(B);
                        M.add_stoc(B);
                        cout<<"S-a adaugat in stoc masina:\n";
                        B->afis();
                    }
                }
                catch(int d)
                {
                    cout << "Nu corespunde: ";
                    B->id_generator--;
                    B->afis();
                }
            }
            else
            {
                if(tip=="MICA")
                {
                    Mica *A=new Mica();
                    in>>A;
                    A->set_tip(tip);
                    A->id_generator++;
                    try
                    {
                        if (A->get_lungime() > 4.1 || A->get_lungime() < 3.85)
                            throw (1);
                        else
                        {
                            cout<<"S-a adaugat in stoc masina:\n";
                            A->afis();
                            V.add_stoc(A);
                        }
                    }
                    catch(int d)
                    {
                        cout << "Nu corespunde:";
                        A->id_generator--;
                        A->afis();
                    }
                }
                else if(tip=="MINI")
                {
                    Mini *A=new Mini();
                    A->set_tip(tip);
                    in>>A;
                    A->id_generator++;
                    try
                    {
                        if(A->get_lungime()>=4 || A->get_litraj()>=2)
                            throw (1);
                        else
                        {
                            cout<<"S-a adaugat in stoc masina:\n";
                            A->afis();
                            V.add_stoc(A);
                        }
                    }
                    catch(int d)
                    {
                        cout << "Nu corespunde:";
                        A->id_generator--;
                        A->afis();
                    }
                }
                else if(tip=="COMPACTA")
                {
                    Compacta *A=new Compacta();
                    in>>A;
                    A->set_tip(tip);
                    A->id_generator++;
                    try
                    {
                        if(A->get_model()!="SEDAN" && A->get_model()!="HATCHBACK" && A->get_model()!="COMBI")
                            throw (1);
                        else
                        {
                            cout<<"S-a adaugat in stoc masina:\n";
                            A->afis();
                            V.add_stoc(A);
                        }
                    }
                    catch(int d)
                    {
                        cout << "Nu corespunde:";
                        A->id_generator--;
                        A->afis();
                    }
                    V.add_stoc(A);
                    A->afis();
                }
            }
            }
            break;
        case 2:
            {
                int idm;
                string tipm;
                cout<<"Introduceti tipul si id-ul masinii:";
                cin>>tipm>>idm;
                if(V.id_exist(idm))
                {
                    Masina *A=new Masina();
                    A=V.find_pret(idm);
                    //A->id_generator-=2;
                    if(A->get_tip()==tipm)
                    {
                        if(tipm=="MONOVOLUM")
                        {
                            int luna;
                            meniu_luna(luna);
                            if(luna>=6 && luna<=8)
                                A->set_reducere(10);
                            M-=idm;
                        }
                        V-=idm;
                    }
                    else
                        cout<<"Masina nu exista";
                }
                else
                    cout<<"Masina nu exista";
                break;
            }
        case 3:
            {
                out<<V;
                break;
            }
        case 4:
            {
                out<<M;
                break;
            }
        case 5:
            break;
        }
    }
    return 0;
}
