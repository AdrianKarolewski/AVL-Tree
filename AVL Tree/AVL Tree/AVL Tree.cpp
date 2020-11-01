#include <iostream>
#include <conio.h>
#include <time.h>
#include <iomanip>
#include <windows.h>

using namespace std;
class Node
{
public:
    int Key;
    int Height;

    Node* Parent = nullptr;
    Node* LeftCh = nullptr;
    Node* RightCh = nullptr;

    Node(int val)
    {
        Key = val;
    }
    ~Node()
    {
        if (Parent != nullptr) { delete Parent; }
        if (LeftCh != nullptr) { delete LeftCh; }
        if (RightCh != nullptr) { delete RightCh; }
    }
};
class Tree
{
private:
    Node* root = nullptr;
    int m_count = 0;
    int m_hight = 0;
public:
    Tree(int val)
    {
        root = new Node(val);
        m_count++;
    }
    ~Tree()
    {
        if (root != nullptr) { delete root; }
    }
    int GetHeight(Node* node)
    {
        return node == nullptr ?
            -1 :
            node->Height;
    }
    Node* RotateLeft(Node* node)
    {
        Node* balancedNode = node->RightCh;
        balancedNode->Parent = node->Parent;
        if (node == root)
        {
            root = balancedNode;
        }
        node->Parent = balancedNode;
        node->RightCh = balancedNode->LeftCh;
        balancedNode->LeftCh = node;
        if (balancedNode->LeftCh != nullptr)
        {
            balancedNode->LeftCh->Parent = node;

        }
        node->Height = max(GetHeight(node->LeftCh), GetHeight(node->RightCh)) + 1;
        balancedNode->Height = max(GetHeight(balancedNode->LeftCh), GetHeight(balancedNode->RightCh)) + 1;

        return balancedNode;
    }
    Node* RotateRight(Node* node)
    {
        Node* balancedNode = node->LeftCh;

        balancedNode->Parent = node->Parent;
        if (node == root)
        {
            root = balancedNode;
        }
        node->Parent = balancedNode;
        node->LeftCh = balancedNode->RightCh;

        if (balancedNode->RightCh != nullptr)
        {
            balancedNode->RightCh->Parent = node;
        }
        balancedNode->RightCh = node;

        node->Height = max(GetHeight(node->LeftCh), GetHeight(node->RightCh)) + 1;
        balancedNode->Height = max(GetHeight(balancedNode->LeftCh), GetHeight(balancedNode->RightCh)) + 1;

        return balancedNode;
    }
    Node* Insert(Node* rnode, int val)
    {
        if (rnode->Key < val)
        {
            if (rnode->RightCh == nullptr)
            {
                Node* node = new Node(val);
                node->Parent = rnode;
                rnode->RightCh = node;
                node->LeftCh = nullptr;
                node->RightCh = nullptr;
                node->Height = 0;
                m_count++;

            }
            else
            {
                rnode->RightCh = Insert(rnode->RightCh, val);
                rnode->RightCh->Parent = rnode;
            }
        }
        if (rnode->Key > val)
        {
            if (rnode->LeftCh == nullptr)
            {
                Node* node = new Node(val);
                node->Parent = rnode;
                rnode->LeftCh = node;
                node->LeftCh = nullptr;
                node->RightCh = nullptr;
                node->Height = 0;
                m_count++;

            }
            else
            {
                rnode->LeftCh = Insert(rnode->LeftCh, val);
                rnode->LeftCh->Parent = rnode;
            }
        }
        int balance = GetHeight(rnode->LeftCh) - GetHeight(rnode->RightCh);
        if (balance == 2)
        {
            int balance2 = GetHeight(rnode->LeftCh->LeftCh) - GetHeight(rnode->LeftCh->RightCh);
            if (balance2 == 1)
            {
                rnode = RotateRight(rnode);
            }
            else
            {
                rnode->LeftCh = RotateLeft(rnode->LeftCh);
                rnode = RotateRight(rnode);
            }
        }
        else if (balance == -2)
        {
            int balance2 = GetHeight(rnode->RightCh->LeftCh) - GetHeight(rnode->RightCh->RightCh);
            if (balance2 == -1)
            {
                rnode = RotateLeft(rnode);
            }
            else
            {
                rnode->RightCh = RotateRight(rnode->RightCh);
                rnode = RotateLeft(rnode);
            }
        }
        rnode->Height = max(GetHeight(rnode->LeftCh), GetHeight(rnode->RightCh)) + 1;
        return rnode;
    }
    void Insert(int val)
    {
        Insert(root, val);
    }

    void PrintInOrder(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        PrintInOrder(node->LeftCh);
        cout << node->Key << " ";
        PrintInOrder(node->RightCh);

    }
    void PrintInOrder()
    {
        PrintInOrder(root);
    }
    void PrintPreOrder(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        cout << node->Key << " ";
        PrintInOrder(node->LeftCh);

        PrintInOrder(node->RightCh);

    }
    void PrintPreOrder()
    {
        PrintPreOrder(root);
    }
    void PrintPostOrder(Node* node)
    {
        if (node == nullptr)
        {
            return;

        }
        PrintInOrder(node->LeftCh);

        PrintInOrder(node->RightCh);
        cout << node->Key << " ";

    }
    void PrintPostOrder()
    {
        PrintPostOrder(root);
    }

