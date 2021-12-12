#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class BST
{
    struct node
    {
        int data;
        node* left;
        node* right;
        int height;
    };

    node* root;

    void makeEmpty(node* t)
    {
        if(t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    node* insert(int x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
        {
            t->left = insert(x, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(x < t->left->data)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x > t->data)
        {
            t->right = insert(x, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(x > t->right->data)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = std::max(height(t->left), height(t->right))+1;
        return t;
    }

    node* singleRightRotate(node* &t)
    {
        node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = std::max(height(t->left), height(t->right))+1;
        u->height = std::max(height(u->left), t->height)+1;
        return u;
    }

    node* singleLeftRotate(node* &t)
    {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = std::max(height(t->left), height(t->right))+1;
        u->height = std::max(height(t->right), t->height)+1 ;
        return u;
    }

    node* doubleLeftRotate(node* &t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node* doubleRightRotate(node* &t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t)
    {
        node* temp;

        // Element not found
        if(t == NULL)
            return NULL;

        // Searching for element
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        // With one or zero child
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = std::max(height(t->left), height(t->right))+1;

        // If node is unbalanced
        // If left node is deleted, right case
        if(height(t->left) - height(t->right) == 2)
        {
            // right right case
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right node is deleted, left case
        else if(height(t->right) - height(t->left) == 2)
        {
            // left left case
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(node* t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void LKP(node* t)
    {
        if(t == NULL)
            return;
        LKP(t->left);
        std::cout << t->data << " ";
        LKP(t->right);
    }

    void LPK(node* t)
    {
        if (t == NULL)
            return;
        LPK(t->left);
        LPK(t->right);
        std::cout << t->data << " ";
    }

    void KLP(node* t)
    {
        if (t == NULL)
            return;
        std::cout << t->data << " ";
        KLP(t->left);
        KLP(t->right);
    }

    void BFS(std::vector<node*> stack)
    {
        while (!stack.empty())
        {
            node* tmp = stack[0];
            stack.erase(stack.begin());
            if (tmp == NULL)
                continue;
            std::cout << tmp->data << " ";
            if (tmp->left)
                stack.push_back(tmp->left);
            if (tmp->right)
                stack.push_back(tmp->right);
        }
    }

public:
    BST()
    {
        root = NULL;
    }

    void insert(int x)
    {
        root = insert(x, root);
    }

    void remove(int x)
    {
        root = remove(x, root);
    }

    void display()
    {
        std::cout << "> LKP:\n";
        LKP(root);
        std::cout << "\n";

        std::cout << "> LPK:\n";
        LPK(root);
        std::cout << "\n";

        std::cout << "> KLP:\n";
        KLP(root);
        std::cout << "\n";

        std::cout << "> BFS:\n";
        std::vector<node*> stack;
        stack.push_back(root);
        BFS(stack);
        std::cout << "\n";
    }
};

BST read_from_stdin() {
    std::cout << "> Please enter arbitrary numbers:\n";
    std::vector<int> array;

    for(std::string line; getline(std::cin, line);) {

        if(line.empty()) break;

        std::istringstream is(line);
        int n;
        while(is >> n) {
            array.push_back(n);
        }

        if(not is.eof()) {
            is.clear();
            getline(is, line);
            std::cout << "could not extract an int from \"" << line << "\".\n";
            break;
        }

    }
    BST root;
    for(auto i: array) {
        root.insert(i);
    }
    std::cout << '\n';

    return root;
}

int main()
{
    BST t = read_from_stdin();
    t.display();
}