#include<iostream>
#include<cstdio>
#include<cstdlib>
#include <ctime>
#include <ratio>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <cmath>
#include<windows.h>

using namespace std;
string cr, cl, cp;


/////////ARRAY///////////
class Array
{
    int size = 0;
    int* arr;
public:
    void search_element(int value);
    void delete_element(int index);
    void add_on_position(int index, int value);
    void generate_array(int ilosc);
    void show();
    void load();
    void erase();
};

void arrayMenu()
{
    srand(time(NULL));
    int choice, value, index;
    Array tab;
    using namespace std::chrono;
    while (1)
    {
        cout << "____________ARRAY_____________" << endl;
        cout << "0. READ FROM FILE" << endl;
        cout << "1. GENERATE ARRAY" << endl;
        cout << "2. ADD EMELEMNT ON POSITION" << endl;
        cout << "3. DELETE ELEMENT" << endl;
        cout << "4. SHOW ARRAY" << endl;
        cout << "5. FIND ELEMENT" << endl;
        cout << "6. DELETE ARRAY" << endl;
        cout << "7. EXIT" << endl;
        cout << "choice: " << endl;
        cout << "________________________________" << endl;
        cin >> choice;

        high_resolution_clock::time_point start_time;
        high_resolution_clock::time_point end_time;
        duration<double> time;

        switch (choice)
        {
        case 0:
            tab.load();
            break;
        case 1:
            cout << "Give size: ";
            cin >> value;
            tab.generate_array(value);
            cout << endl;
            break;
        case 2:
            cout << "Element: ";
            cin >> value;
            cout << "Position: ";
            cin >> index;
            start_time = high_resolution_clock::now();
            tab.add_on_position(index, value);
            end_time = high_resolution_clock::now();
            time = end_time - start_time;
            cout << endl;
            cout << "Time: " << time / milliseconds(1) << " ms.";
            cout << endl;
            break;
        case 3:

            cout << "What do you want to delete?: ";
            cin >> value;
            start_time = high_resolution_clock::now();
            tab.delete_element(value);
            end_time = high_resolution_clock::now();
            time = end_time - start_time;
            cout << endl;
            cout << "Time: " << time / milliseconds(1) << " ms.";
            cout << endl;
            break;
        case 4:

            tab.show();
            cout << endl;
            break;
        case 5:
            cout << "What to look for?: ";
            cin >> value;
            start_time = high_resolution_clock::now();
            tab.search_element(value);
            end_time = high_resolution_clock::now();
            cout << endl;
            time = end_time - start_time;
            cout << endl;
            cout << "Time: " << time / milliseconds(1) << " ms.";
            cout << endl;
            break;
        case 6:
            tab.erase();
            break;
        case 7:
            return;
        default:
            cout << "no such option" << endl;
        }
    }

}

void Array::erase()
{
    delete arr;
    size = 0;
}

void Array::generate_array(int ammount)
{
    size = ammount;
    arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 1000;
    }
}

void Array::load()
{
    if (size != 0)
    {
        erase();
    }
    string filename;
    cin >> filename;
    fstream myfile;
    myfile.open(filename, ios::in);
    if (myfile.is_open())
    {
        string read;
        int count = 0;
        int value;
        int index = -1;
        while (getline(myfile, read)) {
            value = stoi(read);
            if (count == 0)
            {
                size = value;
                arr = new int[size];
                count++;
            }
            else
            {
                arr[index] = value;
            }
            index++;
        }
        myfile.close();

    }
}

void Array::show()
{
    if (size == 0)
    {
        cout << "Array is empty" << endl;
        return;
    }
    if (size != 0) {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " | ";
        }
        cout << endl;
    }
}

void Array::search_element(int value)
{
    bool found = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            cout << "Element found " << value << " on position: " << i << endl;
            found = 1;
            return;
        }
    }
    if (found == 0)
    {
        cout << "no element" << endl;
    }
}