    int FindInTree(Node* node, int val, int index)
    {
        while (node != nullptr)
        {
            if (val < node->Key)
            {
                index = index * 2;
                node = node->LeftCh;
            }
            else if (val > node->Key)
            {
                index = index * 2 + 1;
                node = node->RightCh;
            }
            else if (val == node->Key)
            {
                return index;
            }
        }


        return 0;
    }
    int FindInTree(int val)
    {
        return FindInTree(root, val, 1);
    }
    Node* FindInTree_Node(Node* node, int val)
    {
        while (node != nullptr)
        {
            if (val < node->Key)
            {
                node = node->LeftCh;
            }
            else if (val > node->Key)
            {

                node = node->RightCh;
            }
            else if (val == node->Key)
            {
                return node;
            }
        }


        return 0;
    }
    int FindMin_in_Node(Node* node)
    {
        if (node->LeftCh != nullptr)
        {
            FindMin_in_Node(node->LeftCh);
        }
        else if (node != nullptr)
        {
            return node->Key;
        }
        else
        {
            return -1;
        }
    }
    int FindMax_in_Node(Node* node)
    {
        if (node->RightCh != nullptr)
        {
            FindMin_in_Node(node->RightCh);
        }
        else if (node != nullptr)
        {
            return node->Key;
        }
        else
        {
            return -1;
        }
    }
    int FindMin_in_Node()
    {
        return FindMin_in_Node(root);
    }
    int FindMax_in_Node()
    {
        return FindMax_in_Node(root);
    }
    int Successor(Node* node)
    {
        if (node->RightCh != nullptr)
        {
            return FindMin_in_Node(node->RightCh);
        }
        else
        {
            Node* parentnode = node->Parent;
            Node* currentnode = node;
            while ((parentnode != nullptr && currentnode == parentnode->RightCh))
            {
                currentnode = parentnode;
                parentnode = currentnode->Parent;
            }
            return parentnode == nullptr ?
                0 :
                parentnode->Key;
        }
        return -1;

    }
    int Successor(int val)
    {
        if (FindInTree(root, val, 1))
        {
            return Successor(FindInTree_Node(root, val));
        }
        else
        {
            return 0;
        }

    }
    int Predecessor(Node* node)
    {
        if (node->LeftCh != nullptr)
        {
            return FindMax_in_Node(node->LeftCh);
        }
        else
        {
            Node* parentnode = node->Parent;
            Node* currentnode = node;
            while ((parentnode != nullptr && currentnode == parentnode->LeftCh))
            {
                currentnode = parentnode;
                parentnode = currentnode->Parent;
            }
            return parentnode == nullptr ?
                0 :
                parentnode->Key;
        }
        return -1;

    }
    int Predecessor(int val)
    {
        if (FindInTree(root, val, 1))
        {
            return Predecessor(FindInTree_Node(root, val));
        }
        else
        {
            return 0;
        }

    }
    int Remove(int val)
    {
        Remove(root, val);
        return 1;
    }

