#include "benchmark.cpp"
#define ERR_DROP 127

struct PuzzTable
{
    F_T table[ROW][COL]; // 盤面
    int x;               // 開始位置 x
    int y;               // 開始位置 y
    int turn;            // 残りターン数

    PuzzTable()
    {
    }

    PuzzTable(int turn) : turn(turn)
    {
        init(table);
        set(table, 0);
        x = rnd(0, COL - 1);
        y = rnd(0, ROW - 1);
    }

    PuzzTable(string str, int x, int y, int turn) : x(x), y(y), turn(turn)
    {
        int j, k;
        for (j = 0; j < ROW; j++)
        {
            for (k = 0; k < COL; k++)
            {
                table[j][k] = (str[k + (COL * j)] - '0') + 1;
            }
        }
    }

    int get_turn()
    {
        return turn;
    }

    std::array<PuzzTable, DIR> next_tables()
    {
        auto tables = std::array<PuzzTable, DIR>();
        int i;
        int dx[DIR] = {-1, 0, 0, 1};
        int dy[DIR] = {0, -1, 1, 0};

        for (i = 0; i < DIR; i++)
        {
            memcpy(tables[i].table, table, sizeof(table));
            tables[i].x = x;
            tables[i].y = y;
            tables[i].turn = turn - 1;

            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || ny < 0 || nx >= COL || ny >= ROW)
            {
                tables[i].table[0][0] = ERR_DROP;
            }
            else
            {
                tables[i].x = nx;
                tables[i].y = ny;

                F_T c = tables[i].table[y][x];
                tables[i].table[y][x] = tables[i].table[ny][nx];
                tables[i].table[ny][nx] = c;
            }
        }
        return tables;
    }

    int eval_otoshi()
    {
        if (table[0][0] == ERR_DROP)
            return -1;
        F_T field[ROW][COL];
        memcpy(field, table, sizeof(table));
        return sum_e(field);
    }

    int eval_ochi()
    {
        if (table[0][0] == ERR_DROP)
            return -1;
        F_T field[ROW][COL];
        memcpy(field, table, sizeof(table));
        return sum_evaluate(field);
    }

    std::array<std::array<int8_t, COL>, ROW> get_table()
    {
        auto field = std::array<std::array<int8_t, COL>, ROW>();
        int j, k;
        for (j = 0; j < ROW; j++)
        {
            for (k = 0; k < COL; k++)
            {
                field[j][k] = table[j][k];
            }
        }
        return field;
    }

    std::array<std::array<int8_t, COL>, ROW> get_XY_as_table()
    {
        auto field = std::array<std::array<int8_t, COL>, ROW>();
        field[y][x] = 1;
        return field;
    }

    void show_table()
    {
        show_field(table);
    }
};

int main()
{
    PuzzTable test = PuzzTable(0);
    test.show_table();
    cout << test.x << test.y << test.turn << "\n";

    test = PuzzTable("000000000000000000022000111200", 2, 4, 0);
    test.show_table();
    cout << test.eval_otoshi() << "\n";
    cout << test.eval_ochi() << "\n";

    for (const auto &record : test.get_XY_as_table())
    {
        for (const auto &record2 : record)
        {
            cout << (char)(record2 + '0');
        }
        cout << '\n';
    }

    for (auto &record : test.next_tables())
    {
        record.show_table();
        cout << record.x << record.y << record.eval_otoshi() << '\n';
    }

    return 0;
}