void Array::add_on_position(int index, int value)
{
    int* NewArr = new int[size + 1];
    for (int i = 0;i < index;++i)
    {
        NewArr[i] = arr[i];
    }
    NewArr[index] = value;
    for (int i = index + 1;i < size + 1;++i)
    {
        NewArr[i] = arr[i - 1];
    }
    delete[] arr;
    arr = NewArr;
    ++size;
}

void Array::delete_element(int index)
{
    if (index > size)
    {
        cout << "no such index" << endl;
        return;
    }

    int* NewArr = new int[size - 1];
    for (int i = 0; i < index; i++)
    {
        NewArr[i] = arr[i];
    }
    for (int i = index;i <= size - 1;i++)
    {
        NewArr[i] = arr[i + 1];
    }
    delete[] arr;
    arr = NewArr;
    size--;
}
/////////////////////////////////////////////

/////////////////DOUBLY LINKED LIST//////////////////////
struct element
{
    int data;
    struct element* next; 
    struct element* prev; 
}*start; 

class List
{
public:
    void generate_list(int ilosc);
    void create_list(int value);
    void show();
    void add_first(int value);
    void add_position(int value, int index);
    void deleteList(int value);
    void search(int value);
    List()
    {
        start = NULL;
    }
};

void load()
{
    string filename;
    cin >> filename;
    fstream myfile;

    myfile.open(filename, ios::in);
    if (myfile.is_open())
    {
        string read;
        getline(myfile, read);
        struct element* last = new(struct element);
        while (getline(myfile, read)) {
            struct element* tmp;
            tmp = new(struct element);
            tmp->data = stoi(read);
                             
            if (start == NULL)
            {
                start = tmp;
                start->next = NULL;
                start->prev = NULL;
                last = start;
            }
            else {
                last->next = tmp;
                tmp->prev = last;
                last = tmp;
                tmp->next = NULL;
            }
        }
        myfile.close();
    }
}

void listMenu()
{
    srand(time(NULL));
    int choice, value, index;
    List list;
    using namespace std::chrono;
    while (1)
    {


        cout << "_____________DOUBLY LINKED LIST______________" << endl;
        cout << "0. LOAD FROM FILE" << endl;
        cout << "1. CREATE FIRST ELEMENT" << endl;
        cout << "2. ADD AT FIRST PSITION" << endl;
        cout << "3. ADD ON POSITION" << endl;
        cout << "4. DELETE ELEMENT" << endl;
        cout << "5. SHOW LIST" << endl;
        cout << "6. GENERATE RANDOM" << endl;
        cout << "7. FIND ELEMENT" << endl;
        cout << "8. EXIT" << endl;

        cout << "choice: " << endl;
        cout << "________________________________" << endl;
        cin >> choice;

        high_resolution_clock::time_point start_time;
        high_resolution_clock::time_point end_time;
        duration<double> time;



        switch (choice)
        {
        case 0:
            load();
            break;
        case 1:
            cout << "Create: ";
            cin >> value;
            list.create_list(value);
            cout << endl;
            break;
        case 2:
            cout << "Add element at first position: ";
            cin >> value;
            start_time = high_resolution_clock::now();
            list.add_first(value);
            end_time = high_resolution_clock::now();
            time = end_time - start_time;
            cout << endl;
            cout << "Time: " << time / milliseconds(1) << " ms.";
            break;
        case 3:
            cout << "Type in element: ";
            cin >> value;
            cout << "Position: ";
            cin >> index;
            start_time = high_resolution_clock::now();
            list.add_position(value, index);
            end_time = high_resolution_clock::now();
            time = end_time - start_time;
            cout << endl;
            cout << "Time: " << time / milliseconds(1) << " ms.";
            cout << endl;
            break;
        case 4:
            if (start == NULL)
            {
                cout << "List empty" << endl;
                break;
            }
            cout << "What to remove?: ";
            cin >> value;
            start_time = high_resolution_clock::now();
            list.deleteList(value);
            end_time = high_resolution_clock::now();
            time = end_time - start_time;
            cout << endl;
            cout << "Time " << time / milliseconds(1) << " ms.";
            cout << endl;

            break;
        case 5:
            list.show();
            cout << endl;
            break;
        case 6:
            cout << "Size: ";
            cin >> value;
            start_time = high_resolution_clock::now();
            list.generate_list(value);
            end_time = std::chrono::high_resolution_clock::now();
            time = end_time - start_time;
            cout << endl;
            cout << "Time: " << time / milliseconds(1) << " ms.";
            cout << endl;
            break;
        case 7:
            cout << "What to find: ";
            cin >> value;
            start_time = high_resolution_clock::now();
            list.search(value);
            cout << endl;
            end_time = high_resolution_clock::now();
            time = end_time - start_time;
            cout << endl;
            cout << "Time: " << time / milliseconds(1) << " ms.";
            cout << endl;
            break;
        case 8:
            return; break;
        default:
            cout << "no such option" << endl;
        }
    }

}

