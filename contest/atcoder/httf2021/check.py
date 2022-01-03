import os
import optuna
import numpy as np
import matplotlib.pyplot as plt

N1=100
N2=30
RANGE1=(0,50)
RANGE2=(50,300)
result=[]

os.system("copy /Y \"C:\\Users\\stran\\Desktop\\programming\\c++\\comp\\a.exe\" aByPython.exe")

def check(arg_str,is_print,input_range):
    scores=[]
    ave_score=0
    n=input_range[1]-input_range[0]
    for i in range(input_range[0],input_range[1]):
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
                scores.append(int(temp[2]))
        assert flag, "no score"
    ave_score/=n
    if is_print:
        scores.sort()
        print(scores)
        plt.xticks(np.arange(1500, 2500, 100))
        plt.hist(scores,bins=20,alpha=0.5,ec='navy',range=(1500,2500))
        plt.savefig("fig.png")
        plt.show()
    return ave_score

def objective(trial):
    global result
    init_member_ability=trial.suggest_uniform("init_member_ability", 0, 30)
    task_fast_cost1=trial.suggest_uniform("task_fast_cost1", 0, 5)
    task_fast_cost2=trial.suggest_uniform("task_fast_cost2", 0, 5)
    diff_a=trial.suggest_uniform("diff_a", 0, 2)
    diff_b=trial.suggest_uniform("diff_b", 0, 0.3)
    diff_c=trial.suggest_uniform("diff_c", 0, 1)
    expect_th=trial.suggest_uniform("expect_th", 0, 20)
    task_rnd_init_per=trial.suggest_uniform("task_rnd_init_per", 0, 1)
    task_rnd_lim_day=trial.suggest_uniform("task_rnd_lim_day", 0, 2000)
    arg_str=str(init_member_ability)+" "+str(task_fast_cost1)+" "+str(task_fast_cost2)
    arg_str+=" "+str(diff_a)+" "+str(diff_b)+" "+str(diff_c)
    arg_str+=" "+str(expect_th)
    arg_str+=" "+str(task_rnd_init_per)+" "+str(task_rnd_lim_day)
    score=check(arg_str,False,RANGE1)
    result.append((arg_str,score))
    print("score: {}".format(score))
    return -score

study=optuna.create_study()
study.optimize(objective, n_trials=N1)
print(study.best_params)
result.sort(key=lambda x: -x[1])
result2=[]
for i in range(0,N2):
    print("final round {}/{}".format(i+1,N2))
    score=check(result[i][0],False,RANGE2)
    result2.append((result[i][0],score))
    
result2.sort(key=lambda x: -x[1])
print("arg: "+result2[0][0])
print("score: {}".format(result2[0][1]))
check(result2[0][0],True,RANGE2)