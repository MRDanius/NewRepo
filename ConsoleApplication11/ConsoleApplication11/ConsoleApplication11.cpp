#include <iostream>
#include <queue> // Для очереди
using namespace std;

// Структура для узла дерева
struct Node {
    int val;      // Значение узла
    Node* left;   // Левый потомок
    Node* right;  // Правый потомок
};

// Структура для "верхушки дерева"
struct Tree {
    Node* root;  // Указатель на корень дерева
};

// Функция для добавления элемента в бинарное дерево поиска
void addToTree(Tree& tree, int value) {
    Node* newNode = new Node; // Создаём новый узел
    newNode->val = value;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (tree.root == nullptr) {
        // Если дерево пустое, новый узел становится корнем
        tree.root = newNode;
        return;
    }

    Node* tmp = tree.root; // Временная переменная для обхода дерева
    while (true) {
        if (value < tmp->val) {
            // Если значение меньше текущего узла, идём влево
            if (tmp->left == nullptr) {
                tmp->left = newNode; // Вставляем узел
                break;
            }
            else {
                tmp = tmp->left;
            }
        }
        else {
            // Если значение больше или равно, идём вправо
            if (tmp->right == nullptr) {
                tmp->right = newNode; // Вставляем узел
                break;
            }
            else {
                tmp = tmp->right;
            }
        }
    }
}

// Рекурсивная функция для очистки дерева
void del(Node* x) {
    if (x->left != nullptr) {
        del(x->left); // Очистка левого поддерева
    }
    if (x->right != nullptr) {
        del(x->right); // Очистка правого поддерева
    }
    delete x; // Удаление текущего узла
}

// Функция для вывода дерева по уровням
void printTreeByLevels(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }

    queue<Node*> q;  // Очередь для обхода в ширину
    q.push(root);

    int level = 0;
    bool isEmptyLevel = false; // Флаг для проверки пустоты уровня
    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());  // Явное приведение к int
        isEmptyLevel = true; // Начинаем с предположения, что уровень пустой

        cout << "Level " << level++ << ": ";
        // Обрабатываем все узлы текущего уровня
        for (int i = 0; i < levelSize; i++) {
            Node* current = q.front();
            q.pop();

            if (current != nullptr) {
                cout << current->val << " "; // Выводим значение текущего узла
                q.push(current->left);      // Добавляем левого потомка
                q.push(current->right);     // Добавляем правого потомка
                isEmptyLevel = false; // Уровень не пустой
            }
            else {
                cout << "-- "; // Если узел пустой, выводим черточки
            }
        }

        // Если уровень был пустым (все элементы в очереди были nullptr), завершить вывод
        if (isEmptyLevel) {
            break;
        }

        cout << endl; // Переход на новую строку после вывода уровня
    }
}

int main() {
    Tree tree = { nullptr }; // "Крышеватель" дерева

    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements:" << endl;
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        addToTree(tree, value);
    }

    cout << "Binary Search Tree (level-order):" << endl;
    printTreeByLevels(tree.root); // Выводим дерево по уровням

    // Очистка дерева
    if (tree.root != nullptr) {
        del(tree.root);
        tree.root = nullptr;
    }

    // Проверка, что дерево очищено
    if (tree.root == nullptr) {
        cout << "Tree cleared successfully!" << endl;
    }

    return 0;
}
