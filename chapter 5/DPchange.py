# -*- coding: utf-8 -*-
"""
Spyder Editor

This temporary script file is located here:
/home/jordi/.spyder2/.temp.py
"""

def DPChange(money, coins):
    MinNumCoins = [0]
    for m in range(1,money+1):
        MinNumCoins.append(999999)
        for i in range(0, len(coins)):
            if m >= coins[i]:
                if MinNumCoins[m-coins[i]]+1 < MinNumCoins[m]:
                    MinNumCoins[m] = MinNumCoins[m-coins[i]] + 1
        
    print MinNumCoins[money]


coins = [32,51,31,5,3,1]
money = 18760
DPChange(money, coins)