void List::create_list(int value)
{
    struct element* tmp;
    tmp = new(struct element);
    tmp->data = value;
    tmp->next = NULL;
    if (start == NULL)
    {
        tmp->prev = NULL;
        start = tmp;
    }

}


void List::generate_list(int value)
{

    for (int i = 0; i < value; i++)
    {
        struct element* tmp;
        tmp = new(struct element);
        tmp->data = rand() % 1000;
        tmp->prev = NULL;
      
        if (start == NULL)
        {
            start = tmp;
            start->next = NULL;
        }
        else {
            tmp->next = start;
            start->prev = tmp;
            start = tmp;

        }

    }
    cout << "Elements added" << endl;
}

void List::add_first(int value)
{
    if (start == NULL)
    {
        cout << "Create first!!!" << endl;
        return;
    }
    struct element* tmp;
    tmp = new(struct element);
    tmp->prev = NULL;
    tmp->data = value;
    tmp->next = start;
    start->prev = tmp;
    start = tmp;
    cout << "Element added" << endl;
}


void List::add_position(int value, int pos)
{
    if (start == NULL)
    {
        cout << "Create first!!!" << endl;
        return;
    }
    struct element* tmp, * p;
    p = start;
    for (int i = 0;i < pos - 1;i++)
    {
        p = p->next;
        if (p == NULL)
        {
            cout << "Its less than ";
            cout << pos << " elements." << endl;
            return;
        }
    }
    tmp = new(struct element);
    tmp->data = value;
    if (p->next == NULL)
    {
        p->next = tmp;
        tmp->next = NULL;
        tmp->prev = p;
    }
    else
    {
        tmp->next = p->next;
        tmp->next->prev = tmp; //1 2 (4)<->3     tmp=4 q=2
        p->next = tmp;
        tmp->prev = p;
    }
    cout << "Element added" << endl;
}


void List::deleteList(int value)
{
    struct element* tmp, * p;
    if (start->data == value)
    {
        tmp = start;
        start = start->next;
        start->prev = NULL;
        cout << "Element deleted" << endl;
        free(tmp); 
        return;
    }
    p = start;
    while (p->next->next != NULL)
    {

        if (p->next->data == value) 
        {
            tmp = p->next;
            p->next = tmp->next;
            tmp->next->prev = p;
            cout << "Element deleted" << endl;
            free(tmp);
            return;
        }
        p = p->next;
    }
    if (p->next->data == value)
    {
        tmp = p->next;
        free(tmp);
        p->next = NULL;
        cout << "Element deleted" << endl;
        return;
    }
    cout << "no such element: " << value << endl;
}

void List::show()
{
    struct element* p;
    if (start == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }


    cout << "List:" << endl;
    int counter = 0;
    p = start;
    while (p != NULL)
    {
        if (p->next != NULL)
            cout << p->data << " <---> ";
        if (p->next == NULL)
            cout << p->data << endl;
        p = p->next;
        counter++;
    }


    int* tab;
    tab = new int[counter];

    p = start;

    cout << "List backwards:" << endl;

    for (int i = 0; i < counter; i++)
    {
        tab[i] = p->data;
        p = p->next;
    }
    for (int i = counter - 1;i >= 0;i--)
    {
        if (i > 0)
            cout << tab[i] << " <---> ";
        if (i == 0)
            cout << tab[i] << endl;
    }
}


