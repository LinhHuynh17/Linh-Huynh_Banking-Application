/*Linh Huynh
CSS 342
Instructor:Professor Dimpsey
Program 5*/
#include <iostream>
#include "BSTree.h"
using namespace std;
BSTree::BSTree() {
    root_ = nullptr;
}

BSTree::BSTree(const BSTree& tree) {

}

BSTree::~BSTree() {
    Cleantree(root_);
    root_ = nullptr;
}

bool BSTree::Insert(Account* account) {
    if (root_ == nullptr) {
        root_ = new Node(account);
        return true;
    }
    else {
        Node* temp = root_;
        Node* cur = nullptr;
        while (temp != nullptr) {
            if (account->GetId() < temp->p_acct->GetId()) {
                cur = temp;
                temp = temp->left;
            }
            else {
                if (account->GetId() > temp->p_acct->GetId()) {
                    cur = temp;
                    temp = temp->right;
                }
                else {
                    return false;
                }
            }
        }
        if (account->GetId() < cur->p_acct->GetId()) {
            cur->left = new Node(account);
        }
        else {
            cur->right = new Node(account);
        }
        return true;
    }
}

bool BSTree::Retrieve(const int& account_id, Account*& account) const {
    Node* res = retrieve(root_, account_id);
    if (res == nullptr) {
        account = nullptr;
        return false;
    }
    else {
        account = res->p_acct;
        return true;
    }
}

void BSTree::Display() const {
    PrintTree(root_);
}

bool BSTree::Delete(const int& account_id, Account*& account) {
    Node* res = DeleteNode(root_, account_id);
    account = res->p_acct;
    return account != nullptr;
}