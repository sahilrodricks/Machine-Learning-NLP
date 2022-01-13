// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


TEST(test_ctor) {
  BinarySearchTree<int> b;
  ASSERT_TRUE(b.empty())
  ASSERT_TRUE(b.size() == 0)
  ASSERT_TRUE(b.height() == 0);
  
  b.insert(1);
  BinarySearchTree<int> b2(b);
  ASSERT_TRUE(b.size() == b2.size());
  ASSERT_TRUE(b.height() == b2.height());
  
  b.insert(5);
  BinarySearchTree<int> b3(b);
  ASSERT_TRUE(b.size() == b3.size());
  ASSERT_TRUE(b.height() == b3.height());
    
  ASSERT_TRUE(b.size() != b2.size());
  ASSERT_TRUE(b.height() != b2.height());
}

TEST(test_assign) {
  BinarySearchTree<int> b;
  BinarySearchTree<int> b2;
  ASSERT_TRUE(b.empty())
  ASSERT_TRUE(b.size() == 0)
  ASSERT_TRUE(b.height() == 0);
  
  b2 = b;
  ASSERT_TRUE(b2.empty())
  ASSERT_TRUE(b2.size() == 0)
  ASSERT_TRUE(b2.height() == 0);
   
  b.insert(1);
  b.insert(5);
               
  ASSERT_TRUE(b.size() != b2.size());
  b = b2;
  ASSERT_TRUE(b.size() == b2.size());
  ASSERT_TRUE(b.height() == b2.height());
}


TEST(test_empty) {
  BinarySearchTree<int> b;
  ASSERT_TRUE(b.empty())
  
  b.insert(1);
  ASSERT_FALSE(b.empty());
  
  b.insert(2);
  ASSERT_FALSE(b.empty());
}
       
TEST(test_height) {
  BinarySearchTree<int> b;
  ASSERT_TRUE(b.height() == 0);
  
  b.insert(1);
  ASSERT_TRUE(b.height() == 1);
  
  b.insert(2);
  ASSERT_TRUE(b.height() == 2);
                                 
  b.insert(0);
  ASSERT_TRUE(b.height() == 2);
                                
  b.insert(3);
  ASSERT_TRUE(b.height() == 3);
}
  
  
TEST(test_size) {
  BinarySearchTree<int> b;
  ASSERT_TRUE(b.size() == 0);
  
  b.insert(1);
  ASSERT_TRUE(b.size() == 1);
  
  b.insert(2);
  ASSERT_TRUE(b.size() == 2);
                                 
  b.insert(0);
  ASSERT_TRUE(b.size() == 3);
                                
  b.insert(3);
  ASSERT_TRUE(b.size() == 4);
}
  
TEST(test_traverse_inorder) {
  BinarySearchTree<int> b;
  stringstream s1;
  b.traverse_inorder(s1);
    
  ASSERT_TRUE(s1.str() == "");
  
  b.insert(5);
  stringstream s2;
  b.traverse_inorder(s2);
  ASSERT_TRUE(s2.str() == "5 ");
  
  b.insert(3);
  stringstream s3;
  b.traverse_inorder(s3);
  ASSERT_TRUE(s3.str() == "3 5 ");
  
  b.insert(4);
  stringstream s4;
  b.traverse_inorder(s4);
  ASSERT_TRUE(s4.str() == "3 4 5 ");
  
  b.insert(7);
  stringstream s5;
  b.traverse_inorder(s5);
  ASSERT_TRUE(s5.str() == "3 4 5 7 ");
}
 

