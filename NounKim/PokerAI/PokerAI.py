##from dependencies import pypokerengine as pk
from pypokerengine.api.game import setup_config, start_poker
from Bot.fishplayer import FishPlayer
from Bot.consoleplayer import ConsolePlayer
from Bot.randomplayer import RandomPlayer
from Bot.honestplayer import HonestPlayer
from Bot.reinforceplayer import ReinforcePlayer

config = setup_config(max_round=1, initial_stack=1000, small_blind_amount=20)

config.register_player(name="Smart1", algorithm=ReinforcePlayer())
config.register_player(name="Smart2", algorithm=ReinforcePlayer())

config.register_player(name="Random0", algorithm=RandomPlayer())
config.register_player(name="Random1", algorithm=RandomPlayer())

config.register_player(name="Honest0", algorithm=HonestPlayer())
config.register_player(name="Honest1", algorithm=HonestPlayer())

game_result = start_poker(config, verbose=1)

