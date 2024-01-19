# 演算法分析機測 第四題: 單一源最短路徑 (Single-Source Shortest Paths)
# 學號 : 10727211
# 姓名 : 林彥輝
# 中原大學資訊工程學系

import copy


# 參考複習網站 : https://www.youtube.com/watch?v=_lHSawdgXpI

class Read:
    def __init__(self):
        self.n = None
        self.edge_size = None
        self.source_vertex = None
        self.diagram = []

    def ReadInput(self):
        self.n = int(input('Enter vertex size  n : '))
        if self.n is 0:
            raise Exception('exit')

        self.edge_size = int(input('Enter vertex edge  n : '))
        self.source_vertex = int(input('Enter source vertex name : '))
        self.diagram.append(None)  # default
        print('Start Enter ', str(self.edge_size), ' line\'s Edge Weight :')

        for i in range(1, self.n + 1):  # init
            self.diagram.append(Vertex(i))

        for i in (range(self.edge_size)):
            one_begin, one_end, one_weight = input().split()
            self.diagram[int(one_begin)].insert_edge(int(one_end), int(one_weight))

        return self.source_vertex, self.diagram


class Vertex:
    def __init__(self, name):
        self.name = name
        self.edge = []  # edge[0] = node_name,  edge[1] = node_weight
        self.visited = False

    def insert_edge(self, node_name, node_weight):
        temp = [node_name, node_weight]
        self.edge.append(temp)

    def debug_print_vertex_info(self):
        print('name is ', str(self.name))
        print('edge is ', str(self.edge))
        print('visit is ', str(self.visited))


class Dijkstra:
    def __init__(self, source_vertex, diagram):

        self.table = []
        self.diagram = diagram
        self.source_vertex = source_vertex

        for i in range(len(diagram)):
            if i is 0:
                self.table.append(None)
            else:
                if i is self.source_vertex:
                    self.table.append(0)
                else:
                    self.table.append(-1)
        self.running(self.diagram[self.source_vertex])
        self.printfinal()

    def running(self, one_vertex):

        # visited
        one_vertex.visited = True
        one_vertex.edge = self.sort(one_vertex.edge)
        # updated
        for i in one_vertex.edge:
            if self.table[i[0]] > self.table[one_vertex.name] + i[1] or self.table[i[0]] < 0:
                self.table[i[0]] = self.table[one_vertex.name] + i[1]

        # next recursion
        for i in one_vertex.edge:
            if self.diagram[i[0]].visited is False:
                self.running(self.diagram[i[0]])

    def sort(self, list):  # Insertion Sort
        for i in range(len(list)):
            tempNum = list[i]
            j = i - 1
            while j >= 0 and tempNum[1] < list[j][1]:
                list[j + 1] = list[j]
                j = j - 1
            list[j + 1] = tempNum
        return list

    def printfinal(self):
        for i in range(len(self.table)):
            if i is 0:
                pass
            else:
                if i is self.source_vertex:
                    pass
                else:
                    if self.table[i] > 0:
                        print(str(self.source_vertex), ' to ', str(i), ' = ', str(self.table[i]))
                    else:
                        print(str(self.source_vertex), ' to ', str(i), ' = ', 'infinite')
        print()


if __name__ == '__main__':
    try:
        while True:
            read = Read()
            source_vertex, diagram = read.ReadInput()
            node = Dijkstra(source_vertex, diagram)
            print()
    except:
        print('exit')
        pass
