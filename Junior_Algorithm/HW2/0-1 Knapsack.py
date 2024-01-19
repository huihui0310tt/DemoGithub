# 演算法分析機測 第二題: 0-1 背包問題 (0-1 Knapsack)
# 學號 : 10727211
# 姓名 : 林彥輝
# 中原大學資訊工程學系

# 補救影片 : https://www.youtube.com/watch?v=PkWGsbx0Uxw

import copy


class Read:
    def __init__(self):
        self.w = None
        self.n = None
        self.item_list = []

    def ReadInput(self):
        self.w = int(input('Enter a Knapsack\'s  W: '))
        self.n = int(input('Enter item size  n:'))

        print('Enter Each Content\'s Weight, Value')
        print('[For example ( 1 2 ) ] :')

        self.item_list.append(None)
        for i in (range(self.n)):
            new_item_weight, new_item_value = [int(x) for x in input().split()]
            new_item = Item(str(i + 1), new_item_weight, new_item_value)
            self.item_list.append(new_item)
        print()
        return self.w, self.item_list


class Item:
    def __init__(self, name, weight, value):
        self.name = str(name)
        self.weight = weight
        self.value = value

    def print_info(self):
        print()
        print('item name', str(self.name))
        print('item weight', str(self.weight))
        print('item value', str(self.value))
        print()


class Knapsack:
    def __init__(self, knapsack_size, list_item):
        self.table = []
        self.knapsack_size = knapsack_size
        self.list_item = list_item

        for i in range((len(list_item))):
            temp = []
            for j in range(knapsack_size + 1):
                key = None
                if i is 0 or j is 0:
                    key = 0
                content = []
                temp_2 = [key, content]

                temp.append(temp_2)
            self.table.append(temp)

        self.evaluate()
        self.printfinal()

    def evaluate(self):  # 填表
        # print('evaluate', str(max_i), str(max_j))
        # self.table[i][j][0] = 'Here'
        for i in range(1, len(self.table)):
            for j in range(1, len(self.table[i])):
                if self.list_item[i].weight > j:
                    self.table[i][j][0] = copy.deepcopy(self.table[i - 1][j][0])
                    self.table[i][j][1] = copy.deepcopy(self.table[i - 1][j][1])
                else:
                    if self.table[i - 1][j][0] >= self.table[i - 1][j - self.list_item[i].weight][0] + self.list_item[i].value:
                        self.table[i][j][0] = copy.deepcopy(self.table[i - 1][j][0])
                        self.table[i][j][1] = copy.deepcopy(self.table[i - 1][j][1])
                    else:
                        self.table[i][j][0] = copy.deepcopy(
                            self.table[i - 1][j - self.list_item[i].weight][0] + self.list_item[i].value)
                        self.table[i][j][1] = copy.deepcopy(self.table[i - 1][j - self.list_item[i].weight][1])
                        self.table[i][j][1].append(self.list_item[i].name)
                # self.debug_printtable()

    def printfinal(self):
        print('Total Value = ', str(self.table[-1][-1][0]))

        print('Items ', end='')
        for i in range(len(self.table[-1][-1][1])):
            if i is 0:
                print(self.table[-1][-1][1][i], end='')
            else:
                print(', ', self.table[-1][-1][1][i], end='')

        print()

    def debug_printtable(self):
        for i in self.table:
            for j in i:
                print(j[0], end='   ')
            print()


if __name__ == '__main__':
    read = Read()
    knapsack_size, list_item = read.ReadInput()

    knapsack = Knapsack(knapsack_size, list_item)
