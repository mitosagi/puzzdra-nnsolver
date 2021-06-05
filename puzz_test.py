from puzzpy import PuzzTable
table = PuzzTable(10)
table.show_table()
for a in table.next_tables():
    a.show_table()
    print(a.get_XY_as_table())
