#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#define LANGUAGE 1251
#define INITADD 5

using namespace std;

struct Node
{
    int number;
    struct Node* next;
    struct Node* previous;
};

void printList(Node* start, int& length)
{
    cout << "Список: " << endl;
    Node* add = start->next;
    for (int i = 0; i < length; i++)
    {
        cout << add->number << " ";
        add = add->next;
    }
    cout << endl;
}

void addLast(Node* end, int& length, int toAdd)
{
    Node* adder = new Node;
    adder->number = toAdd;
    end->previous->next = adder;
    adder->next = end;
    adder->previous = end->previous;
    end->previous = adder;
    length++;

}

void addFirst(Node* start, int& length, int toAdd)
{
    Node* adder = new Node;
    adder->number = toAdd;
    adder->next = start->next;
    start->next->previous = adder;
    start->next = adder;
    adder->previous = start;
    length++;

}

void deleteLast(Node* end, int& length) {
    Node* add = end->previous;
    end->previous = add->previous;
    add->previous->next = end;
    delete add;
    length--;
}

void deleteFirst(Node* start, int& length) {
    Node* add = start->next;
    start->next = add->next;
    add->next->previous = start;
    delete add;
    length--;
}

void addElem(Node* start, Node* end, int& length, int num) {
    if (num == 0) {
        Node* addNew = new Node;
        cout << "Введите значение нового элемента: ";
        int elem;
        cin >> elem;
        addFirst(start, length, elem);
    }
    else if ((num < length) and (num >= 0)) {
        cout << "Введите значение нового элемента: ";
        int elem;
        cin >> elem;
        if (num < ceil(length / 2)) {
            Node* add = start->next;
            for (int i = 1; i < num; i++) {
                add = add->next;
            }
            Node* addNew = new Node;
            addNew->number = elem;
            add->next->previous = addNew;
            addNew->next = add->next;
            add->next = addNew;
            addNew->previous = add;
        }
        else {
            Node* add = end->previous;
            for (int i = 1; i < length - num; i++) {
                add = add->previous;
            }
            Node* addNew = new Node;
            addNew->number = elem;
            add->previous->next = addNew;
            addNew->previous = add->previous;
            addNew->next = add;
            add->previous = addNew;
        }

        length++;

        printList(start, length);
    }
    else { cout << "Ошибка ввода, такого индекса нет" << endl; }
}

Node* findElem(Node* start, Node* end, int& length, int num) {

    if ((num < length) and (num >= 0)) {


        if (num < ceil(length / 2)) {
            Node* add = start->next;
            for (int i = 0; i < num; i++) {
                add = add->next;
            }
            return add;
        }
        else {
            Node* add = end->previous;
            for (int i = 1; i < length - num; i++) {
                add = add->previous;
            }
            return add;
        }
    }
    else { cout << "Ошибка ввода, такого индекса нет" << endl; }

}

void delElem(Node* start, Node* end, int& length, int num) {

    if ((num < length) and (num >= 0)) {

        Node* del = findElem(start, end, length, num);
        del->next->previous = del->previous;
        del->previous->next = del->next;
        length--;

    }
    else { cout << "Ошибка ввода, такого индекса нет" << endl; }
}

void delArr(Node* start, int& length) {
    Node* del = start->next;
    while (length != 0) {
        deleteFirst(start, length);

    }
    cout << "Список удален" << endl;
}

void newName(Node* start, Node* end, int& length, int num) {

    if ((num < length) and (num >= 0)) {
        int name;
        cout << "Введите новое значение элемента: ";
        cin >> name;

        Node* add = findElem(start, end, length, num);
        add->number = name;

        printList(start, length);
    }
    else { cout << "Ошибка ввода, такого индекса нет" << endl; }

}

void reverse(Node*& start, Node*& end, int& length) {
    Node* add = start->next;
    Node* temp = new Node;
    for (int i = 1; i <= length; i++) {
        temp->next = add->next;
        temp->previous = add->previous;
        add->next = temp->previous;
        add->previous = temp->next;
        add = temp->next;
    }

    temp = start;
    start = end;
    end = temp;
    start->next = start->previous;
    start->previous = NULL;
    end->previous = end->next;
    end->next = NULL;


}