void List::search(int value)
{
    struct element* p;
    if (start == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }
    p = start;

    while (p != NULL)
    {
        if (p->data == value)
        {
            cout << "element found: " << value << endl;
            return;
        }
        p = p->next;
    }

}
////////////////////////////////////////////

///////////////////HEAP////////////////////
class Heap
{
    int* T;
    int size = 0;

public:
    void find_element(int value);
    void remove(int index);
    void add(int value);
    void repairDown(int tab[], int index, int rozmiar);
    void repairUp(int tab[], int index);
    void generate_heap(int ilosc);
    void show(string sp, string sn, int v);
    void load();
    void erase();
    void showAsArray();
};

void heapMenu()
{
    cr = cl = cp = "  ";
    cr[0] = 218; cr[1] = 196;
    cl[0] = 192; cl[1] = 196;
    cp[0] = 179;
    srand(time(NULL));
    int choice, value;
    Heap heap;
    using namespace std::chrono;
    while (1)
    {
        cout << "____________BINARY HEAP_____________" << endl;
        cout << "0. LOAD FROM FILE" << endl;
        cout << "1. GENERATE HEAP" << endl;
        cout << "2. ADD" << endl;
        cout << "3. DELETE" << endl;
        cout << "4. SHOW HEAP" << endl;
        cout << "5. FIND" << endl;
        cout << "6. ERASE" << endl;
        cout << "6. EXIT" << endl;
        cout << "choice: " << endl;
        cout << "________________________________" << endl;
        cin >> choice;

        high_resolution_clock::time_point start_time;
        high_resolution_clock::time_point end_time;
        duration<double> time;

        switch (choice)
        {
        case 0:
            heap.load();
            break;
        case 1:
            cout << "Size: ";
            cin >> value;
            heap.generate_heap(value);
            cout << endl;
            break;

        case 2:
            cout << "Element: ";
            cin >> value;

            start_time = high_resolution_clock::now();
            heap.add(value);
            end_time = high_resolution_clock::now();
            time = end_time - start_time;
            cout << endl;
            cout << "Time: " << time / milliseconds(1) << " ms.";
            cout << endl;
            break;
        case 3:

            cout << "What to remove?: ";
            cin >> value;

            start_time = high_resolution_clock::now();
            heap.remove(value);
            end_time = high_resolution_clock::now();
            time = end_time - start_time;
            cout << endl;
            std::cout << "Time: " << time / milliseconds(1) << " ms.";
            cout << endl;
            break;

        case 4:
            heap.show("", "", 0);
            cout << endl;
            heap.showAsArray();
            cout << endl;
            break;
        case 5:
            cout << "What to find?: ";
            cin >> value;
            start_time = high_resolution_clock::now();
            heap.find_element(value);
            cout << endl;
            end_time = high_resolution_clock::now();
            time = end_time - start_time;
            cout << endl;
            std::cout << "Time: " << time / milliseconds(1) << " ms.";
            cout << endl;
            break;
        case 6:
            heap.erase(); break;
        case 7:
            return; break;
        default:
            cout << "no such option" << endl;
        }
    }

}

void Heap::generate_heap(int size)
{

    T = new int[size + 100];
    int value;
    int i, j;
    for (int z = 0; z < size; z++)
    {
        value = rand() % 1000;
        i = size++;
        j = (i - 1) / 2;

        while (i > 0 && T[j] < value)
        {
            T[i] = T[j];
            i = j;
            j = (i - 1) / 2;
        }

        T[i] = value;
    }
}

void Heap::erase()
{
    delete T;
    size = 0;
}

