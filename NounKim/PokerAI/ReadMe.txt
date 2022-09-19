몬테카를로 CFR(Counterfactual Regret Minimization) 를 기반으로 한 포커 AI를 제작할 예정. 현재 https://github.com/johnsoong216/PokerOddsCalc.git 과 pypokerengine 을 기반으로 작성 중

reinforceplayer.py 에 몬테카를로 CFR(Counterfactual Regret Minimization)  적용 예정.

2022.09.16 현재 몬테카를로-부정적 추측 승률 계산 시뮬레이션만 적용되어 있음.

---------------------------------------------------------

터미널에서

pip install -r requirement.txt
python PokerAI.py > log.txt  실행시 로그 생성 가능

--------------------------------------------------------

PokerAI.py 에서
config = setup_config(max_round=1, initial_stack=1000, small_blind_amount=20)

max_round : 포커를 진행할 라운드  
initial_stack: 플레이어가 가진 칩의 양
small_blind_amount: 스몰 블라인드가 내야할 칩의 개수

--------------------------------------------------------------

알고리즘 설명: 2022 09 19 기준

베팅 해석(상대방이 콜을 했는지, 폴드를 했는지 레이즈를 했다면 얼마나 했는지에 따라 전략 결정)
전략 결정(Fold 전략, Call 전략, Raise 전략, 균형 전략이 있음)
지표 해석(몬테카를로 시뮬레이션을 통한 긍정적, 부정적 승률 분석, 전략에 따라 분석 지표가 달라짐.)
결과 분석 후 반영(강화학습, 베팅 해석과 지표 해석에 영향을 준다.)

