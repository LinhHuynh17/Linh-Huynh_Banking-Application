/*Linh Huynh
CSS 342
Instructor:Professor Dimpsey
Program 5*/
#ifndef BSTREE_H_
#define BSTREE_H_
#include "account.h"
class BSTree {
public:
    BSTree();
    BSTree(const BSTree& tree);
    ~BSTree();
    bool Insert(Account* account);
    // retrieve object, first parameter is the ID of the account
    // second parameter holds pointer to found object, NULL if not found
    bool Retrieve(const int& account_id, Account*& account) const;
    // Delete object, first parameter is the ID of the account
    // second parameter holds pointer to found object, NULL if not found
    bool Delete(const int& account_id, Account*& account);
    // BSTree& operator=(const BSTree& tree);
    // displays the contents of a tree to cout; you could also overload operator << 
    void Display() const;
    // int Size() const;
    // friend ostream operator<< (ostream&os, const BSTree& tree);
    void PrintSt() {
        cout << root_->p_acct->GetId() << endl;
        cout << root_->right->p_acct->GetId() << endl;
    }

private:
    struct Node
    {
        Account* p_acct;
        Node* right;
        Node* left;
        Node(Account* account) {
            p_acct = account;
            right = nullptr;
            left = nullptr;
        }
    };
    Node* root_;
    Node* retrieve(Node* root, const int& account_id) const {
        if (root == nullptr) {
            return nullptr;
        }
        else {
            if (account_id == root->p_acct->GetId()) {
                return root;
            }
            else {
                if (account_id < root->p_acct->GetId()) {
                    return retrieve(root->left, account_id);
                }
                else {
                    return retrieve(root->right, account_id);
                }
            }
        }
    }
    void PrintTree(Node* root) const {
        if (root == nullptr) {
            return;
        }
        else {
            PrintTree(root->left);
            root->p_acct->DisplayFunds();
            cout << endl;
            PrintTree(root->right);
        }
    }

    void PrintTree(Node* root, ostream& os) const {
        if (root == nullptr) {
            return;
        }
        else {
            PrintTree(root->left);
            root->p_acct->DisplayFunds();
            os << endl;
            PrintTree(root->right);
        }
    }
    void Cleantree(Node* root) {
        if (root->left != nullptr)
            Cleantree(root->left);
        if (root->right != nullptr)
            Cleantree(root->right);
        delete root->p_acct;
        delete root;
    }

    Node* CopyTree(Node* root) {
        if (root != nullptr) {
            Node* new_root = new Node(root->p_acct);
            new_root->left = CopyTree(root->left);
            new_root->right = CopyTree(root->right);
            return new_root;
        }
        else return nullptr;
    }

    //ancestor is the parent of the node to be deleted
    Node* MinValueNode(Node* node)
    {
        Node* current = node;

        /* loop down to find the leftmost leaf */
        while (current && current->left != NULL)
            current = current->left;

        return current;
    }

    Node* DeleteNode(Node* root, const int& account_id) {
        if (root == nullptr) {
            return root;
        }

        if (account_id < root->p_acct->GetId()) { //key < data of current node -> move to left and delete
            root->left = DeleteNode(root->left, account_id);
        }
        else {
            if (account_id > root->p_acct->GetId()) { //key > data of current node -> move to right and delete
                root->right = DeleteNode(root->right, account_id);
            }
            else {
                if (root->left == nullptr) { //deleted node has only right child
                    Node* temp = root->right;
                    delete root;
                    return temp;
                }
                else {
                    if (root->right == nullptr) { //deleted node has only right child
                        Node* temp = root->left;
                        delete root;
                        return temp;
                    }
                }
                //deleted Node has 2 children (has sub tree)
                Node* temp = MinValueNode(root->right);
                root->p_acct->SetId(temp->p_acct->GetId());
                root->right = DeleteNode(root->right, temp->p_acct->GetId());
            }
        }
        return root;
    }
};
#endif
