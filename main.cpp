#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
/* Авторы: Мальцева П., Чапурина А.
Группа: 8307
Формализация задания: 6 вариант - ((A|B)&~C)|D */

using namespace std;

const int count = 4;
const int maxSize = 32; //Мощность универсума

struct Set
{
    char c = '\0';
    Set *next = NULL;
};

bool checkSet(const char *set, int size, char c)
{
    for (int i = 0; i < size; i++)
    {
        if (set[i] == c)
            return true;
    }
    return false;
}

bool checkSet2(Set *set, char c)
{
    for (Set *q = set; q; q = q->next)
    {
        if (q->c == c)
            return true;
    }
    return false;
}

void add2(Set *set, char c)
{
    if (checkSet2(set, c))
        return;
    for (Set *m = set; m; m = m->next)
    {
        if (m->c == '\0')
        {
            m->c = c;
        }
        else if (m->next == nullptr)
        {
            Set *current = new Set;
            current->c = c;
            m->next = current;
            break;
        }
    }
}

char **randomSet(int sizeCount)
{
    char **set_s = new char *[count];
    for (int i = 0; i < count; i++)
    {
        set_s[i] = new char[sizeCount];
        for (int j = 0; j < sizeCount; j++)
        {
            char c;
            do
            {
                c = 'А' + (rand() % maxSize);
            }
            while (checkSet(set_s[i], sizeCount, c));
            set_s[i][j] = c;
        }
    }
    return set_s;
}

void outputSet(char **set_s, int size)
{
    cout << "Число элементов во множествах: " << size << endl;
    char set = 'A';
    for (int i = 0; i < count; i++)
    {
        cout << "Множество " << set << ": {";
        for (int j = 0; j < size; ++j)
        {
            cout << set_s[i][j];
        }
        cout << "}" << endl;
        set++;
    }
}

void printList(Set *set)
{
    for (Set *m = set; m; m = m->next)
    {
        cout << m->c;
    }
}

Set *transform2(char **set_s, int size)
{
    Set *listset_s = new Set[count];
    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            add2(&listset_s[i], set_s[i][j]);
        }
    }
    return listset_s;
}

bool **transform3(char *universum, char **set_s, int size)
{
    bool **binaryset_s = new bool *[count];
    for (int i = 0; i < count; i++)
    {
        binaryset_s[i] = new bool[maxSize];
        for (int j = 0; j < maxSize; ++j)
        {
            binaryset_s[i][j] = false;
        }
    }
    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int k;
            for (k = 0; set_s[i][j] != universum[k]; ++k) {}
            binaryset_s[i][k] = true;
        }
    }
    return binaryset_s;
}

long *transform4(char *universum, char **set_s, int size)
{
    long *machineset_s = new long[count];
    for (int i = 0; i < count; i++)
    {
        machineset_s[i] = 0;
    }
    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int k;
            for (k = 0; set_s[i][j] != universum[k]; ++k) {}
            machineset_s[i] ^= (1 << k);
        }
    }
    return machineset_s;
}

