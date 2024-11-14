// Listint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <cstddef>//para size_t
#include <list>//para size_t
#include <stdexcept>
#include <cstdint>//para uint64_t
using namespace std;

//exce��o personalizada para falha de aloca��o de mem�ria

class MemoryAllocationException : public std::exception {
    uint64_t listSize;
public:
    explicit MemoryAllocationException(uint64_t size) : listSize(size){}
    const char* what() const noexcept override {
        return "\nFalha ao alocar mem�ria para lista ligada.\n";
    }
    uint64_t getListSize()const noexcept {
        return listSize;
    }
};

struct Node_int {
    int value;//volor aramazenado no n�
    Node_int* next;//ponteiro para o proximo n�
    Node_int(int val) : value(val), next(nullptr){ cout << "Node_int criado com valor: " << value << endl; }
    ~Node_int() { cout << "Node_int destruido" << endl; }
};

class List_Int {
private:
    Node_int* head; //ponteiro para o primeiro n� da lista
    size_t _size; //tamanho da lista
    //fun��o auxiliar para libertar n�s(evita duplica��o no destrutor e no operador de atribui��o)
    void clear() {
        Node_int* current = head;
        while (current != nullptr) {
            Node_int* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = nullptr;
        _size = 0;
    }
    //fun��o auxiliar para copiar n�s de outra lista
    void copyFrom(const List_Int& other) {
        if (other.head == nullptr) {
            head = nullptr;
            _size = 0;
            return;
        }
        head = new Node_int(other.head->value);
        Node_int* currentOther = other.head->next;
        Node_int* currentThis = head;
        while (currentOther != nullptr) {
            currentThis->next = new Node_int(currentOther->value);
            currentThis = currentThis->next;
            currentOther = currentOther->next; 
        }
        _size = other._size;
    }

public:
    
    List_Int(): head(nullptr), _size(0){ 
        cout << "List_int criada " << endl; 
    }
    //construtor c�pia
    List_Int(const List_Int& other) : head(nullptr), _size(0){ 
        cout << "List_int criada " << endl; 
        copyFrom(other);
    }

    //operador atribui��o
    List_Int& operator=(const List_Int& other) {
        if (this != &other) {//evita auto atribui��o
            clear();//liberta a mem�ria atual
            copyFrom(other);//copia n�s do objeto other
        }
        return *this;
    }

    ~List_Int() {
        clear();
        cout << "List_int destruida " << endl;
    }
    //adiciona um n�mero ao final da lista
    bool add(int number) {
        try {
            Node_int* newNode = new Node_int(number);
            if (!head) {
                head = newNode;
            }
            else {
                Node_int* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
            _size++;
            return true;
        }
        catch (const std::bad_alloc&) {
            //lan�a uma exce��o personalizada caso a aloca��o falhe
            throw MemoryAllocationException(_size);
        }
    }
    //obtem o valor na posi��o especifica
    int* get(size_t pos) {
        if (pos >= _size) {
            return nullptr; // retorna nullptr se a posi��o for inv�lida
        }
        Node_int* current = head;
        for (size_t i = 0; i < pos; ++i) {
            current = current->next;
        }
        return &(current->value);
    }
    //remove o primeiro n� com o valor especificado
    bool remove(int number) {
        Node_int* current = head;
        Node_int* previous = nullptr;

        while (current != nullptr && current->value != number) {
            previous = current;
            current = current->next;
        }
        if (current == nullptr) {
            return false;//valor n�o encontrado
        }
        if (previous == nullptr) {
            head = current->next;//remover o n� da cabe�a
        }
        else {
            previous->next = current->next;
        }
        delete current;
        _size--;
        return true;
    }
    //remove o n� da posi��o especificada
    bool remove(size_t pos) {
        if (pos >= _size) {
            return false;//posi��o inv�lida
        }
        Node_int* current = head;
        Node_int* previous = nullptr;

        for (size_t i = 0; i < pos; ++i) {
            previous = current;
            current = current->next;
        }
        if (current == nullptr) {
            head = current->next; // remove o n� da cabe�a
        }
        else {
            previous->next = current->next;
        }
        delete current;
        _size--;
        return true;   
    }
    //retorna o tamanho atual da lista
    /*size_t size() const {
        return _size;
    }*/

    //adicionar um novo elemento na cauda da lista
    bool addToTail(int number) {
        try {
            Node_int* newNode = new Node_int(number);//tenta alocar memoria para um novo n�
            if (!head) {
                head = newNode;
            }
            else {
                Node_int* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
            _size++;
            return true;
        }
        catch (const bad_alloc&) {
            //lan�a uma exce��o personalizada caso a aloca��o falhe
            throw MemoryAllocationException(_size);
        }
    }
    //adicionar um novoelemento na cabe�a da lista
    bool addToHead(int number) {
        try {
            Node_int* newNode = new Node_int(number);//tenta alocar memoria para um novo n�
            
            newNode->next = head ;
            head = newNode;
            _size++;
            return true;
          
        }
        catch (const bad_alloc&) {
            //lan�a uma exce��o personalizada caso a aloca��o falhe
            throw MemoryAllocationException(_size);
        }
    }
    //retorna o tamanho da lista
    uint64_t size()const {
        return _size;
    }
    //imprime o conteudo da lista
    void print()const {
        Node_int* current = head;
        while (current != nullptr) {
            cout << current->value << " -> ";
            current = current->next;
        }
        cout << "nullptr " << endl;
    }

};


int main()
{
    List_Int listHeadInsertion;
    List_Int listTailInsertion;

    //inser��o na cabe�a
    cout << "Insercao na cabeca da lista: " << endl;
    listHeadInsertion.addToHead(3);
    listHeadInsertion.addToHead(2);
    listHeadInsertion.addToHead(1);
    cout << "Lista apos insecao na cabeca: " << endl;
    listHeadInsertion.print();


    //inser��o na cauda
    cout << "Insercao na cauda da lista: " << endl;
    listTailInsertion.addToHead(4);
    listTailInsertion.addToHead(5);
    listTailInsertion.addToHead(6);
    cout << "Lista apos insecao na cauda: " << endl;
    listTailInsertion.print();

    /*List_Int list;
    try {
        int count = 0;
        while (true) {
            list.add(count++);
        }
    }
    catch (const MemoryAllocationException& e) {
        cerr << e.what() << "\n";
        cerr << "Tamanho da lista quando a memoria foi esgotada: " << e.getListSize() << "\n";
    }*/
    
    /////////////////////////////////////////////////////////////////

    /*//cria��o de uma lista de listas ligada List_Int
    std::list<List_Int> ListaDeListas;

    List_Int list;

    //adiciona elementos � lista
    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);

    //aloca��o de list no contentor STL ListaDeListas
    ListaDeListas.push_back(list);

    cout << "conteudo inicial da lista 1 " << endl;
    for (size_t i = 0; i < list.size(); ++i) {
        cout << "Elemento: " << i << " : " << *(list.get(i)) << endl;
    }
   
    //criar uma nova lista
    List_Int list2;
    cout << "Lista 2 criada " << endl;
    list2.add(50);
    list2.add(60);
    
    //aloca��o de list2 no contentor STL ListaDeListas
    ListaDeListas.push_back(list2);

    //c�pia da lista 2
    cout << "Atribuicao da lista 2  a lista 1 " << endl;
    list = list2;
    
    //adicionar elementos extra
    cout << "Adicionar elemento " << endl;
    list2.add(80);
     
    
    //cout << "\nElemento da posicao 1: " << *(list.get(0)) << endl;
    //cout << "\nElemento da posicao 1: " << *(list2.get(0)) << endl;

    cout << "conteudo da lista 1 apos atribuicao: \n" << endl;

    for (size_t i = 0; i < list.size(); ++i) {
        cout << "Elemento: " << i << " : " << *(list.get(i)) << endl;
    }

    cout << "conteudo da lista 2 apos atribuicao: \n" << endl;

    for (size_t i = 0; i < list2.size(); ++i) {
        cout << "Elemento: " << i << " : " << *(list2.get(i)) << endl;
    }

    
    
    //esvazia a lista removendo todos os elementos
    while (list2.size() > 0) {
        list2.remove(0);
    }
    
    //esvazia a lista removendo todos os elementos
    while (list.size() > 0) {
        list.remove(0);
    }*/

    //////////////////////////////////////////////////////////////////////////

    /*//remover elemento pelo valor
    list.remove(20);
    cout << "Tamanho da lista apos remover 20" << list.size() << endl;
    //remover elemento pela posi��o
    list.remove(3);
    cout << "tamanho da lista apos remover posicao 4: " << list.size() << endl;*/

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
