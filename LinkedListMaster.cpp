/**
 * LinkedListMaster.cpp - 单链表操作核心实现
 * 
 * Copyright (c) 2025 Solibooster (孤独书生212). All rights initially reserved.
 * 开源协议：MIT License
 * 
 * 创建日期: 2025-07-27
 * 作者: SoliBooster (孤独书生212)
 * 联系方式: 18199608@qq.com
 * 
 * 功能特性:
 *   - 完整的单链表增删改查实现
 *   - 包含边界条件处理和内存管理
 *   - 适合教学/学习使用
 * 
 * 使用条款:
 *   1. 允许自由修改和分发
 *   2. 需保留本版权声明
 *   3. 禁止直接商业牟利使用
 * 
 * GitHub: https://github.com/SoliBooster
 */

#include <iostream>
using namespace std;

//定义链表节点
struct Node{    //struct Node:定义一个链表结构体
    int data;   //节点存储的数据
    Node* next; //指向下一个节点的指针
    //构造函数
    Node(int x):data(x),next(nullptr){}
};

//创建一个简单的链表：1 -> 2 -> 3 -> nullptr
Node* createLinkedList(){
    Node* head = new Node(1);               //创建头结=节点，存储1
    head -> next = new Node(2);             //头节点的next指向第二个节点，存储2
    head -> next -> next = new Node(3);     //第二个节点的next指向第三个节点，存储3
    return head;                            //返回头节点
}

//在链表头部插入新节点
Node* insertAtHead(Node* head, int x){
    Node* newNode = new Node(x);            //创建新节点,存储x
    newNode -> next = head;                 //新节点的next指向原头节点
    return newNode;                         //新节点成为新的头节点，返回新头节点
}

//在链表尾部插入新节点
void insertAtTail(Node* head, int x){       
    Node* newNode = new Node(x);            //创建新节点

    //如果链表为空
    if(head == nullptr){
        head = newNode;                     //新节点就是头节点                
        return;
    }

    
    Node* current = head;
    while(current->next != nullptr){        //遍历到最后一个节点
        current = current->next;
    }
    //在尾部插入新节点
    current -> next = newNode;              //最后一个节点的next指向新节点
}

//在指定位置插入新节点（位置从0开始）
Node* insertAtPosition(Node* head, int x, int pos){
    Node* newNode = new Node(x);

    //在头部插入
    if(pos == 0){
        newNode -> next = head;
        return newNode;
    }

    Node* current = head;
    //找到插入位置的前一个节点
    for(int i = 0; (i < pos - 1) && (current != nullptr); i++){
        current = current -> next;
    }

    //如果位置有效
    if(current != nullptr){
        newNode->next = current->next;
        current->next = newNode;
    }

    return head;
}

//删除链表头节点
Node* deleteAtHead(Node* head){
    if(head == nullptr) return nullptr;             //如果链表为空，直接返回nullptr
                                                    
    Node* newHead = head->next;                     //新头节点是原头节点的下一个节点
    delete head;                                    //释放释放原头节点的内存
    return newHead;
}

//删除尾节点
Node* deleteAtTail(Node* head){
    if(head == nullptr || head->next == nullptr){
        delete head;                                //如果链表为空或只有一个节点，直接删除
        return nullptr;
    }

    Node* current = head;

    while (current->next->next != nullptr){         //找到倒数第二个节点
        current = current->next;
    }
    
    delete current->next;//释放尾结点内存
    current->next = nullptr;//设置新的尾结点

    return head;
}

//删除第一个值为x的节点
Node* deleteByValue(Node* head, int x){
    //链表为空
    if (head == nullptr)return nullptr;

    //要删除的是头结点
    if (head->data == x){
        Node* temp = head->next;
        delete head;
        return temp;
    }
    
    Node* current = head;
    //找到要删除节点的前一个节点
    while(current->next != nullptr && current->next->data != x){
        current = current->next;
    }

    //如果找到要删除的节点
    if(current->next != nullptr){
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    return head;
}

//修改指定位置节点的值
void modifyAtPosition(Node* head, int pos, int newx){
    Node* current = head;
    int count = 0;

    //找到指定位置的节点
    while (current != nullptr && count < pos){
        current = current->next;
        count++;
    }
    
    //如果位置有效
    if(current != nullptr){
        current->data = newx;
    }
}

//获取指定位置节点的值
int getAtPosition(Node* head, int pos){
    Node* current = head;
    int count = 0;

    while (current != nullptr &&count < pos){
        current = current->next;
        count++;
    }

    if (current == nullptr){
        return -1; // 表示未找到
    }
    
    return current->data;
}

//查找值为x的节点的位置（从0开始）
int findPositionByValue(Node* head, int x){
    Node* current = head;
    int pos = 0;

    while(current != nullptr){
        if(current->data == x){
            return pos;
        }
        current = current->next;
        pos++;
    }

    return -1; //表示未找到
}

//找到链表内容
void printList(Node* head){
    Node* current = head;               //从头节点开始遍历
    while (current != nullptr){         //只要当前节点不为空
        cout << current->data << " ";   //打印当前节点的数据
        current = current->next;        //移动到下一个节点
    }
    cout << endl;
}

int main() {
    // 创建链表：1->2->3
    Node* head = createLinkedList();
    cout << "原始链表: ";
    printList(head); // 输出: 1 2 3
    
    // 在头部插入0
    head = insertAtHead(head, 0);
    cout << "头部插入0后: ";
    printList(head); // 输出: 0 1 2 3
    
    // 在尾部插入4
    insertAtTail(head, 4);
    cout << "尾部插入4后: ";
    printList(head); // 输出: 0 1 2 3 4
    
    // 在位置2插入10
    head = insertAtPosition(head, 10, 2);
    cout << "位置2插入10后: ";
    printList(head); // 输出: 0 1 10 2 3 4
    
    // 删除头节点
    head = deleteAtHead(head);
    cout << "删除头节点后: ";
    printList(head); // 输出: 1 10 2 3 4
    
    // 删除尾节点
    head = deleteAtTail(head);
    cout << "删除尾节点后: ";
    printList(head); // 输出: 1 10 2 3
    
    // 删除值为10的节点
    head = deleteByValue(head, 10);
    cout << "删除值为10的节点后: ";
    printList(head); // 输出: 1 2 3
    
    // 修改位置1的值为20
    modifyAtPosition(head, 1, 20);
    cout << "修改位置1的值为20后: ";
    printList(head); // 输出: 1 20 3
    
    // 查询位置1的值
    cout << "位置1的值: " << getAtPosition(head, 1) << endl; // 输出: 20
    
    // 查询值为3的位置
    cout << "值为3的位置: " << findPositionByValue(head, 3) << endl; // 输出: 2
    
    return 0;
}

//掌握链表艺术，从增删改查开始！