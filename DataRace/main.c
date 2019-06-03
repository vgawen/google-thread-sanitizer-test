#include <stdio.h>
#include <pthread.h>

void threadAFunc(void *arg);
void threadBFunc(void *arg);

int g_a;

struct STRUCT_TEST {int a; int b;} g_test;

unsigned char a[12];

union UNION_TEST{int a; char b;} g_unionTest;

struct STRUCT_TEST2{ int a;struct STRUCT_TEST2 *next;}  g_structTest;


int main(int argc, char *argv[])
{
    pthread_attr_t attr;

    pthread_t threadA;
    pthread_t threadB;

    //1\7\8
    pthread_create(&threadA, NULL, (void *)threadAFunc, &g_a);

    pthread_create(&threadB, NULL, (void *)threadBFunc, &g_a);

    //2
//    pthread_create(&threadA, NULL, (void *)threadAFunc, &g_test);
//    pthread_create(&threadB, NULL, (void *)threadBFunc, &g_test);

    //3
//    pthread_create(&threadA, NULL, (void *)threadAFunc, a);
//    pthread_create(&threadB, NULL, (void *)threadBFunc, a);

    //5
//    pthread_create(&threadA, NULL, (void *)threadAFunc, &g_unionTest);
//    pthread_create(&threadB, NULL, (void *)threadBFunc, &g_unionTest);

    //6
//    pthread_create(&threadA, NULL, (void *)threadAFunc, &g_structTest);
//    pthread_create(&threadB, NULL, (void *)threadBFunc, &g_structTest);
    pthread_join(threadA, NULL);

    pthread_join(threadB, NULL);

    printf("Hello World!\n");
    return 0;
}

//实验结果：
//2、3、4、6不会报Data Race Warning，1、5、7、8 报Data Race Warning
//Data Race Warning 是基于对相同地址的访问
//两个线程只要对同一个地址有读写操作，且都执行到，就会报data race warning。跟执行时间没有关系。

//1
//报data racing warning

//void threadAFunc(void *arg)
//{
////    int *local = (int *)arg;
//    int b;
//    //while (1)
//    {
//        g_a=8;
//        printf("threadA read %d\n", g_a);
//        //usleep(100);
//    }
//}

//void threadBFunc(void *arg)
//{
////    int *local = (int *)arg;
//    usleep(1000000);
//    int b;
//    while (1)
//    {
//        //g_a = 8;
//        printf("threadB write %d\n", g_a);
//        usleep(100);
//    }

//}


//2
//不报data racing warning

//void threadAFunc(void *arg)
//{
//    struct STRUCT_TEST *test = (struct STRUCT_TEST *)arg;
//    while (1)
//    {
//        test->a = 8;
//        printf("threadA write %d\n", test->a);
//        usleep(100);
//    }
//}

//void threadBFunc(void *arg)
//{
//    struct STRUCT_TEST *test = (struct STRUCT_TEST *)arg;
//    while (1)
//    {
//        printf("threadB read %d\n", test->b);
//        usleep(100);
//    }
//}


//3、4
//不报data racing warning

//void threadAFunc(void *arg)
//{
//    unsigned char *test = (unsigned char *)arg;
//    while (1)
//    {
//        test[0] = 8;
//        printf("threadA write %d\n", test[0]);
//        usleep(100);
//    }
//}

//void threadBFunc(void *arg)
//{
//    unsigned char *test = (unsigned char *)arg;
//    while (1)
//    {
//        printf("threadB read %d\n", test[1]);
//        usleep(100);
//    }
//}



//5
//报data racing warning

//void threadAFunc(void *arg)
//{
//    union UNION_TEST *test = (union UNION_TEST *)arg;
//    while (1)
//    {
//        test->a = 8;
//        printf("threadA write %d\n", test->a);
//        usleep(100);
//    }
//}

//void threadBFunc(void *arg)
//{
//    union UNION_TEST *test = (union UNION_TEST *)arg;
//    while (1)
//    {
//        printf("threadB read %d\n", test->b);
//        usleep(100);
//    }
//}



//6
//不报data racing warning

//void threadAFunc(void *arg)
//{
//    struct STRUCT_TEST2 *test = (struct STRUCT_TEST2 *)arg;
//    while (1)
//    {
//        if (test->next)
//            free(test->next);
//        test->next = (struct STRUCT_TEST2 *) malloc(sizeof(struct STRUCT_TEST2));
//        printf("threadA write %p\n", test->next);
//        usleep(100);
//    }
//}

//void threadBFunc(void *arg)
//{
//    struct STRUCT_TEST2 *test = (struct STRUCT_TEST2 *)arg;
//    while (1)
//    {
//        printf("threadB read %d\n", test->a);
//        usleep(100);
//    }
//}


//7
//报data racing warning

//void threadAFunc(void *arg)
//{
//    int *local = (int *)arg;
//    while (1)
//    {
//        *local = 7;
//        //printf("threadA read %d\n", *local);
//        usleep(100);
//    }
//}

//void threadBFunc(void *arg)
//{
//    int *local = (int *)arg;
//    while (1)
//    {
//        *local = 8;
//        //printf("threadB write\n");
//        usleep(100);
//    }

//}



//8
//报data racing warning

void threadAFunc(void *arg)
{
    //int *local = (int *)arg;
    while (1)
    {
        //(*local)++;
        g_a++;
        //printf("threadA read %d\n", g_a);
        usleep(100);
    }
}

void threadBFunc(void *arg)
{
    //int *local = (int *)arg;
    while (1)
    {
        g_a--;
        //(*local)--;
        printf("threadB write\n");
        usleep(100);
    }

}