TEST(test_traverse_preorder) {
  BinarySearchTree<int> b;
  stringstream s1;
  b.traverse_preorder(s1);
    
  ASSERT_TRUE(s1.str() == "");
  
  b.insert(5);
  stringstream s2;
  b.traverse_preorder(s2);
  ASSERT_TRUE(s2.str() == "5 ");
  
  b.insert(3);
  stringstream s3;
  b.traverse_preorder(s3);
  ASSERT_TRUE(s3.str() == "5 3 ");
  
  b.insert(4);
  stringstream s4;
  b.traverse_preorder(s4);
  ASSERT_TRUE(s4.str() == "5 3 4 ");
  
  b.insert(7);
  stringstream s5;
  b.traverse_preorder(s5);
  ASSERT_TRUE(s5.str() == "5 3 4 7 ");
}
 
TEST(test_check_sorting_invariant) {
  BinarySearchTree<int> b;
  ASSERT_TRUE(b.check_sorting_invariant());
  b.insert(5);
  ASSERT_TRUE(b.check_sorting_invariant());
  b.insert(3);
  ASSERT_TRUE(b.check_sorting_invariant());
  b.insert(4);
  ASSERT_TRUE(b.check_sorting_invariant());
  b.insert(7);
  ASSERT_TRUE(b.check_sorting_invariant());
  b.insert(10);
  ASSERT_TRUE(b.check_sorting_invariant());
  
  /*
            5
         3      7
           4       10
  
  */
  
  *(b.begin()) = 1;
  ASSERT_TRUE(b.check_sorting_invariant());
  *(b.begin()) = 2;
  ASSERT_TRUE(b.check_sorting_invariant());
  *(b.begin()) = 4;
  ASSERT_FALSE(b.check_sorting_invariant());
  *(b.begin()) = 3;
  
  auto it = b.find(10);
  *it = 9;
  ASSERT_TRUE(b.check_sorting_invariant());
  *it = 7;
  ASSERT_FALSE(b.check_sorting_invariant());
  
}

TEST(test_min_element) {
  BinarySearchTree<int> b;
  ASSERT_TRUE(b.min_element() == b.end());
  b.insert(5);
  auto it = b.min_element();
  ASSERT_TRUE(it != b.end() && *it == 5);
  b.insert(3);
  it = b.min_element();
  ASSERT_TRUE(it != b.end() && *it == 3);
  b.insert(7);
  it = b.min_element();
  ASSERT_TRUE(it != b.end() && *it == 3);
  b.insert(9);
  it = b.min_element();
  ASSERT_TRUE(it != b.end() && *it == 3);
  b.insert(4);
  it = b.min_element();
  ASSERT_TRUE(it != b.end() && *it == 3);
  b.insert(2);
  it = b.min_element();
  ASSERT_TRUE(it != b.end() && *it == 2);
  b.insert(1);
  it = b.min_element();
  ASSERT_TRUE(it != b.end() && *it == 1);
   
}
   
TEST(test_max_element) {
  BinarySearchTree<int> b;
  ASSERT_TRUE(b.max_element() == b.end());
  b.insert(5);
  auto it = b.max_element();
  ASSERT_TRUE(it != b.end() && *it == 5);
  b.insert(7);
  it = b.max_element();
  ASSERT_TRUE(it != b.end() && *it == 7);
  b.insert(3);
  it = b.max_element();
  ASSERT_TRUE(it != b.end() && *it == 7);
  b.insert(2);
  it = b.max_element();
  ASSERT_TRUE(it != b.end() && *it == 7);
  b.insert(6);
  it = b.max_element();
  ASSERT_TRUE(it != b.end() && *it == 7);
  b.insert(20);
  it = b.max_element();
  ASSERT_TRUE(it != b.end() && *it == 20);
  b.insert(18);
  it = b.max_element();
  ASSERT_TRUE(it != b.end() && *it == 20);
  b.insert(100);
  it = b.max_element();
  ASSERT_TRUE(it != b.end() && *it == 100);
}

