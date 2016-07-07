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
  ~bt () {};
  void insert(int val)
  {
    root_ = insert_i(val, root_);
  }

  void inorder_traversal()
  {
    inorder(root_);
  }

private:
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
  return 0;
}
