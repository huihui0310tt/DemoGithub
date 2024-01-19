# 演算法分析機測 第一題: 雙子星塔 (Twin Towers)
# 學號 : 10727211
# 姓名 : 林彥輝
# 中原大學資訊工程學系

import copy


class read:
    def __init__(self):

        self.tower_1 = []
        self.tower_2 = []

    def read_input(self):
        leng = [int(x) for x in input('Please enter tower1 and tower2 len : ').split()]
        # self.len_2 = int(input())

        if leng[0] is 0 and leng[1] is 0:
            raise Exception('exit')
        else:
            self.tower_1 = [int(x) for x in input("Please Enter list of Number :").split()]
            self.tower_2 = [int(x) for x in input("Please Enter list of Number :").split()]

        return self.tower_1, self.tower_2


class twin_towers:
    def __init__(self, tower1, tower2, count):
        output = self.running(copy.deepcopy(tower1), copy.deepcopy(tower2))
        self.printfinal(count, output)

    def running(self, tower1, tower2):

        if len(tower1) is 0 or len(tower2) is 0:
            return 0

        tower1_not_take = copy.deepcopy(tower1)
        tower1_take = copy.deepcopy(tower1)
        tower2_not_take = copy.deepcopy(tower2)
        tower2_take = copy.deepcopy(tower2)

        have_same = 0

        # not take
        tower1_not_take.pop(0)
        path1 = self.running(tower1_not_take, tower2_not_take)
        # take
        while True:
            if len(tower2_take) is 0:
                break
            elif tower1_take[0] is not tower2_take[0]:
                tower2_take.pop(0)
            elif tower1_take[0] is tower2_take[0]:
                tower1_take.pop(0)
                tower2_take.pop(0)
                have_same = 1
                break
        path2 = self.running(tower1_take, tower2_take) + have_same

        if path2 > path1:
            return path2
        else:
            return path1

    def printfinal(self, count, output):
        print('Twin Towers #', str(count))
        print('Number of Tiles: ', str(output))


if __name__ == '__main__':
    count = 0
    while True:
        try:
            count = count + 1
            read_main = read()
            tower_1, tower_2 = read_main.read_input()
            towers = twin_towers(tower_1, tower_2, count)
            print()
        except:
            break
