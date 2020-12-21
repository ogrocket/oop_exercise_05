#include <memory>
#include <iostream>

template <class T>
struct Node;

template <class T>
void operator++(std::shared_ptr<Node<T>>& node){
    if (node){
        node = node->next;
    }
    else {
        throw std::runtime_error("nullptr #1\n");
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

template <typename T>
struct Node{
    T data;
    std::shared_ptr<Node<T>> next;

    Node(){
        next = nullptr;
    }

    Node(const T d){
        data = d;
        next = nullptr;
    }

    friend void operator++<>(std::shared_ptr<Node<T>> &node);
    friend bool operator!=<>(const Node<T> &left_value, const Node<T> &right_value);
    friend bool operator==<>(const Node<T> &left_value, const Node<T> &right_value);
    friend std::ostream &operator<<<>(std::ostream &cout, const Node<T> &node);
};


template <typename T>
class Queue{
private:

    size_t size = 0;
    std::shared_ptr<Node<T>> first;
    std::shared_ptr<Node<T>> last;

 public:

    class Iterator{
    private:

        std::shared_ptr<Node<T>> iterator;
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        Iterator(){
            iterator = nullptr;
        }
        explicit Iterator(const std::shared_ptr<Node<T>> &iter){
            iterator = iter;
        }

        friend void operator++(Iterator &iter){
            ++iter.iterator;
        }

        friend bool operator!=(const Queue<T>::Iterator &left, const Queue<T>::Iterator &right){
            return left.iterator != right.iterator;
        }

        Node<T> &operator*() {
            return *iterator;
        }

        friend std::ostream &operator<<(std::ostream &out, const Iterator &iter){
            out << *iter.iterator;
            return out;
        }

        bool Null(){
            return iterator == nullptr;
        }
    };
    Iterator Begin() {
        return Iterator(first);
    }

    Iterator End() {
        return Iterator(last->next);
    }

    Queue(){
        first = nullptr;
        last = nullptr;
    }

    ~Queue(){}

    size_t Size(){
        return size;
    }

    T Top (){
        if (first != nullptr) {
            return first->data;
        }
        else {
            throw std::runtime_error("nullptr #2\n");
        }
    }

    void Push(const T& elem){
        Node<T>* new_node = new Node<T>(elem);
        std::shared_ptr<Node<T>> pointer(new_node);
        if (size == 0){
            last = pointer;
            first = last;
        }
        else if (size == 1){
            first->next = last;
            last->next = pointer;
            last = pointer;
        }
        else{
            last->next = pointer;
            last = pointer;
        }
        size++;
    }

    void Pop(){
        if (first != nullptr){
            first = first->next;
            size--;
        }
        else{
            throw std::runtime_error("There is nothing to pop\n");
        }
    }


    void Insert(Queue<T>::Iterator& iter, const T& elem){
        std::unique_ptr<Node<T>> new_node(new Node<T>(elem));
        std::shared_ptr<Node<T>> new_pointer = std::move(new_node);
        std::shared_ptr<Node<T>> next_pointer = first;
        if (*iter == *first) {
            new_pointer-> next = first;
            first = new_pointer;
        }
         else if (next_pointer) {
                    if (!iter.Null()){
                        while(*next_pointer-> next != *iter) {
                            ++next_pointer;
                        }
                    }
                    else{
                        while (new_pointer->next != nullptr) {
                            ++next_pointer;
                        }
                    }

                    if (next_pointer->next == nullptr) {
                        next_pointer->next = new_pointer;
                        last = new_pointer;
                    }
                    else{
                        new_pointer->next = next_pointer->next;
                        next_pointer->next = new_pointer;
                    }
         }
         else {
            first = new_pointer;
        }
        size++;
    }

    void Erase(Iterator &iter) {
        if (iter.Null()) {
            throw std::runtime_error("nullptr #3\n");
        }
        else {
            if (*iter == *first) {
                first = first->next;
            }
            else {
                std::shared_ptr<Node<T>> next_ptr = first;
                while (*next_ptr->next != *iter) {
                    ++next_ptr;
                }
                next_ptr->next = next_ptr->next->next;
            }
            --size;
        }
    }

};
