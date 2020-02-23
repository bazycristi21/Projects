#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
ifstream in1("date1.in");
ifstream in2("date2.in");
ofstream out("date.out");
map <pair<int, char>,int> tranzitii_1;
map <pair<int, char>,int> tranzitii_2;
map <pair<pair<int, int>,char>,pair<int,int>> tranzitii;
queue <pair<int,int>> Q;
int delta_1(int q, char a)
{
    return tranzitii_1[make_pair(q,a)];
}
int delta_2(int q, char a)
{
    return tranzitii_2[make_pair(q,a)];
}
int delta_tilda_1(int q, string aw)
{
    char a=aw[0];
    if(aw.size()==1)
        return delta_1(q,a);
    else
    {
        aw.erase(0,1);
        int p=delta_1(q,a);
        return delta_tilda_1(p,aw);
    }

}
int delta_tilda_2(int q, string aw)
{
    char a=aw[0];
    if(aw.size()==1)
        return delta_2(q,a);
    else
    {
        aw.erase(0,1);
        int p=delta_2(q,a);
        return delta_tilda_2(p,aw);
    }

}
pair<int,int> delta(pair<int,int> q, char a)
{
    return tranzitii[{q,a}];
}
pair<int,int> delta_tilda(pair<int,int> q, string aw)
{
    char a=aw[0];
    if(aw.size()==1)
        return delta(q,a);
    else
    {
        aw.erase(0,1);
        return delta_tilda(delta(q,a),aw);
    }

}

int main()
{
    int nr_st_1,nr_litere_1,st_initiala_1,nr_st_finale_1,nr_tranzitii_1,nr_cuvinte_1;
    int nr_st_2,nr_litere_2,st_initiala_2,nr_st_finale_2,nr_tranzitii_2,nr_cuvinte_2;

    int i;
    in1>>nr_st_1;
    vector <int> stari_1(nr_st_1+1);
    for(i=0;i<nr_st_1;i++)
    {
        in1>>stari_1[i];
    }
    in1>>nr_litere_1;
    vector <char> litere_1(nr_litere_1+1);
    for(i=0;i<nr_litere_1;i++)
    {
        in1>>litere_1[i];
    }
    in1>>st_initiala_1;
    in1>>nr_st_finale_1;
    vector <int> st_finale_1(nr_st_finale_1+1);
    for(i=0;i<nr_st_finale_1;i++)
    {
        in1>>st_finale_1[i];
    }
    in1>>nr_tranzitii_1;
    for(i=0;i<nr_tranzitii_1;i++)
    {
        int a,c;
        char b;
        in1>>a>>b>>c;
        tranzitii_1[{a,b}]=c;
    }
    int j;
    in1>>nr_cuvinte_1;
    vector <string> cuvinte_1;
    for(i=0;i<nr_cuvinte_1;i++)
    {
        string cuvant;
        in1>>cuvant;
        cuvinte_1.push_back(cuvant);
    }
    //////////

    in2>>nr_st_2;
    vector <int> stari_2(nr_st_2+1);
    for(i=0;i<nr_st_2;i++)
    {
        in2>>stari_2[i];
    }
    in2>>nr_litere_2;
    vector <char> litere_2(nr_litere_2+1);
    for(i=0;i<nr_litere_2;i++)
    {
        in2>>litere_2[i];
    }
    in2>>st_initiala_2;
    in2>>nr_st_finale_2;
    vector <int> st_finale_2(nr_st_finale_2+1);
    for(i=0;i<nr_st_finale_2;i++)
    {
        in2>>st_finale_2[i];
    }
    in2>>nr_tranzitii_2;

    for(i=0;i<nr_tranzitii_2;i++)
    {
        int a,c;
        char b;
        in2>>a>>b>>c;
        tranzitii_2[make_pair(a,b)]=c;
    }

    in2>>nr_cuvinte_2;
    vector <string> cuvinte_2;
    for(i=0;i<nr_cuvinte_2;i++)
    {
        string cuvant;
        in2>>cuvant;
        cuvinte_2.push_back(cuvant);
    }
    vector <char> Limbaj;
    vector <int> vizLimbaj(27,0);
    for(i=0;i<nr_litere_1;i++)
    {
        vizLimbaj[litere_1[i]-'a']++;
    }
    for(i=0;i<nr_litere_2;i++)
    {
        vizLimbaj[litere_2[i]-'a']++;
    }
    for(int j=0;j<26;j++)
        if(vizLimbaj[j]==2)
            Limbaj.push_back('a'+j);
    vector <int> Stari_numerotate;
    for(auto i: stari_1)
        for(auto j:stari_2)
             Stari_numerotate.push_back(i*10000+j);
    for(auto i:stari_1)
        for (auto j:stari_2)
            for(auto k:Limbaj)
                    tranzitii[{{i,j},k}]={tranzitii_1[{i,k}],tranzitii_2[{j,k}]};
    map <pair<int, char>,int> tranzitii_numerotate;
    for(auto i:stari_1)
        for (auto j:stari_2)
            for(auto k:Limbaj)
                tranzitii_numerotate[{i*10000+j,k}]=tranzitii_1[{i,k}]*10000+tranzitii_2[{j,k}];

    vector <pair<int, int>> Finale;
    vector <int> Finale_numerotate;
    int st_init_numerotata=st_initiala_1*10000+st_initiala_2;
    for(auto i:st_finale_1)
        for(auto j: st_finale_2)
        {
            Finale.push_back({i,j});
            Finale_numerotate.push_back(i*10000+j);
        }
    out<<Stari_numerotate.size()<<"\n";
    for(auto i: Stari_numerotate)
    {
        out<<i<<" ";
    }
    out<<"\n";
    out<<Limbaj.size()<<"\n";
    for(char i:Limbaj)
        out<<i<<" ";
    out<<"\n";
    out<<st_init_numerotata<<"\n";
    out<<Finale_numerotate.size()<<"\n";
    for(auto i:Finale_numerotate)
    {
        out<<i<<" ";
    }
    out<<"\n"<<tranzitii_numerotate.size()<<"\n";
    for(auto i: tranzitii_numerotate)
    {
       out<<i.first.first<<" "<<i.first.second<<" "<<i.second<<"\n";
    }
}
