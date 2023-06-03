//�������� � ��������� �������� ���� ������.
//����������� ������ ��� ��������� ������ ������, 
//������ ������� �������� �������� ������������� ���� � ������ ������, 
//���������� ��� � ����� ��������(���� �������� ���������� �������� � ����).
//� ��������� ������ ���� ����������� ��������� ����������� : �������� ������, 
//���������� ����� ������, ����� ���������� �� ��������� �����, �������� 
//���������� � �������� ������, ����� ����������, ������� ��������������� 
//�������, ������������ ������ ��� ������ �� ���������.���������� ������� ������.
// 
//���������� ������� ������.

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// ��������� ���� ������
typedef struct Node {
    int key;
    char name[100];
    char passport[20];
    struct Node* left;
    struct Node* right;
} Node;

// �������� ������ ���� ������
Node* createNode(int key, const char* name, const char* passport) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy_s(newNode->name, sizeof(newNode->name), name);
    strcpy_s(newNode->passport, sizeof(newNode->passport), passport);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ������� ������ ���� � ������
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

// ����� ���� � �������� ������ � ������
Node* searchNode(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return searchNode(root->left, key);
    }

    return searchNode(root->right, key);
}

// ����� ������������ ���� � ������
Node* findMinNode(Node* node) {
    Node* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

// �������� ���� � �������� ������ �� ������
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

// ����� ���������� �� ����
void printNode(Node* node) {
    printf("����: %d, ���: %s, ����� ��������: %s\n", node->key, node->name, node->passport);
}

// ����� ������ � ������� ����������� ������ (��������� �����)
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printNode(root);
        inorderTraversal(root->right);
    }
}

// ���������� ������� ������
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

// ������������ ������, ������� �������
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
        printf("�������� ��������:\n");
        printf("1. ������� ������\n");
        printf("2. �������� ����� ������\n");
        printf("3. ����� ���������� �� �����\n");
        printf("4. �������� ���������� � �������� ������\n");
        printf("5. ����� ����������\n");
        printf("6. ��������� ������� ������\n");
        printf("7. �����\n");
        printf("������� ����� ���������� ��������: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            // �������� ������
            if (root != NULL) {
                freeTree(root);
            }
            root = NULL;
            printf("������ �������.\n");
            break;
        case 2:
            // ���������� ����� ������
            printf("������� ����: ");
            scanf_s("%d", &key);
            printf("������� ���: ");
            scanf_s(" %s", name, sizeof(name));
            printf("������� ����� ��������: ");
            scanf_s(" %s", passport, sizeof(passport));
            root = insertNode(root, key, name, passport);
            printf("������ ���������.\n");
            break;
        case 3:
            // ����� ���������� �� �����
            printf("������� ����: ");
            scanf_s("%d", &key);
            result = searchNode(root, key); // Assign the result
            if (result != NULL) {
                printf("��������� ����������:\n");
                printNode(result);
            }
            else {
                printf("������ � �������� ������ �� �������.\n");
            }
            break;
        case 4:
            // �������� ���������� � �������� ������
            printf("������� ����: ");
            scanf_s("%d", &key);
            root = deleteNode(root, key);
            printf("������ �������.\n");
            break;
        case 5:
            // ����� ����������
            printf("���������� � ������:\n");
            inorderTraversal(root);
            break;
        case 6:
            // ���������� ������� ������
            printf("������� ������: %d\n", getTreeDepth(root));
            break;
        case 7:
            // ����� �� ���������
            freeTree(root);
            printf("��������� ���������.\n");
            return 0;
        default:
            printf("�������� �����. ���������� �����.\n");
            break;
        }
        printf("\n");
    }
}
