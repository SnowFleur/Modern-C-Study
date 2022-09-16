from pypokerengine.api.game import setup_config, start_poker
from fishplayer import FishPlayer
from consoleplayer import ConsolePlayer
from randomplayer import RandomPlayer
from honestplayer import HonestPlayer

config = setup_config(max_round=100, initial_stack=1000, small_blind_amount=20)
config.register_player(name="Hogu1", algorithm=FishPlayer())
config.register_player(name="Hogu2", algorithm=FishPlayer())
config.register_player(name="Hogu3", algorithm=FishPlayer())
config.register_player(name="Hogu4", algorithm=FishPlayer())
config.register_player(name="Random1", algorithm=RandomPlayer())
config.register_player(name="Random2", algorithm=RandomPlayer())
config.register_player(name="Random3", algorithm=RandomPlayer())
config.register_player(name="Random4", algorithm=RandomPlayer())
config.register_player(name="Random5", algorithm=RandomPlayer())
config.register_player(name="Honest1", algorithm=HonestPlayer())
game_result = start_poker(config, verbose=1)
