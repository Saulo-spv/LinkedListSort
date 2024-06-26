#include <iostream>
#include <cstdlib> 
#include <chrono>

using std::cout;
using std::cin;
using std::string;
using std::endl;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

typedef struct Node
{
    int iValue;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* newNode(int);
void addElementEnd(Node**, int);
void addElementFront(Node**, int);
Node* searchNodebyValue(Node*, int);
void insertAfter(Node*, int);
void insertBefore(Node*, int);
void deleteNode(Node**, Node*);
void deleteNodebyValue(Node**, int);
void printList(Node*);
void swapValue(int&, int&);

// Algoritmos de ordenação

void bubbleSort(Node*);
void optimizedBubbleSort(Node* head);

void selectionSort_Aux(Node*);
void selectionSort(Node*);
void selectionSort_Aux(Node*);
void optimizedSelectionSort(Node*);

int main()
{
    // Criação do cabelhaço da lista
    Node* head1 = NULL;

    // Adicionando elementos na lista
    for(int c = 1; c <= 10; c++){
        addElementEnd(&head1, c);
    }

    // Desordena a lista
    Node* finalNode = searchNodebyValue(head1, 10);
    swapValue(head1->iValue, finalNode->iValue);

    // Impressão da lista
    cout << "LISTA NAO ORDENADA: " << endl;
    printList(head1);

    // Ordena a lista
    optimizedBubbleSort(head1);

    // Lista ordenada
    cout << "LISTA ORDENADA (BUBBLE): " << endl;
    printList(head1);

    // Desordena a lista
    finalNode = searchNodebyValue(head1, 10);
    swapValue(head1->iValue, finalNode->iValue);

    // Impressão da lista
    cout << "LISTA NAO ORDENADA: " << endl;
    printList(head1);

    // Ordena a lista
    optimizedSelectionSort(head1);

    // Lista ordenada
    cout << "LISTA ORDENADA (SELECTION): " << endl;
    printList(head1);


    // Teste com tempos em caso onde a lista esta ordenacada em quase toda parte

    // Criação do cabelhaço da lista
    Node* head2 = NULL;
    Node* head3 = NULL;
    Node* head4 = NULL;
    Node* head5 = NULL;

    // Adicionando elementos na lista
    for(int c = 1; c <= 10000; c++){

        int iNum = rand();
        addElementEnd(&head2, iNum);
        addElementEnd(&head3, iNum);
        addElementEnd(&head4, iNum);
        addElementEnd(&head5, iNum);
    }

    // Teste com Bubble Sort

    // Ordena a lista
    auto timeStart = high_resolution_clock::now();
    bubbleSort(head2);
    auto timeStop = high_resolution_clock::now();

    auto timeDuration = duration_cast<nanoseconds>(timeStop-timeStart);

    cout << "Tempo gastado com bubble sort: " << timeDuration.count() << " nanosegundos" << endl;

    // Ordena a lista com algoritmo otimizado
    timeStart = high_resolution_clock::now();
    optimizedBubbleSort(head3);
    timeStop = high_resolution_clock::now();

    timeDuration = duration_cast<nanoseconds>(timeStop-timeStart);

    cout << "Tempo gastado com bubble sort otimizado: " << timeDuration.count() << " nanosegundos" << endl;

    // Teste com Selection Sort

    // Ordena a lista
    timeStart = high_resolution_clock::now();
    selectionSort(head4);
    timeStop = high_resolution_clock::now();

    timeDuration = duration_cast<nanoseconds>(timeStop-timeStart);

    cout << "Tempo gastado com selection sort: " << timeDuration.count() << " nanosegundos" << endl;

    // Ordena a lista com algoritmo otimizado
    timeStart = high_resolution_clock::now();
    optimizedSelectionSort(head5);
    timeStop = high_resolution_clock::now();

    timeDuration = duration_cast<nanoseconds>(timeStop-timeStart);

    cout << "Tempo gastado com selection sort otimizado: " << timeDuration.count() << " nanosegundos" << endl;

    return 0;
}


Node* newNode(int iValue)
{
    // Criação do nó
    Node* node = (Node*) malloc(sizeof(Node));
    
    // Caso a memória seja alocada com sucesso
    if (node != NULL)
    {
        // Inicialização dos parâmetros
        node->iValue = iValue;
        node->ptrPrev = NULL;
        node->ptrNext = NULL;
        return node;
    }
    
    return NULL;
}

void addElementEnd(Node** head, int iValue)
{
    // Criação do nó
    Node* node = newNode(iValue);
    
    // Se o cabeçalho da lista for vazio, i.e, lista vazia
    if ((*head) == NULL)
    {   
        // A lista se reduz a este nó
        (*head) = node;
    }
    // Caso contrário, i.e, cabeçalho-não vazio
    else
    {
        // Criação de um nó dinâmico
        Node* current = (*head);

        // Percurso até o fim da lista
        while (current->ptrNext != NULL) current = current->ptrNext;

        // Inserção do nó
        node->ptrPrev = current;
        current->ptrNext = node;
    }
}

void addElementFront(Node** head, int iValue)
{
    // Criação do nó
    Node* node = newNode(iValue);
    
    // Se o cabeçalho da lista não for vazio, i.e, lista não-vazia 
    if ((*head) != NULL)
    {
        // Inserção do nó antes do cabeçalho
        node->ptrNext = (*head);
        (*head)->ptrPrev = node;
        // Correção na posição do cabeçalho
        (*head) = node;
        return;
    }

    // Se lista for vazia, a operação se reduz a inserção do nó no cabeçalho
    (*head) = node;
}

Node* searchNodebyValue(Node* head, int iValue)
{
    // Se o cabeçalho da lista for vazio, i.e, lista vazia 
    if (head == nullptr)
    {
        cout << "Empty list! Impossible to search value." << endl;
        return head;
    }
    // Se o valor buscado está no cabeçalho
    else if (head->iValue == iValue)
    {
        // Retornamos o nó do cabeçalho
        return head;
    }
    // Caso contrário
    else
    {
        // Criação de um nó dinâmico
        Node* current = head;

        // Percurso até o fim da lista
        while (current != nullptr & current->iValue != iValue) current = current->ptrNext;
        
        // Se não foi encontrado o nó buscado
        if (current == nullptr)
        {
            cout << "Element not found, sorry." << endl;
            return current;
        }
        // Caso seja encontrado
        else
        {
            // Retornamos um ponteiro para o nó buscado
            return current;
        }
    }
}

void insertAfter(Node* ptrLocation, int iValue)
{
    // Se a localização do nó é vazia
    if (ptrLocation == NULL)
    {
        cout << "Location is NULL. Impossible to insert." << endl;
        return;
    }
    
    // Caso a localização seja válida, criamos o nó
    Node* node = newNode(iValue);
    
    // Inserção do nó na posição desejada
    node->ptrNext = ptrLocation->ptrNext;
    node->ptrPrev = ptrLocation;
    
    ptrLocation->ptrNext = node;
    
    // Verificação de elementos após o nó adicionado. Se for o caso, efetuamos uma operação extra
    if (node->ptrNext != NULL) node->ptrNext->ptrPrev = node;
}

void insertBefore(Node* ptrLocation, int iValue)
{
    // Se a localização do nó é vazia
    if (ptrLocation == NULL)
    {
        cout << "Location is NULL. Impossible to insert." << endl;
        return;
    }

    // Caso a localização seja válida, criamos o nó
    Node* node = newNode(iValue);

    // Verificação se a localização se refere ao primeiro nó
    if (ptrLocation->ptrPrev == nullptr)
    {
        // Inserção do nó para este caso
        ptrLocation->ptrPrev = node;
        node->ptrNext = ptrLocation;
        return;
    }
    // Caso contrário, efetuamos a devida iserção do nó
    Node* ptrTemp = ptrLocation->ptrPrev;
    ptrTemp->ptrNext = node;
    node->ptrNext = ptrLocation;
    node->ptrPrev = ptrTemp;
}

void deleteNode(Node** head, Node* ptrDelete)
{
    // Se o cabeçalho for vazio ou o ponteiro inválido
    if ((*head) == NULL || ptrDelete == NULL)
    {
        cout << "Can't remove it." << endl;
        return;
    }

    // Caso contrário, verifica-se se o nó a ser removido é o primeiro nó da lista
    if ((*head) == ptrDelete) (*head) = ptrDelete->ptrNext;
    // Verificação se existe nós a frente do nó a ser removido
    if (ptrDelete->ptrNext != NULL) ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev;
    // Verificação se existe nós antes do nó a ser removido
    if (ptrDelete->ptrPrev != NULL) ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;
    // Exclusão do nó
    free(ptrDelete);
}

void deleteNodebyValue(Node** head, int iValue)
{
    // Busca pelo nó com o valor a ser removido
    Node* node = searchNodebyValue(*head, iValue);
    // Remove o nó encontrado
    deleteNode(head, node);
}

void printList(Node* head)
{
    // Se o cabeçalho for vazio, i.e., lista vazia
    if (head == NULL)
    {
        cout << "Empty list!" << endl;
    }
    // Caso o cabeçalho fornecido não seja para o primeiro nó da fila
    else if (head->ptrPrev != NULL)
    {
        cout << "Sorry, you're in the middle of list. Please try again with the head of the list." << endl;
    }
    else
    {
        // Criação de nó dinâmico
        Node* current = head;

        cout << "Elements: \n";
        // Percurso até o fim da lista
        while (current != NULL)
        {
            // Impressão dos valores dos nós
            cout << current->iValue << " " << endl;
            current = current->ptrNext;
        } 
    }
}

/*ALGORITMOS DE ORDENAÇÃO*/

void swapValue(int& irefValue1, int& irefValue2)
{
    irefValue1 ^= irefValue2;
    irefValue2 ^= irefValue1;
    irefValue1 ^= irefValue2;
}


/*BUBBLESORT*/

void bubbleSort(Node* head) {

    // Verifica se a lista está vazia
    if (head == nullptr) {
        cout << "Empty list!" << endl;
        return;
    }

    Node* currentOuter = head; // Ponteiro para percorrer a lista externamente
    Node* currentInner = NULL; // Ponteiro para percorrer a lista internamente

    // Percorre a lista com dois loops
    while(currentOuter->ptrNext != NULL){
        currentInner = head;
        while(currentInner->ptrNext != NULL){
            // Compara e troca os elementos se necessário
            if(currentInner->iValue > currentInner->ptrNext->iValue){
                swapValue(currentInner->iValue, currentInner->ptrNext->iValue);
            }
            currentInner = currentInner->ptrNext;
        }
        currentOuter = currentOuter->ptrNext;
    }
}

void optimizedBubbleSort(Node* head) {

    // Verifica se a lista está vazia
    if (head == nullptr) {
        cout << "Empty list!" << endl;
        return;
    }

    // Inicializa o ponteiro 'last' e o coloca no final da lista
    Node* last = head;
    while(last->ptrNext != NULL) {
        last = last->ptrNext;
    }

    Node* current = NULL;

    // Inicializa um flag que indica se ouve trocas naquela iteração
    bool swapped = true;

    // Enquanto não houver trocas em alguma iteração
    while(swapped){
        current = head;
        swapped = false;

        // Percorre a lista e compara elementos adjacentes
        while(current != last){
            // Se o valor atual for maior que o próximo, troca os valores
            if(current->iValue > current->ptrNext->iValue){
                swapValue(current->iValue, current->ptrNext->iValue);
                // Define 'swapped' como verdadeiro, indicando que houve uma troca
                swapped = true;
            }
            current = current->ptrNext;
        }
        // Atualiza 'last' para o nó anterior, pois os proximos ja estão ordenados
        last = last->ptrPrev;
    }
}

/*SELECTION*/

void selectionSort_Aux(Node* ptrAtual)
{
    // Condição de parada (final da lista)
    if (ptrAtual->ptrNext == NULL) return;

    // Criação de nó dinâmico
    Node* current = ptrAtual;

    // Percurso até o fim da lista
    while (current != NULL)
    {
        // Se algum nó for menor que o atual, atualizamos o atual
        if (current->iValue < ptrAtual->iValue) swapValue(ptrAtual->iValue,ptrAtual->iValue);
        current = current->ptrNext;
    }

    // Chamamos recursivamente a função
    selectionSort_Aux(ptrAtual->ptrNext);
}

void selectionSort(Node* head)
{
    // Se o cabeçalho for vazio, i.e., lista vazia
    if (head == NULL)
    {
        cout << "Empty list!" << endl;
    }
    // Caso o cabeçalho fornecido não seja para o primeiro nó da fila
    else if (head->ptrPrev != NULL)
    {
        cout << "Sorry, you're in the middle of list. Please try again with the head of the list." << endl;
    }
    else
    {
        selectionSort_Aux(head);
    }
}

void optimizedSelectionSort_Aux(Node* ptrAtual)
{
    // Condição de parada (final da lista)
    if (ptrAtual->ptrNext == NULL) return;

    // Criação de nó dinâmico
    Node* current = ptrAtual;
    // Criação de nó pivô
    Node* ptrPivot = ptrAtual;

    // Percurso até o fim da lista
    while (current != NULL)
    {
        // Se algum nó for menor que o pivô, atualizamos o pivô
        if (current->iValue < ptrPivot->iValue) ptrPivot = current;
        current = current->ptrNext;
    }

    // Se o pivô não for o nó atual, efetuamos a troca
    if (ptrPivot != ptrAtual) swapValue(ptrPivot->iValue,ptrAtual->iValue);

    // Chamamos recursivamente a função
    selectionSort_Aux(ptrAtual->ptrNext);
}

void optimizedSelectionSort(Node* head)
{
    // Se o cabeçalho for vazio, i.e., lista vazia
    if (head == NULL)
    {
        cout << "Empty list!" << endl;
    }
    // Caso o cabeçalho fornecido não seja para o primeiro nó da fila
    else if (head->ptrPrev != NULL)
    {
        cout << "Sorry, you're in the middle of list. Please try again with the head of the list." << endl;
    }
    else
    {
        optimizedSelectionSort_Aux(head);
    }
}