    Node* Remove(Node* node, int val)
    {
        if (m_count == 1)
        {
            cout << "Usuwajac zniszczysz drzewo !!!" << endl;
            cout << endl << "Aby kontynuowac wcisnij dowolny klawisz ";
            getchar();
            getchar();
            return nullptr;
        }
        if (node == nullptr)
        {
            cout << "Nie ma takiego klucza w drzewie, wcisnij klawisz by kontynuowac" << endl;
            getchar();
            getchar();
            return nullptr;
        }
        if (node->Key == val)
        {
            if (node->LeftCh == nullptr && node->RightCh == nullptr)
            {
                if (node == root)
                {
                    root = nullptr;
                }
                node = nullptr;

            }
            else if (node->LeftCh == nullptr && node->RightCh != nullptr)
            {
                if (node == root)
                {
                    root = node->RightCh;
                }
                node->RightCh->Parent = node->Parent;
                node = node->RightCh;
            }
            else if (node->LeftCh != nullptr && node->RightCh == nullptr)
            {

                node->LeftCh->Parent = node->Parent;
                node = node->LeftCh;
                if (node == root)
                {
                    root = node->LeftCh;
                }
            }
            else
            {
                int successorKey = Successor(val);
                node->Key = successorKey;
                node->RightCh = Remove(node->RightCh, successorKey);
            }
        }
        else if (node->Key < val)
        {
            node->RightCh = Remove(node->RightCh, val);
        }
        else
        {
            node->LeftCh = Remove(node->LeftCh, val);
        }
        if (node != nullptr)
        {
            int balance = GetHeight(node->LeftCh) - GetHeight(node->RightCh);
            if (balance == 2)
            {
                int balance2 = GetHeight(node->LeftCh->LeftCh) - GetHeight(node->LeftCh->RightCh);
                if (balance2 == 1)
                {
                    node = RotateRight(node);
                }
                else
                {
                    node->LeftCh = RotateLeft(node->LeftCh);
                    node = RotateRight(node);
                }
            }
            else if (balance == -2)
            {
                int balance2 = GetHeight(node->RightCh->LeftCh) - GetHeight(node->RightCh->RightCh);
                if (balance2 == -1)
                {
                    node = RotateLeft(node);
                }
                else
                {
                    node->RightCh = RotateRight(node->RightCh);
                    node = RotateLeft(node);
                }
            }
        }
        node->Height = max(GetHeight(node->LeftCh), GetHeight(node->RightCh)) + 1;
        return node;
    }

};
int main()
{
    long int Number, index;
    int successor, predecessor;
    short choice;
    cout << "Aby zaczac zabawe dodaj korzen do drzewa: ";
    cin >> Number;
    Tree tree1(Number);
    while (1)
    {
        cout << "Co chcesz zrobic: " << endl;
        cout << "1. Wstawic liczbe do drzewa(zakladamy unikalnosc kluczy drzewa) " << endl;
        cout << "2. Wypisac drzewo w porzadku inorder " << endl;
        cout << "3. Wypisac drzewo w porzadku preorder " << endl;
        cout << "4. Wypisac drzewo w porzadku postorder " << endl;
        cout << "5. Znajdz element w drzewie " << endl;
        cout << "6. Znajdz nastepnik elementu " << endl;
        cout << "7. Znajdz poprzednik elementu " << endl;
        cout << "8. Znajdz najmniejsz liczbe " << endl;
        cout << "9. Znajdz najwieksz liczbe " << endl;
        cout << "10. Aby usunac wybrana wartosc " << endl;
        cout << "11. Aby zakonczyc " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Jaka liczbe chcesz dodac: ";             cin >> Number;
            tree1.Insert(Number);
            break;
        case 2:
            cout << "W porzadku inorder: " << endl;
            tree1.PrintInOrder();
            cout << endl << "Aby kontynuowac wcisnij dowolny klawisz ";
            getchar();
            getchar();
            break;
        case 3:
            cout << "W porzadku preorder: " << endl;
            tree1.PrintPreOrder();
            cout << endl << "Aby kontynuowac wcisnij dowolny klawisz ";
            getchar();
            getchar();
            break;
        case 4:
            cout << "W porzadku postorder: " << endl;
            tree1.PrintPostOrder();
            cout << endl << "Aby kontynuowac wcisnij dowolny klawisz ";
            getchar();
            getchar();
            break;

        case 5:
            cout << "Jaki element chcesz znalesc? :";
            cin >> Number;
            index = tree1.FindInTree(Number);
            if (index)
            {
                cout << "Element znajduje sie na indexie : " << index << endl;
            }
            else
            {
                cout << "Nie ma takiego elementu w drzewie" << endl;
            }
            cout << endl << "Aby kontynuowac wcisnij dowolny klawisz ";
            getchar();
            getchar();
            break;
        case 6:
        {
            cout << "Dla jakiego elementu nastepnik chcesz znalesc : ";
            cin >> Number;
            int successor = tree1.Successor(Number);
            if (successor)
            {
                cout << "Nastepnikiem dla " << Number << " jest " << successor;
            }
            else
            {
                cout << Number << " nie posiada nastepnika, lub nie ma go w drzewie";
            }
            cout << endl << "Aby kontynuowac wcisnij dowolny klawisz";
            getchar();
            getchar();
        }
        break;
        case 7:
        {
            cout << "Dla jakiego elementu poprzednik chcesz znalesc : ";
            cin >> Number;
            int predecessor = tree1.Predecessor(Number);
            if (predecessor)
            {
                cout << "Poprzednikiem dla " << Number << " jest " << predecessor;
            }
            else
            {
                cout << Number << " nie posiada poprzednika, lub nie ma go w drzewie";
            }
            cout << endl << "Aby kontynuowac wcisnij dowolny klawisz ";
            getchar();
            getchar();
        }
        break;
        case 8:
        {
            cout << "Oto najmniejszy element: " << tree1.FindMin_in_Node();
            cout << endl << "Aby kontynuowac wcisnij dowolny klawisz ";
            getchar();
            getchar();
            break;
        }
        case 9:
            cout << "Oto najwiekszy element: " << tree1.FindMax_in_Node();
            cout << endl << "Aby kontynuowac wcisnij dowolny klawisz";
            getchar();
            getchar();
            break;
        case 10:
            cout << "Jaki element chcesz usunac : ";
            cin >> Number;
            tree1.Remove(Number);
            break;
        case 11:
            return 0;
        default:
            cout << "Niepoprawny wybor";
            break;

        }
        system("cls");
    }
    return 0;
}
