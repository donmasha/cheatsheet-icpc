struct Trie {
  struct Node {
    Node * child[2];
    int cnt;
    Node() {
      child[0] = child[1] = NULL;
      cnt = 0;
    }
  };

  Node * head;

  Trie() {
    head = new Node();
  }

  void insert(int val) {
    Node * cur = head;
    for (int i = 30; i >= 0; i--) {
      bool v = val & (1 << i);
      ++cur -> cnt;
      if (cur -> child[v] == NULL) {
        cur -> child[v] = new Node();
      }
      cur = cur -> child[v];
    }
    ++cur -> cnt;
  }

  void erase(int val) {
    Node * cur = head;
    for (int i = 30; i >= 0; i--) {
      bool v = val & (1 << i);
      --cur -> cnt;
      cur = cur -> child[v];
    }
    --cur -> cnt;
  }

  int getMinXOR(int val) {
    Node * cur = head;
    int ret = 0;
    for (int i = 30; i >= 0; i--) {
      bool v = val & (1 << i);
      if (cur -> child[v] != NULL && cur -> child[v] -> cnt != 0) {
        cur = cur -> child[v];
      } else {
        cur = cur -> child[v ^ 1];
        ret |= (1 << i);
      }
    }
    return ret;
  }
};