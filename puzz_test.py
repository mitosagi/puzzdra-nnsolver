from puzzpy import PuzzTable
table = PuzzTable(10)
table.show_table()
for a in table.next_tables():
    print(a.get_table())
    print(a.get_XY_as_table())

print(table.get_turn())

table = PuzzTable(10)
table.show_table()
str1 = table.get_table()[0]
print(type(str1[0]))