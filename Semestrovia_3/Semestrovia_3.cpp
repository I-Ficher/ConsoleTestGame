#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>


using namespace std;

class Graph
{
    int m; // количество вершин
    int n; // количество ребер/дуг
    int** a; // матрица смежности графа
public:
    Graph() {
        int m = 10;
        int n = 10;
        int a[10][10];
    }
    Graph(int m, int n);
    void TravelMap(const char* file);
    void Print();
    ~Graph();
};

Graph::Graph(int m, int n)
{
    this->m = m; 
    this->n = n;
    a = new int* [m];
    for (int i = 0; i < m; i++)
    {
        a[i] = new int[m];
        for (int j = 0; j < m; j++)
            a[i][j] = (i == j) ? 0 : INT_MAX;
    }
}

void Graph::Print()
{
    for(int i=0;i<m;i++)
    {
        for (int j = 0; j < m; j++)
            if (a[i][j] != INT_MAX)
                cout << a[i][j] << "\t";
            else cout << "M\t";
        cout << endl;
    }
}

void Graph::TravelMap(const char* file)
{
    int x=0;
    ifstream fin(file);
    if (!fin.is_open()) {
        cout << "error file not found" << endl;
    }
    a[0][1] = a[1][0] = 1;
    a[1][2] = a[2][1] = 2;
    a[2][3] = a[3][2] = 3;
    a[3][4] = a[4][3] = 4;
    a[4][5] = a[5][4] = 5;
    a[5][6] = a[6][5] = 6;
    a[6][7] = a[7][6] = 7;
    a[7][8] = a[8][7] = 8;
    a[8][9] = a[9][8] = 9;
    a[9][0] = a[0][9] = 10;
    int gplace;
    while (!fin.eof()) {
        char str[4];
        fin.getline(str, 10);
        gplace = atoi(str);
    }
    fin.close();
    for (int j = 0; j < 10; j++) {
        for (int l = j; l < 10; l++) {
            
            if (gplace == a[j][l]) {
                if (gplace == 1)
                    cout << "хотите перейти в 10";
                else
                    cout << "хотите перейти в " << gplace - 1;

                if (gplace == 10)
                    cout << " или в 1 город?" << endl;
                else
                    cout << " или в " << gplace + 1 << " город?" << endl;

                cin >> x;
                if (x != gplace && (x == gplace + 1 || x == gplace - 1))
                {
                    ofstream fin;
                    fin.open(file);
                    switch (x)
                    {
                    case 1:
                        fin << "1";
                        break;
                    case 2:
                        fin << "2";
                        break;
                    case 3:
                        fin << "3";
                        break;
                    case 4:
                        fin << "4";
                        break;
                    case 5:
                        fin << "5";
                        break;
                    case 6:
                        fin << "6";
                        break;
                    case 7:
                        fin << "7";
                        break;
                    case 8:
                        fin << "8";
                        break;
                    case 9:
                        fin << "9";
                        break;
                    case 10:
                        fin << "10";
                        break;
                    default:
                        cout << "неправильно введена цифра" << endl;
                    }
                }
                else cout << "некорректный ввод" << endl;
            }
        }
    }
}

Graph::~Graph()
{
    for (int i = 0; i < m; i++)
        delete[] a[i];
    delete[] a;
}

void findplace(const char* file,const char* file2) {
    ifstream fin(file);
    ifstream in(file2);
    if (!fin.is_open()) {
        cout << "error file not found" << endl;
    }
    if (!in.is_open()) {
        cout << "error file not found" << endl;
    }
    else if (in.peek() == EOF)  {
        cout << "Вы в пустоши" << endl;
    }
    while (!in.eof())
    {
        char Str[300];
        char* Ptr = NULL;
        in.getline(Str, 300);
        char* ggplace = strtok_s(Str, "", &Ptr);
        while (!fin.eof() ) {
            char str[300];
            char* ptr=NULL;
            fin.getline(str, 300);
            char* gName = strtok_s(str, "$", &ptr);
            char* gJob = strtok_s(ptr, "$", &ptr);
            char* gplace = strtok_s(ptr, "$", &ptr);
            char* gitem = strtok_s(ptr, "$", &ptr);
            if (strcmp(gplace, ggplace) == 0) {
                cout << "Вы находитесь в: " << ggplace << " городе" << endl;
            }
        }
    }
    fin.close();
    in.close();
   
}

