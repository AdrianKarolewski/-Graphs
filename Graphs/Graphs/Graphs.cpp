#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;
class Graph
{
private:

    int m_vertex, m_edges;
    vector<vector<int> > vertex;           // pierwszy argument nr wieszcholka drugi to stopien wieszcho³ka
    vector<vector<int> > edges;            // przy grafie skierowanym pierwszy argument to wieszcholek wychodzacy drgui to wchodzacy
    vector<vector<int> > incident_m;       // macierz incydencji
    vector<vector<int> > neightborhood_m;  // macierz sasiedztwa
    vector<string>       predecessorList;  // lista poprzednikow
    vector<string>       successorList;    // lista nastepnikow
    vector<string>       incidentLIst;     // lista incydencji
    vector<int>          visited;       // lista odwiedzonych
public:
    Graph(int m_v, int m_e):
        m_vertex(m_v) , m_edges(m_e)
    {
        vertex.reserve(m_v);
        neightborhood_m.reserve(m_v);
        incident_m.reserve(m_v);
        for (int i = 0; i < m_vertex; i++)                    //tworzymy wektory dwuwymiarowe
        {
            vertex.emplace_back(vector<int>(2));
            neightborhood_m.emplace_back(vector<int>(m_vertex));
            incident_m.emplace_back(vector<int>(m_edges));
        }
        edges.reserve(m_e);
        for (int i = 0; i < m_edges; i++)                        //tworzymy wektor dwuwymiarowe
        {
            edges.emplace_back(vector<int>(2));
        }
    }
    void createVertex()
    {
        for (int i = 0; i < m_vertex; i++)
        {
            vertex[i][0] = i + 1;                           // kazdy wierzcholek ma koklejne numery
            vertex[i][1] = 0;                               // inicjalizacja wartosci stopnia wieszcholkow ( na poczatku bez polaczen )
        }
    }
    void createEdges()
    {
        for (int i = 0; i < m_edges; i++)
        {
            int first = -1, secound = -1;
            int j = 0;
            while ((first <= 0 || first > m_vertex) || (secound <= 0 || secound > m_vertex))  // zabezpieczenie przed blednym nr wieszcholka
            {
                if (j != 0)
                {
                    cout << "BLAD W NR Wierzcholka !!! POPRAW" << endl;
                }
                j++;
                cout << "Podawaj Wierzcholki w krawedzi pamietaj z zakresu od 1 do " << m_vertex << endl;
                cout << "Podaj pierwszy Wierzcholek krawedzi: " << endl; cin >> first;
                cout << "Podaj drugi Wierzcholek krawedzi: " << endl; cin >> secound;
            }
            edges[i][0] = first;    // wieszcholek wyjsciowy
            edges[i][1] = secound;  // wieszcholek wejsciowy
        }
    }
    void countDegree()
    {
        for (int i = 0; i < m_edges; i++)
        {
            vertex[(edges[i][0]) - 1][1]++;
            if ((edges[i][0]) == (edges[i][1]))  // jezeli pentla to stopien wzrasta o jeden
            {
                continue;
            }
            vertex[(edges[i][1]) - 1][1]++;
        }
    }
    void printVertex()
    {
        cout << "************************************************" << endl;
        for (int i = 0; i < m_vertex; i++)
        {
            cout << "Wierzcholek nr " << vertex[i][0] << " stopien Wierzcholek " << vertex[i][1] << endl;
        }
        cout << "************************************************" << endl;
        getchar();
    }
    void printEdges()
    {
        cout << "************************************************" << endl;
        for (int i = 0; i < m_edges; i++)
        {
            cout << "Wierzcholek wyjsciowy " << edges[i][0] << " Wierzcholek wejsciowy " << edges[i][1] << endl;
        }
        cout << "************************************************" << endl;
        getchar();
    }
    void addVertex()
    {
        vertex.emplace_back(vector<int>(2));
        vertex[m_vertex][0] = m_vertex + 1;
        vertex[m_vertex][1] = 0;
        for (int i = 0; i < m_vertex; i++)
        {
            neightborhood_m[i].emplace_back(0);
        }
        m_vertex++;

        incident_m.emplace_back(vector<int>(m_edges));           //uzupelnienei macierzy incydencji i sasiedztwa
        neightborhood_m.emplace_back(vector<int>(m_vertex));
        for (int i = 0; i < m_vertex; i++)
        {
            neightborhood_m[i].emplace_back(0);
        }
    }
    void addEdge()
    {
        edges.emplace_back(vector<int>(2));                                               // dodanie miejsca na nowa krawedz
        int first = -1, secound = -1;
        int j = 0;
        while ((first <= 0 || first > m_vertex) || (secound <= 0 || secound > m_vertex))
        {
            if (j != 0)
            {
                cout << "BLAD W NR WIERZCHOLKA !!! POPRAW" << endl;
            }
            j++;
            cout << "Podawaj Wierzcholki w krawedzi pamietaj z zakresu od 1 do " << m_vertex << endl;
            cout << "Podaj pierwszy Wierzcholek krawedzi: " << endl; cin >> first;
            cout << "Podaj drugi Wierzcholek krawedzi: " << endl; cin >> secound;

        }
        edges[m_edges][0] = first;                       // wieszcholek wyjsciowy
        edges[m_edges][1] = secound;                     // wieszcholek wejsciowy
        vertex[(edges[m_edges][0]) - 1][1] ++;           // aktualizacja stopni wieszcholka
        if ((edges[m_edges][0]) != (edges[m_edges][1]))  // jezeli pentla to stopien wzrasta o jeden
        {
            vertex[(edges[m_edges][1]) - 1][1] ++;
        }
        neightborhood_m[edges[m_edges][0] - 1][edges[m_edges][1] - 1] = 1;   //uzupelnienie macierzy sasiedztwa
        neightborhood_m[edges[m_edges][1] - 1][edges[m_edges][0] - 1] = -1;
        for (int i = 0; i < m_vertex; i++)
        {
            incident_m[i].emplace_back(0);
        }
        incident_m[edges[m_edges][0] - 1][m_edges] = 1;   //uzupelnienie macierzy incydencji
        incident_m[edges[m_edges][1] - 1][m_edges] = -1;

        m_edges++;
    }
    void createMIncident(bool isDigraf)
    {
        for (int i = 0; i < m_edges; i++)
        {
            incident_m[edges[i][0] - 1][i] = 1;
            if (isDigraf)
            {
                incident_m[edges[i][1] - 1][i] = -1;
            }
            else
            {
                incident_m[edges[i][1] - 1][i] = 1;
            }

        }
    }
    void createMNeightborhood(bool isDigraf)
    {
        for (int i = 0; i < m_edges; i++)
        {
            neightborhood_m[edges[i][0] - 1][edges[i][1] - 1] = 1;
            if (isDigraf)
            {
                neightborhood_m[edges[i][1] - 1][edges[i][0] - 1] = -1;
            }
            else
            {
                neightborhood_m[edges[i][1] - 1][edges[i][0] - 1] = 1;
            }

        }
    }
    void printIncidentM()
    {
        cout << "*********************************************************" << endl;
        cout << "Macierz incydencji" << endl;
        for (int i = 0; i < m_vertex; i++)
        {
            for (int j = 0; j < m_edges; j++)
            {
                cout << " | " << setw(2) << incident_m[i][j];
            }
            cout << " |" << endl;
        }
        cout << "********************************************************" << endl;
        getchar();
    }
    void printNeightborhoodM()
    {
        cout << "********************************************************" << endl;
        cout << "Macierz sasiedztwa" << endl;
        for (int i = 0; i < m_vertex; i++)
        {
            for (int j = 0; j < m_vertex; j++)
            {
                cout << " | " << setw(2) << neightborhood_m[i][j];
            }
            cout << " | " << endl;
        }
        cout << "********************************************************" << endl;
        getchar();
    }
    void delEdge(int f_ver, int s_ver)
    {

        int i = -1;
        for (int j = 0; j < m_edges; j++)
        {
            if ((edges[j][0] == f_ver) && (edges[j][1] == s_ver))    // znajdujemy index krawedzi
            {
                i = j;
                vertex[edges[j][0] - 1][1]--;
                if (f_ver != s_ver)           // zapobiega zmniejszaniu stopnia o 2 przy petli
                {
                    vertex[edges[j][1] - 1][1]--;
                }
                break;
            }
        }
        if (i == -1)
        {
            return;
        }

        for (int j = 0; j < m_vertex; j++)
        {
            auto k = incident_m[j].begin();   // usuwamy z listy incydencji krawędz
            for (int z = 0; z < i; z++)
            {
                k++;
            }
            incident_m[j].erase(k);
        }
        neightborhood_m[edges[i][1] - 1][edges[i][0] - 1] = 0;   // ustawiwamy brak sasiedztwa
        neightborhood_m[edges[i][0] - 1][edges[i][1] - 1] = 0;
        auto k = edges.begin();
        for (int z = 0; z < i; z++)
        {
            k++;
        }
        edges.erase(k); // usuwamy krawedz z vektora krawedzi
        m_edges--;
    }
    void delVertex(bool isDigraph)
    {
        int nr_v;
        cout << "Podaj nr Wierzcholka do usuniecia: ";                    cin >> nr_v;
        cout << "Pozostale Wierzcholki tez zmienia swoja numeracje !!!" << endl;
        nr_v;
        int i = 0;

        for (int j = 0; j < m_edges; j++) // usuwanie krawedzi tego weiszcholka
        {
            if ((edges[j][0] == nr_v))
            {
                delEdge(edges[j][0], edges[j][1]);
            }
            else if (edges[j][1] == nr_v)
            {
                delEdge(edges[j][1], edges[j][0]);
            }
        }
        for (int j = 0; j < m_edges; j++)  // obinzanie kluczy krawedzi bo klucze wieszcholkow spadna tez
        {
            if (edges[j][0] > nr_v)
            {
                edges[j][0]--;
            }
            if (edges[j][1] > nr_v)
            {
                edges[j][1]--;
            }
        }
        for (int k = nr_v; k < m_vertex; k++)
        {
            vertex[k][0]--;
        }

        for (int k = 0; k < m_vertex; k++)      // zerowanie macierzy sasiedztwa i incydencji by zapobiec błędą
        {
            for (int j = 0; j < m_vertex; j++)
            {
                neightborhood_m[k][j] = 0;
            }
            for (int j = 0; j < m_edges; j++)
            {
                incident_m[k][j] = 0;
            }
        }
        auto k = vertex.begin();         //"index" wieszchołka do usuniecia
        for (int z = 0; z < nr_v - 1; z++)
        {
            k++;
        }
        vertex.erase(k);                 //usuniecie z wektora wieszcholkow

        for (int z = 0; z < m_vertex; z++) // zmniejszenie macierzy sasiedztwa
        {
            neightborhood_m[z].pop_back();
        }
        m_vertex--;
        neightborhood_m.pop_back();       // zmniejszenie macierzy sasiedztwa
        incident_m.pop_back();            // usuniecie nadmiarowego wieszchołka z macierzy incydencji

        createMIncident(isDigraph);       //ponowne stworzenie macierzy incydencji i sasiedztwa
        createMNeightborhood(isDigraph);
        return;
    }
    void createPredecessorList(bool isDigraph)
    {
        if (!isDigraph)
        {
            return;
        }
        predecessorList = vector<string>(m_vertex);          // budujemy liste poprzednikow
        string helpString;
        for (int i = 0; i < m_vertex; i++)
        {
            helpString = "";
            helpString += to_string(i + 1);
            for (int j = 0; j < m_vertex; j++)
            {
                if (neightborhood_m[i][j] == -1)
                {
                    helpString += " -> " + to_string(j + 1);
                }
            }
            predecessorList[i] = helpString;
        }
    }
    void createSuccesorList(bool isDigraph)
    {
        if (!isDigraph)
        {
            return;
        }
        successorList = vector<string>(m_vertex);          // budujemy liste nastepnikow
        string helpString;
        for (int i = 0; i < m_vertex; i++)
        {
            helpString = "";
            helpString += to_string(i + 1);
            for (int j = 0; j < m_vertex; j++)
            {
                if (neightborhood_m[i][j] == 1)
                {
                    helpString += " -> " + to_string(j + 1);
                }
            }
            successorList[i] = helpString;
        }
    }
    void createPredecessorListINCIDENT(bool isDigraph)
    {
        if (!isDigraph)
        {
            return;
        }

        predecessorList = vector<string>(m_vertex);          // budujemy liste poprzednikow

        string helpString;
        for (int i = 0; i < m_vertex; i++)
        {
            helpString = "";
            helpString += to_string(i + 1);
            for (int j = 0; j < m_edges; j++)
            {
                if (incident_m[i][j] == -1)
                {
                    for (int z = 0; z < m_vertex; z++)
                    {
                        if ((incident_m[z][j]) == 1)
                        {
                            helpString += " -> " + to_string(z + 1);
                        }
                    }

                }
            }
            predecessorList[i] = helpString;
        }
    }
    void createSuccesorListINCIDENT(bool isDigraph)
    {
        if (!isDigraph)
        {
            return;
        }
        successorList = vector<string>(m_vertex);          // budujemy liste nastepnikow
        string helpString;
        for (int i = 0; i < m_vertex; i++)
        {
            helpString = "";
            helpString += to_string(i + 1);
            for (int j = 0; j < m_edges; j++)
            {
                if (incident_m[i][j] == 1)
                {
                    for (int z = 0; z < m_vertex; z++)
                    {
                        if ((incident_m[z][j]) == -1)
                        {
                            helpString += " -> " + to_string(z + 1);
                        }
                    }

                }
            }
            successorList[i] = helpString;
        }
    }
    void printSuccessorList(bool isDigraph)
    {
        if (!isDigraph)
        {
            cout << "To nie graf skierowany" << endl;
            return;
        }
        cout << "************************************************" << endl;
        for (int i = 0; i < m_vertex; i++)
        {
            cout << successorList[i] << endl;
        }
        cout << "************************************************" << endl;
    }
    void printPredecessorList(bool isDigraph)
    {
        if (!isDigraph)
        {
            cout << "To nie graf skierowany" << endl;
            return;
        }
        cout << "************************************************" << endl;
        for (int i = 0; i < m_vertex; i++)
        {
            cout << predecessorList[i] << endl;
        }
        cout << "************************************************" << endl;
    }
    void createIncidentList(bool isDigraph)
    {
        if (isDigraph)
        {
            return;
        }

        incidentLIst = vector<string>(m_vertex);          // budujemy liste incydencji

        string helpString;
        for (int i = 0; i < m_vertex; i++)
        {
            helpString = "";
            helpString += to_string(i + 1);
            for (int j = 0; j < m_vertex; j++)
            {
                if (neightborhood_m[i][j] == 1)
                {
                    helpString += " -> " + to_string(j + 1);
                }
            }
            incidentLIst[i] = helpString;

        }
    }
    void printIncidentList(bool isDigraph)
    {
        if (isDigraph)
        {
            cout << "To jest graf skierowany nie ma tej listy" << endl;
            return;
        }
        cout << "************************************************" << endl;
        cout << "Lista incydencji";
        for (int i = 0; i < m_vertex; i++)
        {
            cout << incidentLIst[i] << endl;
        }
        cout << "************************************************" << endl;
    }
    void dfs(int u, vector<vector<int> > list1, vector<int> ilosc_nastepnikow, vector<int>& stos) {
        visited[u] = true;
        int i;
        for (i = 0; i < ilosc_nastepnikow[u]; i++) {
            if (!visited[list1[u][i]]) {
                dfs(list1[u][i], list1, ilosc_nastepnikow, stos);
            }
        }
        stos.emplace_back(u);
    }
    void sortowanie(bool isDigraph) {
        if (!isDigraph)
        {
            cout << "To nie jest graf skierowany!" << endl;
            return;
        }

        int i;
        vector<int> stos;
        vector<int> ilosc_nastepnikow(m_vertex);
        visited = vector<int>(m_vertex);

        int u = 0, p; // u - aktualny wierzcholek
        for (i = 0; i <= m_vertex; i++) {
            visited[i] = false;
        }
        vector<vector<int>> List;
        for (int i = 0; i < m_vertex; i++)
        {
            List.emplace_back(vector<int>(m_vertex));
        }
        for (int i = 0; i < m_vertex; i++)
        {
            p = 0;
            for (int j = 0; j < m_vertex; j++)
            {
                if (neightborhood_m[i][j] == 1)
                {
                    List[i][p++] = j;
                }
            }
            ilosc_nastepnikow[i] = p;
        }
        for (u = 0; u < m_vertex; u++) {
            if (!visited[u]) {
                dfs(u, List, ilosc_nastepnikow, stos);
            }
        }
        cout << "Graf wypisany w porzadku topologicznym: \n";
        for (vector<int>::reverse_iterator it = stos.rbegin(); it != stos.rend(); ++it) {
            cout << " " << *it + 1;
            cout << "\n";
        }
    }
    void isEdge(int first_v, int secound_v, bool isDigraf)
    {
        if (isDigraf)
        {
            if ((neightborhood_m[first_v - 1][secound_v - 1] == 1) && (neightborhood_m[secound_v - 1][first_v - 1] == -1))
            {
                cout << "Istnieje taka krawedz";
                return;
            }
        }
        else
        {
            if ((neightborhood_m[first_v - 1][secound_v - 1] == 1) && (neightborhood_m[secound_v - 1][first_v - 1] == 1))
            {
                cout << "Istnieje taka krawedz";
                return;
            }
        }
    }
};
int main()
{
    int how_m_vertex, how_m_edges;
    bool digraph;
    int first, secound;
    cout << "Tworzymy graf" << endl;
    cout << "Podaj ilosc Wierzcholkow: " << endl;       cin >> how_m_vertex;
    cout << "Podaj ilosc krawedzi: " << endl;       cin >> how_m_edges;
    cout << "Jezeli graf ma byc skierowany wpisz 1 jezeli nie wpisz 0" << endl;       cin >> digraph;

    Graph g1 = Graph(how_m_vertex, how_m_edges);
    g1.createVertex();               g1.createEdges();                  g1.countDegree();
    g1.createMIncident(digraph);     g1.createMNeightborhood(digraph);  g1.createPredecessorList(digraph);
    g1.createSuccesorList(digraph);  g1.createIncidentList(digraph);
    short choice;
    while (true)
    {
        cout << "?????????????????????????????????????????????????" << endl;
        cout << "1. Wypisz Wierzcholek i stopnie" << endl;
        cout << "2. Wypisz krawedzie" << endl;
        cout << "3. Dodaj Wierzcholek" << endl;
        cout << "4. Dodaj krawendz" << endl;
        cout << "5. Wypisz macierz sasiedztwa" << endl;
        cout << "6. Wypisz macierz incydencji" << endl;
        cout << "7. Usun krawedz" << endl;
        cout << "8. Usun Wierzcholek" << endl;
        cout << "9. Wypisz liste nastepnikow  ( jezeli wybrales graf skierowany " << endl;
        cout << "10.Wypisz liste poprzednikow( jezeli wybrales graf skierowany)" << endl;
        cout << "11.Wypisz liste incydencji (jezeli wybrales graf nieskierowany)" << endl;
        cout << "12.Posortuj i wypisz graf topologicznie (jezeli wybrales graf skierowany)" << endl;
        cout << "13.Sprawdz czy istnieje krawedz w grafie" << endl;
        cout << "14.Zakoncz" << endl;

        cout << "?????????????????????????????????????????????????" << endl;
        cout << "Co chcesz zrobic: "; cin >> choice;
        switch (choice)
        {
        case 1:
            g1.printVertex();
            break;
        case 2:
            g1.printEdges();
            break;
        case 3:
            g1.addVertex();
            g1.createPredecessorList(digraph);
            g1.createSuccesorList(digraph);
            g1.createIncidentList(digraph);
            break;
        case 4:
            g1.addEdge();
            g1.createPredecessorList(digraph);
            g1.createSuccesorList(digraph);
            g1.createIncidentList(digraph);
            break;
        case 5:
            g1.printNeightborhoodM();
            break;
        case 6:
            g1.printIncidentM();
            break;
        case 7:

            cout << "Ktora krawedz usunac " << endl;
            cout << "Wierzcholek poczatkowy: "; cin >> first;
            cout << "Wierzcholek koncowy: ";    cin >> secound;
            g1.delEdge(first, secound);
            g1.createPredecessorList(digraph);
            g1.createSuccesorList(digraph);
            g1.createIncidentList(digraph);
            g1.createMIncident(digraph);
            g1.createMNeightborhood(digraph);
            break;
        case 8:
            g1.delVertex(digraph); // nw jak to w praktyce czy nie zniszczy za duzo
            g1.createPredecessorList(digraph);
            g1.createSuccesorList(digraph);
            g1.createIncidentList(digraph);
            g1.createMIncident(digraph);
            g1.createMNeightborhood(digraph);
            break;
        case 9:
            g1.printSuccessorList(digraph);
            break;
        case 10:
            g1.printPredecessorList(digraph);
            break;
        case 11:
            g1.printIncidentList(digraph);
            break;
        case 12:
            g1.sortowanie(digraph);
            break;
        case 13:
            cout << "Wierzcholek poczatkowy: "; cin >> first;
            cout << "Wierzcholek koncowy: ";    cin >> secound;
            g1.isEdge(first, secound, digraph);
        case 14:
            return 0;
        default:
            cout << "Niepoprawny wybor";
            break;

        }
    }
    return 0;
}
