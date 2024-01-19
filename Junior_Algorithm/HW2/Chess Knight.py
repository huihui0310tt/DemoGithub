# 演算法分析機測 第五題: 洋棋騎士 (Chess Knight)
# 學號 : 10727211
# 姓名 : 林彥輝
# 中原大學資訊工程學系


class Read:
    def __init__(self):
        self.start = None
        self.destination = None

    def ReadInput(self):
        self.start, self.destination = input('Please enter two coordinate (start、end) : ').split()
        if self.start is 0 and self.destination is 0:
            raise Exception('exit')
        else:
            coordinate_start = coordinate(convert(self.start[0]), convert(self.start[1]))
            coordinate_destination = coordinate(convert(self.destination[0]), convert(self.destination[1]))
            return coordinate_start, coordinate_destination


def convert(char):
    if char is '1' or char is 'a':
        return 1
    elif char is '2' or char is "b":
        return 2
    elif char is '3' or char is 'c':
        return 3
    elif char is '4' or char is 'd':
        return 4
    elif char is '5' or char is 'e':
        return 5
    elif char is '6' or char is 'f':
        return 6
    elif char is '7' or char is 'g':
        return 7
    elif char is '8' or char is 'h':
        return 8

    elif char is 1:
        return 'a'
    elif char is 2:
        return 'b'
    elif char is 3:
        return 'c'
    elif char is 4:
        return 'd'
    elif char is 5:
        return 'e'
    elif char is 6:
        return 'f'
    elif char is 7:
        return 'g'
    elif char is 8:
        return 'h'
    else:
        raise Exception('Error type')


class coordinate:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.visited = False
        self.edge = []

    def insert_edge(self, node):
        self.edge.append(node)

    def debug_print_info(self):
        print('(', str(self.x), ',', str(self.y), ')', end='')

    def debug_print_edge(self):
        print('(', str(self.x), ',', str(self.y), ')')
        print(' edge is :', end='')
        for i in self.edge:
            i.debug_print_info()
        print()


###


class Play:
    def __init__(self, start, end):
        self.start = start
        self.end = end
        self.map_coordinate = []
        self.table = []

        for y in range(9):
            temp_map_coordinate = []
            temp_table = []
            for x in range(9):
                if x is 0 or y is 0:
                    temp_map_coordinate.append(None)
                    temp_table.append(None)
                else:
                    temp_map_coordinate.append(coordinate(y, x))
                    temp_table.append(-1)
            self.map_coordinate.append(temp_map_coordinate)
            self.table.append(temp_table)

        for x in range(1, 9):
            for y in range(1, 9):
                link = []
                link.append(self.move_type1(self.map_coordinate[x][y]))
                link.append(self.move_type2(self.map_coordinate[x][y]))
                link.append(self.move_type3(self.map_coordinate[x][y]))
                link.append(self.move_type4(self.map_coordinate[x][y]))
                link.append(self.move_type5(self.map_coordinate[x][y]))
                link.append(self.move_type6(self.map_coordinate[x][y]))
                link.append(self.move_type7(self.map_coordinate[x][y]))
                link.append(self.move_type8(self.map_coordinate[x][y]))

                for i in link:
                    if i is not None:
                        self.map_coordinate[x][y].edge.append(self.map_coordinate[i.x][i.y])

        self.table[start.x][start.y] = 0
        self.play(self.map_coordinate[start.x][start.y])
        self.printfinal()

    def play(self, one_vertex):

        # print('debug : (', str(one_vertex.x), ',', str(one_vertex.y), ')')

        # visited
        one_vertex.visited = True
        one_vertex.edge = self.sort(one_vertex.edge)
        # updated
        for i in one_vertex.edge:
            if self.table[i.x][i.y] > self.table[one_vertex.x][one_vertex.y] + 1 or self.table[i.x][i.y] < 0:
                self.table[i.x][i.y] = self.table[one_vertex.x][one_vertex.y] + 1

        # next recursion
        for i in one_vertex.edge:
            if self.map_coordinate[i.x][i.y].visited is False:
                self.play(self.map_coordinate[i.x][i.y])

    def sort(self, list):  # Insertion Sort
        for i in range(len(list)):
            tempNum = list[i]
            j = i - 1
            while j >= 0 and self.count_distance(tempNum, self.end) < self.count_distance(list[j], self.end):  #
                list[j + 1] = list[j]
                j = j - 1
            list[j + 1] = tempNum
        return list

    def move_up(self, point):
        if point.y is 1:
            raise Exception('Out of map')
        else:
            return coordinate(point.x, point.y - 1)

    def move_down(self, point):
        if point.y is 8:
            raise Exception('Out of map')
        else:
            return coordinate(point.x, point.y + 1)

    def move_left(self, point):
        if point.x is 1:
            raise Exception('Out of map')
        else:
            return coordinate(point.x - 1, point.y)

    def move_right(self, point):
        if point.x is 8:
            raise Exception('Out of map')
        else:
            return coordinate(point.x + 1, point.y)

    def move_type1(self, point):
        # ↑
        # ↑ ←
        try:
            step_1 = self.move_left(point)
            step_2 = self.move_up(step_1)
            step_3 = self.move_up(step_2)
            return step_3
        except:
            return None

    def move_type2(self, point):
        # ↓ ←
        # ↓
        try:
            step_1 = self.move_left(point)
            step_2 = self.move_down(step_1)
            step_3 = self.move_down(step_2)
            return step_3
        except:
            return None

    def move_type3(self, point):
        # ↑
        # ← ←
        try:
            step_1 = self.move_left(point)
            step_2 = self.move_left(step_1)
            step_3 = self.move_up(step_2)
            return step_3
        except:
            return None

    def move_type4(self, point):
        # ← ←
        # ↓
        try:
            step_1 = self.move_left(point)
            step_2 = self.move_left(step_1)
            step_3 = self.move_down(step_2)
            return step_3
        except:
            return None

    def move_type5(self, point):
        #   ↑
        # → ↑
        try:
            step_1 = self.move_right(point)
            step_2 = self.move_up(step_1)
            step_3 = self.move_up(step_2)
            return step_3
        except:
            return None

    def move_type6(self, point):
        # → ↓
        #   ↓
        try:
            step_1 = self.move_right(point)
            step_2 = self.move_down(step_1)
            step_3 = self.move_down(step_2)
            return step_3
        except:
            return None

    def move_type7(self, point):
        #   ↑
        # → →
        try:
            step_1 = self.move_right(point)
            step_2 = self.move_right(step_1)
            step_3 = self.move_up(step_2)
            return step_3
        except:
            return None

    def move_type8(self, point):
        # → →
        #   ↓
        try:
            step_1 = self.move_right(point)
            step_2 = self.move_right(step_1)
            step_3 = self.move_down(step_2)
            return step_3
        except:
            return None

    def count_distance(self, point_1, point_2):

        if point_1.x is None or point_1.y is None:
            return None

        return abs(point_1.x - point_2.x) + abs(point_1.y - point_2.y)

    def printfinal(self):
        name_start = convert(start.x) + str(start.y)
        name_end = convert(end.x) + str(end.y)
        print('From', name_start, 'to', name_end, ', Knight Moves = ', str(self.table[end.x][end.y]))


if __name__ == '__main__':
    try:
        while True:
            read = Read()
            start, end = read.ReadInput()
            Play(start, end)
            print()
    except:
        pass
