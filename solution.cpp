#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

/* takeaways
   - keep track of the max average while
     traverse the tree
   - when visits a subtree 
     - add up the sum of its child node values
     - and up the number of its child nodes
     - compare the avg passed down and 
       update avg if the avg of the subtree,
       (sum/number of nodes) is higher    
*/

struct Node
{
  int val;
  vector<Node *> children;
  Node(int _val)
  {
    val = _val;
  }
};

class Solution
{
private:
  /* this is where the recursion happens */
  vector<int> _maxAvg(Node *root, double &avg)
  {
    /* tree with just one node */
    if (root != nullptr && root->children.size() == 0)
    {
      avg = max(avg, root->val * 1.0);
      return {root->val, 1};
    }

    /*C++ notes 
      - vector vs tuple; choose one  
    */
    /* 
      - store the following for a given subtree
        in a vector:
        {sum of all node values, number of nodes} 
    */
    vector<int> sumNum{root->val, 1}; // exactly two elements

    for (auto &child : root->children)
    {
      auto childSumNum = _maxAvg(child, avg);
      /* add up the result */
      sumNum[0] += childSumNum[0];
      sumNum[1] += childSumNum[1];
    }
    avg = max(avg, (sumNum[0] / sumNum[1] * 1.0));
    return sumNum;
  }

public:
  double maxAvg(Node *root)
  {
    double avg = 0.0;
    if (root == nullptr || root->children.size() == 0)
      return avg;
    _maxAvg(root, avg);

    return avg;
  }
};

Node *testFixture1()
{
  auto *root = new Node(5);
  root->children.push_back(new Node(6));
  root->children.push_back(new Node(5));
  return root;
}

Node *testFixture2()
{
  auto *root = new Node(20);
  root->children.push_back(new Node(12));
  root->children.push_back(new Node(18));
  root->children[0]->children.push_back(new Node(11));
  root->children[0]->children.push_back(new Node(13));
  root->children[1]->children.push_back(new Node(15));
  root->children[1]->children.push_back(new Node(8));

  return root;
}

void test1()
{
  Solution sol;
  auto tree = testFixture1();

  cout << "Test 1 - expect to see 6" << endl;
  cout << "result: " << sol.maxAvg(tree) << endl;
}

void test2()
{
  Solution sol;
  auto tree = testFixture2();

  cout << "Test 2 - expect to see 15" << endl;
  cout << "result: " << sol.maxAvg(tree) << endl;
}

main()
{
  test1();
  test2();
  return 0;
}