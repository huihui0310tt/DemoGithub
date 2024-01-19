# 演算法分析機測 第三題: 霍夫曼碼 (Huffman Codes)
# 學號 : 10727211
# 姓名 : 林彥輝
# 中原大學資訊工程學系

import copy

count = 0


class Read:
    def __init__(self):
        self.n = None
        self.input_list = []

    def ReadInput(self):
        self.n = int(input('Enter item size  n : '))
        if self.n is 0:
            raise Exception('exit')
        print('Enter Each Content\'s character, frequency')
        print('[For example ( a 45 ) ] :')

        for i in (range(self.n)):
            one_character, one_frequency = input().split()
            one_item = Node(one_character, int(one_frequency))
            self.input_list.append(one_item)

        print()
        return self.input_list


class Node:
    def __init__(self, name=None, frequency=None, parent=None, left=None, right=None):
        self.name = name
        self.frequency = frequency  # compare key
        self.codeword = []
        self.parent = parent
        self.left = left
        self.right = right

    def update_single_codeward(self):
        if self.parent is None:
            empty_list = []
            return empty_list
        elif self.parent.left is self:
            temp_list = self.parent.update_single_codeward()
            temp_list.append('0')
            return temp_list
        elif self.parent.right is self:
            temp_list = self.parent.update_single_codeward()
            temp_list.append('1')
            return temp_list
        else:
            print('Error')

        # print('update_single_codeward')

    def print_format(self):
        print('Name is :', str(self.name))
        print('frequency is :', str(self.frequency))
        print('codeword is :', str(self.codeword))
        print()


class Huffman:
    def __init__(self, input_list):
        # print('debug', str(len(input_list)))
        self.monitor_list = copy.copy(input_list)  # monitor all node

        self.huffman_list = copy.copy(self.monitor_list)  # working list
        # print('debug', str(len(self.monitor_list)))
        # print('debug', str(len(self.huffman_list)))
        self.merge()
        self.print_codeward()

    def merge(self):
        while len(self.huffman_list) is not 1:
            # merge
            self.sort()
            temp = Node(frequency=self.huffman_list[0].frequency + self.huffman_list[1].frequency,
                        left=self.huffman_list[0], right=self.huffman_list[1])
            temp.left.parent = temp
            temp.right.parent = temp
            self.huffman_list.pop(0)
            self.huffman_list.pop(0)
            self.huffman_list.append(temp)

        self.update_everynode_codeward()

    def update_everynode_codeward(self):
        # update_single_codeward
        for i in self.monitor_list:
            i.codeword = i.update_single_codeward()

    def sort(self):  # Insertion Sort
        for i in range(len(self.huffman_list)):
            tempNum = self.huffman_list[i]
            j = i - 1
            while j >= 0 and tempNum.frequency < self.huffman_list[j].frequency:
                self.huffman_list[j + 1] = self.huffman_list[j]
                j = j - 1
            self.huffman_list[j + 1] = tempNum

    def print_codeward(self):
        print('Huffman Codes #', str(count))

        for i in self.monitor_list:
            print(str(i.name), '  ', end='')
            for j in i.codeword:
                print(str(j), end='')
            print()
        print()

if __name__ == '__main__':
    while True:
        try:
            count = count + 1
            read = Read()
            huffman = Huffman(read.ReadInput())
        except:
            break
