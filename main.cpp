#include <iostream>

using namespace std;

class field
{
    int bomb[9][9]; // если открыто, число бомб вокруг. Если нет, то -1 -- бомба есть, -2 -- нет
    int flag[9][9]; // поле для компьютера -- помечены единицей те поля, где он точно нашёл бомбу
    double p[9][9]; // поле для компьютера
public:
    field()
    {
        // заполнение массива bomb: используя функцию rand() инициализируем 10 элементов -1, а оставшиеся -- -2
        for(int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                flag[i][j] = 0;
                p[i][j] = 10;  // так как в процессе нам нужно будет искать наименьшие из установленных значений р, и все установленные значения не больше 1, то для неустановленных значений можно пока установить любое число, большее 1
            }
    }
    int getbomb(int x, int y)
    {
        if (bomb[x][y] == -1)
            return -1;
        else if (bomb[x][y] == -2)
            return 0;
        else
            return 1;
    }
    void setnum(int x, int y) // считаем число, которое нужно записать в только что открытую клетку без бомбы
    {
        int begx = (x == 0 ? 0 : x - 1);
        int endx = (x == 8 ? 8 : x + 1);
        int begy = (y == 0 ? 0 : y - 1);
        int endy = (y == 8 ? 8 : y + 1);
        int count = 0;
        for (int i = begx; i <= endx; i++)
            for (int j = begy; j <= endy; j++)
                if (bomb[i][j] == -1)
                    count++;
        bomb[x][y] = count;
    }
    int sum(int x, int y) // сумма чисел на открытых клетках вокруг нераскрытой
    {
        if (bomb[x][y] >= 0)
            return -1;
        int begx = (x == 0 ? 0 : x - 1);
        int endx = (x == 8 ? 8 : x + 1);
        int begy = (y == 0 ? 0 : y - 1);
        int endy = (y == 8 ? 8 : y + 1);
        int count = 0;
        for (int i = begx; i <= endx; i++)
            for (int j = begy; j <= endy; j++)
                if (bomb[i][j] >= 0)
                    count += bomb[i][j];
        return count;
    }
    int notopennum(int x, int y) // количество неоткрытых клеток вокруг раскрытой
    {
        if (bomb[x][y] < 0)
            return -1;
        int begx = (x == 0 ? 0 : x - 1);
        int endx = (x == 8 ? 8 : x + 1);
        int begy = (y == 0 ? 0 : y - 1);
        int endy = (y == 8 ? 8 : y + 1);
        int count = 0;
        for (int i = begx; i <= endx; i++)
            for (int j = begy; j <= endy; j++)
                if (bomb[i][j] < 0)
                    count++;
        return count;
    }
    int flagnum(int x, int y) // количество найденных бомб вокруг клетки
    {
        if (bomb[x][y] < 0)
            return -1;
        int begx = (x == 0 ? 0 : x - 1);
        int endx = (x == 8 ? 8 : x + 1);
        int begy = (y == 0 ? 0 : y - 1);
        int endy = (y == 8 ? 8 : y + 1);
        int count = 0;
        for (int i = begx; i <= endx; i++)
            for (int j = begy; j <= endy; j++)
                if (flag[i][j] == 1)
                    count++;
        return count;
    }
    void setp (int x, int y)
    {
        if (bomb[x][y] < 0)
            p[x][y] =  -1;
        else if (this->notopennum(x, y))
            p[x][y] = ((double)(bomb[x][y] - this->flagnum(x, y))) / (this->notopennum(x, y) - this->flagnum(x, y));
        else
            p[x][y] = 10;
    }
    double getp (int x, int y)
    {
        return p[x][y];
    }
    void setflag (int x, int y)
    {
        flag[x][y] = 1;
    }
};

/*class compplayer
{
    int flag[9][9];
public:
    compplayer()
    {
        for(int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                flag[i][j] = 0;
    }

};*/

int main()
{
    field f;
    int x1 = -1, y1 = -1, x2 = -1, y2 = -1, res1 = 0, res2 = 0;
    while() // пусть игрок ходит первым, а компьютер вторым
    {
        cin >> x1 >> y1; // считаем, что игрок вводит корректные данные
        if (f.getbomb(x1, y1) < 0)
        {
            res1 -= 5;
            break;
        }
        else if (f.getbomb(x1, y1) == 0)
        {
            f.setnum(x1, y1);
        }
        if (x1 >= 0 && y1 >= 0)
        {
            int begx = (x1 == 0 ? 0 : x1 - 1);
            int endx = (x1 == 8 ? 8 : x1 + 1);
            int begy = (y1 == 0 ? 0 : y1 - 1);
            int endy = (y1 == 8 ? 8 : y1 + 1);
            int count = 0;
            for (int i = begx; i <= endx; i++)
                for (int j = begy; j <= endy; j++)
                    if (f.getbomb(x1, y1) > 0)
                        f.setp(x1, y1);
        }
        if (x2 >= 0 && y2 >= 0)
        {
            int begx = (x2 == 0 ? 0 : x2 - 1);
            int endx = (x2 == 8 ? 8 : x2 + 1);
            int begy = (y2 == 0 ? 0 : y2 - 1);
            int endy = (y2 == 8 ? 8 : y2 + 1);
            int count = 0;
            for (int i = begx; i <= endx; i++)
                for (int j = begy; j <= endy; j++)
                    if (f.getbomb(x2, y2) > 0)
                        f.setp(x1, y1);
        }
        // далее проходим по массиву р и ищем наименьшее значения. Далее для всех нераскрытых соседей элементов с наименьшим р считаем f.sum. И открываем элемент с наибольшим значением f.sum
    }
    cout << "Hello World!" << endl;
    return 0;
}
