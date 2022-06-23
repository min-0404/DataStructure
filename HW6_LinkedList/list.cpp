// #include "list.h"

// void IntList::Push_Back(int e) {
//     if (!first)
//     first = last = new Node(e);
//     else {
//         last->link = new Node(e);
//         last = last->link;
// };


// void IntList::Insert(int e){
//     Node* temp = first;
//     if(!first){
//         while(temp -> data < e){ temp = temp -> link;}
//         temp -> link = new Node(e, temp -> link);
//         }
//     else{
//         first = new Node(e);
//     }
// }

// void IntList::Delete(int e)
// {
//     Node* temp1 = first;
//     Node* temp2 = first;
//     while(1){ //temp1을 삭제할 노드로 만들어줌
//         temp1 = temp1 -> link;
//         if(temp1 -> data == e)  break;
//     }
//     while(temp2 -> data < e){ //temp2를 삭제할 이전 노드로 만들어줌
//         temp2 = temp2 -> link;
//     }
//     if(first){
//         temp2 -> link = temp1 -> link;
//         delete temp1; 
//     }
//     else{
//         delete first;
//     }
// };

// ostream& operator<<(ostream& os, IntList& il)
// {
//     Node *ptr = il.first;
//     while (ptr != NULL)
//     {
//         os << ptr->data << " ";
//         ptr = ptr->link;
//     }
//     os << endl;
//     return os;
// }

