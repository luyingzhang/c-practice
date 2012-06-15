/*
 * pthread6.c
 *
 *  Created on: 2012/6/11
 *      Author: http://sp1.wikidot.com/pthread
 */

#include <pthread.h>     // 引用 pthread 函式庫
#include <stdio.h>

void *print_george(void *argu) {    // 每隔一秒鐘印出一次 George 的函數
  while (1) {
    printf("George\n");
    sleep(1);
  }
  return NULL;
}

void *print_mary(void *argu) {     // 每隔一秒鐘印出一次 Mary 的函數
  while (1) {
    printf("Mary\n");
    sleep(2);
  }
  return NULL;
}

int main() {     // 主程式開始
  pthread_t thread1, thread2;     // 宣告兩個執行緒
  pthread_create(&thread1, NULL, &print_george, NULL); // (thread 變數, thread 特性, 描述 thread 行為的函數, 這個函數所需的參數)
  pthread_create(&thread2, NULL, &print_mary, NULL);   // (thread 變數, thread 特性, 描述 thread 行為的函數, 這個函數所需的參數)
  while (1) {     // 主程式每隔一秒鐘，印出分隔行
    printf("----------------\n");
    sleep(1);     // 停止一秒鐘
  }
  return 0;
}
