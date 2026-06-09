// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

template <typename DataType>
class BST {
 private:
  struct Item {
    DataType val;
    int freq;
    Item* l_child;
    Item* r_child;

    explicit Item(const DataType& v)
        : val(v), freq(1), l_child(nullptr), r_child(nullptr) {}
  };

  Item* head;

  void addNode(Item*& ptr, const DataType& v) {
    if (!ptr) {
      ptr = new Item(v);
      return;
    }
    if (v < ptr->val) addNode(ptr->l_child, v);
    else if (v > ptr->val) addNode(ptr->r_child, v);
    else ptr->freq++;
  }

  int calcHeight(Item* ptr) const {
    return ptr ? 1 + std::max(calcHeight(ptr->l_child),
                              calcHeight(ptr->r_child)) : 0;
  }

  int findCount(Item* ptr, const DataType& v) const {
    if (!ptr) return 0;
    if (ptr->val == v) return ptr->freq;
    return (v < ptr->val) ? findCount(ptr->l_child, v)
                          : findCount(ptr->r_child, v);
  }

  void traverseInOrder(Item* ptr,
                       std::vector<std::pair<DataType, int>>& res) const {
    if (!ptr) return;
    traverseInOrder(ptr->l_child, res);
    res.emplace_back(ptr->val, ptr->freq);
    traverseInOrder(ptr->r_child, res);
  }

  void deallocate(Item* ptr) {
    if (!ptr) return;
    deallocate(ptr->l_child);
    deallocate(ptr->r_child);
    delete ptr;
  }

  BST(const BST&);
  BST& operator=(const BST&);

 public:
  BST() : head(nullptr) {}

  ~BST() {
    deallocate(head);
  }

  void insert(const DataType& v) {
    addNode(head, v);
  }

  int depth() const {
    return calcHeight(head) - 1;
  }

  int search(const DataType& v) const {
    return findCount(head, v);
  }

  std::vector<std::pair<DataType, int>> getNodesSortedByFrequency() const {
    std::vector<std::pair<DataType, int>> data;
    traverseInOrder(head, data);

    struct Cmp {
      bool operator()(const std::pair<DataType, int>& a,
                      const std::pair<DataType, int>& b) const {
        return a.second > b.second;
      }
    };

    std::sort(data.begin(), data.end(), Cmp());
    return data;
  }
};

#endif  // INCLUDE_BST_H_