void insertList(Node* start, Node* end, int& length, bool& insert, Node* startBegin, Node* endBegin, int& lengthBegin, int num) {
    if ((num < length) and (num >= 0)) {
        cout << "Значение элемента по индексу " << num << ": ";

        Node* add = findElem(start, end, length, num);
        add->next->previous = endBegin->previous;
        endBegin->previous->next = add->next;
        startBegin->next->previous = add;
        add->next = startBegin->next;

        length += lengthBegin;
        insert = true;
        printList(start, length);
    }
    else { cout << "Ошибка ввода, такого индекса нет" << endl; }
}

void insertListBegin(Node* start, int& length, bool& insert, Node* startBegin, Node* endBegin, int& lengthBegin) {

    endBegin->previous->next = start->next;
    start->next->previous = endBegin->previous;
    start->next = startBegin->next;
    startBegin->next->previous = start;
    length += lengthBegin;
    insert = true;



}

void insertListEnd(Node* end, int& length, bool& insert, Node* startBegin, Node* endBegin, int& lengthBegin) {

    startBegin->next->previous = end->previous;
    end->previous->next = startBegin->next;
    endBegin->previous->next = end;
    end->previous = endBegin->previous;
    length += lengthBegin;
    insert = true;
}

void enterEnd(Node* start, Node* end, Node* startBegin, Node* endBegin, int& length) {
    Node* add = end;
    int index = 1;
    while (!(add->previous == endBegin->previous)) {
        index += 1;
        add = add->previous;
    }
    index = length - index;
    cout << "Последнее вхождение списка в список (индекс): " << index << endl;
}

void enterFirst(Node* start, Node* end, Node* startBegin, Node* endBegin, int& length) {
    Node* add = start;
    int index = 0;
    while (!(add->next == startBegin->next)) {
        index += 1;
        add = add->next;
    }
    cout << "Первое вхождение списка в список (индекс): " << index << endl;
}

void swap(Node* start, Node* end, int& length, int num1, int num2) {
    int temp;
    Node* add1 = findElem(start, end, length, num1);
    Node* add2 = findElem(start, end, length, num2);
    temp = add1->number;
    add1->number = add2->number;
    add2->number = temp;
}

void listInlist(bool check) {
    if (check)cout << "Список был вставлен в список" << endl;
    else cout << "Вставки списка в список не было" << endl;
}

void listEmpty(int length) {
    if (length == 0) {
        cout << "Список пустой" << endl;
    }
    else cout << "Список не пустой" << endl;
}