struct Item                  //Структура с инфополями и адресным полем
{
    char Name[20];
    Item* Next;                 //Адресное поле
};

class ItemList                      //Класс Список
{
    Item* Head;                 //Указатель на последний активный элемент или просто голова списка
public:
    ItemList() { Head = NULL; }           //Конструктор и инициализация указателя пустым значением
   

    void Add(const char* file, const char* file2)
    {
        ifstream fin(file);
        ifstream in(file2);
        if (!fin.is_open()) {
            cout << "error file not found" << endl;
        }
        if (!in.is_open()) {
            cout << "error file not found" << endl;
        }
        else if (in.peek() == EOF) {
            cout << "Вы в пустоши" << endl;
        }
        while (!in.eof())
        {

            char Str[300];
            char* Ptr = NULL;
            in.getline(Str, 300);
            char* ggplace = strtok_s(Str, "", &Ptr);
            while (!fin.eof()) {
                char str[300];
                char* ptr = NULL;
                fin.getline(str, 300);
                char* gName = strtok_s(str, "$", &ptr);
                char* gJob = strtok_s(ptr, "$", &ptr);
                char* gplace = strtok_s(ptr, "$", &ptr);
                if (strcmp(gplace, ggplace) == 0) {
                    char* gitem = strtok_s(ptr, "$", &ptr);
                    Item* temp = new Item;
                    temp->Next = Head;
                    strcpy_s(temp->Name, gitem);
                    Head = temp;
                }
            }
        }
        fin.close();
        in.close();
                          
    }

    void Show() {
        Item* temp = Head;                 //Определяем указатель, который изначально он равен адресу начала списка
        if (temp != NULL) {
            while (temp != NULL)                   //До тех пор пока не встретит пустое значение
            {
                cout << temp->Name << " "<<endl;
                temp = temp->Next;                    
            }
        }
        else {
            cout << "Инвентарь пуст" << endl;
        }
    }

    ~ItemList()
    {
        while (Head != NULL)          //Пока по адресу не пусто
        {
            Item* temp = Head->Next;   //Временная переменная для хранения адреса следующего элемента
            delete Head;                //Освобождаем адрес обозначающий начало
            Head = temp;                  //Меняем адрес на следующий
        }
    }
};


void ListNpc() {
    
    ifstream fin("NPC.txt");
    if (!fin.is_open())
    {
        cout << "Failed to open file" << endl;
    }
    while (!fin.eof())
    {
        char str[100];
        char* ptr = NULL;

        fin.getline(str, 100);
        char* gName = strtok_s(str, "$", &ptr);
        char* gJob = strtok_s(ptr, "$", &ptr);
        char* gplace = strtok_s(ptr, "$", &ptr);
        char* gitem = strtok_s(ptr, "$", &ptr);
        cout <<"Имя-"<< gName<<" , Профессия-"<< gJob << " , Местожительство-" << gplace << " , Предметы-" << gitem << endl;
    }
    fin.close();
}

int main()
{
    setlocale(LC_ALL, "");
    Graph g(10, 10);
    ItemList itl;
    ListNpc();//первый метод вывода всех Персонажей
    int bread = 5;
    int choose;
    int back=1;
        while (back == 1) {
            if (bread > 0) {
                cout << "1-выберите куда идти" << endl;
                cout << "2-проверить инвентарь" << endl;
                cout << "3-взять предмет у персонажа" << endl;
                cout << "4-проверить где находишься" << endl;
                cin >> choose;
                switch (choose)
                {
                case 1: {
                    g.TravelMap("GG.txt");//Путешествие по карте
                    bread--;
                    break;
                }
                case 2: {
                    itl.Show();//Показ инвентаря
                    cout << "У вас осталось " << bread << " штук хлеба" << endl;
                    break;
                }
                case 3: {
                    itl.Add("NPC.txt", "GG.txt");//Берем предмет у персонажа
                    cout << "Вы взяли предмет" << endl;
                    break;
                }
                case 4: {
                    findplace("NPC.txt", "GG.txt");//Осмотр местности
                    break;
                }
                default:
                    cout << "Сделан неправильный выбор" << endl;
                    break;
                }
                cout << "Вернуться в меню? (1 - Да,а другая введенная цифра выйти) "; cin >> back;

        }
            else {
                cout << "У вас закончился хлеб" << endl;//смерть
                break;
            }
    }
    
}