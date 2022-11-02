import datetime
import random

from pypokerengine.players import BasePokerPlayer
from .ReinforceStrategy.PokerOddsCalculator.table import HoldemTable


#from joblib import Parallel, delayed
#import multiprocessing

TurnDic = {"preflop":30, "flop":35, "turn":40, "river":45}
Simulation_Bios = 0 #최소 0


class ReinforcePlayer(BasePokerPlayer):

    def declare_action(self, valid_actions, hole_card, round_state):


        Diversification = 1 # 시뮬레이션 변수 부여 횟수
        Winrate = 0
        CommunityExist = False

        reverse_card1 = self.reverse_card(hole_card[0])
        reverse_card2 = self.reverse_card(hole_card[1])
        
        if round_state['community_card'] != []:
            reverse_community_cards = [self.reverse_card(rev_com_card) for rev_com_card in  round_state['community_card']]
            CommunityExist = True   

        #start = datetime.datetime.now()
        for i in range(Diversification):

            ht = HoldemTable(num_players=self.get_number_of_players(round_state), deck_type='full')
            ht.add_to_hand(1, [reverse_card1, reverse_card2])
            if(CommunityExist):
                ht.add_to_community(reverse_community_cards)
            
            #Simulation_Bios = 추측의 강도, negative = 내 입장에서 긍정적 추측(상대의 패가 나쁘게 나옴)인지 부정적 추측(상대의 패가 좋게 나옴)인지
            ht.next_round(bios = Simulation_Bios, negative=True)
            SimulationResult = ht.simulate(num_scenarios=150000)
            #print("SimulationResult['Player 1 Win']: ", SimulationResult['Player 1 Win'])
            Winrate += SimulationResult['Player 1 Win']
        #end = datetime.datetime.now()
        #print("걸린 시간: ", end-start)

        Winrate /= Diversification
        #print("Total: ", Winrate)

        WinrateBios = self.get_turn_bios(round_state)

        if Winrate < WinrateBios : action = valid_actions[0] #fold
        elif Winrate >= WinrateBios: #raise
            action = valid_actions[2]
            action['amount'] = valid_actions[2]["amount"]["min"]
            if action['amount'] == -1 or random.randrange(0,2) == 1:
                action = valid_actions[1]
        else: action = valid_actions[1] # call
        
        # if round_state['street'] != "preflop":
        #     print("Players_hand: ", ht.view_hand())

        return action['action'], action['amount']

    def receive_game_start_message(self, game_info):
        pass

    def receive_round_start_message(self, round_count, hole_card, seats):
        pass

    def receive_street_start_message(self, street, round_state):
        pass

    def receive_game_update_message(self, action, round_state):
        pass

    def receive_round_result_message(self, winners, hand_info, round_state):
        pass

    def get_number_of_players(self, round_state):
        number = len([player["name"] for player in round_state["seats"] if player['state'] != 'folded'])
        return number


    def reverse_card(self, card):
        reverse_card = card[::-1]
        return reverse_card


    def get_turn_bios(self, round_state):
        street = round_state["street"]
        return TurnDic[street]

    def TypeSimulate(self, ht, Simulation_Bios ):
        ht.next_round(Simulation_Bios, negative=True)
        SimulationResult = ht.simulate(num_scenarios=100)
        print(SimulationResult['Player 1 Win'])
        Winrate += SimulationResult['Player 1 Win']
