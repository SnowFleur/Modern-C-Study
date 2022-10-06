class Node:
    def __init__(self, node, data):
        
        self.poker_fold = 0
        self.poker_call = 1
        self.poker_raise = 2
        
        self.user_name = ''

        self.user_choise = None

        self.user_money = 0 #money + stake = 라운드 시작할 때 가지고 있었던 돈
        self.user_stake = 0
        self.total_stake = 0
        
        self.prev_node = None
        self.next_node = []

    def append_node(self, prev_node, data):
        self.prev_node = prev_node
        prev_node.next_node.append(self)
        self.user_name = data['name']
        self.user_choise = data['choise']
        self.user_money = data['user_money']
        self.user_stake = data['user_stake']
        self.total_stake = prev_node.total_stake + self.user_stake
