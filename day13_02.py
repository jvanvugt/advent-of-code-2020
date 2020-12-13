puzzle = open("inputs/day13.txt").read().splitlines()[1]
ids_and_offsets = [(int(s), i) for i, s in enumerate(puzzle.split(",")) if s != "x"]

def mod_divide(a, b, m):
    return pow(b, -1, m) * a % m

cycle_length, cycle_offset = ids_and_offsets[0]
for num, offset in ids_and_offsets[1:]:
    i = mod_divide((offset - cycle_offset) % num, cycle_length, num)
    cycle_offset = cycle_offset + cycle_length * i
    cycle_length *= num
print(cycle_length - cycle_offset)