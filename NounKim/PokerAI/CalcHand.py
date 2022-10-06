from Bot.ReinforceStrategy.PokerOddsCalculator.table import HoldemTable
import Bot.ReinforceStrategy.PokerOddsCalculator.utils as util

import numpy as np
import itertools as it
import pickle as pk




ht = HoldemTable(num_players=2, deck_type='full')

num = ["2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"]
items = [num, num]
#print(list(it.combinations(num, 2)))
#list_169 = list(it.product(*items))
all_list = []
list_78 = list(it.combinations(num, 2))

for item in num:
    list_78.append((item, item))

all_list = list_78