double getTime1(char **set_s, int size, bool writeAnswer)
{
    auto start = clock();
    int k = 0;
    char *answer = new char[count * size];
    for (int i = 0; i < size; i++)
    {
        if (!checkSet(set_s[2], size, set_s[0][i]))
        {
            if (!checkSet(answer, k, set_s[0][i]))
            {
                answer[k] = set_s[0][i];
                k++;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (!checkSet(set_s[2], size, set_s[1][i]))
        {
            if (!checkSet(answer, k, set_s[1][i]))
            {
                answer[k] = set_s[1][i];
                k++;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (!checkSet(answer, k, set_s[3][i]))
        {
            answer[k]= set_s[3][i];
            k++;
        }
    }
    if (writeAnswer)
    {
        cout << "Искомое множество через массив: {";
        for (int i = 0; i < k; i++)
        {
            cout << answer[i];
        }
        cout << "}" << endl;
    }
    auto stop = clock();
    return (stop - start) / (double) CLOCKS_PER_SEC;
}

double getTime2(Set *set_s, bool writeAnswer)
{
    auto start = clock();
    Set answer;
    for (Set *m = &set_s[0]; m; m = m->next)
    {
        if (!checkSet2(&set_s[2], m->c))
        {
            if (!checkSet2(&answer, m->c))
            {
                add2(&answer, m->c);
            }
        }
    }

    for (Set *m = &set_s[1]; m; m = m->next)
    {
        if (!checkSet2(&set_s[2], m->c))
        {
            if (!checkSet2(&answer, m->c))
            {
                add2(&answer, m->c);
            }
        }
    }

    for (Set *m = &set_s[3]; m; m = m->next)
    {
        if (!checkSet2(&answer, m->c))
        {
            add2(&answer, m->c);
        }
    }
    if (writeAnswer)
    {
        cout << "Искомое множество через список: {";
        printList(&answer);
        cout << "}" << endl;
    }
    auto stop = clock();
    return (stop - start) / (double) CLOCKS_PER_SEC;
}

double getTime3(char *universum, bool **set_s, bool writeAnswer)
{
    auto start = clock();
    bool answer[maxSize];
    for (int i = 0; i < maxSize; i++)
    {
        answer[i] = false;
        answer[i] |= (set_s[0][i] |set_s[1][i]) & (!set_s[2][i]);
    }
    for (int i = 0; i < maxSize; i++)
    {
        answer[i] |= set_s[3][i];
    }

    if (writeAnswer)
    {
        cout << "Искомое множество через массив битов: {";
        for (int i = 0; i < maxSize; i++)
        {
            if (answer[i])
            {
                cout << universum[i];
            }
        }
        cout << "}" << endl;
    }
    auto stop = clock();
    return (stop - start) / (double) CLOCKS_PER_SEC;
}

double getTime4(char *universum, long *set_s, bool writeAnswer)
{
    auto start = clock();
    long answer = 0;
    answer |= (set_s[0] | set_s[1]) &~(set_s[2]);
    answer |= set_s[3];

    if (writeAnswer)
    {
        cout << "Искомое множество через машинные слова: {";
        for (int i = 0; i < maxSize; i++)
        {
            if ((answer >> i & 1))
            {
                cout << universum[i];
            }
        }
        cout << "}" << endl;
    }
    auto stop = clock();
    return (stop - start) / (double) CLOCKS_PER_SEC;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL,"Russian");
    const int number = 10;
    int setSize[] = {3,5};
    char universum[maxSize];
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    for (int i = 0, j = 'А'; j <= 'Я'; ++i, ++j)
    {
        universum[i] = j;
    }

    for (auto i : setSize)
    {
        double time1 = 0;
        double time2 = 0;
        double time3 = 0;
        double time4 = 0;
        char **set_s = randomSet(i);
        Set *listset_s = transform2(set_s, i);
        bool **binaryset_s = transform3(universum, set_s, i);
        long *machineset_s = transform4(universum, set_s, i);

        outputSet(set_s, i);

        for (int j = 0; j < number; j++)
        {
            time1 += getTime1(set_s, i, j == 0);
            time2 += getTime2(listset_s, j == 0);
            time3 += getTime3(universum, binaryset_s, j == 0);
            time4 += getTime4(universum, machineset_s, j == 0);
        }
        time1 /= number;
        time2 /= number;
        time3 /= number;
        time4 /= number;
        cout << "---------------------------------------" << endl;
        cout << "Время обработки массива: " << time1 << " c" << endl;
        cout << "Время обработки списка: " << time2 << " c" << endl;
        cout << "Время обработки массива битов: " << time3 << " c" << endl;
        cout << "Время обработки машинного слова: " << time4 << " c" << endl << endl;
    }

    system("pause");
    return 0;
}