void Heap::load()
{

    string filename;
    cin >> filename;
    fstream myfile;
    myfile.open(filename, ios::in);
    if (myfile.is_open())
    {
        string read;
       
        int value;
        int count = 0;

        while (getline(myfile, read)) {
            value = stoi(read);
            if (count == 0)
            {

                T = new int[value + 100];
                count = 1;
            }
            else {
                int i, j;

                i = size++;
                j = (i - 1) / 2;

                while (i > 0 && T[j] < value)
                {
                    T[i] = T[j];
                    i = j;
                    j = (i - 1) / 2;
                }

                T[i] = value;
            }
        }
        myfile.close();

    }
}

void Heap::show(string sp, string sn, int v)
{
    string s;

    if (v < size)
    {
        s = sp;
        if (sn == cr) s[s.length() - 2] = ' ';
        show(s + cp, cr, 2 * v + 2);

        s = s.substr(0, sp.length() - 2);

        cout << s << sn << T[v] << endl;

        s = sp;
        if (sn == cl) s[s.length() - 2] = ' ';
        show(s + cp, cl, 2 * v + 1);
    }
}

void Heap::showAsArray()
{
    
    if (size != 0) {
        for (int i = 0; i < size; i++)
        {
            cout << T[i] << " | ";
        }
        cout << endl;
    }
}

void Heap::find_element(int value)
{
    bool found = 0;
    for (int i = 0; i < size; i++)
    {
        if (T[i] == value)
        {
            cout << "element found" << value << " on position: " << i << endl;
            found = 1;
        }
    }
    if (found == 0)
    {
        cout << "no element" << endl;
    }
}

void Heap::add(int v)
{
    int i, j;

    i = size++; 
    j = (i - 1) / 2; 

    while (i > 0 && T[j] < v)
    {
        T[i] = T[j];
        i = j;
        j = (i - 1) / 2;
    }

    T[i] = v;
}


void Heap::remove(int value)
{
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (T[i] == value) {
            index = i;
        }
    }
    if (index != -1) {
        if (size == 1) {
            --size;
            T[0] = NULL;
        }
        else {
            T[index] = T[size - 1];
            T[size - 1] = 0;
            --size;
            int rodzic = floor((index - 1) / 2);
            if (T[rodzic] < T[index]) {
                repairUp(this->T, index);
            }
            else
            {
                repairDown(this->T, index, this->size);
            }
        }
    }

}

void Heap::repairDown(int tab[], int index, int size)
{
    int left, right;
    while (size > 2 * index + 1)
    {
        if (size > 2 * index + 2) 
        {
            right = 2 * index + 2;
            left = 2 * index + 1;
            if ((tab[left] > tab[index]) || (tab[right] > tab[index]))
            {
                if (tab[left] > tab[right])
                {
                    int tmp = tab[index];
                    tab[index] = tab[left];
                    tab[left] = tmp;
                    index = left;
                }
                if (tab[right] > tab[left])
                {
                    int tmp = tab[index];
                    tab[index] = tab[right];
                    tab[right] = tmp;
                    index = right;
                }
            }
            else return;
        }
        else 
        {
            left = 2 * index + 1;
            if (tab[left] > tab[index])
            {
                int tmp = tab[index];
                tab[index] = tab[left];
                tab[left] = tmp;
                index = left;
            }
            else
            {
                return;
            }
        }
    }
}

void Heap::repairUp(int tab[], int index)
{
    bool heapReg = true;
    int tmp;
    while (heapReg)
    {
        int parent = floor((index - 1) / 2);
        if (tab[parent] < tab[index])
        {
            tmp = tab[parent];
            tab[parent] = tab[index];
            tab[index] = tmp;
        }
        else
        {
            heapReg = false;
        }
        index = parent;
        if (index == 0) {
            heapReg = false;
        }
    }
}
/////////////////////////////////////////////
int main()
{
    while (1)
    {
        system("CLS");
        cout << "1. ARRAY" << endl;
        cout << "2. LIST" << endl;
        cout << "3. HEAP" << endl;
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("CLS");
            arrayMenu();
            break;
        case 2:
            system("CLS");
            listMenu();
            break;
        case 3:
            system("CLS");
            heapMenu();
            break;
        }

    }
    return 0;

}
