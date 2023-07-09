
// q1: reverse linked list
class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *prev = NULL, *curr = head, *next = NULL;
        while (curr != NULL)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
        return head;
    }
};

// q2: 

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL || head->next == NULL)
            return head;

        ListNode* curr = head;
        int count = 0;
        while (curr != NULL && count < k) {
            curr = curr->next;
            count++;
        }

        if (count == k) {
            curr = reverseKGroup(curr, k);

            while (count > 0) {
                ListNode* nextNode = head->next;
                head->next = curr;
                curr = head;
                head = nextNode;
                count--;
            }

            head = curr;
        }

        return head;
    }
};

// Utility function to print a linked list
void printList(ListNode* head) {
    ListNode* curr = head;
    while (curr != NULL) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    // Create a sample linked list: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8
    ListNode* head = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(4);
    ListNode* node5 = new ListNode(5);
    ListNode* node6 = new ListNode(6);
    ListNode* node7 = new ListNode(7);
    ListNode* node8 = new ListNode(8);
    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = node7;
    node7->next = node8;

    int k = 3;  // Group size

    Solution solution;
    ListNode* reversedHead = solution.reverseKGroup(head, k);

    // Print the reversed linked list
    printList(reversedHead);

    // Clean up memory
    ListNode* curr = reversedHead;
    while (curr != NULL) {
        ListNode* temp = curr;
        curr = curr->next;
        delete temp;
    }

    return 0;
}

// q3: Intersection of Two Linked Lists
class Solution {
public:
    int length(ListNode *head){
        int len = 0;
        while(head){
            len++;
            head = head->next;
        }
        return len;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return NULL;

        //step1
        int lenA = length(headA), lenB = length(headB);

        //step2
        if(lenA>lenB){
            while(lenA>lenB){
                headA = headA->next;
                lenA--;
            }
        }
        else if(lenA<lenB){
            while(lenA<lenB){
                headB = headB->next;
                lenB--;
            }
        }
        
        //step 3
        while(headA && headB){
            if(headA==headB) return headA;
            headA = headA->next;
            headB = headB->next;
        }
        return NULL;
    }
};
