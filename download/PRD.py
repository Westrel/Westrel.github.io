# PRD类
# 使暴击的随机更看脸
import random



class CRIT(object):
    crit_rate = 0

    def __init__(self, rate=0):
        self.setCritRate(rate)
        return

    def setCritRate(self, rate):
        self.crit_rate = rate
        return rate
    
    def isAttackCrit(self, rate):
        rad = random.random()
        if rad<=rate:
            return True
        else:
            return False

# P(n)=p
class NOMALCRIT(CRIT):
    crit_rate = 0

    def __init__(self, rate=0):
        super().__init__(rate)

    def setCritRate(self, rate):
        self.crit_rate = rate
        return rate
    
    def isAttackCrit(self):
        return super().isAttackCrit(self.crit_rate)

# P(n)=n*C
class PRD(CRIT):
    intRateBasicC = {}
    panel_crit_rate = 0
    basic_crit_rate = 0
    last = 1
    current_rate = last*basic_crit_rate

    def __init__(self, rate=0):
        super().__init__(rate)
        self.calC()
        self.setCritRate(rate)
        return

    def curP(self, b_r):
        if b_r>=1:
            return 1
        elif b_r<=0:
            return 0
        n_max = 1/b_r
        if type(n_max) is not int:
            n_max = int(n_max) + 1
        else:
            pass
        assert(type(n_max) is int)
        fore_success_p = 0
        exp_p = 0
        cur_p = 0
        for i in range(n_max):
            cur_p = min(1, i * b_r) * (1-fore_success_p)
            fore_success_p += cur_p
            exp_p += i * cur_p
        return 1/exp_p

    def curC(self, p_r):
        max_r = p_r
        min_r = 0
        mid_r = (max_r + min_r)/2.
        p_last = 1.
        while 1:
            p_now = self.curP(mid_r)
            if abs(p_now-p_last)<=0:
                return mid_r
            if p_now>p_r:
                max_r = mid_r
            else:
                min_r = mid_r
            mid_r = (max_r + min_r)/2.
            p_last = p_now
        
    def calC(self):
        for i in range(101):
            self.intRateBasicC[i/100] = self.curC(i/100)
        return
    
    def setCritRate(self, rate):
        self.panel_crit_rate = rate
        if self.panel_crit_rate in self.intRateBasicC:
            self.basic_crit_rate = self.intRateBasicC[self.panel_crit_rate]
        else:
            self.basic_crit_rate = self.curC(rate)
        self.current_rate = self.last*self.basic_crit_rate
        return self.panel_crit_rate, self.basic_crit_rate

    def isAttackCrit(self):
        res = super().isAttackCrit(self.current_rate)
        if res:
            self.last = 1
        else:
            self.last += 1
        self.current_rate = self.basic_crit_rate*self.last
        return res



if __name__ == "__main__":
    prd = PRD()
    attack = NOMALCRIT()
    crit_rate = 0.2
    basic_attack = 1
    crit_mul_rate = 2.0

    atk_cnt = 10000
    prd_hurt = 0
    att_hurt = 0

    prd.setCritRate(crit_rate)
    attack.setCritRate(crit_rate)

    prd_crit = []
    att_crit = []

    for i in range(atk_cnt):
        if prd.isAttackCrit():
            prd_crit.append(i)
            prd_hurt += basic_attack*crit_mul_rate
        else:
            prd_hurt += basic_attack
        if attack.isAttackCrit():
            att_crit.append(i)
            att_hurt += basic_attack*crit_mul_rate
        else:
            att_hurt += basic_attack
    
    print("PRD mode cause ", prd_hurt, " damage.")
    print("Nomal mode cause: ", att_hurt, " damage.")

    print("PRD mode crit position:", prd_crit[:50], "...")
    print("Nomal mode crit position:", att_crit[:50], "...")

    prd_ins = {}
    att_ins = {}
    for i in range(len(prd_crit)-1):
        ins = prd_crit[i+1]-prd_crit[i]
        if ins in prd_ins:
            prd_ins[ins] += 1
        else:
            prd_ins[ins] = 1
    for i in range(len(att_crit)-1):
        ins = att_crit[i+1]-att_crit[i]
        if ins in att_ins:
            att_ins[ins] += 1
        else:
            att_ins[ins] = 1
    print("PRD mode ins: ", prd_ins)
    print("Nomal mode ins: ", att_ins)

    import matplotlib.pyplot as plt
    prd_keys = list(prd_ins.keys())
    prd_values = list(prd_ins.values())
    att_keys = list(att_ins.keys())
    att_values = list(att_ins.values())

    plt.subplot(3, 1, 1)
    plt.bar(prd_keys, prd_values)
    plt.ylabel("Count")
    plt.xlabel("Every two crits instance")
    plt.title("PRD mode")

    plt.subplot(3, 1, 3)
    plt.bar(att_keys, att_values)
    plt.ylabel("Count")
    plt.xlabel("Every two crits instance")
    plt.title("Nomal mode")

    plt.show()