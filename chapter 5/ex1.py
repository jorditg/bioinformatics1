# -*- coding: utf-8 -*-
"""
Spyder Editor

This temporary script file is located here:
/home/jordi/.spyder2/.temp.py
"""

m=[0,1,2,3,4,1,1,2,3,4,2,2,2]
for i in [13,14,15,16,17,18,19,20,21,22]:
    a=min(m[i-6]+1,m[i-5]+1,m[i-1]+1)
    m.append(a)
print m