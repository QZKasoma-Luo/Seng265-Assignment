#!/usr/bin/env python3

import random

print(__doc__)

class GenRandom(object):
    '''Here is GenRandom class'''
    def __init__(self, lower_bound:int, high_bound:int) -> None:
        self.lower_bound = lower_bound
        self.higher_bound = high_bound
        self.int_number:int = random.randint(self.lower_bound, self.higher_bound)
        self.float_number:float = random.uniform(self.lower_bound, self.higher_bound)
    



class ArtConfig:
    '''Here is ArtConfig class'''
    def __init__(self, CNT:int, length:int, height:int) -> None:
        self.CNT:int = CNT
        self.SHA:int = GenRandom(0,2).int_number
        self.X:int = GenRandom(0,length).int_number
        self.Y:int = GenRandom(0, height).int_number
        self.RAD:int = GenRandom(0, 100).int_number
        self.RX:int = GenRandom(10, 30).int_number
        self.RY:int = GenRandom(10, 30).int_number
        self.W:int = GenRandom(10, 100).int_number
        self.H:int = GenRandom(10, 100).int_number
        self.R:int = GenRandom(0, 255).int_number
        self.G:int = GenRandom(0, 255).int_number
        self.B:int = GenRandom(0, 255).int_number
        self.op:float = GenRandom(0, 1).float_number

    def print_label(self):
        '''print the output'''
        print("%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d %3.1f" %(self.CNT, self.SHA, self.X, self.Y, self.RAD, self.RX, self.RY, self.W, self.H, self.G, self.R, self.B, self.op))


def main():
    print("%3s %3s %3s %3s %3s %3s %3s %3s %3s %3s %3s %3s %3s" %("CNT", "SHA", "X", "Y", "RAD", "RX", "RY", "W", "H", "G", "R", "B", "OP"))
    for row in range(10):
        ArtConfig(row, 400, 100).print_label()

if __name__ == '__main__':
    main()