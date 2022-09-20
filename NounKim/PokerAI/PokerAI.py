##from dependencies import pypokerengine as pk
from pypokerengine.api.game import setup_config, start_poker
from Bot.fishplayer import FishPlayer 
from Bot.consoleplayer import ConsolePlayer
from Bot.randomplayer import RandomPlayer
from Bot.honestplayer import HonestPlayer
from Bot.reinforceplayer import ReinforcePlayer


# max_round : 포커를 진행할 라운드  
# initial_stack: 플레이어가 가진 칩의 양
# small_blind_amount: 스몰 블라인드가 내야할 칩의 개수


readConfig = open("config.txt", 'r')

max_round_int = int(readConfig.readline().split('=')[1])
initial_stack_int = int(readConfig.readline().split('=')[1])
small_blind_amount_int = int(readConfig.readline().split('=')[1])
#Create_ConsloePlayer = int(readConfig.readline().split('=')[1])
Create_FishPlayer = int(readConfig.readline().split('=')[1])
Create_RandomPlayer = int(readConfig.readline().split('=')[1])
Create_HonestPlayer = int(readConfig.readline().split('=')[1])
Create_ReinforcePlayer = int(readConfig.readline().split('=')[1])

readConfig.close()



config = setup_config(max_round=max_round_int, initial_stack=initial_stack_int, small_blind_amount=small_blind_amount_int)

# 플레이어 등록. 임포트 된 인공지능 알고리즘을 사용하여 이름과 함께 넣으면 포커봇 생성.
# 작성 가능한 포커봇 종류:
#  
# FishPlayer : 무조건 콜을 외치는 포커봇 
# ConsolePlayer: 직접 조종 가능한 포커봇 - 현재 config에서 지원하지 않음.
# RandomPlayer: 랜덤하게 콜, 폴드, 레이즈를 외치고 레이즈 양을 조절하는 포커봇
# HonestPlayer: 승률을 계산해서 콜을 외치는 포커봇
# ReinforcePlayer: 다른 것보다는 좀 더 똘똘한 포커봇

for i in range(Create_FishPlayer):
    create_name = "Fish"+str(i)
    config.register_player(name=create_name, algorithm=FishPlayer())

for i in range(Create_RandomPlayer):
    create_name = "Random"+str(i)
    config.register_player(name=create_name, algorithm=RandomPlayer())

for i in range(Create_HonestPlayer):
    create_name = "Honest"+str(i)
    config.register_player(name=create_name, algorithm=HonestPlayer())

for i in range(Create_ReinforcePlayer):
    create_name = "Reinforce"+str(i)
    config.register_player(name=create_name, algorithm=ReinforcePlayer())


# config.register_player(name="Smart1", algorithm=ReinforcePlayer())
# config.register_player(name="Smart2", algorithm=ReinforcePlayer())

# config.register_player(name="Random0", algorithm=RandomPlayer())
# config.register_player(name="Random1", algorithm=RandomPlayer())

# config.register_player(name="Honest0", algorithm=HonestPlayer())
# config.register_player(name="Honest1", algorithm=HonestPlayer())

game_result = start_poker(config, verbose=1)

