// This project involves inputting various info of applicant like application no.,name,marks secured,negative marking
// After all this inputs linked list is prepared containing applicants with marks secured in decreasing order
// Then prepared an array of adresses of nodes so required application can be easily fetched with less Time Complexity

#include "bits/stdc++.h"
using namespace std;

// Creating special linked list containing varibales like Application Number, Applicant Name, Marks secured, Applicant rank, Negative marking
class Node{
public:
    int application_no,marks,rank,negative_marking;
    string name;
    Node* next;
    Node(int application_val,string application_name,int application_marks,int negative_marks){
        application_no = application_val;
        name = application_name;
        marks = application_marks;
        negative_marking = negative_marks;
        next = NULL;
    }
};

// Inserting applicants data into linked list to sort them according to marks secured!
// Highest marks are at the top of linked list!
void insert(Node* &head,int application_no,string name,int marks,int negative_marks){
    Node* current = new Node(application_no,name,marks,negative_marks);
    if(head==NULL){      // Case: > When first node in inserted!
        head = current;
        return;
    }
    Node* temp = head; 
    if(temp->marks <= current->marks){     
        if(temp->marks<current->marks){                                 // Case: > When current applicant marks is highest yet!
            current->next = head;
            head = current;
            return;
        }
        else if(temp->negative_marking>current->negative_marking){      // Case: > When current marks and top marks are equal but negative marking factor of top node is greater!
            current->next = head;
            head = current;
            return;
        }
        else{                                                           // Case: > When current marks and top marks are equal but negative marks of current node is equal or greater!
            if(temp->next!=NULL){
                while(temp->next!=NULL and temp->next->negative_marking<current->negative_marking and temp->next->marks==current->marks){  // Run through all greater negative marking nodes to reach last node with greater negative marking then current node!
                    temp = temp->next;
                }
            }
            if(temp->next!=NULL){    
                while(temp->next!=NULL and temp->next->negative_marking==current->negative_marking and temp->next->marks==current->marks){  // Run through all equal negative marking nodes to reach last node with equal negative marking then current node!
                    temp = temp->next;
                }
            }    
            current->next = temp->next;
            temp->next = current;
            return; 
        }
    }      

    while((temp->marks>=current->marks) and (temp!=NULL)){    // Case: > When current marks is somewhere at middle!
        if( temp->next!=NULL and temp->next->marks==current->marks and temp->next->negative_marking>current->negative_marking ){
            break;
        }
        else if( (temp->next==NULL) or (temp->next->marks<current->marks) ){
            break;
        }
        else{
            temp = temp->next;
        }    
    }
    current->next = temp->next;
    temp->next = current;
    return;
}

// Allotment of ranks according to the sorted marks in linked list!
// At same time arranging the applications in array on the basis of application number!
void allotment(Node* array[],Node* &head){
    Node* temp = head;
    int i=1;
    while(head!=NULL){
        head->rank = i;   // Here alloting rank to the applicant!
        array[head->application_no] = head;    // Arrangement in array
        if(head->next!=NULL){
            if(head->marks!=head->next->marks or head->negative_marking!=head->next->negative_marking){
                i++;  // RANK!
            }
        }    
        head = head->next;
    }
    head = temp;
    return; 
}

// BINARY SEARCH of application number in array created {Reduce Time Complexity}
void fetch(Node* array[],int application_required,int low,int high){
    if(application_required == array[(low+high)/2]->application_no){
        // Printing out various info of required application number!
        cout<<"Applicant Name: "<<array[(low+high)/2]->name<<endl<<"Applicant Application Number: "<<array[(low+high)/2]->application_no<<endl<<"Applicant Marks secured: "<<array[(low+high)/2]->marks<<endl<<"Negative Marking: "<<array[(low+high)/2]->negative_marking<<endl<<"Applicant Rank: "<<array[(low+high)/2]->rank<<endl;
    }
    if(application_required > array[(low+high)/2]->application_no){
        fetch(array,application_required,(low+high)/2,high);
    }
    if(application_required < array[(low+high)/2]->application_no){
        fetch(array,application_required,low,(low+high)/2);
    }
}

signed main(){
    Node* head = NULL;
    int total_applications;
    cin>>total_applications;

    Node** array;
    array = new Node*[total_applications+1];

    for(int i=0;i<total_applications;i++){
        int no,mark,negative_marks;
        string namee;
// NOTE: > Applications number should start from 1. 
//         If applications are in large number and application number need to be start from any other integer.
//         The code needs to be slightly modified to prevent extra memory usage!
        cin>>no>>namee>>mark>>negative_marks;
        if(mark<=100 and (negative_marks+mark<=100)){   // Note: You can also set .... to application number
            insert(head,no,namee,mark,negative_marks);
        }
        else{
            Node* n = new Node(no,namee,0,0);
            n->rank = 0;
            array[no] = n;
        }    
    }

    allotment(array,head);

    int application_required;
    cin>>application_required;
    if(application_required==total_applications){
        cout<<"Applicant Name: "<<array[application_required]->name<<endl<<"Applicant Application Number: "<<array[application_required]->application_no<<endl<<"Applicant Marks secured: "<<array[application_required]->marks<<endl<<"Negative Marking: "<<array[application_required]->negative_marking<<endl<<"Applicant Rank: "<<array[application_required]->rank<<endl;
    }
    else{
        fetch(array,application_required,1,total_applications);
    }    

    delete []array;     // Free memory of dynamic allocated array of Node* !
    while(head!=NULL){  // Free memory of dynamic allocated Nodes in linked list !
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}