TEST(test_min_greater_than) {
  BinarySearchTree<int> b;
  ASSERT_TRUE(b.min_greater_than(3) == b.end());
  b.insert(5);
  auto it = b.min_greater_than(3);
  ASSERT_TRUE(it != b.end() && *it == 5);
  it = b.min_greater_than(5);
  ASSERT_TRUE(it == b.end());
  it = b.min_greater_than(7);
  ASSERT_TRUE(it == b.end());
  
  b.insert(7);
  b.insert(1);
  b.insert(12);
  b.insert(10);
  
  it = b.min_greater_than(0);
  ASSERT_TRUE(it != b.end() && *it == 1);
                                          
  it = b.min_greater_than(1);
  ASSERT_TRUE(it != b.end() && *it == 5);
                
  it = b.min_greater_than(5);
  ASSERT_TRUE(it != b.end() && *it == 7);
  it = b.min_greater_than(6);
  ASSERT_TRUE(it != b.end() && *it == 7);
  it = b.min_greater_than(7);
  ASSERT_TRUE(it != b.end() && *it == 10);
  it = b.min_greater_than(10);
  ASSERT_TRUE(it != b.end() && *it == 12);
  it = b.min_greater_than(12);
  ASSERT_TRUE(it == b.end());
  
}


TEST(test_find) {
  BinarySearchTree<int> b;
  ASSERT_TRUE(b.find(3) == b.end());
  b.insert(5);
  ASSERT_TRUE(b.find(3) == b.end());
  ASSERT_TRUE(b.find(4) == b.end());
  ASSERT_TRUE(b.find(5) != b.end() && *b.find(5) == 5);
  
  b.insert(7);
  ASSERT_TRUE(b.find(6) == b.end());
  ASSERT_TRUE(b.find(5) != b.end() && *b.find(5) == 5);
  ASSERT_TRUE(b.find(7) != b.end() && *b.find(7) == 7);
  
  b.insert(6);
  b.insert(12);
  ASSERT_TRUE(b.find(6) != b.end() && *b.find(6) == 6);
  ASSERT_TRUE(b.find(12) != b.end() && *b.find(12) == 12);
   
}

TEST(test_insert) {
  BinarySearchTree<int> b;
  auto it = b.insert(5);
  ASSERT_TRUE(it != b.end() && *it == 5);
  
  it = b.insert(12);
  ASSERT_TRUE(it != b.end() && *it == 12);
  
  it = b.insert(3);
  ASSERT_TRUE(it != b.end() && *it == 3);
}

TEST(test_iterator) {
  BinarySearchTree<int> b;
  ASSERT_TRUE(b.begin() == b.end());
  
  b.insert(5);
  b.insert(3);
  b.insert(7);
  b.insert(2);
  b.insert(4);
  b.insert(8);
  b.insert(6);

  auto it = b.begin();
  ASSERT_TRUE(it != b.end() && *it == 2);
  auto itold = it++;
  ASSERT_TRUE(itold != b.end() && *itold == 2);
  ASSERT_TRUE(it != b.end() && *it == 3);
  
  auto itnew = ++it;
  ASSERT_TRUE(itnew != b.end() && *itnew == 4);
  ASSERT_TRUE(it == itnew);
  ASSERT_TRUE(it == b.find(4));
  
  it++;
  ASSERT_TRUE(it == b.find(5));
  ASSERT_TRUE(it != b.end() && *it == 5);
  
  ++it;
  ASSERT_TRUE(it != b.end() && *it == 6);
  ++it;
  ASSERT_TRUE(it != b.end() && *it == 7);
  ++it;
  ASSERT_TRUE(it != b.end() && *it == 8);
  ++it;
  ASSERT_TRUE(it == b.end());
                            
  BinarySearchTree<std::string> b2;
  b2.insert("test");
  b2.insert("hello");
  b2.insert("good day");
  
  auto its = b2.find("test");
  ASSERT_TRUE(its != b2.end() && its->length() == 4 && *its == string("test"));

  its = b2.find("hello");
  ASSERT_TRUE(its != b2.end() && its->length() == 5);

  its = b2.find("good day");
  ASSERT_TRUE(its != b2.end() && its->length() == 8 && (*its)[0] == 'g');
  
}
  

TEST_MAIN()
