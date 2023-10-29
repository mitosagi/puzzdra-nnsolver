#include "benchmark.cpp"
#define ERR_DROP 127

int evaluate_zenkeshi(F_T field[ROW][COL], int flag) {
	int combo = 0;
    int zenkeshi = 0;

	while (1) {
		int cmb = 0;
		F_T chkflag[ROW][COL]={0};
		F_T delflag[ROW][COL]={0};
		F_T GetHeight[COL];
		for (int row = 0; row < ROW; row++) {
			for (int col = 0; col < COL; col++) {
				F_T num=field[row][col];
				if(row==0){
				GetHeight[col]=(F_T)ROW;
				}
				if(num>0 && GetHeight[col]==(F_T)ROW){
				GetHeight[col]=(F_T)row;
				}
				if (col <= COL - 3 && num == field[row][col + 1] && num == field[row][col + 2] && num > 0) {
					delflag[row][col]=1;
					delflag[row][col+1]=1;
					delflag[row][col+2]=1;
				}
				if (row <= ROW - 3 && num == field[row + 1][col] && num == field[row + 2][col] && num > 0) {
					delflag[row][col]=1;
					delflag[row+1][col]=1;
					delflag[row+2][col]=1;
				}
			}
		}
		for (int row = 0; row < ROW; row++) {
			for (int col = 0; col < COL; col++) {
				if (delflag[row][col] > 0) {
					if (chain(row, col, field[row][col], field, chkflag, delflag) >= 3) {
						cmb++;
					}
				}
			}
		}
		combo += cmb;
		//コンボが発生しなかったら終了
		if (cmb == 0 || 0 == (flag & EVAL_COMBO)) { break; }
		for (int row = 0; row < ROW; row++) {
			for (int col = 0; col < COL; col++) {
				//コンボになったドロップは空になる
				if (delflag[row][col]> 0) { field[row][col] = 0; }
			}
		}

		if (flag & EVAL_FALL){
		for(int x=0;x<COL;x++){
		fall(x,GetHeight[x],field);
		}
		}//落下処理発生
		if (flag & EVAL_SET){set(field, 0);}//落ちコン発生

	}
	//return combo;
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (field[row][col] > 0) {
                zenkeshi -= 1;
            }
        }
    }

    return zenkeshi;
}

int sum_e_zenkeshi(F_T field[ROW][COL]) {//落とし有り、落ちコン無しコンボ数判定関数
	return evaluate_zenkeshi(field, EVAL_FALL | EVAL_COMBO);
}

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

    void set_turn(int new_turn)
    {
        turn = new_turn;
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

    int eval_zenkeshi()
    {
        // if (table[0][0] == ERR_DROP)
        //     return -1;
        F_T field[ROW][COL];
        memcpy(field, table, sizeof(table));
        return sum_e_zenkeshi(field);
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
