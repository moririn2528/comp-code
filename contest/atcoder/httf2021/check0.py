import os
import optuna
import numpy as np
import matplotlib.pyplot as plt
import random

os.system("copy /Y \"C:\\Users\\stran\\Desktop\\programming\\c++\\comp\\a.exe\" aByPython.exe")
final_score=0
final_arg=""
check_input=50
input_size=500

def check(arg_str,is_print,offset):
    ave_score=0
    for i in range(offset,offset+check_input):
        cmd_str="cargo run --release --bin tester aByPython.exe "
        cmd_str+=arg_str+" < in/"
        cmd_str+=str(i).zfill(4)+".txt > out.txt 2>err.txt"
        os.system(cmd_str)
        f=open('err.txt', 'r')
        data=f.read().split('\n')
        flag=False
        for line in data:
            temp=line.split(' ')
            if temp[0]=="Score" and len(temp)>=2:
                ave_score+=int(temp[2])
                flag=True
        assert flag, "no score"
    ave_score/=check_input
    if is_print:
        scores.sort()
        print(scores)
        plt.xticks(np.arange(1500, 2500, 100))
        plt.hist(scores,bins=20,alpha=0.5,ec='navy',range=(1500,2500))
        plt.savefig("fig.png")
        plt.show()
    return ave_score

def objective(trial):
    global final_score
    global final_arg
    init_member_ability=trial.suggest_uniform("init_member_ability", 0, 30)
    task_fast_cost=trial.suggest_uniform("task_fast_cost", 0, 5)
    diff=trial.suggest_uniform("diff", 0, 1)
    expect_th=trial.suggest_uniform("expect_th", 0, 20)
    task_rnd_init_per=trial.suggest_uniform("task_rnd_init_per", 0, 1)
    task_rnd_lim_day=trial.suggest_uniform("task_rnd_lim_day", 0, 2000)
    arg_str=str(init_member_ability)+" "+str(task_fast_cost)+" "+str(diff)
    arg_str+=" "+str(expect_th)
    arg_str+=" "+str(task_rnd_init_per)+" "+str(task_rnd_lim_day)
    score=check(arg_str,False,random.randint(0,input_size-check_input))
    if final_score<score:
        final_score=score
        final_arg=arg_str
    print("score: {}".format(score))
    return -score

study=optuna.create_study()
study.optimize(objective, n_trials=200)
print(study.best_params)
check(final_arg,True,0)