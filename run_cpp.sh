set -e

DAY=`printf %02d $1`

g++ day${DAY}.cpp --std=c++20 -Wall -Wextra -I /home/joris/advent-of-code-2020/vcpkg/packages/range-v3_x64-linux/include && ./a.out
rm a.out
