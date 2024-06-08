  struct Node {
    int data{};
    Node* left{};
    Node* right{};
  };

//binary search tree
  Node* insert(Node* root, int data) {
    if (root == NULL) {
      return new Node();
    } else {
      Node* cur;
      if (data <= root->data) {
        cur = insert(root->left, data);
        root->left = cur;
      } else {
        cur = insert(root->right, data);
        root->right = cur;
      }

      return root;
    }
  }
