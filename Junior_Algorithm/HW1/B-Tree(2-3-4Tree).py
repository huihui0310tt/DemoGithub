# 演算法分析機測 第四題: B-Tree( 2-3-4-Tree)
# 學號 : 10727211 / 10727240 / 10727244
# 姓名 :  林彥輝   /  賴卷狄   /   陳佳欣
# 中原大學資訊工程學系

class Node:
    def __init__(self, parent=None, children_one=None, children_two=None, children_three=None, children_four=None,
                 newkey=None):
        # initialize parent / child links
        self.parent = parent

        self.children = []
        if children_one is not None:
            self.children.append(children_one)
            if children_two is not None:
                self.children.append(children_two)
                if children_three is not None:
                    self.children.append(children_three)
                    if children_four is not None:
                        self.children.append(children_four)

        self.key = []
        if newkey is not None:
            self.key.append(newkey)

    def num_of_key(self):
        return len(self.key)

    def num_of_children(self):
        return len(self.children)

    def split_root(self, onekey=None):
        if self.num_of_children() is 0:
            self.children.append(Node(newkey=self.key[0], parent=self))
            self.children.append(Node(newkey=self.key[2], parent=self))
            self.key.pop(2)
            self.key.pop(0)
            if onekey is not None:
                if self.children[0].key[0] > onekey:
                    self.children[0].insert_empty_key(onekey)
                else:
                    self.children[1].insert_empty_key(onekey)
        else:
            self_children_0 = self.children[0]
            self_children_1 = self.children[1]
            self_children_2 = self.children[2]
            self_children_3 = self.children[3]
            left = Node(newkey=self.key[0], parent=self, children_one=self_children_0, children_two=self_children_1)
            right = Node(newkey=self.key[2], parent=self, children_one=self_children_2, children_two=self_children_3)
            self.children[0].parent = left
            self.children[1].parent = left
            self.children[2].parent = right
            self.children[3].parent = right
            self.children.clear()

            self.children.append(left)
            self.children.append(right)
            self.key.pop(2)
            self.key.pop(0)
            if onekey is not None:
                if self.children[0].key[0] > onekey:
                    self.children[0].insert_empty_key(onekey)
                else:
                    self.children[1].insert_empty_key(onekey)

    def split(self, onekey=None):
        if self.parent is None:
            self.split_root(onekey)
        else:
            # push the middle node to parent
            if self.parent.num_of_key() < 3:
                self.parent.insert_empty_key(self.key[1])
            else:
                self.parent.split(self.key[1])

            self_index_2_key = self.key[2]
            self_parent = self.parent
            new_right = Node(parent=self_parent, newkey=self_index_2_key)
            if self.num_of_children() > 0:
                new_right.children.append(self.children[2])
                new_right.children.append(self.children[3])
                self.children[2].parent = new_right
                self.children[3].parent = new_right
                self.children.pop()
                self.children.pop()

            if self is self.parent.children[0]:
                self.parent.children.insert(1, new_right)  # index
            elif self is self.parent.children[1]:
                self.parent.children.insert(2, new_right)  # index
            elif self is self.parent.children[2]:
                self.parent.children.insert(3, new_right)  # index
            elif self is self.parent.children[3]:
                print("error")
            else:
                print("error")

            remain_key_1 = self.key[1]
            self.key.pop(2)
            self.key.pop(1)

            if onekey is not None:
                if onekey < remain_key_1:
                    self.insert_empty_key(onekey)
                else:
                    new_right.insert_empty_key(onekey)

    def insert_empty_key(self, a):
        self.key.append(a)
        self.key.sort()

    def search(self, newkey):
        if self.num_of_children() is 0:  # leaf
            if self.num_of_key() < 3:
                self.insert_empty_key(newkey)
            else:
                self.split(newkey)
        else:
            if self.num_of_children() is 4:
                self.split()

                if self.parent is None:
                    self.search(newkey)
                else:
                    self.parent.search(newkey)
            else:
                num_key = self.num_of_key()
                if num_key is 1:
                    if newkey < self.key[0]:
                        self.children[0].search(newkey)
                    else:
                        self.children[1].search(newkey)
                elif num_key is 2:
                    if newkey < self.key[0]:
                        self.children[0].search(newkey)
                    elif newkey < self.key[1]:
                        self.children[1].search(newkey)
                    else:
                        self.children[2].search(newkey)
                elif num_key is 3:
                    if newkey < self.key[0]:
                        self.children[0].search(newkey)
                    elif newkey < self.key[1]:
                        self.children[1].search(newkey)
                    elif newkey < self.key[2]:
                        self.children[2].search(newkey)
                    else:
                        self.children[3].search(newkey)

    def print_key(self):
        num = self.num_of_key()
        if num is 0:
            print("(None)")
        elif num is 1:
            print("(", end='')
            print(self.key[0], end='')
            print(")", end='')
        elif num is 2:
            print("(", end='')
            print(self.key[0], end='')
            print(",", end='')
            print(self.key[1], end='')
            print(")", end='')
        elif num is 3:
            print("(", end='')
            print(self.key[0], end='')
            print(",", end='')
            print(self.key[1], end='')
            print(",", end='')
            print(self.key[2], end='')
            print(")", end='')

    def preorder(self):
        self.print_key()
        child_num = self.num_of_children()
        if child_num >= 1:
            self.children[0].preorder()
        if child_num >= 2:
            self.children[1].preorder()
        if child_num >= 3:
            self.children[2].preorder()
        if child_num >= 4:
            self.children[3].preorder()

    def postorder(self):
        child_num = self.num_of_children()
        if child_num >= 1:
            self.children[0].postorder()
        if child_num >= 2:
            self.children[1].postorder()
        if child_num >= 3:
            self.children[2].postorder()
        if child_num >= 4:
            self.children[3].postorder()
        self.print_key()


class TwoThreeTree:
    def __init__(self):
        self.root = Node()
        print("example input1 : 3 7 4 9 10 0 5 6 8 2 1")
        print("example input2 :  1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21")
        a = [int(x) for x in input("Please Enter list of Number :").split()]
        for onekey in a:
            self.root.search(onekey)

        print("2-3-4 Tree (Preorder):")
        self.root.preorder()
        print()
        print("2-3-4 Tree (Postorder):")
        self.root.postorder()
        print()


if __name__ == '__main__':  # main()

    tree = TwoThreeTree()
