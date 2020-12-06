template <class T>
struct Node;

template <class T>
void operator++(std::shared_ptr<Node<T>>& node){
    if (node){
        node = node->next;
    }
    else {
        throw std::runtime_error("nullptr\n");
    }
}

template <class T>
bool operator!=(const Node<T>& left, const Node<T>& right){
    return &left != &right;
}

template <class T>
bool operator==(const Node<T>& left, const Node<T>& right){
    return &left.data == &right.data;
}

template <class T>
std::ostream &operator<<(std::ostream &cout, const Node<T>& node){
    cout << node.data;
    return cout;
}

template <typename N>
struct Node{
    N data;
    std::shared_ptr<Node<N>> next;

    Node(){
        next = nullptr;
    }

    Node(const N data){
        this->data = data;
        next = nullptr;
    }

    friend void operator++<>(std::shared_ptr<Node<T>> &node);

    friend bool operator!=<>(const Node<T> &left_value, const Node<T> &right_value);

    friend bool operator==<>(const Node<T> &left_value, const Node<T> &right_value);

    friend std::ostream &operator<<<>(std::ostream &cout, const Node<T> &node);
};
