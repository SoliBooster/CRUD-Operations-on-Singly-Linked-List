#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
struct Node {
    T data;         //存储的数据
    Node* prev;     //指向前一个节点的指针
    Node* next;     //指向后一个节点的指针

    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;  //头节点指针
    Node<T>* tail;  //尾节点指针
    int size;       //链表长度
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {};
    ~DoublyLinkedList() {
        clear();
    }

    //检查链表是否为空
    bool isEmpty() const {
        return size == 0;
    }

    //获取链表长度
    int getSize() const {
        return size;
    }

    //在链表头部插入节点
    void insertAtHead(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (isEmpty()) {
            //如果链表为空，新节点即是头也是尾
            head = tail = newNode;
        } else {
            //新节点的next指向当前头节点
            newNode->next = head;
            //当前头节点的prev指向新节点
            head->prev = newNode;
            //更新头节点为新节点
            head = newNode;
        }
        size++;
    }

    //在链表尾部插入节点
    void insertAtTail(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (isEmpty()) {
            //如果链表为空，新节点即是头也是尾
            head = tail = newNode;
        } else {
            //新节点的prev指向当前尾节点
            newNode->prev = tail;
            //当前尾节点的next指向新节点
            tail->next = newNode; 
            //更新尾节点为新节点
            tail = newNode;
        }
        size++;
    }

    //在指定位置插入节点
    void insertAt(int index, const T& value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            insertAtHead(value);
        } else if (index == size) {
            insertAtTail(value);
        } else {
            //找到要插入位置的前一个节点
            Node<T>* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            //创建新节点
            Node<T>* newNode = new Node<T>(value);

            //设置新节点的前后关系
            newNode->prev = current;
            newNode->next = newNode;

            size++;
        }
    }

    //删除头节点
    void deleteAtHead() {
        if (isEmpty()) {
            throw runtime_error("Cannot delete from empty list");
        }
        
        Node<T>* temp = head;

        if (head == tail) {
            //只有一个节点的情况
            head = tail = nullptr;
        } else {
            //更新头节点
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        size--;
    }

    //删除尾节点
    void deleteAtTail() {
        if (isEmpty()) {
            throw runtime_error("Cannot delete from emptylist");
        }

        Node<T>* temp = tail;

        if (head == tail) {
            //只有一个节点的情况
            head = tail = nullptr;
        } else {
            //更新尾节点
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
        size--;
    }

    //删除指定位置的节点
    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }

        if (index == 0) {
            deleteAtHead();
        } else if (index == size - 1) {
            deleteAtTail();
        } else {
            //找到要删除的节点
            Node<T>* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            //更新相邻节点的指针
            current->prev->next = current->next;
            current->next->prev = current->prev;

            delete current;
            size--;
        }
    }

    //获得指定位置的值
    T get(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }

        Node<T>* current;
        //根据位置决定从头还是从尾开始遍历更高效；
        if (index < size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        }
        
        return current->data;
    }

    //更新指定位置的值
    void set(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }

        Node<T>* current;
        if (index < size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = size - 1; i > index; i--) {
                current = current->prev;
            }
        }

        current->data = value;
    }

    //清空链表
    void clear() {
        while (!isEmpty()) {
            deleteAtHead();
        }
    }

    //打印链表（从头到尾）
    void printForward() const {
        Node<T>* current = head;
        cout << "Forward: [ ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "]" << endl;
    }

    //打印链表（从尾到头）
    void printBackward() const {
        Node<T>* current = tail;
        cout << "Backward: [ ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << "]" << endl;
    }
};

int main() {
    DoublyLinkedList<int> dll;
    
    // 插入测试
    dll.insertAtHead(10);
    dll.insertAtHead(20);
    dll.insertAtTail(30);
    dll.insertAt(1, 40);
    
    // 打印测试
    dll.printForward();  // 输出: Forward: [ 20 40 10 30 ]
    dll.printBackward(); // 输出: Backward: [ 30 10 40 20 ]
    
    // 删除测试
    dll.deleteAtHead();
    dll.deleteAtTail();
    dll.deleteAt(1);
    
    dll.printForward();  // 输出: Forward: [ 40 ]
    
    // 获取和设置测试
    std::cout << "Element at 0: " << dll.get(0) << std::endl; // 输出: 40
    dll.set(0, 50);
    std::cout << "After set, element at 0: " << dll.get(0) << std::endl; // 输出: 50
    
    // 清空测试
    dll.clear();
    std::cout << "After clear, size: " << dll.getSize() << std::endl; // 输出: 0
    
    return 0;
}

