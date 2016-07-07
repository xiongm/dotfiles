#include <iostream>
#include <vector>

using namespace std;

struct Node
{
  int val;
  Node * left;
  Node * right;
  Node(int v)
    :val(v), left(nullptr), right(nullptr)
  {}
};

class bt
{
public:
  bt () :root_(nullptr) {};
  ~bt () {
    erase();
  };
  void insert(int val)
  {
    root_ = insert_i(val, root_);
  }

  void inorder_traversal()
  {
    inorder(root_);
  }

  void erase()
  {
    erase_i(root_);
    root_ = nullptr;
  }
private:
  void erase_i(Node * parent)
  {
    if (!parent) return;
    if (parent->left)
    {
      erase_i(parent->left);
      parent->left = nullptr;
    }
    if (parent->right)
    {
      erase_i(parent->right);
      parent->right = nullptr;
    }
    delete parent;
  }

  void inorder(Node * root)
  {
    if (!root) return;

    inorder(root->left);
    cout << root->val << endl;
    inorder(root->right);
  }

  Node * insert_i(int val, Node * root)
  {
    if (!root)
    {
      Node * new_node = new Node(val);
      return new_node;
    }
    if (val < root->val)
    {
      root->left = insert_i(val, root->left);
      return root;
    }
    if (val > root->val)
    {
      root->right = insert_i(val, root->right);
      return root;
    }
  }
private:
  Node *root_;
};

int main(int argc, char *argv[])
{
  vector<int> nodes {5, 1,3, 4, 2};

  bt btree;

  for (auto i : nodes)
  {
    btree.insert(i);
  }

  btree.inorder_traversal();

  cout << "erasing tree" << endl;
  btree.erase();

  btree.inorder_traversal();
  return 0;
}
