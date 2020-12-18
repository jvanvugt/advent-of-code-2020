class MyNumA:
    def __init__(self, x): self.x = x
    def __add__(self, o): return MyNumA(self.x + o.x)
    def __sub__(self, o): return MyNumA(self.x * o.x)

    @staticmethod
    def repl(line):
        return line.replace("*", "-")

class MyNumB:
    def __init__(self, x): self.x = x
    def __mul__(self, o): return MyNumB(self.x + o.x)
    def __sub__(self, o): return MyNumB(self.x * o.x)

    @staticmethod
    def repl(line):
        return line.replace("*", "-").replace("+", "*")

def compute(line, num_class):
    line = num_class.repl(line)
    to_eval = []
    i = 0
    while i < len(line):
        if line[i].isdigit():
            end = i + 1
            while end < len(line) and line[end].isdigit():
                end += 1
            to_eval.append(f"{num_class.__name__}({line[i:end]})")
            i = end
        else:
            to_eval.append(line[i])
            i += 1
    return eval("".join(to_eval)).x

lines = open("inputs/day18.txt").read().splitlines()
print(sum(map(lambda l: compute(l, MyNumA), lines)))
print(sum(map(lambda l: compute(l, MyNumB), lines)))
