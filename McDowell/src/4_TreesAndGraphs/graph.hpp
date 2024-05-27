#pragma once
#include <functional>
#include <deque>
#include <memory>
#include <unordered_set>
#include <unordered_map>

template<typename T>
struct WeakPtrHash {
  size_t operator()(const std::weak_ptr<T>& wp) const {
    auto sp = wp.lock();
    return std::hash<decltype(sp)>()(sp);
  }
};


template<typename T>
struct WeakPtrEqual {
  bool operator()(const std::weak_ptr<T>& left, const std::weak_ptr<T>& right) const {
    return !left.owner_before(right) && !right.owner_before(left);
  }
};



template <typename State>
class Graph {
public:

  class Node {
  public:
    Node(const std::string& n) : name_(n) {
    }
    virtual ~Node() {}

    bool isAdjacentFor(const std::shared_ptr<Node>& other) const {
      return childs_.find(other) != childs_.end();
    }

    void addChild(const std::shared_ptr<Node>& other) {
      childs_.insert(other);
    }

    const std::unordered_set<std::weak_ptr<Node>, WeakPtrHash<Node>, WeakPtrEqual<Node>>& getAdjacent() const {
      return childs_;
    }

    const std::string& Name() const {
      return name_;
    }

    mutable State state_;
    std::string name_;

  private:
    std::unordered_set<std::weak_ptr<Node>, WeakPtrHash<Node>, WeakPtrEqual<Node>> childs_;
  };



  bool matrix(size_t i, size_t j) const {
    if (i == j)
      return false;

    const auto& s = nodes_[i];
    const auto& d = nodes_[j];
    return s->isAdjacentFor(d);
  }



  std::shared_ptr<Node>& addNode(const std::string& name = std::string()) {
    nodes_.emplace_back(std::make_shared<Node>(name));
    if (!name.empty())
      namedNodes_[name] = nodes_.back();
    return nodes_.back();
  }



  const std::shared_ptr<Node>& operator[] (size_t i) const {
    return nodes_[i];
  }


  const std::shared_ptr<Node>& operator[] (const std::string& name) const {
    return namedNodes_.at(name);
  }


  const std::deque<std::shared_ptr<Node>>& getNodes() const {
    return nodes_;
  }


private:
  std::deque<std::shared_ptr<Node>> nodes_;
  std::unordered_map<std::string, std::shared_ptr<Node>> namedNodes_;
};



template <typename State>
using Node = std::shared_ptr<typename Graph<State>::Node>;