int main()
{
    SetConsoleCP(LANGUAGE);
    SetConsoleOutputCP(LANGUAGE);

    int lengthMain = 0;
    int lengthBegin = 0;
    Node* headMain = new Node;
    Node* headBegin = new Node;
    Node* tailMain = new Node;
    Node* tailBegin = new Node;
    Node* add = NULL;
    int firstElem;
    int countAdded = 0;
    int choice;
    int choiceBegin;
    bool insert = false;

    cout << "Введите список, который будет служить вставным" << endl << endl;
    if (lengthBegin == 0)
    {
        cout << "Введите первый элемент для добавления в список: ";
        cin >> firstElem;
        add = new Node;
        add->number = firstElem;
        add->next = tailBegin;
        add->previous = headBegin;
        headBegin->next = add;
        tailBegin->previous = add;
        lengthBegin++;
        printList(headBegin, lengthBegin);
    }
    do {
        cout << "-----------------------------------------" << endl;
        cout << "Выберите действие: " << endl;
        cout << "1. Добавить элемент в конец списка" << endl;
        cout << "0. Если ввод закончен" << endl;
        cout << "-----------------------------------------" << endl;
        cin >> choiceBegin;
        switch (choiceBegin)
        {
        case 1:
            int lastElem;
            cout << "Введите элемент для добавления: ";
            cin >> lastElem;
            addLast(tailBegin, lengthBegin, lastElem);
            printList(headBegin, lengthBegin);
            break;
        }
    } while (choiceBegin != 0);

    cout << endl << "Работа с основным списком" << endl << endl;
    do
    {
        if (lengthMain == 0)
        {
            cout << "Введите первый элемент для добавления в список: ";
            cin >> firstElem;
            add = new Node;
            add->number = firstElem;
            add->next = tailMain;
            add->previous = headMain;
            headMain->next = add;
            tailMain->previous = add;
            lengthMain++;
            printList(headMain, lengthMain);
        }

        cout << endl << "-----------------------------------------" << endl;
        cout << "Выберите действие: " << endl;
        cout << "1. Добавить элемент в конец списка" << endl;
        cout << "2. Добавить элемент в начало списка" << endl;
        cout << "3. Удалить последний элемент списка" << endl;
        cout << "4. Удалить первый элемент списка" << endl;
        cout << "5. Добавить элемент по индексу" << endl;
        cout << "6. Получить элемент по индексу" << endl;
        cout << "7. Удалить элемент по индексу" << endl;
        cout << "8. Получить размер списка" << endl;
        cout << "9. Удалить все элементы списка" << endl;
        cout << "10. Заменить элемент по индексу" << endl;
        cout << "11. Проверка на пустоту списка" << endl;
        cout << "12. Поменять порядок элементов на обратный" << endl;
        cout << "13. Вставить список в список по индексу" << endl;
        cout << "14. Вставить другой список в конец" << endl;
        cout << "15. Вставить другой список в начало" << endl;
        cout << "16. Проверить на содержание одного списка в другом" << endl;
        if (insert) {
            cout << "17. Поиск первого вхождения списка в список" << endl;
            cout << "18. Поиск последнего вхождения списка в список" << endl;
        }
        cout << "19. Обмен двух элементов списка по индексам" << endl;
        cout << endl << "0. Завершить работу со списком." << endl;
        cout << "-----------------------------------------" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            int lastElem;
            cout << "Введите элемент для добавления: ";
            cin >> lastElem;
            addLast(tailMain, lengthMain, lastElem);
            printList(headMain, lengthMain);
            break;
        case 2:
            int firstElem;
            cout << "Введите элемент для добавления: ";
            cin >> firstElem;
            addFirst(headMain, lengthMain, firstElem);
            printList(headMain, lengthMain);
            break;
        case 3:
            deleteLast(tailMain, lengthMain);
            printList(headMain, lengthMain);
            break;

        case 4:
            deleteFirst(headMain, lengthMain);

            printList(headMain, lengthMain);
            break;

        case 5:
            cout << "Введите индекс элемента для добавления: ";
            int indexAdd;
            cin >> indexAdd;
            addElem(headMain, tailMain, lengthMain, indexAdd);
            break;

        case 6:
            cout << "Введите индекс элемента: ";
            int indexFind;
            cin >> indexFind;
            cout << "Значение элемента по индексу " << indexFind << ": ";
            add = findElem(headMain, tailMain, lengthMain, indexFind);

            cout << add->number << endl;
            break;

        case 7:
            cout << "Введите индекс элемента для удаления: ";
            int indexDel;
            cin >> indexDel;
            delElem(headMain, tailMain, lengthMain, indexDel);
            printList(headMain, lengthMain);
            break;

        case 8:
            cout << "Длина списка: " << lengthMain << endl;
            break;

        case 9:
            delArr(headMain, lengthMain);
            break;

        case 10:
            cout << "Введите индекс элемента: ";
            cin >> indexFind;
            newName(headMain, tailMain, lengthMain, indexFind);
            break;

        case 11:
            listEmpty(lengthMain);
            break;

        case 12:
            reverse(headMain, tailMain, lengthMain);
            printList(headMain, lengthMain);
            break;

        case 13:
            cout << "Введите индекс элемента, после которого вставить список: ";
            int indexInsert;
            cin >> indexInsert;
            insertList(headMain, tailMain, lengthMain, insert, headBegin, tailBegin, lengthBegin, indexInsert);
            break;

        case 14:
            insertListEnd(tailMain, lengthMain, insert, headBegin, tailBegin, lengthBegin);
            printList(headMain, lengthMain);
            break;

        case 15:
            insertListBegin(headMain, lengthMain, insert, headBegin, tailBegin, lengthBegin);
            printList(headMain, lengthMain);
            break;

        case 16:
            listInlist(insert);
            break;

        case 17:
            if (insert) {
                enterFirst(headMain, tailMain, headBegin, tailBegin, lengthMain);
            }
            break;

        case 18:
            if (insert) {
                enterEnd(headMain, tailMain, headBegin, tailBegin, lengthMain);
            }
            break;

        case 19:
            cout << "Введите индексы элементов, которые нужно поменять местами: ";
            int indexFirst;
            int indexSecond;
            cin >> indexFirst;
            cin >> indexSecond;
            swap(headMain, tailMain, lengthMain, indexFirst, indexSecond);
            printList(headMain, lengthMain);
            break;
        }
    } while (choice != 0);

    return 0;
    _getch();
}
