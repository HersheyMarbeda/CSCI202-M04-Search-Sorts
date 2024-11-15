// /*
//    Program Assignment Name: Search and Sorts
//
//    Programmer: Hershey Marbeda
//    Instructor: Dr. Carver
//    Course: CSCI 202: Data Structures and Algorithms
//
//
//    Last Date Updated: 11.16.2024
//
// ----- Program Assignment Description -----
// 1. Write and test two programs
//  - Use selection sort for linked lists.
//  - Use merge sort for linked lists.
// 2. Compare the efficiency between the merge and selection sort.
// 3. Test with AT LEAST lists with these number of elements
//  - 1
//  - 10
//  - 100
//  - 1000
// 4. You will need to know the time in milliseconds to run each and graph the comparison of n vs time.
//
// */


#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// Linked List creation of Node
struct Node
{
    int info;
    Node* link;
};

class toSearch
{
private:
    
    Node* first; // Pointer to the first node
    Node* last;  // Pointer to the last node
    
    // Helper function to merge two sorted lists
    Node* merge(Node* left, Node* right)
    {
        if (!left) return right;
        if (!right) return left;
        
        Node* result = nullptr;
        if (left->info <= right->info)
        {
            result = left;
            result->link = merge(left->link, right);
        }
        
        else
        {
            result = right;
            result->link = merge(left, right->link);
        }
        
        return result;
    }
    
    // Helper function to split the list into two halves
    void split(Node* source, Node** front, Node** back)
    {
        Node* slow = source;
        Node* fast = source->link;
        
        while (fast != nullptr)
        {
            fast = fast->link;
            
            if (fast != nullptr)
            {
                slow = slow->link;
                fast = fast->link;
            }
        }
        
        *front = source;
        *back = slow->link;
        slow->link = nullptr;
    }
    
    // Recursive merge sort
    Node* mergeSort(Node* node)
    {
        if (node == nullptr || node->link == nullptr)
        {
            return node;
        }
        
        Node* front = nullptr;
        Node* back = nullptr;
        split(node, &front, &back);
        
        front = mergeSort(front);
        back = mergeSort(back);
        
        return merge(front, back);
    }
    
public:
    // Constructor
    toSearch() : first(nullptr), last(nullptr) {}
    
    // Destructor
    ~toSearch()
    {
        clear();
    }
    
    void addNode(int value)
    {
        Node* newNode = new Node;
        newNode->info = value;
        newNode->link = nullptr;
        
        if (first == nullptr)
        {
            first = last = newNode;
        }
        
        else
        {
            last->link = newNode;
            last = newNode;
        }
    }
    
    void display() const
    {
        Node* current = first;
        
        while (current != nullptr)
        {
            cout << current->info << " ";
            current = current->link;
        }
        cout << std::endl;
    }
    
    void clear()
    {
        Node* current = first;
        
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        first = last = nullptr;
    }
    
    void SelectionSort()
    {
        Node* current = first;
        
        while (current != nullptr)
        {
            Node* smallest = current;
            Node* nextNode = current->link;
            
            while (nextNode != nullptr)
            {
                if (nextNode->info < smallest->info)
                {
                    smallest = nextNode;
                }
                nextNode = nextNode->link;
            }
            
            if (smallest != current)
            {
                std::swap(current->info, smallest->info);
            }
            
            current = current->link;
        }
    }
    
    void MergeSearch()
    {
        first = mergeSort(first);
        
            // Update last pointer
        Node* current = first;
        while (current && current->link != nullptr)
        {
            current = current->link;
        }
        last = current;
    }
};

int main()
{
    // Table Headings
    cout << string(100,'-') << endl
         << "\t\t\t\t\t\t\tDifference between Selection and Merge Sorts \n"
         << "\t\t\t\t\t\t\t\t\t M04.2: Search and Sorts\n"
         << string(100,'-') << endl << endl;
    // Declare the toSearch object
    toSearch list;
    
    // Adding nodes
    /*
    list.addNode(100);
    list.addNode(10);
    list.addNode(1000);
    list.addNode(1);
    */
    
    for (int i = 1; i <= 100'000; i++)
    {
        list.addNode(i);
    }
    
    // Measure time for Selection Sort
    clock_t start = clock();
    list.SelectionSort();
    
    
    cout << "Time taken For Selection Sort: " << fixed << setprecision(8) << (double)(clock() - start) / CLOCKS_PER_SEC
         << " seconds N = 100,000" << endl;
        
    // Reset the list
    list.clear();
/*
    list.addNode(100);
    list.addNode(10);
    list.addNode(1000);
    list.addNode(1);
*/
    for (int i = 1; i <= 100'000; i++)
    {
        list.addNode(i);
    }
    
    // Measure time for Merge Sort
    start = clock(); // Reset start for Merge Sort
    list.MergeSearch();
    cout << "Time taken For Merge Sort: " << fixed << setprecision(8) << (double)(clock() - start) / CLOCKS_PER_SEC
         << " seconds for N = 100,000" << endl;
    
    cout << endl << endl;
    return 0;
}
