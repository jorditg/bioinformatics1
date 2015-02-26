#!/usr/bin/python

import sys

def main():
    l = [2,2,3,3,4,5,6,7,8,10]
    PartialDigest(l)

def DeleteMax(l):
    m = max(l)
    l.remove(m)
    return l,m

def PartialDigest(l):
    l, width  = DeleteMax(l)
    x = [0, width]
    Place(l, x, width)

def deltas(s):
    r = []
    for i in s:
        for j in s:
            if i != j:
                r.append(abs(i-j))
    return r

def set_included(s, subs):
    inc = 1
    for i in subs:
        present = 0
        for j in s:
            if i == j:
                present = 1
        if present == 0:
            inc = 0
            break
    return inc

def remove_set(parent, remset):
    for i in remset:
        parent.remove(i)
    return parent

def Place(l, x, width):
    if l == []:
        print x
        sys.exit(0)
    l,y = DeleteMax(l)
    xUy = x
    xUy.append(y)
    difxUy = deltas(xUy)
    if set_included(l,xUy):
        x = xUy
        lmdeltasxUy = remove_set(l,difxUy)
        x=Place(lmdeltasxUy, width)
        x.remove(y)
    wyUx = x 
    wyUx.append(width - y)
    if set_included(l, wyUx):
        x.append(width - y)
        lmdeltaswyUx = remove_set(l,wyUx)
        x = Place(lmdeltaswyUx, width)
        x.remove(width - y)

    return x

          

if __name__ == "__main__":

    main()
