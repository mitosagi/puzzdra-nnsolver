from puzzpy import PuzzTable
table = PuzzTable(10)
table.show_table()
for a in table.next_tables():
    print(a.get_table())
    print(a.get_XY_as_table())

print(table.get_turn())
table.set_turn(55)
print(table.get_turn())

table = PuzzTable(10)
table.show_table()
str1 = table.get_table()[0]
print(type(str1[0]))

# 定数
TABLEX = 6
TABLEY = 5
COLORS = 3
import random
# table = PuzzTable("".join([str(random.randrange(COLORS)) for i in range(TABLEX*TABLEY)]), 0, 0, 0) # n色陣　操作時間m秒
table = PuzzTable("".join(["0" for i in range(TABLEX*TABLEY)]), 0, 0, 0) # n色陣　操作時間m秒
table.show_table()
print(table.eval_zenkeshi())
