//Создание и обработка структур типа Дерево.
//Разработать проект для обработки дерева поиска, 
//каждый элемент которого содержит целочисленный ключ и строку текста, 
//содержащую ФИО и номер паспорта(ввод исходной информации записать в файл).
//В программе должны быть реализованы следующие возможности : создание дерева, 
//добавление новой записи, поиск информации по заданному ключу, удаление 
//информации с заданным ключом, вывод информации, решение индивидулььного 
//задания, освобождение памяти при выходе их программы.Определить глубину дерева.
// 
//Определить глубину дерева.

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Структура узла дерева
typedef struct Node {
    int key;
    char name[100];
    char passport[20];
    struct Node* left;
    struct Node* right;
} Node;

// Создание нового узла дерева
Node* createNode(int key, const char* name, const char* passport) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy_s(newNode->name, sizeof(newNode->name), name);
    strcpy_s(newNode->passport, sizeof(newNode->passport), passport);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Вставка нового узла в дерево
Node* insertNode(Node* root, int key, const char* name, const char* passport) {
    if (root == NULL) {
        return createNode(key, name, passport);
    }

    if (key < root->key) {
        root->left = insertNode(root->left, key, name, passport);
    }
    else if (key > root->key) {
        root->right = insertNode(root->right, key, name, passport);
    }

    return root;
}

// Поиск узла с заданным ключом в дереве
Node* searchNode(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return searchNode(root->left, key);
    }

    return searchNode(root->right, key);
}

// Поиск минимального узла в дереве
Node* findMinNode(Node* node) {
    Node* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Удаление узла с заданным ключом из дерева
Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMinNode(root->right);
        root->key = temp->key;
        strcpy_s(root->name, sizeof(root->name), temp->name);
        strcpy_s(root->passport, sizeof(root->passport), temp->passport);
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

// Вывод информации об узле
void printNode(Node* node) {
    printf("Ключ: %d, ФИО: %s, Номер паспорта: %s\n", node->key, node->name, node->passport);
}

// Обход дерева в порядке возрастания ключей (инфиксный обход)
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printNode(root);
        inorderTraversal(root->right);
    }
}

// Вычисление глубины дерева
int getTreeDepth(Node* root) {
    if (root == NULL) {
        return 0;
    }
    else {
        int leftDepth = getTreeDepth(root->left);
        int rightDepth = getTreeDepth(root->right);

        if (leftDepth > rightDepth) {
            return leftDepth + 1;
        }
        else {
            return rightDepth + 1;
        }
    }
}

// Освобождение памяти, занятой деревом
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
   
    Node* root = NULL;
    int choice, key;
    char name[100], passport[20];
    Node* result = NULL;  // Declare and initialize "result" 

    while (1) {
        printf("Выберите действие:\n");
        printf("1. Создать дерево\n");
        printf("2. Добавить новую запись\n");
        printf("3. Поиск информации по ключу\n");
        printf("4. Удаление информации с заданным ключом\n");
        printf("5. Вывод информации\n");
        printf("6. Вычислить глубину дерева\n");
        printf("7. Выход\n");
        printf("Введите номер выбранного действия: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            // Создание дерева
            if (root != NULL) {
                freeTree(root);
            }
            root = NULL;
            printf("Дерево создано.\n");
            break;
        case 2:
            // Добавление новой записи
            printf("Введите ключ: ");
            scanf_s("%d", &key);
            printf("Введите ФИО: ");
            scanf_s(" %s", name, sizeof(name));
            printf("Введите номер паспорта: ");
            scanf_s(" %s", passport, sizeof(passport));
            root = insertNode(root, key, name, passport);
            printf("Запись добавлена.\n");
            break;
        case 3:
            // Поиск информации по ключу
            printf("Введите ключ: ");
            scanf_s("%d", &key);
            result = searchNode(root, key); // Assign the result
            if (result != NULL) {
                printf("Найденная информация:\n");
                printNode(result);
            }
            else {
                printf("Запись с заданным ключом не найдена.\n");
            }
            break;
        case 4:
            // Удаление информации с заданным ключом
            printf("Введите ключ: ");
            scanf_s("%d", &key);
            root = deleteNode(root, key);
            printf("Запись удалена.\n");
            break;
        case 5:
            // Вывод информации
            printf("Информация в дереве:\n");
            inorderTraversal(root);
            break;
        case 6:
            // Вычисление глубины дерева
            printf("Глубина дерева: %d\n", getTreeDepth(root));
            break;
        case 7:
            // Выход из программы
            freeTree(root);
            printf("Программа завершена.\n");
            return 0;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
            break;
        }
        printf("\n");
    }
}
