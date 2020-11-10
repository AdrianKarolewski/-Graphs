#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
class Graph
{
private:

    int m_vertex, m_edges;
    std::vector<std::vector<int> > vertex;           // pierwszy argument nr wieszcholka drugi to stopien wieszcho³ka
    std::vector<std::vector<int> > edges;            // przy grafie skierowanym pierwszy argument to wieszcholek wychodzacy drgui to wchodzacy
    std::vector<std::vector<int> > incident_m;       // macierz incydencji
    std::vector<std::vector<int> > neightborhood_m;  // macierz sasiedztwa
    std::vector<std::string>       predecessorList;  // lista poprzednikow
    std::vector<std::string>       successorList;    // lista nastepnikow
    std::vector<std::string>       incidentLIst;     // lista incydencji
    std::vector<int>          visited;       // lista odwiedzonych
public:
    Graph(int m_v, int m_e):
        m_vertex(m_v) , m_edges(m_e)
    {
        vertex.reserve(m_v);
        neightborhood_m.reserve(m_v);
        incident_m.reserve(m_v);
        for (int i = 0; i < m_vertex; i++)                    //tworzymy wektory dwuwymiarowe
        {
            vertex.emplace_back(std::vector<int>(2));
            neightborhood_m.emplace_back(std::vector<int>(m_vertex));
            incident_m.emplace_back(std::vector<int>(m_edges));
        }
        edges.reserve(m_e);
        for (int i = 0; i < m_edges; i++)                        //tworzymy wektor dwuwymiarowe
        {
            edges.emplace_back(std::vector<int>(2));
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
                    std::cout << "BLAD W NR Wierzcholka !!! POPRAW" << std::endl;
                }
                j++;
                std::cout << "Podawaj Wierzcholki w krawedzi pamietaj z zakresu od 1 do " << m_vertex << std::endl;
                std::cout << "Podaj pierwszy Wierzcholek krawedzi: " << std::endl; std::cin >> first;
                std::cout << "Podaj drugi Wierzcholek krawedzi: " << std::endl; std::cin >> secound;
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
        std::cout << "************************************************" << std::endl;
        for (int i = 0; i < m_vertex; i++)
        {
            std::cout << "Wierzcholek nr " << vertex[i][0] << " stopien Wierzcholek " << vertex[i][1] << std::endl;
        }
        std::cout << "************************************************" << std::endl;
        std::cin.get();
    }
    void printEdges()
    {
        std::cout << "************************************************" << std::endl;
        for (int i = 0; i < m_edges; i++)
        {
            std::cout << "Wierzcholek wyjsciowy " << edges[i][0] << " Wierzcholek wejsciowy " << edges[i][1] << std::endl;
        }
        std::cout << "************************************************" << std::endl;
        std::cin.get();
    }
    void addVertex()
    {
        vertex.emplace_back(std::vector<int>(2));
        vertex[m_vertex][0] = m_vertex + 1;
        vertex[m_vertex][1] = 0;
        for (int i = 0; i < m_vertex; i++)
        {
            neightborhood_m[i].emplace_back(0);
        }
        m_vertex++;

        incident_m.emplace_back(std::vector<int>(m_edges));           //uzupelnienei macierzy incydencji i sasiedztwa
        neightborhood_m.emplace_back(std::vector<int>(m_vertex));
        for (int i = 0; i < m_vertex; i++)
        {
            neightborhood_m[i].emplace_back(0);
        }
    }
    void addEdge()
    {
        edges.emplace_back(std::vector<int>(2));                                               // dodanie miejsca na nowa krawedz
        int first = -1, secound = -1;
        int j = 0;
        while ((first <= 0 || first > m_vertex) || (secound <= 0 || secound > m_vertex))
        {
            if (j != 0)
            {
                std::cout << "BLAD W NR WIERZCHOLKA !!! POPRAW" << std::endl;
            }
            j++;
            std::cout << "Podawaj Wierzcholki w krawedzi pamietaj z zakresu od 1 do " << m_vertex << std::endl;
            std::cout << "Podaj pierwszy Wierzcholek krawedzi: " << std::endl; std::cin >> first;
            std::cout << "Podaj drugi Wierzcholek krawedzi: " << std::endl; std::cin >> secound;

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
        std::cout << "*********************************************************" << std::endl;
        std::cout << "Macierz incydencji" << std::endl;
        for (int i = 0; i < m_vertex; i++)
        {
            for (int j = 0; j < m_edges; j++)
            {
                std::cout << " | " << std::setw(2) << incident_m[i][j];
            }
            std::cout << " |" << std::endl;
        }
        std::cout << "********************************************************" << std::endl;
        std::cin.get();
    }
    void printNeightborhoodM()
    {
        std::cout << "********************************************************" << std::endl;
        std::cout << "Macierz sasiedztwa" << std::endl;
        for (int i = 0; i < m_vertex; i++)
        {
            for (int j = 0; j < m_vertex; j++)
            {
                std::cout << " | " << std::setw(2) << neightborhood_m[i][j];
            }
            std::cout << " | " << std::endl;
        }
        std::cout << "********************************************************" << std::endl;
        std::cin.get();
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
            incident_m[j].erase(incident_m[j].begin() + i);
        }
        neightborhood_m[edges[i][1] - 1][edges[i][0] - 1] = 0;   // ustawiwamy brak sasiedztwa
        neightborhood_m[edges[i][0] - 1][edges[i][1] - 1] = 0;

        edges.erase(edges.begin() + i); // usuwamy krawedz z vektora krawedzi
        m_edges--;
    }
    void delVertex(bool isDigraph)
    {
        int nr_v;
        std::cout << "Podaj nr Wierzcholka do usuniecia: ";                    std::cin >> nr_v;
        std::cout << "Pozostale Wierzcholki tez zmienia swoja numeracje !!!" << std::endl;
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
       
        vertex.erase(vertex.begin() + nr_v - 1);                 //usuniecie z wektora wieszcholkow

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
        predecessorList = std::vector<std::string>(m_vertex);          // budujemy liste poprzednikow
        std::string helpString;
        for (int i = 0; i < m_vertex; i++)
        {
            helpString = "";
            helpString += std::to_string(i + 1);
            for (int j = 0; j < m_vertex; j++)
            {
                if (neightborhood_m[i][j] == -1)
                {
                    helpString += " -> " + std::to_string(j + 1);
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
        successorList = std::vector<std::string>(m_vertex);          // budujemy liste nastepnikow
        std::string helpString;
        for (int i = 0; i < m_vertex; i++)
        {
            helpString = "";
            helpString += std::to_string(i + 1);
            for (int j = 0; j < m_vertex; j++)
            {
                if (neightborhood_m[i][j] == 1)
                {
                    helpString += " -> " + std::to_string(j + 1);
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

        predecessorList = std::vector<std::string>(m_vertex);          // budujemy liste poprzednikow

        std::string helpString;
        for (int i = 0; i < m_vertex; i++)
        {
            helpString = "";
            helpString += std::to_string(i + 1);
            for (int j = 0; j < m_edges; j++)
            {
                if (incident_m[i][j] == -1)
                {
                    for (int z = 0; z < m_vertex; z++)
                    {
                        if ((incident_m[z][j]) == 1)
                        {
                            helpString += " -> " + std::to_string(z + 1);
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
        successorList = std::vector<std::string>(m_vertex);          // budujemy liste nastepnikow
        std::string helpString;
        for (int i = 0; i < m_vertex; i++)
        {
            helpString = "";
            helpString += std::to_string(i + 1);
            for (int j = 0; j < m_edges; j++)
            {
                if (incident_m[i][j] == 1)
                {
                    for (int z = 0; z < m_vertex; z++)
                    {
                        if ((incident_m[z][j]) == -1)
                        {
                            helpString += " -> " + std::to_string(z + 1);
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
            std::cout << "To nie graf skierowany" << std::endl;
            return;
        }
        std::cout << "************************************************" << std::endl;
        for (int i = 0; i < m_vertex; i++)
        {
            std::cout << successorList[i] << std::endl;
        }
        std::cout << "************************************************" << std::endl;
    }
    void printPredecessorList(bool isDigraph)
    {
        if (!isDigraph)
        {
            std::cout << "To nie graf skierowany" << std::endl;
            return;
        }
        std::cout << "************************************************" << std::endl;
        for (int i = 0; i < m_vertex; i++)
        {
            std::cout << predecessorList[i] << std::endl;
        }
        std::cout << "************************************************" << std::endl;
    }
    void createIncidentList(bool isDigraph)
    {
        if (isDigraph)
        {
            return;
        }

        incidentLIst = std::vector<std::string>(m_vertex);          // budujemy liste incydencji

        std::string helpString;
        for (int i = 0; i < m_vertex; i++)
        {
            helpString = "";
            helpString += std::to_string(i + 1);
            for (int j = 0; j < m_vertex; j++)
            {
                if (neightborhood_m[i][j] == 1)
                {
                    helpString += " -> " + std::to_string(j + 1);
                }
            }
            incidentLIst[i] = helpString;

        }
    }
    void printIncidentList(bool isDigraph)
    {
        if (isDigraph)
        {
            std::cout << "To jest graf skierowany nie ma tej listy" << std::endl;
            return;
        }
        std::cout << "************************************************" << std::endl;
        std::cout << "Lista incydencji";
        for (int i = 0; i < m_vertex; i++)
        {
            std::cout << incidentLIst[i] << std::endl;
        }
        std::cout << "************************************************" << std::endl;
    }
    void dfs(int u, std::vector<std::vector<int> > list1, std::vector<int> ilosc_nastepnikow, std::vector<int>& stos) {
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
            std::cout << "To nie jest graf skierowany!" << std::endl;
            return;
        }

        int i;
        std::vector<int> stos;
        std::vector<int> ilosc_nastepnikow(m_vertex);
        visited = std::vector<int>(m_vertex);

        int u = 0, p; // u - aktualny wierzcholek
        for (i = 0; i <= m_vertex; i++) {
            visited[i] = false;
        }
        std::vector<std::vector<int>> List;
        for (int i = 0; i < m_vertex; i++)
        {
            List.emplace_back(std::vector<int>(m_vertex));
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
        std::cout << "Graf wypisany w porzadku topologicznym: \n";
        for (std::vector<int>::reverse_iterator it = stos.rbegin(); it != stos.rend(); ++it) {
            std::cout << " " << *it + 1;
            std::cout << "\n";
        }
    }
    void isEdge(int first_v, int secound_v, bool isDigraf)
    {
        if (isDigraf)
        {
            if ((neightborhood_m[first_v - 1][secound_v - 1] == 1) && (neightborhood_m[secound_v - 1][first_v - 1] == -1))
            {
                std::cout << "Istnieje taka krawedz";
                return;
            }
        }
        else
        {
            if ((neightborhood_m[first_v - 1][secound_v - 1] == 1) && (neightborhood_m[secound_v - 1][first_v - 1] == 1))
            {
                std::cout << "Istnieje taka krawedz";
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
    std::cout << "Tworzymy graf" << std::endl;
    std::cout << "Podaj ilosc Wierzcholkow: " << std::endl;       std::cin >> how_m_vertex;
    std::cout << "Podaj ilosc krawedzi: " << std::endl;       std::cin >> how_m_edges;
    std::cout << "Jezeli graf ma byc skierowany wpisz 1 jezeli nie wpisz 0" << std::endl; std::cin >> digraph;

    Graph g1 = Graph(how_m_vertex, how_m_edges);
    g1.createVertex();               g1.createEdges();                  g1.countDegree();
    g1.createMIncident(digraph);     g1.createMNeightborhood(digraph);  g1.createPredecessorList(digraph);
    g1.createSuccesorList(digraph);  g1.createIncidentList(digraph);
    short choice;
    while (true)
    {
        std::cout << "?????????????????????????????????????????????????" << std::endl;
        std::cout << "1. Wypisz Wierzcholek i stopnie" << std::endl;
        std::cout << "2. Wypisz krawedzie" << std::endl;
        std::cout << "3. Dodaj Wierzcholek" << std::endl;
        std::cout << "4. Dodaj krawendz" << std::endl;
        std::cout << "5. Wypisz macierz sasiedztwa" << std::endl;
        std::cout << "6. Wypisz macierz incydencji" << std::endl;
        std::cout << "7. Usun krawedz" << std::endl;
        std::cout << "8. Usun Wierzcholek" << std::endl;
        std::cout << "9. Wypisz liste nastepnikow  ( jezeli wybrales graf skierowany " << std::endl;
        std::cout << "10.Wypisz liste poprzednikow( jezeli wybrales graf skierowany)" << std::endl;
        std::cout << "11.Wypisz liste incydencji (jezeli wybrales graf nieskierowany)" << std::endl;
        std::cout << "12.Posortuj i wypisz graf topologicznie (jezeli wybrales graf skierowany)" << std::endl;
        std::cout << "13.Sprawdz czy istnieje krawedz w grafie" << std::endl;
        std::cout << "14.Zakoncz" << std::endl;

        std::cout << "?????????????????????????????????????????????????" << std::endl;
        std::cout << "Co chcesz zrobic: "; std::cin >> choice;
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

            std::cout << "Ktora krawedz usunac " << std::endl;
            std::cout << "Wierzcholek poczatkowy: "; std::cin >> first;
            std::cout << "Wierzcholek koncowy: ";    std::cin >> secound;
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
            std::cout << "Wierzcholek poczatkowy: "; std::cin >> first;
            std::cout << "Wierzcholek koncowy: ";    std::cin >> secound;
            g1.isEdge(first, secound, digraph);
        case 14:
            return 0;
        default:
            std::cout << "Niepoprawny wybor";
            break;

        }
    }
    return 0;
}
