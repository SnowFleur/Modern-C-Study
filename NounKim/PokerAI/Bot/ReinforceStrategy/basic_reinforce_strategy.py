
TurnDic = {"preflop":0, "flop":5, "turn":10, "river":15}

class Node:
    def __init__(self):
        
        poker_fold = 0
        poker_call = 1
        poker_raise = 2
        
        user_name = ""

        user_choise = [poker_fold, poker_call, poker_raise]

        user_money = 0
        user_stake = 0
        total_stake = 0
        pass





# 형식 저장 {"CCCRFR" : {"20.3, 60.5"  : [{21 : "36_27_4_7.2,3.4,6.6..."}, {}, {},...]}, {}, {}, {}...}     
# 걸린 돈/전체 판돈 기준 소수점 2번째 자리까지

class reinforce_learning_20220919:
    def __init__(self):
        pass
    
    
    def Bet_Interpretation(self, RootNode): # 매 베팅 라운드마다 앞선 상대방의 결정을 모아 어떤 전략을 행할지 결정
        pass

    def Strategy_Dicision(self): # 총 4개의 전략이 있음. Fold, Call. Raise, 균형 전략이 있다.
        pass

    def Indicator_Interpretation(self): # 몬테카를로 시뮬레이션을 통한 추측. 전략에 따라 분석 지표가 달라짐.
        pass

    def Results_Analysis(self): # 결과를 분석하고 베팅 해석(Bet_Interpretation)과 지표 해석(Indicator_Interpretation)에 영향을 준다.
        pass