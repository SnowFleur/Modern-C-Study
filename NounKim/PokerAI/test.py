from Bot.ReinforceStrategy.PokerOddsCalculator import table

ht = table.HoldemTable(num_players = 6, deck_type = 'full')
ht.add_to_hand(1, ['TD', 'TS'])
ht.next_round()
ht.simulate()
print(ht.simulate())
print("sss \n")
print(ht.view_table())
