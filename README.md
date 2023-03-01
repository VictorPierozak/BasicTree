# Binary Trees 
This project was made for Algotihms and Data Structer classes.
Project in principle was meant to contain implementation of Red-Black Tree and AVL Tree. Due to similiarities in both structeres type I decided to base them on the one template class that could be used to make other binary trees in the future.

# Class hierachy - short description
There are two base class: one for tree structer, and one for node structer.
* <b>basic_node<typename nodeType, typename nodeValue></b> is class from which other node classes should inherit from to guarantee properly cooperation with tree classes.
  * First template argument is a given node class
  * Second argument is type of value stored in a node (it should has defined <,>, == operators).
  * <i>For example: class Xnode storing integer value should has definition starting as follow: class Xnode: public basic_node<Xnode, int></i>
  
* <b>basic_tree<typename nodeType, typename nodeValue></b>contain essential operation on binary tree: inserting value, fiding values, travelsars, deleting node and rotation, template arguments are the same as in the basic_node.

All other tree and node classes inherit from these two, so there are:
* Red-black tree represented by following classes:
  * RBNode - inherit from basic_node<RBNode, int>
  * RBTree - inherit from basic_tree<RBNode, int>
  
* AVL tree represented by following classes:
  * AVLNode - inherit from basic_node<AVLNode, int>
  * AVLTree  - inherit from basic_tree<AVLNode, int>

* BST tree represented by following classes:
  * BSTNode - inherit from basic_node<BSTNode, int>
  * BSTTree  - inherit from basic_tree<BSTNode, int>

